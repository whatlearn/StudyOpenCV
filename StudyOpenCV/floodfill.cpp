#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

char *windowName = "result";

int main()
{
	char *imgPath = "test.jpg";
	Mat src = imread(imgPath, IMREAD_COLOR);
	Vec3b pf = src.at<Vec3b>(10,10);
	Scalar color(pf);
	cout << int(pf[0]) << endl;

	///Floodfill
	//int g_nConnectivity = 8;
	//int g_nNewMaskVal = 255;
	//int flags = g_nConnectivity | (g_nNewMaskVal << 8) | CV_FLOODFILL_FIXED_RANGE | CV_FLOODFILL_MASK_ONLY;
	//Mat mask = Mat::zeros(src.rows+2, src.cols+2, CV_8UC1);
	//floodFill(src, mask, Point(200, 300),Scalar(255),0, Scalar(20, 20, 20), Scalar(20, 20, 20), flags);
	Rect ccomp;
	int area = floodFill(src, Point(200, 300), color, &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
	rectangle(src, ccomp, Scalar(0, 0, 255), 5, 8);
	cout << area << endl;

	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, src);
	waitKey(0);
	return 0;
}