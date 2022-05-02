#include "fruit.h"

int main() {
	cv::Mat3b d1 = imread("depth/0728.png", cv::IMREAD_COLOR);
	cv::Mat3b d2 = imread("depth/depth445.png", cv::IMREAD_COLOR);
	cv::Mat3b fruit = imread("depth/color445.png", cv::IMREAD_COLOR);
	cv::Mat3b screen = imread("fruit/screen.png", cv::IMREAD_COLOR);
	cv::Mat1b binary, dst1, sabungray, peri, temp, temp2,temp3, e1, e2, e3, e4, e5,e6,c1,c2,c3,c4,c5,c6;
	cv::Mat3b sabun, colored, rgb, hsv, kukei, ss;
	cv::Mat1i labeled;
	
	difference(d1, d2, ss);
	//difference(screen, fruit, sabun);
	bgr2gray(ss, sabungray);
	binarization(sabungray, binary, 20);

	median(binary, temp);
	median(temp, temp2);
	median(temp2, temp3);
	erode(temp3, e1,8);
	dilate(e1, dst1,8);
	
	
	//bgr2h(fruit, dst1);
	//perimeter(dst1, peri);

	labeldraw(fruit, dst1, kukei);
	//labeling(dst1, labeled);
	//coloring(labeled, colored);

	//bgr(fruit, dst1, rgb);
	//bgr2hsv(rgb, dst1, hsv);
	//cv::imshow("graygray",temp3);
	cv::imshow("result", dst1);

	cv::imshow("result1w", kukei);

	//cv::imshow("results1", kukei);
	//cv::imshow("kukei", peri);	
	cv::waitKey(0);

	return 0;
}
