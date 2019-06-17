#include<opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

char *windowName = "Final Result";
char *trackBar = "cannyVal";

void OnTrackBar(int pos, void* data);

int main()
{
	namedWindow(windowName, WINDOW_NORMAL);

	Mat srcImage = imread("tool.jpg", IMREAD_COLOR);
	blur(srcImage, srcImage, Size(5, 5));

	int lowEdge = 0;
	createTrackbar(trackBar, windowName, &lowEdge, 5, OnTrackBar,&srcImage);
	OnTrackBar(lowEdge, &srcImage);

	waitKey(0);
	return 0;
}

void OnTrackBar(int pos, void * data)
{
	Mat src = *(Mat*)data;
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Mat edges;
	Canny(gray, edges, 45, 90, 3);
	Mat element = getStructuringElement(MORPH_RECT, Size(9, 3));
	morphologyEx(edges, edges, MORPH_DILATE, element, Point(-1, -1), 3);
	distanceTransform(edges, edges, CV_DIST_L2, 3);
	normalize(edges, edges, 0, 1.0, NORM_MINMAX);
	threshold(edges, edges, .4, 1, THRESH_BINARY);
	edges.convertTo(edges, CV_8UC1, 256);
	Mat masks = Mat::zeros(edges.size(), CV_32SC1);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(masks, contours, saturate_cast<int>(i), Scalar::all(static_cast<int>(i) + 200), -1);
	}
	//watershed(src, masks);
	Mat mark = Mat::zeros(masks.size(), CV_8UC1);
	masks.convertTo(mark, CV_8UC1);
	imshow(windowName,mark);
}
