#include "fruit.h"

//カラー画像をグレースケールに変換
void bgr2gray(const cv::Mat3b& src, cv::Mat1b& dst)
{
	dst = cv::Mat1b(src.size());
	// dst = cv::Mat1b(src.rows, src.cols); //こっちでも可

	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			dst(y, x) = static_cast<uchar>(std::floor(0.114 * src(y, x)[0] + 0.587 * src(y, x)[1] + 0.299 * src(y, x)[2]));
			if (dst(y, x) == 255) {
				dst(y, x) = 0;
			}
		}
	}

}

void erode(const cv::Mat1b& src, cv::Mat1b& dst,int a)
{
	dst = src.clone();
	cv::Mat1b temp;
	

	for (int i = 0; i < a; i++) {
		zeroPadding(dst, temp, 1);
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 255 && (temp(y, x + 1) == 0 || temp(y + 1, x) == 0 || dst(y, x - 1) == 0 || temp(y - 1, x) == 0 || temp(y - 1, x - 1) == 0 || temp(y - 1, x + 1) == 0 || temp(y + 1, x - 1) == 0 || temp(y + 1, x + 1) == 0)) {
					dst(y-1 , x-1 ) = 0;
				}
			}
		}
	}
}

void dilate(const cv::Mat1b& src, cv::Mat1b& dst,int a)
{
	dst = src.clone();
	cv::Mat1b temp;

	for (int i = 0; i < a; i++) {
		zeroPadding(dst, temp, 1);
		for (int y = 1; y < temp.rows - 1; ++y) {
			for (int x = 1; x < temp.cols - 1; ++x) {
				if (temp(y, x) == 0 && (temp(y, x + 1) == 255 || temp(y + 1, x) == 255 || temp(y, x - 1) == 255 || temp(y - 1, x) == 255 || temp(y - 1, x - 1) == 255 || temp(y - 1, x + 1) == 255 || temp(y + 1, x - 1) == 255 || temp(y + 1, x + 1) == 255)) {
					dst(y - 1, x - 1) = 255;
				}
			}
		}
	}
	
}
//２値化する
void binarization(const cv::Mat1b& src, cv::Mat1b& dst, int thresh)
{
	dst = cv::Mat1b(src.size());
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) < thresh) dst(y, x) = 0;
			else dst(y, x) = 255;
		}
	}
}

//差分（物体ー背景）＝RGB画像
void difference(const cv::Mat3b& screen, const cv::Mat3b& src, cv::Mat3b& dst)
{
	dst = cv::Mat3b(src.size());
	for (int i = 0; i < 3; ++i) {
		for (int y = 0; y < src.rows; ++y) {
			for (int x = 0; x < src.cols; ++x) {
				if (abs(screen(y, x)[i] - src(y, x)[i]) < 200) {
					dst(y, x)[i] = 0;
				}
				/*else {
					dst(y, x)[i] = 255;
				}*/
			}
		}
	}
}



int max1(double a, double b, double c) {
	int max = a;
	if (b >= max) max = b;

	if (c >= max) max = c;

	return max;
}
int min1(double a, double b, double c) {
	int min = a;
	if (b <= min) min = b;

	if (c <= min) min = c;

	return min;
}

void copyPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth)
{
	dst = cv::Mat1b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);
	for (int y = 0; y < src.rows + paddingWidth * 2; ++y) {
		for (int x = 0; x < (src.cols) + paddingWidth * 2; ++x) {
			if (y >= 0 && y < paddingWidth) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(0, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(0, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(0, src.cols - 1);
				}
			}
			else if (y >= paddingWidth && y < src.rows + paddingWidth) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(y - paddingWidth, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(y - paddingWidth, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(y - paddingWidth, src.cols - 1);
				}
			}
			else if (y >= src.rows + paddingWidth && y < src.rows + paddingWidth * 2) {
				if (0 <= x && x < paddingWidth)dst(y, x) = src(src.rows - 1, 0);
				else if (paddingWidth <= x && x < src.cols + paddingWidth) {
					dst(y, x) = src(src.rows - 1, x - paddingWidth);
				}
				else if (src.cols + paddingWidth <= x && x < src.cols + paddingWidth * 2) {
					dst(y, x) = src(src.rows - 1, src.cols - 1);
				}
			}
		}
	}
}
void bubbleSort(std::vector<int>& list)
{


	for (int i = 0; i < (list.size() - 1); i++) {
		for (int j = (list.size() - 1); j > i; j--) {
			if (list[j] < list[j - 1]) {
				int k = list[j];
				list[j] = list[j - 1];
				list[j - 1] = k;
			}
		}
	}
}

void median(const cv::Mat1b& src, cv::Mat1b& dst)
{
	dst = src.clone();
	cv::Mat1b temp;
	copyPadding(src, temp, 1);
	std::vector<int> mid(9);
	for (int y = 1; y < temp.rows - 1; ++y) {
		for (int x = 1; x < temp.cols - 1; ++x) {

			mid[0] = temp(y - 1, x - 1);
			mid[1] = temp(y - 1, x);
			mid[2] = temp(y - 1, x + 1);
			mid[3] = temp(y, x - 1);
			mid[4] = temp(y, x);
			mid[5] = temp(y, x + 1);
			mid[6] = temp(y + 1, x - 1);
			mid[7] = temp(y + 1, x);
			mid[8] = temp(y + 1, x + 1);
			bubbleSort(mid);
			dst(y - 1, x - 1) = mid[4];
		}
	}
}
//HSV値の計算
void bgr2h(const cv::Mat3b& src, const cv::Mat1b& hikaku) {

	double max = 255.0;
	double min = 0.0;
	int i = 0;
	int hue[360];
	int value[255];
	int saturation[255];
	for (int b = 0; b < 360; b++) {
		hue[b] = 0;
	}
	for (int b = 0; b < 255; b++) {
		value[b] = 0;
	}
	for (int b = 0; b < 255; b++) {
		saturation[b] = 0;
	}
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (hikaku(y, x) != 0) {
				int c = 0;
				int s = 0;
				int sat = 0;
				if (src(y, x)[0] == src(y, x)[1] == src(y, x)[2]) hue[i] = 0.0;
				else {

					max = max1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);
					min = min1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);

					if (max == src(y, x)[2]) c = 60.0 * (src(y, x)[1] - src(y, x)[0]) / (max - min);
					else if (max == src(y, x)[1]) c = (60.0 * (src(y, x)[0] - src(y, x)[2]) / (max - min)) + 120.0;
					else if (max == src(y, x)[0])c = (60.0 * (src(y, x)[2] - src(y, x)[1]) / (max - min)) + 240.0;

					s = max;
					sat = ((max - min) * 255.0 / max);
				}

				if (c < 0) c += 360.0;
				for (int d = 0; d < 360; d++) {
					if (c == d) {
						hue[c]++;
					}
				}
				for (int d = 0; d < 255; d++) {
					if (s == d) {
						value[s]++;
					}
				}
				for (int d = 0; d < 255; d++) {
					if (sat == d) {
						saturation[sat]++;
					}
				}
				//std::cout << static_cast<int>(num[i]) << std::endl;

			}
		}
	}
	int maxx = 0;
	int maxxx = 0;
	int maxsa = 0;
	int maxsiki = 0;
	int siki = 0;
	int sikii = 0;
	for (int e = 0; e < 360; e++) {
		if (hue[e] > maxx) {
			maxx = hue[e];
			siki = e;
		}
	}
	for (int e = 0; e < 255; e++) {
		if (value[e] > maxxx) {
			maxxx = value[e];
			sikii = e;
		}
	}
	for (int e = 0; e < 255; e++) {
		if (saturation[e] > maxsa) {
			maxsa = saturation[e];
			maxsiki = e;
		}
	}
	for (int a = 0; a < 255; a++) {
		//std::cout << static_cast<int>(value[a]) << std::endl;
	}
	std::cout << "hue" << std::endl;
	std::cout << maxx << std::endl;
	std::cout << siki << std::endl;
	std::cout << "saturation" << std::endl;
	std::cout << maxsa << std::endl;
	std::cout << maxsiki << std::endl;
	std::cout << "value" << std::endl;
	std::cout << maxxx << std::endl;
	std::cout << sikii << std::endl;

}

int bgrh(const cv::Mat3b& src, const cv::Mat1b& hikaku, int a)
{
	double max = 255.0;
	double min = 0.0;
	int i = 0;
	int hue[360];
	int value[255];
	int saturation[255];
	for (int b = 0; b < 360; b++) {
		hue[b] = 0;
	}
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (hikaku(y, x) == a) {
				int c = 0;
				int s = 0;
				int sat = 0;
				if (src(y, x)[0] == src(y, x)[1] == src(y, x)[2]) hue[i] = 0.0;
				else {

					max = max1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);
					min = min1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);

					if (max == src(y, x)[2]) c = 60.0 * (src(y, x)[1] - src(y, x)[0]) / (max - min);
					else if (max == src(y, x)[1]) c = (60.0 * (src(y, x)[0] - src(y, x)[2]) / (max - min)) + 120.0;
					else if (max == src(y, x)[0])c = (60.0 * (src(y, x)[2] - src(y, x)[1]) / (max - min)) + 240.0;

					s = max;
					sat = ((max - min) * 255.0 / max);
				}

				if (c < 0) c += 360.0;
				for (int d = 0; d < 360; d++) {
					if (c == d) {
						hue[c]++;
					}
				}
			}
		}
	}
	int maxx = 0;
	int siki = 0;

	for (int e = 0; e < 360; e++) {
		if (hue[e] > maxx) {
			maxx = hue[e];
			siki = e;
		}
	}
	
	return siki;
}

int bgrv(const cv::Mat3b& src, const cv::Mat1b& hikaku, int a)
{
	double max = 255.0;
	double min = 0.0;
	int i = 0;
	int hue[255];
	int value[255];
	int saturation[255];
	for (int b = 0; b <255; b++) {
		hue[b] = 0;
	}
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (hikaku(y, x) == a) {
				int c = 0;
				int s = 0;
				int sat = 0;
				if (src(y, x)[0] == src(y, x)[1] == src(y, x)[2]) hue[i] = 0.0;
				else {

					max = max1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);
					min = min1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);

					

					s = max;
					
				}

				for (int d = 0; d < 360; d++) {
					if (s == d) {
						hue[s]++;
					}
				}
			}
		}
	}
	int maxx = 0;
	int siki = 0;

	for (int e = 0; e < 360; e++) {
		if (hue[e] > maxx) {
			maxx = hue[e];
			siki = e;
		}
	}

	return siki;
}

//RGB画像(背景除く）
void bgr(const cv::Mat3b& src, const cv::Mat1b& hikaku, cv::Mat3b& dst) {
	dst = src.clone();
	double max = 255.0;
	double min = 0.0;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (hikaku(y, x) != 0) {
				dst(y, x)[2] = src(y, x)[2];
				dst(y, x)[1] = src(y, x)[1];
				dst(y, x)[0] = src(y, x)[0];

			}
			else {
				dst(y, x)[2] = 0;
				dst(y, x)[1] = 0;
				dst(y, x)[0] = 0;
			}
		}
	}
}


//HSV画像
void bgr2hsv(const cv::Mat3b& src, const cv::Mat1b& hikaku, cv::Mat3b& dst) {
	dst = src.clone();
	double max = 255.0;
	double min = 0.0;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (hikaku(y, x) != 0) {
				double hue = 0.0;
				if (src(y, x)[0] == src(y, x)[1] == src(y, x)[2]) dst(y, x)[0] = 0.0;
				else {
					max = max1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);
					min = min1(src(y, x)[0], src(y, x)[1], src(y, x)[2]);

					if (max == src(y, x)[2]) hue = 60.0 * (src(y, x)[1] - src(y, x)[0]) / (max - min);
					else if (max == src(y, x)[1]) hue = ((60.0 * (src(y, x)[0] - src(y, x)[2]) / (max - min)) + 120.0);
					else if (max == src(y, x)[0])hue = ((60.0 * (src(y, x)[2] - src(y, x)[1]) / (max - min)) + 240.0);

				}
				dst(y, x)[2] = max;
				dst(y, x)[1] = ((max - min) * 255.0 / max);
				if (hue < 0) hue += 360.0;
				dst(y, x)[0] = hue * 0.5;

			}
		}
	}
}

void perimeter(const cv::Mat1b& src, cv::Mat1b& dst) {
	dst = src.clone();
	//dst = cv::Mat1b::zeros(src.rows, src.cols);
	int a = 0;
	int aera = 0;
	int peri = 0;
	double wa = 0.0;
	for (int y = 1; y < src.rows - 1; ++y) {
		for (int x = 1; x < src.cols - 1; ++x) {
			if (src(y, x) == 255) aera++;
			/*if (src(y, x) == 255) {
				if (src(y + 1, x - 1) == 0 || src(y + 1, x) == 0 || src(y + 1, x + 1) == 0
					|| src(y, x - 1) == 0 || src(y, x) == 0 || src(y, x + 1) == 0
					|| src(y - 1, x - 1) == 0 || src(y - 1, x) == 0 || src(y - 1, x + 1) == 0) {
					dst(y, x) = 255;
				}
			}*/
			if (src(y + 1, x - 1) == 255 && src(y + 1, x) == 255 && src(y + 1, x + 1) == 255
				&& src(y, x - 1) == 255 && src(y, x) == 255 && src(y, x + 1) == 255
				&& src(y - 1, x - 1) == 255 && src(y - 1, x) == 255 && src(y - 1, x + 1) == 255) 
			{
				dst(y, x) = 0;
			}
			/*else if (src(y + 1, x) == 255)dst(y, x) = 255;
			else if (src(y + 1, x+1) == 255)dst(y, x) = 255;
			else if (src(y , x+1) == 255)dst(y, x) = 255;
			else if (src(y -1, x+1) == 255)dst(y, x) = 255;
			else if (src(y -1, x) == 255)dst(y, x) = 255;
			else if (src(y - 1, x-1) == 255)dst(y, x) = 255;
			else if (src(y , x-1) == 255)dst(y, x) = 255;*/
		}
	}
	for (int y = 0; y < dst.rows; ++y) {
		for (int x = 0; x < dst.cols; ++x) {
			if (dst(y, x) == 255) peri++;
		}
	}
	wa = double(aera) / double(peri);
	std::cout << "面積" << std::endl;
	std::cout << aera << std::endl;
	std::cout << "周囲長" << std::endl;
	std::cout << peri << std::endl;
	std::cout << wa << std::endl;
	a = int(wa);
}

 
double peri(const cv::Mat1b& src, int a,int per) {
	double peri = 0.0;
	double wa = 0.0;
	double aera = 0.0;
	cv::Mat1b dst;
	dst = src.clone();
	//cv::Mat1b dst;
	//dst = src.clone();
	for (int y = 1; y < src.rows - 1; ++y) {
		for (int x = 1; x < src.cols - 1; ++x) {			
			if (src(y + 1, x - 1) == a && src(y + 1, x) == a && src(y + 1, x + 1) == a
				&& src(y, x - 1) == a && src(y, x) == a && src(y, x + 1) == a
				&& src(y - 1, x - 1) == a && src(y - 1, x) == a && src(y - 1, x + 1) == a)
			{
				dst(y, x) = 0;
			}
		}
	}

	for (int y = 0; y < dst.rows; ++y) {
		for (int x = 0; x < dst.cols; ++x) {
			if (dst(y, x) == a) peri++;
		}
	}

	for (int y = 1; y < src.rows - 1; ++y) {
		for (int x = 1; x < src.cols - 1; ++x) {
			if (src(y, x) == a) aera++;
			

			//if (src(y + 1, x - 1) == a && src(y + 1, x) == a && src(y + 1, x + 1) == a
			//	&& src(y, x - 1) == a && src(y, x) == a && src(y, x + 1) == a
			//	&& src(y - 1, x - 1) == a && src(y - 1, x) == a && src(y - 1, x + 1) == a) {
			//	dst(y, x) = 0;
			//}
			/*else if (src(y + 1, x) == 255)dst(y, x) = 255;
			else if (src(y + 1, x+1) == 255)dst(y, x) = 255;
			else if (src(y , x+1) == 255)dst(y, x) = 255;
			else if (src(y -1, x+1) == 255)dst(y, x) = 255;
			else if (src(y -1, x) == 255)dst(y, x) = 255;
			else if (src(y - 1, x-1) == 255)dst(y, x) = 255;
			else if (src(y , x-1) == 255)dst(y, x) = 255;*/
		}
	}
	/*for (int y = 0; y < dst.rows; ++y) {
		for (int x = 0; x < dst.cols; ++x) {
			if (dst(y, x) == a) peri++;
		}
	}*/
	wa = double(per / aera);
	std::cout << double(aera/(peri*peri)) << std::endl;
	std::cout << wa << std::endl;
	return wa;

}



//2値化の閾値の計算
int discriminantAnalysis(const cv::Mat1b src)
{
	double temp = 0.0;
	double max = 0.0;
	int th = 0;
	for (int i = 0; i < 256; ++i) {
		double w1 = 0.0, w2 = 0.0;
		double m1 = 0.0, m2 = 0.0;
		for (int y = 0; y < src.rows; ++y) {
			for (int x = 0; x < src.cols; ++x) {

				if (src(y, x) < i) {
					w1 = w1 + 1.0;
					m1 += src(y, x);
				}
				else {
					w2 = w2 + 1.0;;
					m2 += src(y, x);
				}
			}
		}
		m1 = m1 / w1;
		m2 = m2 / w2;
		temp = w1 * w2 * (m1 - m2) * (m1 - m2);
		if (temp > max) {
			max = temp;
			th = i;
		}
	}
	return th;
}

void zeroPadding(const cv::Mat1b& src, cv::Mat1b& dst, int paddingWidth)
{
	dst = cv::Mat1b::zeros((src.rows) + paddingWidth * 2, (src.cols) + paddingWidth * 2);

	for (int y = paddingWidth; y < (src.rows) + paddingWidth; ++y) {
		for (int x = paddingWidth; x < (src.cols) + paddingWidth; ++x) {
			dst(y, x) = src(y - paddingWidth, x - paddingWidth);
		}
	}
}

void labeling(const cv::Mat1b& src, cv::Mat1i& dst)
{
	cv::Mat1b temp1;
	zeroPadding(src, temp1, 1);
	cv::Mat1i temp2;
	dst = cv::Mat1i::zeros(src.rows, src.cols);
	temp2 = cv::Mat1i::zeros(temp1.rows, temp1.cols);
	cv::Mat1i temp3;
	temp3 = cv::Mat1i::zeros(temp1.rows, temp1.cols);
	for (int y = 0; y < temp1.rows; ++y) {
		for (int x = 0; x < temp1.cols; ++x) {
			if (temp1(y, x) == 255) {
				temp1(y, x) = 1;
			}
		}
	}

	long A[256];
	for (long i = 1; i < 256; i++) {
		A[i] = i;
	}
	A[0] = 0;

	//一次スキャン
	int a = 1;
	for (int y = 1; y < temp2.rows - 1; ++y) {
		for (int x = 1; x < temp2.cols - 1; ++x) {
			int min[9];
			min[0] = temp2(y - 1, x - 1);
			min[1] = temp2(y - 1, x);
			min[2] = temp2(y - 1, x + 1);
			min[3] = temp2(y, x - 1);
			int b = 256;
			for (int i = 0; i < 4; ++i) {

				if (min[i] != 0) {
					if (min[i] < b) b = min[i];
				}
			}
			if (temp1(y, x) == 1) {
				if (min[0] == 0 && min[1] == 0 && min[2] == 0 && min[3] == 0) {

					temp2(y, x) = a;
					a++;
				}
				else if (temp2(y - 1, x - 1) > 0 || temp2(y, x - 1) > 0 || temp2(y - 1, x) > 0 || temp2(y - 1, x + 1) > 0) {
					temp2(y, x) = b;
					if (temp2(y - 1, x - 1) != 1) {
						A[temp2(y - 1, x - 1)] = b;
						temp2(y - 1, x - 1) = b;
					}
					if (temp2(y, x - 1) != 1) {
						A[temp2(y, x - 1)] = b;
						temp2(y, x - 1) = b;
					}

				}

			}
		}
	}




	//
	for (int d = 0; d < 1; ++d) {
		for (int y = temp2.rows - 2; y > 0; --y) {
			for (int x = temp2.cols - 2; x > 0; --x) {
				int min[4];

				min[0] = temp2(y + 1, x - 1);
				min[1] = temp2(y + 1, x);
				min[2] = temp2(y + 1, x + 1);
				min[3] = temp2(y, x + 1);

				int b = 256;
				for (int i = 0; i < 4; ++i) {
					if (min[i] != 0) {
						if (min[i] < b) b = min[i];
					}
				}

				if (temp2(y, x) > 0) {
					if (min[0] != 0 || min[1] != 0 || min[2] != 0 || min[3] != 0) {
						A[temp2(y, x)] = b;
						temp2(y, x) = b;
						if (temp2(y + 1, x + 1) > b) {

							A[temp2(y + 1, x + 1)] = b;
							temp2(y + 1, x + 1) = b;
						}
						if (temp2(y, x + 1) > b) {

							A[temp2(y, x + 1)] = b;
							temp2(y, x + 1) = b;
						}
					}
				}
			}

		}

	}

	//重複した値を統合
	for (int y = 1; y < temp2.rows - 1; ++y) {
		for (int x = 1; x < temp2.cols - 1; ++x) {
			for (int i = 1; i < 256; i++) {
				if (temp2(y, x) == i) {
					temp3(y, x) = A[i];
				}
			}
		}
	}


	//ラベルの値を調整
	long C[1024];
	int v = 0;
	int wid = 1;


	for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {

			dst(y - 1, x - 1) = temp3(y, x);


		}
	}
	for (int n = 1; n < 10; ++n) {
		for (int y = 1; y < temp3.rows - 1; ++y) {
			for (int x = 1; x < temp3.cols - 1; ++x) {
				if (dst(y - 1, x - 1) == n) {
					//std::cout << dst(y - 1, x - 1) << std::endl;
				}


			}
		}

	}
	//出力画像
	/*int D[50];
	int d = 0;
	for (int y = 1; y < temp3.rows - 1; ++y) {
		for (int x = 1; x < temp3.cols - 1; ++x) {
			for (int i = 0; i < 512; i) {
				if (temp3(y, x) == C[i]) dst(y - 1, x - 1) = i + wid;
				i = i + wid;

				D[d] = i;
				d++;
			}
		}
	}
	for (int i = 0; i < 40; i++) {
		std::cout << D[i] << std::endl;
	}*/
}

void coloring(const cv::Mat1i& src, cv::Mat3b& dst) {
	CV_Assert(!src.empty());
	dst = cv::Mat3b::zeros(src.rows, src.cols);

	int numLabel = 0;
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (numLabel < src(y, x)) {
				numLabel = src(y, x);
			}
		}
	}

	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			if (src(y, x) != 0) {
				int hue = 180 * (src(y, x) - 1) / numLabel;
				dst(y, x) = cv::Vec3b(hue, 255, 255);
			}
		}
	}
	cv::cvtColor(dst, dst, cv::COLOR_HSV2BGR);
}

void drawRect(const cv::Mat3b& src, const cv::Mat1b& two, cv::Mat3b& draw, const uchar color)
{
	int xmin = 847;
	int xmax = 0;
	int ymin = 479;
	int ymax = 0;
	draw = src.clone();
	for (int y = 0; y < two.rows; ++y) {
		for (int x = 0; x < two.cols; ++x) {
			if (two(y, x) == 255) {
				if (y > ymax) ymax = y;
				else if (y < ymin)ymin = y;
				if (x > xmax) xmax = x;
				else if (x < xmin) xmin = x;
			}

		}
	}
	for (int y = 0; y < 2; ++y) {
		for (int x = xmin; x < xmax; ++x) {
			draw(ymin, x) = color;
			draw(ymax, x) = color;
		}
	}
	for (int x = 0; x < 2; ++x) {
		for (int y = ymin; y < ymax; y++) {
			draw(y, xmin) = color;
			draw(y, xmax) = color;
		}
	}
}

void labeldraw(const cv::Mat3b& src, const cv::Mat1b& two, cv::Mat3b& draw)
{

	cv::Mat1i temp;
	cv::Mat1b tem2;
	labeling(two, temp);
	int a = 0;
	draw = src.clone();
	for (int i = 1; i < 50; i++) {

		int xmin = 847;
		int xmax = 0;
		int ymin = 479;
		int ymax = 0;
		for (int y = 0; y < temp.rows; ++y) {
			for (int x = 0; x < temp.cols; ++x) {
				if (temp(y, x) == i) {
					if (y > ymax) ymax = y;
					else if (y < ymin)ymin = y;
					if (x > xmax) xmax = x;
					else if (x < xmin) xmin = x;
				}

			}
		}

		int area = 0;
		area = (ymax - ymin) * (xmax - xmin);
		
		if (bgrh(src, temp, i) > 300) {
			for (int y = 0; y < 4; ++y) {
				for (int x = xmin; x < xmax; ++x) {
					draw(ymin, x) = cv::Vec3b(0, 0, 255);
					draw(ymax, x) = cv::Vec3b(0, 0, 255);
				}
			}
			for (int x = 0; x < 4; ++x) {
				for (int y = ymin; y < ymax; y++) {
					draw(y, xmin) = cv::Vec3b(0, 0, 255);
					draw(y, xmax) = cv::Vec3b(0, 0, 255);
				}
			}
		}
		else if (bgrv(src, temp, i) < 110) {
			for (int y = 0; y < 4; ++y) {
				for (int x = xmin; x < xmax; ++x) {
					draw(ymin, x) = cv::Vec3b(0, 255, 0);
					draw(ymax, x) = cv::Vec3b(0, 255, 0);
				}
			}
			for (int x = 0; x < 4; ++x) {
				for (int y = ymin; y < ymax; y++) {
					draw(y, xmin) = cv::Vec3b(0, 255, 0);
					draw(y, xmax) = cv::Vec3b(0, 255, 0);
				}
			}
		}
		else {
			if (peri(temp, i,area)>=1.1) {
				for (int y = 0; y < 4; ++y) {
					for (int x = xmin; x < xmax; ++x) {
						draw(ymin, x) = cv::Vec3b(0, 255, 255);
						draw(ymax, x) = cv::Vec3b(0, 255, 255);
					}
				}


				for (int x = 0; x < 4; ++x) {
					for (int y = ymin; y < ymax; y++) {
						draw(y, xmin) = cv::Vec3b(0, 255, 255);
						draw(y, xmax) = cv::Vec3b(0, 255, 255);
					}
				}
			}
			else {
				for (int y = 0; y < 4; ++y) {
					for (int x = xmin; x < xmax; ++x) {
						draw(ymin, x) = cv::Vec3b(0, 165, 255);
						draw(ymax, x) = cv::Vec3b(0, 165, 255);
					}
				}


				for (int x = 0; x < 4; ++x) {
					for (int y = ymin; y < ymax; y++) {
						draw(y, xmin) = cv::Vec3b(0, 165, 255);
						draw(y, xmax) = cv::Vec3b(0, 165, 255);
					}
				}
			}

		}
	}
}