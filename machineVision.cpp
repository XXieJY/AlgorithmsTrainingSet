// MachineVision.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

int main(int argc, char** argv)
{
        string str;
        for (int i = 1; i <= 53; ++i) {
                str = "../resources/SE/1/2/" + to_string(i) + ".bmp";
                src = imread(str, IMREAD_GRAYSCALE);
                cout << str << endl;

                //尝试计算灰度直方图
                //进行源图像对比度增强
                ////尝试对数校正
                //Mat dst_log = Mat::zeros(src.size(), src.type());
                //add(src, Scalar(1.0), src);  //计算 r+1
                //src.convertTo(src, CV_32F);  //转化为32位浮点型
                //log(src, dst_log);            //计算log(1+r)
                //float c = 0.2;
                //dst_log = c * dst_log;
                ////归一化处理
                //normalize(dst_log, dst_log, 0, 255, NORM_MINMAX);
                //convertScaleAbs(dst_log, dst_log);


                //尝试laplace对比度增强,首先应该进行噪声消除
                Mat dst_laplace;
                Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 6, -1, 0, -1, 0);
                filter2D(src, dst_laplace, src.depth(), kernel);

                ////尝试gamma校正
                //// build look up table
                //unsigned char lut[256];
                //
                //double fGamma = 0.2;
                //for (int i = 0; i < 256; i++)
                //{
                //	lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
                //}
                //Mat dst_gamma = src.clone();
                //const int channels = dst_gamma.channels();
                //switch (channels)
                //{
                //case 1:
                //{
                //	MatIterator_<uchar> it, end;
                //	for (it = dst_gamma.begin<uchar>(), end = dst_gamma.end<uchar>(); it != end; it++)
                //		//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;
                //		*it = lut[(*it)];
                //	break;
                //}
                //case 3:
                //{
                //	MatIterator_<Vec3b> it, end;
                //	for (it = dst_gamma.begin<Vec3b>(), end = dst_gamma.end<Vec3b>(); it != end; it++)
                //	{
                //		//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;
                //		//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;
                //		//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;
                //		(*it)[0] = lut[((*it)[0])];
                //		(*it)[1] = lut[((*it)[1])];
                //		(*it)[2] = lut[((*it)[2])];
                //	}
                //	break;
                //}
                //}

                //new approaches 1: 阈值化和轮廓提取，然后计算缺陷与轮廓的交集从而标注缺陷是否在电路上。

                //阈值化ostu
                Mat dst_binary;
                cv::threshold(dst_laplace, dst_binary, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
                //namedWindow("ostu", WINDOW_FREERATIO);
                //imshow("ostu", dst_binary);


                //形态学处理,先把噪声滤波，然后模糊，最后形态学处理
                GaussianBlur(dst_binary, dst_binary, Size(3, 3), 0, 0);
                medianBlur(dst_binary, dst_binary, 3);
                //检查滤波情况
                /*                namedWindow("smoothing", WINDOW_FREERATIO);
                imshow("smoothing", dst_binary)*/;
                Mat dst_morph;
                cv::Mat element(3, 3, CV_8U, Scalar(1));
                morphologyEx(dst_binary, dst_morph, cv::MORPH_CLOSE, element);
                ///*                namedWindow("dilate", WINDOW_FREERATIO);
                //                imshow("dilate", dst_morph)*/;

                //二值化
                threshold(dst_morph, dst_morph, 100, 255, CV_THRESH_BINARY);
                dilate(dst_morph, dst_morph, Mat(), Point(-1, -1), 2, 1, 1);
                //namedWindow("thresh_binary", WINDOW_FREERATIO);
                //imshow("thresh_binary", dst_morph);
                string ssout = "output" + to_string(i) + ".bmp";

                imwrite(ssout, dst_morph);



                ////************expired approaches,针对电路板轮廓线判断缺陷是否在电路上的方法 不太可行 因为 轮廓线检测不太完美，受噪声干扰太强。************

                //   //尝试绘电路板轮廓的方法
                ////勾勒出电路区域，对于小的缺陷 判断其是否在区域内 对于大的缺陷  有可能形成阻断电路的特征，此时应该直接判断其与电路的位置关系。
                //Mat contoursImg = src.clone();
                //Mat contoursImage(dst_morph.rows, dst_morph.cols, CV_8U, Scalar(0));
                //Mat drawing = Mat::zeros(dst_morph.size(), CV_8UC3);
                //vector<vector<Point>> contours;
                //vector<Vec4i> hierarchy;
                //RNG rng(12345);
                //findContours(dst_morph, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                ////findContours(dst_morph, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
                //for (int i = 0; i < contours.size(); i++) {
                //	Scalar color = Scalar(255, 255, 255);
                //	drawContours(contoursImg, contours, i, color, 1, 4, hierarchy);
                //	drawContours(contoursImage, contours, i, color, 1, 4, hierarchy);
                //}
                //namedWindow("contours", WINDOW_GUI_EXPANDED);
                //imshow("contours", contoursImg);
                //namedWindow("purelycontours", WINDOW_FREERATIO);
                //imshow("purelycontours", contoursImage);

                ////模板掩盖
                //dst_morph = dst_morph / 255;
                ////src = src.mul(dst_morph);

                //namedWindow("coveredimg", WINDOW_FREERATIO);
                //imshow("coveredimg", src);


                // 检测电路板上blob缺陷
                // 设置blob检测器的参数params
                //               Mat dst_blob = Mat::zeros(src.size(), src.type());
                //               cv::SimpleBlobDetector::Params params;
                //               //使用圆度检测blob
                //               //params.filterByCircularity = true;
                //               //params.minCircularity = 0.1;
                //               //使用面积检测blob
                //               params.filterByConvexity = true;
                //               params.minConvexity = 0.1;
                //               params.minThreshold = 0;
                //               params.maxThreshold = 255;
                //               params.filterByInertia = true;
                //               params.minInertiaRatio = 0.01;
                //               params.filterByArea = true;
                //               params.minArea = 20;
                //               params.filterByCircularity = true;
                //               params.minCircularity = 0.1;
                //               Ptr<SimpleBlobDetector> detector2 = SimpleBlobDetector::create(params);
                //               // Storage for blobs
                //               std::vector<KeyPoint> keypoints;
                //               // Detect blobs
                //               detector2->detect(src, keypoints);
                //               namedWindow("contours", WINDOW_FREERATIO);
                //               drawKeypoints(src, keypoints, dst_blob, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                ///*               imshow("contours", dst_blob);*/



                //	// 设置blob检测器的参数params
                //	cv::SimpleBlobDetector::Params params;
                //	//使用圆度检测blob
                //	params.filterByCircularity = true;
                //	params.minCircularity = 0.1;
                //	params.filterByArea = true;
                //	params.minArea = 25;
                //	params.filterByColor = true;
                //	params.blobColor = 0;
                //	params.filterByConvexity = true;
                //	params.minConvexity = 0.77;
                //
                //	//检测二值图的blob
                //	cv::SimpleBlobDetector::Params params2;
                //	//使用圆度检测blob
                //	params2.filterByCircularity = true;
                //	params2.minCircularity = 0.1;
                //	params2.filterByInertia = true;
                //	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
                //	Ptr<SimpleBlobDetector> detector2 = SimpleBlobDetector::create(params2);
                //	// Storage for blobs
                //	std::vector<KeyPoint> keypoints;
                //	std::vector<KeyPoint> keypoints2;
                //	// Detect blobs
                //	detector->detect(contoursImg, keypoints);
                //	detector2->detect(src_gray, keypoints2);
                //	keypoints.insert(keypoints.end(), keypoints2.begin(), keypoints2.end());
                //	string temp;
                //	for (std::vector<cv::KeyPoint>::iterator blobIterator = keypoints.begin(); blobIterator != keypoints.end(); blobIterator++) {
                //		Point2f coordiante = blobIterator->pt;
                //		float s = blobIterator->size;
                //		temp = to_string(s) + " pixels at " + to_string(coordiante.x) + ", " + to_string(coordiante.y);
                //		cout << temp << endl;
                //		//putText(contoursImg, temp, coordiante, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
                //	}
                //	namedWindow("defects", WINDOW_GUI_EXPANDED);
                //	drawKeypoints(contoursImg, keypoints, src, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                //	//drawKeypoints(contoursImg, keypoints2, src, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                //	imshow("defects", src);
                //
                //	//void thresh_callback(int, void*)
                //	//{
                //	//	Mat canny_output;
                //	//	vector<vector<Point> > contours;
                //	//	vector<Vec4i> hierarchy;
                //	//	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
                //	//	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
                //	//	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
                //	//	for (size_t i = 0; i< contours.size(); i++)
                //	//	{
                //	//		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
                //	//		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
                //	//	}
                //	//	namedWindow("Contours", WINDOW_AUTOSIZE);
                //	//	imshow("Contours", drawing);
                ////}
                //


                //new approach 2: 检测电路骨架的方法。 具体内容还没想好。

        }

        waitKey(0);


        return(0);
}
