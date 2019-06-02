#include <opencv2/opencv.hpp>

#include "datastructure/datastructure.h"
#include "text/CvxText.h"

class ModeSelect{

public:
	ModeSelect();

int playercount;
int PlayWithHuman;

int printUI(cv::Mat *frame,CvxText *title,CvxText *text);
};

void DrawControlComponent(cv::Mat* frame,int *playercount,cv::Mat *Hout,cv::Mat *Cout,int *PlayWithHuman);