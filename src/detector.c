#include "network.h"
#include "region_layer.h"
#include "cost_layer.h"
#include "utils.h"
#include "parser.h"
#include "box.h"
#include "option_list.h"

// >>>>>>>>>>>>> extern functions from c++ >>>>>>>>>>>>>>>
//image load_image_cv(char *filename);    //load a picture
image load_stream_cv();                 //load from a camera
void display_image_cv(image display);   //display frame
void setup_cam();
void label_func(int tl_x, int tl_y, int br_x, int br_y, char *names);  //bounding box labelling for c++
// <<<<<<<<<<<<<< extern functions from c++ <<<<<<<<<<<<<<


// ************* setup values *************
float thresh = 0.35;     //detection threshold
float hier_thresh = 0.5;

char *filename;

list *options;
char *name_list;
char **names;
image **alphabet;
network net;
char buff[256];
char *input;
float nms;
clock_t time_t1;


// ************* support functions *************
void draw_bounding_box(int im_w, int im_h, int num, float thresh, box *boxes, float **probs, char **names, int classes)  //draw rectangle boundaries
{
    int i;

    for(i = 0; i < num; ++i){
        int class = max_index(probs[i], classes);
        float prob = probs[i][class];
        if(prob > thresh){

            box b = boxes[i];

            int temp_tl_x = (b.x-b.w/2.)*im_w;
            int temp_tl_y = (b.y-b.h/2.)*im_h;

            int temp_br_x = (b.x+b.w/2.)*im_w;
            int temp_br_y = (b.y+b.h/2.)*im_h;

            label_func(temp_tl_x, temp_tl_y, temp_br_x, temp_br_y, names[class]);     //pass it to c++ function for labelling

        }

    }
}

// ************* setup values (FOR EVALUATION ONLY!) *************

void setup_proceedure(char *datacfg, char *cfg, char *weights, float thresh_desired){
    
 //setup proceedure
 options = read_data_cfg(datacfg);

 name_list = option_find_str(options, "names", "data/names.list");
 names = get_labels(name_list);
 alphabet = load_alphabet();

 //load network based on cfg
 net = parse_network_cfg(cfg);
 load_weights(&net, weights);
 set_batch_network(&net, 1);

 input= buff;
 nms=.4;    //non max supression
 thresh = thresh_desired;
 srand(2222222);
}

void camera_detector()  // run this through a loop
{    
   image im = load_stream_cv();  //capture a frame from camera

   image sized = resize_image(im, net.w, net.h);
   layer l = net.layers[net.n-1];
        
   int j;
   box *boxes = calloc(l.w*l.h*l.n, sizeof(box));
   float **probs = calloc(l.w*l.h*l.n, sizeof(float *));
   for(j = 0; j < l.w*l.h*l.n; ++j) probs[j] = calloc(l.classes + 1, sizeof(float *));

   float *X = sized.data;
   time_t1=clock();
   network_predict(net, X);
   printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time_t1));

   get_region_boxes(l, 1, 1, thresh, probs, boxes, 0, 0, hier_thresh);

   if (l.softmax_tree && nms) 
       do_nms_obj(boxes, probs, l.w*l.h*l.n, l.classes, nms);
   else if (nms) 
       do_nms_sort(boxes, probs, l.w*l.h*l.n, l.classes, nms);

   //draw_detections(im, l.w*l.h*l.n, thresh, boxes, probs, names, alphabet, l.classes);

   //display_image_cv(im);    //display image in c++

   draw_bounding_box(im.w, im.h, l.w*l.h*l.n, thresh, boxes, probs, names, l.classes);

   free_image(im); 
   free_image(sized);

   free(boxes);
   free_ptrs((void **)probs, l.w*l.h*l.n);
}


/*

Training functions

*/

// Params
int *gpus = 0;
int gpu = 0;
int ngpus = 1;
int clear = 0;

char* train_datacfg; 
char* train_archcfg;    
char* train_weights;

// setup initializations
void setup_detector_training(char *datacfg, char *cfg, char *weights){

    gpu_index = 0;   //only using 1 gpu to train

#ifndef GPU
    gpu_index = -1;
#else
    cuda_set_device(gpu_index);
#endif

    gpu = gpu_index;
    gpus = &gpu;

    train_datacfg = datacfg;
    train_archcfg = cfg;
    train_weights = weights;
}


void execute_detector_training()
{
    list *options = read_data_cfg(train_datacfg);
    char *train_images = option_find_str(options, "train", "data/train.list");
    char *backup_directory = option_find_str(options, "backup", "/backup/");

    srand(time(0));
    char *base = basecfg(train_archcfg);
    printf("%s\n", base);
    float avg_loss = -1;
    network *nets = calloc(ngpus, sizeof(network));

    srand(time(0));
    int seed = rand();
    int i;
    for(i = 0; i < ngpus; ++i){
        srand(seed);
#ifdef GPU
        cuda_set_device(gpus[i]);
#endif
        nets[i] = parse_network_cfg(train_archcfg);
        if(train_weights){
            load_weights(&nets[i], train_weights);
        }
        if(clear) *nets[i].seen = 0;
        nets[i].learning_rate *= ngpus;
    }
    srand(time(0));
    network net = nets[0];

    int imgs = net.batch * net.subdivisions * ngpus;
    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net.learning_rate, net.momentum, net.decay);
    data train, buffer;

    layer l = net.layers[net.n - 1];

    int classes = l.classes;
    float jitter = l.jitter;

    list *plist = get_paths(train_images);

    char **paths = (char **)list_to_array(plist);

    load_args args = {0};
    args.w = net.w;
    args.h = net.h;
    args.paths = paths;
    args.n = imgs;
    args.m = plist->size;
    args.classes = classes;
    args.jitter = jitter;
    args.num_boxes = l.max_boxes;
    args.d = &buffer;
    args.type = DETECTION_DATA;
    args.threads = 8;

    args.angle = net.angle;
    args.exposure = net.exposure;
    args.saturation = net.saturation;
    args.hue = net.hue;

    pthread_t load_thread = load_data(args);
    clock_t time;
    int count = 0;

    while(get_current_batch(net) < net.max_batches){
        if(l.random && count++%10 == 0){
            printf("Resizing\n");
            int dim = (rand() % 10 + 10) * 32;
            if (get_current_batch(net)+200 > net.max_batches) dim = 608;
            printf("%d\n", dim);
            args.w = dim;
            args.h = dim;

            pthread_join(load_thread, 0);
            train = buffer;
            free_data(train);
            load_thread = load_data(args);

            for(i = 0; i < ngpus; ++i){
                resize_network(nets + i, dim, dim);
            }
            net = nets[0];
        }
        time=clock();
        pthread_join(load_thread, 0);
        train = buffer;
        load_thread = load_data(args);

        printf("Loaded: %lf seconds\n", sec(clock()-time));

        time=clock();
        float loss = 0;
#ifdef GPU
        if(ngpus == 1){
            loss = train_network(net, train);
        } else {
            loss = train_networks(nets, ngpus, train, 4);
        }
#else
        loss = train_network(net, train);
#endif
        if (avg_loss < 0) avg_loss = loss;
        avg_loss = avg_loss*.9 + loss*.1;

        i = get_current_batch(net);
        printf("%d: %f, %f avg, %f rate, %lf seconds, %d images\n", get_current_batch(net), loss, avg_loss, get_current_rate(net), sec(clock()-time), i*imgs);
        if(i%1000==0 || (i < 1000 && i%100 == 0)){
#ifdef GPU
            if(ngpus != 1) sync_nets(nets, ngpus, 0);
#endif
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory, base, i);
            save_weights(net, buff);
        }
        free_data(train);
    }
#ifdef GPU
    if(ngpus != 1) sync_nets(nets, ngpus, 0);
#endif
    char buff[256];
    sprintf(buff, "%s/%s_final.weights", backup_directory, base);
    save_weights(net, buff);
}



/*
void picture_detector()
{
    
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        } else {
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return;
            strtok(input, "\n");
        }
        
        image im = load_image_cv(input);  //experiment

        image sized = resize_image(im, net.w, net.h);
        layer l = net.layers[net.n-1];
        
        int j;
        box *boxes = calloc(l.w*l.h*l.n, sizeof(box));
        float **probs = calloc(l.w*l.h*l.n, sizeof(float *));
        for(j = 0; j < l.w*l.h*l.n; ++j) probs[j] = calloc(l.classes + 1, sizeof(float *));

        float *X = sized.data;
        time_t1=clock();
        network_predict(net, X);

        printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time_t1));

        get_region_boxes(l, 1, 1, thresh, probs, boxes, 0, 0, hier_thresh);

        if (l.softmax_tree && nms) 
            do_nms_obj(boxes, probs, l.w*l.h*l.n, l.classes, nms);
        else if (nms) 
             do_nms_sort(boxes, probs, l.w*l.h*l.n, l.classes, nms);


        draw_bounding_box(im.w, im.h, l.w*l.h*l.n, thresh, boxes, probs, names, l.classes);

        free_image(im); 
        free_image(sized);

        free(boxes);
        free_ptrs((void **)probs, l.w*l.h*l.n);

        if (filename) 
            break;
    }
}
*/
