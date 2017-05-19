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
char **names;

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

void setup_proceedure(char *datacfg, char *cfg, char *weights, char *name_list, float thresh_desired){
    
 //setup proceedure
 options = read_data_cfg(datacfg);

 names = get_labels(name_list);

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

   draw_bounding_box(im.w, im.h, l.w*l.h*l.n, thresh, boxes, probs, names, l.classes);

   free_image(im); 
   free_image(sized);

   free(boxes);
   free_ptrs((void **)probs, l.w*l.h*l.n);
}
