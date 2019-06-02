#include <list>

#include "rendering/cvui.h"

#include "predict_mode.h"
#include "predict/predict.h"
#include "rendering/foreground.h"
#include "rendering/background.h"
#include "time/time.h"

using namespace std;

Predict::Predict(){
}

void Predict::MouseClickAction(cv::Point mouse,int *mouseclickchess,Locate_Data coordinate,int current_rotate){

    *mouseclickchess = -127;

    for(int i=0;i<256;i++){
        if((int)(coordinate.x[i])!=-1 && (int)(coordinate.y[i])!=-1)
            Rotate_Coordinate(&coordinate.x[i],&coordinate.y[i],current_rotate);
    }

    for(int i=0;i<256;i++){
        if(abs(coordinate.x[i]-mouse.x)<10 && abs(coordinate.y[i]-mouse.y)<10 )
           if(sqrt(pow((coordinate.x[i]-mouse.x),2)+pow((coordinate.y[i]-mouse.y),2))<=10){
                *mouseclickchess = i;
                return;
           }
    }
}

void Predict::GUIUpdate(char *chess, int mouseclickchess, int *count,list <int> *put_chess_order){

    if(chess[mouseclickchess]==0){
        if(*count<=10)
            chess[mouseclickchess] = 2;
        else
            chess[mouseclickchess] = 1;
    }
    else{
        *count = *count-1;
       (*put_chess_order).pop_back();
    }
}

bool Predict::invalidposition(int mouseclickchess,Transform_1darray_2darray_Convert check){

    bool is_not_valid = true;

    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){
            if(check.array_diamond[i][j] == locatetransformrevers(mouseclickchess)){
                is_not_valid = false;
                break;
            }
        }
    }

    return is_not_valid;
}


bool Predict::printUI(char *chess,cv::Mat *frame,CvxText *text){

    cv::Point mouse;
    preprocess(frame,true);
    cv::Mat preprocess_frame;
    preprocess_frame = (*frame).clone();

    Locate_Data coordinate;
    coordinate.init_1darray_locate();

    bool IsMouseClick = false;
    int mouseclickchess = -127;
    int count = 1;
    bool predict_is_press = false;
    bool predict_is_press_status_error = false;
    int output_value = -1;

    list <int> put_chess_order;
    list<int>::iterator iterator_for_list;

    Transform_1darray_2darray_Convert check;

    for (int i = 0; i < 256; i++) {
		chess[i] = 0;
	}

    char* str;
    char str1[]="離開";
    char str2[]="重新";
    char str3[]="悔棋";
    char str4[]="預測";
    char str5[30]="";

    char str6[]="順時針旋轉";
    char str7[]="逆時針旋轉";

    int rotate_degree = 180;
    int current_rotate = 0;
    int rotate_finish = 0;
    int clockwise = 0;

	while (true){

        *frame = preprocess_frame.clone();
        
        if(clockwise==1){
            if(current_rotate < rotate_finish){
                    current_rotate = current_rotate+4*clockwise;
                    DrawLineCircle(frame,chess,coordinate,current_rotate);
            }
            else{
                clockwise = 0;
            }
        }
        if(clockwise==-1)
        {
            if(current_rotate > rotate_finish){
                    current_rotate = current_rotate+4*clockwise;
                    DrawLineCircle(frame,chess,coordinate,current_rotate);
            }
            else{
                clockwise = 0;
            }
        }
        if(clockwise==0){
            DrawLineCircle(frame,chess,coordinate,current_rotate);
        }

        if (cvui::mouse(cvui::CLICK)) {
			mouse.x = cvui::mouse().x;
			mouse.y = cvui::mouse().y;
			IsMouseClick = true;
		}

        if(IsMouseClick){
            MouseClickAction(mouse,&mouseclickchess,coordinate,current_rotate);
            IsMouseClick = false;
            predict_is_press_status_error = false;
            if(invalidposition(mouseclickchess,check))
                mouseclickchess=-127;
        }

        if(mouseclickchess!=-127){
            if(count<=20 && count >0){
                put_chess_order.push_back(mouseclickchess);
                GUIUpdate(chess,mouseclickchess,&count,&put_chess_order);
                mouseclickchess=-127;
                count++;
            }
            else
                cvui::printf(*frame, 175, 40, 0.4, 0xff0000, "The board is already full, please undo a chess to change.");
        }
            
        DrawControlComponent(frame);

		if (cvui::button(*frame, 600 , 10 ,60, 50, "")) {
		    break;
		}

		if (cvui::button(*frame, 600 , 80 ,60, 50, "")) {
            for (int i = 0; i < 256; i++) {
		        chess[i] = 0;
	        }
            count = 1;
            mouseclickchess = -127;
            IsMouseClick = false;
            predict_is_press = false;
            predict_is_press_status_error = false;
            output_value = -1;
            put_chess_order.clear();
		}
        
        if (cvui::button(*frame, 600 , 150 ,60, 50, "")) {
            if(count>1){
                chess[put_chess_order.back()] = 0;
                put_chess_order.pop_back();
                    count--;
            }
            predict_is_press_status_error = false;
		}

        if (cvui::button(*frame, 600 , 220 ,60, 50, "")) {
            if(count==21){
                predict_is_press = true;
            }
            else
                predict_is_press_status_error = true;
		}

        str = str1;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,45,255,255,255);
        str = str2;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,115,255,255,255);
        str = str3;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,185,255,255,255);
        str = str4;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),605,255,255,255,255);

        getTime(str5);
        str = str5;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),440,690,200,200,200);
        //std::cout << "current time is: " << local.tm_hour<<':'<<local.tm_min<<':'<<local.tm_sec <<std::endl;

        if (cvui::button(*frame, 520 , 565 ,145, 50, "")) {
		    if(clockwise==0){
                clockwise = 1;
                rotate_finish = current_rotate + clockwise * rotate_degree;
            }
		}
        if (cvui::button(*frame, 520 , 615 ,145, 50, "")) {
		    if(clockwise==0){
                clockwise = -1;
                rotate_finish = current_rotate + clockwise * rotate_degree;
            }
		}
        str = str6;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),525,600,200,200,200);
        str = str7;
        DrawTextOnWindow(*frame,text,DrawTextChangeStr(str),525,650,200,200,200);

        if(predict_is_press){
            output_value = predict(chess,check);
            predict_is_press = false;
        }

        if(output_value != -1)
            cvui::printf(*frame, 175, 60, 0.4, 0xff0000, "This board's win rate: %2d%%",output_value);

        if(predict_is_press_status_error)
            cvui::printf(*frame, 175, 20, 0.4, 0xff0000, "Please fill out the board.");

        cvui::update();
		cvui::imshow("中國跳棋對戰程式", *frame);
        if (cv::waitKey(20) == 27)
			return true;
	}
}


void Predict::DrawControlComponent(cv::Mat* frame){

}
