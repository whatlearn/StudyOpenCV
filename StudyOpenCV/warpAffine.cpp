#include<opencv2\opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("rotated.jpg", IMREAD_GRAYSCALE);
	Mat thresh;
	threshold(src, thresh,150, 255, THRESH_BINARY);

	vector<vector<Point>> contours;
	findContours(thresh, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	RotatedRect rect = minAreaRect(contours[1]);
	Point2f vertex[4];
	rect.points(vertex);
	for (size_t j = 0; j < 4; j++)
	{
		//line(src, vertex[j], vertex[(j + 2) % 4], Scalar(0), 1, 8);
	}
	Mat trans = getRotationMatrix2D(rect.center, rect.angle + 90.0, 1.0);
	warpAffine(src, src, trans, src.size());

	Point2f srcPoints[3];
	Point2f dstPoints[3];
	srcPoints[0] = vertex[0];
	dstPoints[0] = vertex[0];
	srcPoints[1] = vertex[1];
	dstPoints[1].x = vertex[1].x + rect.size.height / tan(rect.angle);dstPoints[1].y = vertex[1].y;
	srcPoints[2] = vertex[3];
	dstPoints[2].x = vertex[3].x - rect.size.height / tan(rect.angle); dstPoints[2].y = vertex[3].y;

	Mat M = getAffineTransform(srcPoints, dstPoints);
	warpAffine(src, src, M, src.size());

	imshow("result", src);
	waitKey(0);
	return 0;
}