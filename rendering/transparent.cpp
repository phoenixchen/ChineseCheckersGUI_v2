#include <opencv2/highgui.hpp>
using namespace cv;

void DrawCircle(cv::Mat* frame,float x,float y,float r,CvScalar color,float alpha){

    IplImage img = IplImage(*frame);
    IplImage *rec=(IplImage*)cvClone(&img);
    cvCircle(rec, cvPoint(x,y), r, color,-1);
    cvSetImageROI(&img,cvRect(x-r,y-r,2*r,2*r));
    cvSetImageROI(rec,cvRect(x-r,y-r,2*r,2*r));
    cvAddWeighted(&img,alpha,rec,1-alpha,0.0,&img);
    cvResetImageROI(&img);
    cvReleaseImage(&rec);
	*frame=cvarrToMat(&img,true);
}

void DrawRectangle(cv::Mat* frame,float x,float y,float width,float height,CvScalar color,float alpha){

	IplImage img = IplImage(*frame);
    IplImage *rec=(IplImage*)cvClone(&img);
    cvRectangle(rec,cvPoint(x,y),cvPoint(x+width,y+height),color,-1);
    cvSetImageROI(&img,cvRect(x,y,width,height));
    cvSetImageROI(rec,cvRect(x,y,width,height));
    cvAddWeighted(&img,alpha,rec,1-alpha,0.0,&img);
    cvResetImageROI(&img);
    cvReleaseImage(&rec);
	*frame=cvarrToMat(&img,true);
}


void DrawPolygon(cv::Mat* frame,CvPoint* pts[],int npts[],float width,float height,CvScalar color,float alpha){

	IplImage img = IplImage(*frame);
    IplImage *rec=(IplImage*)cvClone(&img);
    cvFillPoly(rec, pts, npts, 1, color,8,0);
    cvSetImageROI(&img,cvRect(0,0,width,height));
    cvSetImageROI(rec,cvRect(0,0,width,height));
    cvAddWeighted(&img,alpha,rec,1-alpha,0.0,&img);
    cvResetImageROI(&img);
    cvReleaseImage(&rec);
	*frame=cvarrToMat(&img,true);
}