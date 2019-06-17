#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

char *imagePath = "tool.jpg";
char *windowName = "result";

void OnMouse(int event, int x, int y, int flags, void* data);

int main()
{
	namedWindow(windowName, WINDOW_NORMAL);
	Mat srcImage = imread(imagePath, IMREAD_COLOR);

	setMouseCallback(windowName, OnMouse,&srcImage);
	while (true)
	{
		if (waitKey() == 27)
		{
			break;
		}
	}
	return 0;
}

void OnMouse(int event, int x, int y, int flags, void * data)
{
	cout << x << endl;
	cout << y << endl;
	Mat para = *(Mat*)data;
	Mat src = para.clone();
	switch (event)
	{
		case EVENT_LBUTTONDOWN:
		{
			imshow(windowName, src);
		}
			break;
		case EVENT_RBUTTONDOWN:
		{
			Mat gray;
			cvtColor(src, gray, COLOR_BGR2HSV);
			imshow(windowName, gray);
		}
			break;
		default:
			break;
	}
}
