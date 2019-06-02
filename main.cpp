#include <stdlib.h>

#define CVUI_IMPLEMENTATION
#include "rendering/cvui.h"

#include "select_mode.h"
#include "predict_mode.h"
#include "battle_mode.h"

int main() {

	char *chess = (char *)malloc(sizeof(char) * 256 );

	cv::Mat frame = cv::Mat(700, 1245, CV_8UC3);
	cvui::init("中國跳棋對戰程式");
	int selection = -1;

	CvxText title = DrawTextBigInit();
	CvxText text = DrawTextSmallInit();

	ModeSelect before_select;
	selection = before_select.printUI(&frame,&title,&text);

	if(selection==0){
	}
	if(selection==1){
	}
	if(selection==2){
		Predict predict_mode;
		predict_mode.printUI(chess,&frame,&text);
	}
	if(selection==3){
		BattleMode battle_mode;
		battle_mode.printUI(chess,&frame,before_select.PlayWithHuman,before_select.playercount,&text);
	}
	if(selection==4){
		BattleMode battle_mode;
		battle_mode.printUI(chess,&frame,before_select.PlayWithHuman,before_select.playercount,&text);
	}

	return 0;
}