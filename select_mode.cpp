#include <thread>
using namespace std;

#include "rendering/cvui.h"

#include "select_mode.h"
#include "rendering/background.h"
#include "animation/animation.h"

ModeSelect::ModeSelect(){
    playercount = 2;
    PlayWithHuman = 0;
}

int ModeSelect::printUI(cv::Mat *frame,CvxText *title,CvxText *text){

    cv::Point mouse;
    preprocess(frame,false);
    cv::Mat preprocess_frame;
    preprocess_frame = (*frame).clone();

    Locate_Data coordinate;
    coordinate.init_1darray_locate();
    Animation opening;

    bool IsMouseClick = false;
    int current_rotate = 0;
    int rotate_finish = 360;
    int clockwise = 1;
    bool is_first_view = true;

    int RGB[3]={220,220,220};
    int num_circle = 7;

    cv::Mat picture_ai = cv::imread("assets/computer.png", cv::IMREAD_COLOR);
	cv::Mat picture_human = cv::imread("assets/human.png", cv::IMREAD_COLOR);

/***********rotate animation****************/

    //int H_range = 0;
	while (true){
        *frame = cv::imread("assets/BG_opening.png");
        if(clockwise==1){
            if(current_rotate < rotate_finish){
                    //HSVtoRGB(H_range, 100, 100, RGB);
                    opening.DrawLineCircle(frame,coordinate,current_rotate, RGB,num_circle);
                    current_rotate = current_rotate+ 10*clockwise;
                    //H_range = H_range +30;
                    //if(H_range>360)
                    //    H_range = 0;
                    num_circle = num_circle + 7;
                    if(num_circle>255)
                        num_circle = 255;
            }
            else{
                clockwise = 0;
            }
        }
        if(clockwise==0){
            break;
        }
        cvui::update();
		cvui::imshow("中國跳棋對戰程式", *frame);
        if (cv::waitKey(20) == 27)
			break;
        if(is_first_view){
            std::this_thread::sleep_for(chrono::seconds(1));
            is_first_view = false;
        }
    }


/*******************************************/

    char* str;
    char str1[]="中國跳棋對戰程式";
    char str2[]="本程式有debug模式與對戰模式兩種";
    char str3[]="debug模式:";
    char str4[]="1.對戰回放";
    char str5[]="2.各節點參數顯示";
    char str6[]="3.盤面預測";
    char str7[]="對戰模式:";
    char str8[]="4.兩人對戰";
    char str9[]="5.三人對戰";
    char str10[]="對戰盤面皆會自動存檔";

    char str11[]="離開";
    char str12[]="開始";

    RGB[0]=220;
    RGB[1]=220;
    RGB[2]=220;

    *frame = preprocess_frame.clone();
    opening.DrawLineCircle(frame,coordinate,rotate_finish,RGB,num_circle);
    cvui::rect(*frame, 680, 80 , 500, 600, 0x000000,0xc8c8c8);
    
    str = str1;
    DrawTextOnWindow(*frame,title,DrawTextChangeStr(str),700,120,40,40,40);
    str = str2;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),700,150,40,40,40);
    str = str3;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),700,230,40,40,40);
    str = str4;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),730,290,40,40,40);
    str = str5;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),730,330,40,40,40);
    str = str6;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),730,370,40,40,40);
    str = str7;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),700,450,40,40,40);
    str = str8;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),730,490,40,40,40);
    str = str9;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),730,530,40,40,40);
    str = str10;
    DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),700,570,40,40,40);

    bool button[5]={false};
    button[3]=true;
    int clickwhich = -1;

    preprocess_frame = (*frame).clone();

	while (true){

        *frame = preprocess_frame.clone();

        if (cvui::button(*frame, 600 , 10 ,60, 50, "")) {
		    break;
		}
        if (cvui::button(*frame, 600 , 80 ,60, 50, "")) {
            for(int i=0;i<5;i++){
                    if(button[i]!=0)
                        return i;
                }
		}

        str = str11;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,45,255,255,255);
        str = str12;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,115,255,255,255);

        if(cvui::checkbox(*frame, 705, 275,"", &button[0])){
            if(button[0]!=false){
                clickwhich = 0;
                for(int i=0;i<5;i++){
                    if(i==clickwhich)
                        button[i] = true;
                    else
                        button[i] = false;
                }
            }
        }
        if(cvui::checkbox(*frame, 705, 315,"", &button[1])){
            if(button[1]!=false){
                clickwhich = 1;
                for(int i=0;i<5;i++){
                    if(i==clickwhich)
                        button[i] = true;
                    else
                        button[i] = false;
                }
            }
        }
        if(cvui::checkbox(*frame, 705, 355,"", &button[2])){
            if(button[2]!=false){
                clickwhich = 2;
                for(int i=0;i<5;i++){
                    if(i==clickwhich)
                        button[i] = true;
                    else
                        button[i] = false;
                }
            }
        }
        if(cvui::checkbox(*frame, 705, 475,"", &button[3])){
            if(button[3]!=false){
                clickwhich = 3;
                for(int i=0;i<5;i++){
                    if(i==clickwhich)
                        button[i] = true;
                    else
                        button[i] = false;
                }
                playercount = 2;
            }
        }
        if(cvui::checkbox(*frame, 705, 515,"", &button[4])){
            if(button[4]!=false){
                clickwhich = 4;
                for(int i=0;i<5;i++){
                    if(i==clickwhich)
                        button[i] = true;
                    else
                        button[i] = false;
                }
                playercount = 3;
            }
        }


        if(button[3]==true | button[4]==true)
            DrawControlComponent(frame,&playercount,&picture_human,&picture_ai,&PlayWithHuman);

        cvui::update();
		cvui::imshow("中國跳棋對戰程式", *frame);
        if (cv::waitKey(20) == 27)
			break;
	}
}



void DrawControlComponent(cv::Mat* frame,int *playercount,cv::Mat *Hout,cv::Mat *Cout,int *PlayWithHuman){

    switch(*playercount){

        case 3:
        cv::line( *frame,cv::Point(1000,220),cv::Point(1000,520),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(1000,220),cv::Point(1050,220),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(1000,370),cv::Point(1050,370),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(870,520),cv::Point(1050,520),cv::Scalar( 75, 75, 75 ),2.0);

        switch(*PlayWithHuman){
            case 0:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                cvui::window(*frame, 1050, 450, 120, 140, " ");
                cvui::printf(*frame ,1050, 452, 0.6, 0xf0f0f0, "   player3");
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
                if(cvui::button(*frame, 1050, 320, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 2;
                if(cvui::button(*frame, 1050, 470, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 3;
            break;
            case 1:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                cvui::window(*frame, 1050, 450, 120, 140, " ");
                cvui::printf(*frame ,1050, 452, 0.6, 0xf0f0f0, "   player3");
                if(cvui::button(*frame, 1050, 170, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 0;
                if(cvui::button(*frame, 1050, 320, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
                if(cvui::button(*frame, 1050, 470, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
            break;
            case 2:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                cvui::window(*frame, 1050, 450, 120, 140, " ");
                cvui::printf(*frame ,1050, 452, 0.6, 0xf0f0f0, "   player3");
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 2;
                if(cvui::button(*frame, 1050, 320, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 0;
                if(cvui::button(*frame, 1050, 470, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 2;
            break;
            case 3:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                cvui::window(*frame, 1050, 450, 120, 140, " ");
                cvui::printf(*frame ,1050, 452, 0.6, 0xf0f0f0, "   player3");
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 3;
                if(cvui::button(*frame, 1050, 320, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 3;
                if(cvui::button(*frame, 1050, 470, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 0;
            break;
        }
        break;
        case 2:
        cv::line( *frame,cv::Point(1000,220),cv::Point(1000,480),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(1000,220),cv::Point(1050,220),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(1000,370),cv::Point(1050,370),cv::Scalar( 75, 75, 75 ),2.0);
        cv::line( *frame,cv::Point(870,480),cv::Point(1000,480),cv::Scalar( 75, 75, 75 ),2.0);

        switch(*PlayWithHuman){
            case 0:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
                if(cvui::button(*frame, 1050, 320, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 2;
            break;
            case 1:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                if(cvui::button(*frame, 1050, 170, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 0;
                if(cvui::button(*frame, 1050, 320, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
            break;
            case 2:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 2;
                if(cvui::button(*frame, 1050, 320, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 0;
            break;
            case 3:
                cvui::window(*frame, 1050, 150, 120, 140, " ");
                cvui::printf(*frame ,1050, 152, 0.6, 0xf0f0f0, "   player1");
                cvui::window(*frame, 1050, 300, 120, 140, " ");
                cvui::printf(*frame ,1050, 302, 0.6, 0xf0f0f0, "   player2");
                *PlayWithHuman = 0;
                if(cvui::button(*frame, 1050, 170, *Cout, *Cout, *Cout))
                    *PlayWithHuman = 1;
                if(cvui::button(*frame, 1050, 320, *Hout, *Hout, *Hout))
                    *PlayWithHuman = 2;
            break;
        }
        break;
    }
}