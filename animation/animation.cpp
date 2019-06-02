#include <math.h>

#include <opencv2/opencv.hpp>

#include "../datastructure/datastructure.h"
#include "animation.h"

Animation::Animation(){
}

void Animation::DrawLineCircle(cv::Mat* frame,Locate_Data coordinate,int rotate_degree,int RGB[3],int num_circle){
        
    float x0,y0,x1,y1;

    x0 = 290;
    y0 = 110+20*sqrt(3);
    x1 = 330;
    y1 = 110+20*sqrt(3);

    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0-20;
        x1=x1+20;
        y0=y0+20*sqrt(3);
        y1=y1+20*sqrt(3);
    }

    x0=110;
    y0=110+4*20*sqrt(3);
    x1=90;
    y1=110+5*20*sqrt(3);
    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0+40;
        x1=x1+20;
        y1=y1+20*sqrt(3);
    }

    x0=510;
    y0=110+4*20*sqrt(3);
    x1=530;
    y1=110+5*20*sqrt(3);
    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0-40;
        x1=x1-20;
        y1=y1+20*sqrt(3);
    }


    x0=110;
    y0=110+12*20*sqrt(3);
    x1=90;
    y1=110+11*20*sqrt(3);
    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0+40;
        x1=x1+20;
        y1=y1-20*sqrt(3);
    }


    x0=510;
    y0=110+12*20*sqrt(3);
    x1=530;
    y1=110+11*20*sqrt(3);
    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0-40;
        x1=x1-20;
        y1=y1-20*sqrt(3);
    }


    x0=290;
    y0=110+15*20*sqrt(3);
    x1=330;
    y1=110+15*20*sqrt(3);
    for(int row=1;row<13;row++){
        Rotate_Coordinate(&x0,&y0,rotate_degree);
        Rotate_Coordinate(&x1,&y1,rotate_degree);
        cv::line( *frame,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar( 75, 75, 75 ),3);
        x0=x0-20;
        x1=x1+20;
        y0=y0-20*sqrt(3);
        y1=y1-20*sqrt(3);
    }

    for(int i=0;i<num_circle;i++){

        if((int)(coordinate.x[i])!=-1 && (int)(coordinate.y[i])!=-1){
            cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),12,cv::Scalar( 0, 0, 0 ),-1,1 );
            cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( RGB[0], RGB[1], RGB[2] ),-1,1 );
        }
    }

}


void Animation::Rotate_Coordinate(float *x,float *y,int rotate_degree){
    float temp = *x;
    float rotate_center_x = 310;
    float rotate_center_y = 110+8*20*sqrt(3);

    *x  = ((*x-rotate_center_x) * cos( rotate_degree* CV_PI / 180) - (rotate_center_y-*y) *sin( rotate_degree* CV_PI / 180))+rotate_center_x;
    *y = -(((temp-rotate_center_x) * sin( rotate_degree* CV_PI / 180) + (rotate_center_y-*y) *cos( rotate_degree* CV_PI / 180))-rotate_center_y);
}


void Animation::DrawControlComponent(cv::Mat* frame){


}

/*
 * H(Hue): 0 - 360 degree (integer)
 * S(Saturation): 0 - 1.00 (double)
 * V(Value): 0 - 1.00 (double)
 * 
 * output[3]: Output, array size 3, int
 */
void HSVtoRGB(int H, double S, double V, int output[3]){

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	else if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	else if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	else if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	else if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;	
	}
	
	output[0] = (Rs + m) * 255;
	output[1] = (Gs + m) * 255;
	output[2] = (Bs + m) * 255;
}