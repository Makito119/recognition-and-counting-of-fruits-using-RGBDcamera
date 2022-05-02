#ifndef HEADER_HPP
#define HEADER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<string>
#include<opencv2/opencv.hpp>
//#include<vector>

#endif
void erode(const cv::Mat1b& src, cv::Mat1b& dst,int a);
void dilate(const cv::Mat1b& src, cv::Mat1b& dst,int a);
void copyPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth);
void bubbleSort(std::vector<int>& list);
void median(const cv::Mat1b& src, cv::Mat1b& dst);
void bgr2gray(const cv::Mat3b& src, cv::Mat1b& dst);
void bgr2hsv(const cv::Mat3b& src, const cv::Mat1b& hikaku, cv::Mat3b& dst);
void bgr2h(const cv::Mat3b& src, const cv::Mat1b& hikaku);
int bgrh(const cv::Mat3b& src, const cv::Mat1b& hikaku,int a);
int bgrv(const cv::Mat3b& src, const cv::Mat1b& hikaku, int a);
void bgr(const cv::Mat3b& src, const cv::Mat1b& hikaku, cv::Mat3b& dst);
int max1(double a, double b, double c);
int min1(double a, double b, double c);
void binarization(const cv::Mat1b& src, cv::Mat1b& dst, int thresh);
void difference(const cv::Mat3b& screen, const cv::Mat3b& src, cv::Mat3b& dst);
int discriminantAnalysis(const cv::Mat1b src);
void zeroPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth);
void labeling(const cv::Mat1b& src, cv::Mat1i& dst);
void coloring(const cv::Mat1i& src, cv::Mat3b& dst);
void perimeter(const cv::Mat1b& src, cv::Mat1b& dst);
double peri(const cv::Mat1b& src, int a,int area);
void drawRect(const cv::Mat3b& src, const cv::Mat1b& two, cv::Mat3b& draw, const uchar color);
void labeldraw(const cv::Mat3b& src, const cv::Mat1b& two, cv::Mat3b& draw);