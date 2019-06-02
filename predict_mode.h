#include <stdio.h>
#include <list>
#include <opencv2/opencv.hpp>

#include "datastructure/datastructure.h"
#include "text/CvxText.h"

class Predict{

public:
	Predict();

	void MouseClickAction(cv::Point mouse,int *mouseclickchess,Locate_Data coordinate,int current_rotate);
	void GUIUpdate(char *chess, int mouseclickchess, int *count,std::list <int> *put_chess_order);
	bool invalidposition(int mouseclickchess,Transform_1darray_2darray_Convert check);
	bool printUI(char *chess,cv::Mat *frame,CvxText *text);
	void DrawControlComponent(cv::Mat* frame);
};
