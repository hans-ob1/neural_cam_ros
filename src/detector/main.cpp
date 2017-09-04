/*

YOLO implementation with ROS
Modify here to suit your need

DOES NOT COME WITH WARRANTY.
USE AT YOUR OWN RISK

*/


#include <iostream>
#include <stdlib.h>     /* malloc, calloc, realloc, free */
#include <ctime>
#include <fstream>
#include <unistd.h>    /* get current work directory */

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio/videoio.hpp>  // Video write
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "supportfunc.hpp"      //custom functions

#include <neural_cam_ros/obstacle.h>
#include <neural_cam_ros/obstacleStack.h>
#include <thread>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Point32.h>
#include <tf/transform_listener.h>
#include <laser_geometry/laser_geometry.h>

// for publish of images
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;
using namespace cv;

extern "C" {
#include "detector.h"
}

// ********************************************************
// ********* support functions ****************************
// ********************************************************

VideoCapture cap_un;
Mat img_cpp;

// temp storage for detected objects
std::vector<detectedBox> detectedobjects;

/*
// convert IplImage to Mat   (NOT IN USE)
void convert_frame(IplImage* input){
    img_cpp = cv::cvarrToMat(input);
}
*/

// draw boxes
extern "C" void label_func(int tl_x, int tl_y, int br_x, int br_y, char *names, float prob){

   //TODO: Make this part (detection interests) more tidy, e.g load from cfg files

   string str(names);
   Scalar color;
   bool keep = false;

   if(str == "pedestrian"){  //index 01
     color = Scalar(255, 0, 0);  //coral color
     keep = true;
   }else if (str == "bike"){ //index 02
     color = Scalar(0, 0, 255);     //orange color
     keep = true;
   }else if (str == "vehicle"){ //index 03
     color = Scalar(0,255,0);      //gold color
     keep = true;
   }else{
     color = Scalar(0,0,0);          //black
   }


   if(keep){
     detectedBox tempstorage;

     if(tl_x < 0)
        tl_x = 0;
     if(tl_y < 0)
        tl_y = 0;

     if(br_x > img_cpp.cols)
        br_x = img_cpp.cols;
     if(br_y > img_cpp.rows)
        br_y = img_cpp.rows;

     tempstorage.topLeft = Point(tl_x,tl_y);
     tempstorage.bottomRight = Point(br_x,br_y);
     tempstorage.name = str;
     tempstorage.objectColor = color;
     tempstorage.prob = prob;

     detectedobjects.push_back(tempstorage);  //rmb to destory this
   }

}

vector<detectedBox> display_frame_cv(bool display){

    vector<detectedBox> pass_objects(detectedobjects);

    if(display){
    for(int j = 0; j < detectedobjects.size(); j++){
          Point namePos(detectedobjects[j].topLeft.x,detectedobjects[j].topLeft.y-10);  //position of name
            rectangle(img_cpp, detectedobjects[j].topLeft, detectedobjects[j].bottomRight, detectedobjects[j].objectColor, 2, CV_AA);                  //draw bounding box
            putText(img_cpp, detectedobjects[j].name, namePos, FONT_HERSHEY_PLAIN, 2.0, detectedobjects[j].objectColor, 1.5);                          //write the name of the object
        }

        imshow("detected results", img_cpp); //display as external window
    }

    detectedobjects.clear();  //clear vector for next cycle

    return pass_objects;
}

// capture from camera stream
image convertMat(Mat input)
{
   if (input.empty()){
       cout << "Warning: frame is empty! Check camera setup" << endl;
       return make_empty_image(0,0,0);
    }

    image im = mat_to_image(input);
    rgbgr_image(im);
    return im;
}


// initialization of deep learning network
bool init_network_param(){

	 char cwd[1024];
	 string cwd_str;

  	 if (getcwd(cwd, sizeof(cwd)) != NULL){
      	fprintf(stdout, "Current working dir: %s\n", cwd);
      	cwd_str = cwd;
     }
  	 else
        perror("getcwd() error");

     char *datacfg;
     char *cfg;
     char *weights;
     char *namelist;
     float thresh_desired;
     
     //default (running voc)
     string datafile = "cfg/voc.data";
     string archfile = "cfg/tiny-yolo-voc.cfg";
     string weightfile = "tiny-yolo-voc.weights";
     string namefile = "data/voc.names";

     ifstream confFile("setup.cfg");

     string line;
     int cnt = 0;
     if(confFile.is_open()){
       while( std::getline(confFile, line) ){
           istringstream is_line(line);
           string key;

           if(getline(is_line, key, '=')){
               string value;
               if(getline(is_line, value)){

               	  string value_fp = cwd_str + "/" + value;
                  if(cnt == 0){
                    datacfg = new char[value_fp.length() + 1];
                    strcpy(datacfg, value_fp.c_str());
                  }
                  else if(cnt == 1){
                    cfg = new char[value_fp.length() + 1];
                    strcpy(cfg, value_fp.c_str());
                  }
                  else if(cnt == 2){

                    if(value_fp.length() == 0)
                       weights = 0;
        			else{
                       weights = new char[value_fp.length() + 1];
                       strcpy(weights, value_fp.c_str());
        			}

                  }
                  else if(cnt == 3){

                    thresh_desired = strtof((value).c_str(),0); // string to float

                  }else if(cnt == 4){
                  	namelist = new char[value_fp.length() + 1];
                  	strcpy(namelist, value_fp.c_str());        // get the name list
                  }

                  cnt++;
               }
           }
       }
     }else{

         datacfg = new char[datafile.length() + 1];
         strcpy(datacfg, datafile.c_str());

         cfg = new char[archfile.length() + 1];
         strcpy(cfg, archfile.c_str());
  
         weights = new char[weightfile.length() + 1];
         strcpy(weights, weightfile.c_str());

         namelist = new char[weightfile.length() + 1];
         strcpy(namelist, namefile.c_str());

         thresh_desired = 0.35;

         cout << "Error: Unable to open setup.cfg, make sure it exists in the parent directory" << endl;
         
         return 0;
     }

     //initialize c api
 
     setup_proceedure(datacfg, cfg, weights, namelist, thresh_desired);

     delete [] datacfg;
     delete [] cfg;
     delete [] weights;
     delete [] namelist;

     return 1;
}

// initialize camera setup
bool init_camera_param(int cam_id, int cap_w, int cap_h){

      cap_un.open(cam_id);
      if(!cap_un.isOpened()){
         cout << "camera stream failed to open!" <<endl;
   		   return false;
      }else{
         cap_un.set(CV_CAP_PROP_FRAME_WIDTH,cap_w);
         cap_un.set(CV_CAP_PROP_FRAME_HEIGHT,cap_h);
         return true;
      }
}

// run this in a loop
vector<detectedBox> process_camera_frame(bool display, Mat in){

     image im = convertMat(in);
     camera_detector(im);      //draw frame from img_cpp;

     vector<detectedBox> curr_captured;
     curr_captured = display_frame_cv(display);

     return curr_captured;
}


// pub image
class ImageProcessor
{
  ros::NodeHandle nh_;
  ros::Publisher obstacles_pub;

  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;

public:
  ImageProcessor():it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/stereo_depth_ros/frames", 1, &ImageProcessor::imageCb, this);
    obstacles_pub = nh_.advertise<neural_cam_ros::obstacleStack>("obstacles", 1000);

  }

  ~ImageProcessor(){
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
  
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    img_cpp = cv_ptr->image;
    
    neural_cam_ros::obstacle d_data;
    neural_cam_ros::obstacleStack d_msg;

    vector<detectedBox> curr_preprocessed = process_camera_frame(true, img_cpp);   //true if want to display detection, false for no display

    for(unsigned int i = 0; i < curr_preprocessed.size(); i++){

      d_data.topleft.x = curr_preprocessed[i].topLeft.x;
      d_data.topleft.y = curr_preprocessed[i].topLeft.y;

      d_data.bottomright.x = curr_preprocessed[i].bottomRight.x;
      d_data.bottomright.y = curr_preprocessed[i].bottomRight.y;
      
      d_data.prob = curr_preprocessed[i].prob;

      d_data.name = curr_preprocessed[i].name;

      d_msg.stack_obstacles.push_back(d_data);
    }

    d_msg.stack_len = curr_preprocessed.size();
    d_msg.stack_name = "detections";      // check camera header

    obstacles_pub.publish(d_msg);
    
    cv::waitKey(1);
  }

};


//-------------------------------------------------------->
//<---------------------- main ---------------------------->
//-------------------------------------------------------->

int main(int argc, char* argv[]){

  ros::init(argc, argv, "talker");
  
#ifdef SUBIMAGES

  init_network_param();       //initialize the CNN parameters
  ImageProcessor ic;
  ros::spin();

#else
  ros::NodeHandle n("~");

  // ros publish items: image, object detected arrays
  ros::Publisher obstacles_pub = n.advertise<neural_cam_ros::obstacleStack>("obstacles", 1000);

  // get parameters from launch file
  int serial_number = -1;
  int cap_width = 640;
  int cap_height = 480;

  n.getParam("video_device", serial_number);
  n.getParam("cap_width", cap_width);
  n.getParam("cap_height", cap_height);
  
  cout << "Direct Image Acquisition from Camera Device" << serial_number << endl;
  cout << "Webcam Serial: " << serial_number << endl;
  cout << "Capture Resoultion: " << cap_width << "x" << cap_height << endl;

  image_transport::ImageTransport it_(n);
  image_transport::Publisher image_pub_ = it_.advertise("/neural_cam_ros/frames", 1);   //publishes a raw image

  cv_bridge::CvImage out_msg;
  out_msg.encoding = sensor_msgs::image_encodings::BGR8; // Encode to BGR8 format

  /* will read setup.cfg file for configuration details */
  if(!init_camera_param(serial_number, cap_width, cap_height))
      return -1;

  init_network_param();       //initialize the CNN parameters

  for(;;){

    //TODO: tidy up
  	//declare of ROS Parameters (refresh every cycle)
  	neural_cam_ros::obstacle d_data;
  	neural_cam_ros::obstacleStack d_msg;

    vector<detectedBox> curr_preprocessed;

    cap_un >> img_cpp;
    curr_preprocessed = process_camera_frame(false,img_cpp);   //true if want to display detection, false for no display

    for(int i = 0; i < curr_preprocessed.size(); i++){

    	d_data.topleft.x = curr_preprocessed[i].topLeft.x;
    	d_data.topleft.y = curr_preprocessed[i].topLeft.y;

    	d_data.bottomright.x = curr_preprocessed[i].bottomRight.x;
    	d_data.bottomright.y = curr_preprocessed[i].bottomRight.y;
    	
    	d_data.prob = curr_preprocessed[i].prob;

    	d_data.name = curr_preprocessed[i].name;

    	d_msg.stack_obstacles.push_back(d_data);
    }

    d_msg.stack_len = curr_preprocessed.size();
    d_msg.stack_name = "detections";      // check camera header

    obstacles_pub.publish(d_msg);

    out_msg.image    = img_cpp;           // Your cv::Mat  
    image_pub_.publish(out_msg.toImageMsg());

    if(waitKey (1) == 'q')  	               // close upon press 'q'
        break;
  }

#endif

   return 0;
}
