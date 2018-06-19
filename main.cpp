// PhotoMontage.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "PhotoMontage.h"
#include <string>
using namespace cv;

Mat read(String path){
    Mat res=imread(path);
    Mat out;
    resize(res, out, Size(res.cols/2,res.rows/2),INTER_AREA);
    return out;
}
int main(int argc, char* argv[])
{
    std::vector<cv::Mat> Images;
    ///请在此处读入N 张照片,例子如下:
    std::string fpath="/Users/cheriewang/Desktop/蒙太奇/PhotoMontage/";
    Images.push_back(read("0.JPG"));
    Images.push_back(read("1.JPG"));
    Images.push_back(read("2.JPG"));
    Images.push_back(read("3.JPG"));
    Images.push_back(read("4.JPG"));
    
    ///请在此处读入N 张Label,注意这些label里面,白色的代表用户的笔触,黑色的代表背景,例子如下:
    std::vector<cv::Mat> Labels;
    Labels.push_back(read("0.BMP"));
    Labels.push_back(read("1.BMP"));
    Labels.push_back(read("2.BMP"));
    Labels.push_back(read("3.BMP"));
    Labels.push_back(read("4.BMP"));
    
    
    
    ///set all the labels to undefined
    cv::Mat Label(Images[0].rows, Images[0].cols, CV_8SC1);
    Label.setTo(PhotoMontage::undefined);
    ///set the labels according to the Labels read
    int height = Images[0].rows;
    int width = Images[0].cols;
    for (int label_idx = 0 ; label_idx < Images.size(); label_idx++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0 ; x < width; x++)
            {
                if (Labels[label_idx].at<cv::Vec3b>(y,x)(0) > 0)
                {
                    Label.at<uchar>(y,x) = label_idx;
                }
            }
        }
    }
    
    ///Run photomontage
    PhotoMontage PM;
    PM.Run(Images,Label);
    
    return 0;
}

