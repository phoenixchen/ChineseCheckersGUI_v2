#include <opencv2/opencv.hpp>

class Animation{
public:
	Animation();

	void Rotate_Coordinate(float *x,float *y,int rotate_degree);
	void DrawLineCircle(cv::Mat* frame,Locate_Data coordinate,int rotate_degree,int RGB[3],int num_circle);
	void DrawControlComponent(cv::Mat* frame);
};

void HSVtoRGB(int H, double S, double V, int output[3]);