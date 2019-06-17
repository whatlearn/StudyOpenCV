#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	namedWindow("test",WINDOW_NORMAL);
	Mat src = imread("tool.jpg");
	imshow("test", src);
	while (true)
	{
		int val = waitKey();
		if ( val == 27)
		{
			cout << "OK" << endl;
			break;
		}
	}
	return 0;
}