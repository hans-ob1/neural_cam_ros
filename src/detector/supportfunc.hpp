#ifndef SUPPORTFUNC_H
#define SUPPORTFUNC_H

#include <opencv2/videoio/videoio.hpp>  // Video write
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

typedef struct {
    int h;
    int w;
    int c;
    float *data;
} image;

struct detectedBox{
    Point topLeft;
    Point bottomRight;
    string name;
    Scalar objectColor;
    float prob;
};


void constrain_image(image im);
image copy_image(image p);
void free_image(image m);
float get_pixel(image m, int x, int y, int c);
void rgbgr_image(image im);
image ipl_to_image(IplImage* src);
image make_empty_image(int w, int h, int c);
image mat_to_image(Mat& src);
#endif
