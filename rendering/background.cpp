#include "cvui.h"

#include "transparent.h"

void preprocess(cv::Mat *frame,bool right_corner){

	cv::Mat BG = cv::imread("assets/BG.png");
    *frame = BG.clone();
    float x = 310,y=110+8*20*sqrt(3);
    float r = 8*20*sqrt(3);
    float alpha = 0.4;
    DrawCircle(frame,x,y,r,CV_RGB(200,200,200),alpha);

    for(int i=80;i<=650;i=i+30){
        CvScalar colorj;
        CvScalar colorj_plum;

        if(i%4==0){
            colorj = CV_RGB(238,238,238);
            colorj_plum = CV_RGB(221,221,221);
        }
        else{
            colorj = CV_RGB(221,221,221);
            colorj_plum = CV_RGB(238,238,238);
        }
        if(right_corner){
            DrawRectangle(frame,680,i,275,30,colorj,0.2);cvui::rect(*frame, 680, i , 275, 30, 0x000000, 0xff000000);
            DrawRectangle(frame,955,i,275,30,colorj_plum,0.2);cvui::rect(*frame, 955, i , 275, 30, 0x000000, 0xff000000);
        }
    }

    cvui::window(*frame, 780, 10, 400, 50, "notice:");
    cvui::rect(*frame, 781, 31 , 398, 28, 0xff0000);
	cvui::text(*frame, 790 , 35, "Look before you leap.", 0.5);
    cvui::printf(*frame, 10, 10, 0.4, 0xCECECE, "Made by Phoenix");
}