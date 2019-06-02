#include <opencv2/opencv.hpp>

void DrawCircle(cv::Mat* frame,float x,float y,float r,CvScalar color,float alpha);

void DrawRectangle(cv::Mat* frame,float x,float y,float width,float height,CvScalar color,float alpha);

void DrawPolygon(cv::Mat* frame,CvPoint* pts[],int npts[],float width,float height,CvScalar color,float alpha);