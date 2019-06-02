#include <math.h>

#include "foreground.h"

void Rotate_Coordinate(float *x,float *y,int rotate_degree){
    float temp = *x;
    float rotate_center_x = 310;
    float rotate_center_y = 110+8*20*sqrt(3);

    *x  = ((*x-rotate_center_x) * cos( rotate_degree* CV_PI / 180) - (rotate_center_y-*y) *sin( rotate_degree* CV_PI / 180))+rotate_center_x;
    *y = -(((temp-rotate_center_x) * sin( rotate_degree* CV_PI / 180) + (rotate_center_y-*y) *cos( rotate_degree* CV_PI / 180))-rotate_center_y);
}

void DrawLineCircle(cv::Mat* frame,char * chess,Locate_Data coordinate,int rotate_degree){
        
        float x0,y0,x1,y1;

        x0 = 290;
        y0 = 110+20*sqrt(3);
        x1 = 330;
        y1 = 110+20*sqrt(3);

        float rotate_x0,rotate_y0,rotate_x1,rotate_y1;

        for(int row=1;row<13;row++){
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
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
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
            x0=x0+40;
      		x1=x1+20;
      		y1=y1+20*sqrt(3);
        }

        x0=510;
        y0=110+4*20*sqrt(3);
        x1=530;
        y1=110+5*20*sqrt(3);
        for(int row=1;row<13;row++){
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
            x0=x0-40;
            x1=x1-20;
            y1=y1+20*sqrt(3);
        }


        x0=110;
        y0=110+12*20*sqrt(3);
        x1=90;
        y1=110+11*20*sqrt(3);
        for(int row=1;row<13;row++){
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
            x0=x0+40;
            x1=x1+20;
            y1=y1-20*sqrt(3);
        }


        x0=510;
        y0=110+12*20*sqrt(3);
        x1=530;
        y1=110+11*20*sqrt(3);
        for(int row=1;row<13;row++){
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
            x0=x0-40;
            x1=x1-20;
            y1=y1-20*sqrt(3);
        }


        x0=290;
        y0=110+15*20*sqrt(3);
        x1=330;
        y1=110+15*20*sqrt(3);
        for(int row=1;row<13;row++){
            rotate_x0 = x0;
            rotate_y0 = y0;
            rotate_x1 = x1;
            rotate_y1 = y1;
            Rotate_Coordinate(&rotate_x0,&rotate_y0,rotate_degree);
            Rotate_Coordinate(&rotate_x1,&rotate_y1,rotate_degree);
            cv::line( *frame,cv::Point(rotate_x0,rotate_y0),cv::Point(rotate_x1,rotate_y1),cv::Scalar( 75, 75, 75 ),3);
            x0=x0-20;
            x1=x1+20;
            y0=y0-20*sqrt(3);
            y1=y1-20*sqrt(3);
        }

        for(int i=0;i<256;i++){

            if((int)(coordinate.x[i])!=-1 && (int)(coordinate.y[i])!=-1){
                Rotate_Coordinate(&coordinate.x[i],&coordinate.y[i],rotate_degree);
                cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),12,cv::Scalar( 0, 0, 0 ),-1,1 );
            }

            if(chess[i]!=-1 && chess[i]!=0){

                switch(chess[i]){
                    case 1:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 0, 0, 255 ),-1,1 );break;
                    case 2:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 0, 195, 0 ),-1,1 );break;
                    case 3:
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 255, 0, 0 ),-1,1 );break;
                }
            }
            else{
                if((int)(coordinate.x[i])!=-1 && (int)(coordinate.y[i])!=-1)
                    cv::circle( *frame,cv::Point(coordinate.x[i],coordinate.y[i]),10,cv::Scalar( 220, 220, 220 ),-1,1 );
            }
        }

}

void DrawControlComponent(cv::Mat* frame){

}