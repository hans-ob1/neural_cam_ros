#ifndef DETECTOR_H_
#define DETECTOR_H_
 
 void setup_proceedure(char *datacfg, char *cfg, char *weights, float thresh_desired);
 void camera_detector();
 void picture_detector();

 void setup_detector_training(char *datacfg, char *cfg, char *weights);
 void execute_detector_training();
#endif
