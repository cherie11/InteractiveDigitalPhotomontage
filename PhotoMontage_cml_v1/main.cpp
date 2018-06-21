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
#include <iostream>
using namespace std;

Mat read(String path){
    Mat res=imread(path);
    printf("%s\n",path.c_str() );
    cout<<path<<endl;
    Mat out;
    resize(res, out, Size(res.cols/2,res.rows/2),INTER_AREA);
    return out;
}
int main(int argc, char* argv[])
{
    // int num_image = (argc-1)/2;
    std::vector<cv::Mat> Images;
    std::vector<cv::Mat> Labels;

    ///请在此处读入N 张照片,例子如下:
    // std::string fpath="/Users/apple/Desktop/计算摄影学/bug/";
    for(int i=1;i<argc;i++){
        Images.push_back(read(argv[i]));

    }
    // for(int i=num_image+1;i<argc;i++){
    //      Labels.push_back(read(argv[i]));
    // }
   
    
    ///请在此处读入N 张Label,注意这些label里面,白色的代表用户的笔触,黑色的代表背景,例子如下:
  
    
    
    
    ///set all the labels to undefined
    cv::Mat Label(Images[0].rows, Images[0].cols, CV_8SC1);
    Label.setTo(PhotoMontage::undefined);
    ///set the labels according to the Labels read


    // int height = Images[0].rows;
    // int width = Images[0].cols;
    // for (int label_idx = 0 ; label_idx < Images.size(); label_idx++)
    // {
    //     for (int y = 0; y < height; y++)
    //     {
    //         for (int x = 0 ; x < width; x++)
    //         {
    //             if (Labels[label_idx].at<cv::Vec3b>(y,x)(0) > 0)
    //             {
    //                 Label.at<uchar>(y,x) = label_idx;
    //             }
    //         }
    //     }
    // }
    
    ///Run photomontage
    PhotoMontage PM;
    PM.Run(Images,Label,7);
    FILE * fp = fopen("finish.txt","w+");
    fprintf(fp, "done\n" );
    return 0;
}

