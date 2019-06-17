#include<opencv2\opencv.hpp>
#include<iostream>

#define WINDOWNAME "Linear Blend"
#define TRACKBAENAME "TrackBar"
#define ALPHAMAX 100

using namespace cv;
using namespace std;

static void OnTrackBar(int, void* userdata);

int main()
{
	Mat src = imread("image.jpeg",IMREAD_COLOR);

	int alpha_slider = 0;
	namedWindow(WINDOWNAME, WINDOW_NORMAL);
	createTrackbar(TRACKBAENAME, WINDOWNAME, &alpha_slider, ALPHAMAX, OnTrackBar,&src);
	OnTrackBar(alpha_slider, &src);
	waitKey(0);
	return 0;
}

static void OnTrackBar(int , void* userdata)
{
	Mat srcImage = (*(Mat*)userdata).clone();
	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	vector<Mat> vhsv;
	split(hsvImage, vhsv);
	float alpha = getTrackbarPos(TRACKBAENAME, WINDOWNAME) * 2.0 / ALPHAMAX;
	Mat temp(srcImage.rows, srcImage.cols, CV_32FC1);
	temp = vhsv[2] * alpha;
	temp.convertTo(temp, CV_8UC1);
	vhsv[2] = temp;
	merge(vhsv, hsvImage);
	cvtColor(hsvImage, srcImage, COLOR_HSV2BGR);
	imshow(WINDOWNAME, srcImage);
}