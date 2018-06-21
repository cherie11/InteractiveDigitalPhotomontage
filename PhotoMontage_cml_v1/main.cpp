// PhotoMontage.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "PhotoMontage.h"
#include <string>
#include <ctime>
using namespace cv;
using namespace std;

#define DEBUG 0
Mat read(String path){
    Mat res=imread(path);
    printf("%s\n",path.c_str() );
    int ratio=1;
    cout<<path<<" "<<res.cols/ratio<<","<<res.rows/ratio<<endl;
    Mat out;
    resize(res, out, Size(res.cols/ratio,res.rows/ratio),INTER_AREA);
    return out;
}

int main(int argc, char* argv[])
{
    std::vector<cv::Mat> Images;
    ///请在此处读入N 张照片,例子如下:
    
    /*For auto max likelihood*/
    std::string fpath="./img/cathedral/";
    Images.push_back(read(fpath+"0.jpg"));
    Images.push_back(read(fpath+"1.jpg"));
    Images.push_back(read(fpath+"2.jpg"));
    Images.push_back(read(fpath+"3.jpg"));
    Images.push_back(read(fpath+"4.jpg"));
    
    /*for video composite*/
    // std::string fpath="./img/video/";
    // Images.push_back(read(fpath+"0.png"));
    // Images.push_back(read(fpath+"3.png"));
    // Images.push_back(read(fpath+"1.png"));
    // Images.push_back(read("./img/result/video/max_likelihood背景图.png"));
    
    ///请在此处读入N 张Label,注意这些label里面,白色的代表用户的笔触,黑色的代表背景,例子如下:
    std::vector<cv::Mat> Labels;
#if DEBUG
    std::string fpath="./img/family/";
    Images.push_back(read(fpath+"0.JPG"));
    Images.push_back(read(fpath+"1.JPG"));
    Images.push_back(read(fpath+"2.JPG"));
    Images.push_back(read(fpath+"3.JPG"));
    Images.push_back(read(fpath+"4.JPG"));
    
    Labels.push_back(read(fpath+"0.BMP"));
    Labels.push_back(read(fpath+"1.BMP"));
    Labels.push_back(read(fpath+"2.BMP"));
    Labels.push_back(read(fpath+"3.BMP"));
    Labels.push_back(read(fpath+"4.BMP"));
#endif
    
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
    PhotoMontage PM;
    time_t start = std::time(NULL);
    PM.Run(Images,Label,MAX_LIKEHOOD );
    time_t end = std::time(NULL);
    std::cout<<end-start<<std::endl;
    FILE * fp = fopen("finish.txt","w+");
    fprintf(fp, "%d", int(end-start));
    fprintf(fp, "done\n" );
    return 0;
}

