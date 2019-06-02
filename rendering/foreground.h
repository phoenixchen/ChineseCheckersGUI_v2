#include <opencv2/opencv.hpp>

#include "../datastructure/datastructure.h"

void Rotate_Coordinate(float *x,float *y,int rotate_degree);

void DrawLineCircle(cv::Mat* frame,char * chess,Locate_Data coordinate,int rotate_degree);

void DrawControlComponent(cv::Mat* frame);