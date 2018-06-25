
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "PhotoMontage.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <iostream>
using namespace cv;
using namespace std;

Mat read(String path){    
    printf("%s\n",path.c_str() );

    Mat res=imread(path);
    imshow("s",res);
    // printf("%s\n",path.c_str() );
    int ratio=1;
    cout<<path<<" "<<res.cols/ratio<<","<<res.rows/ratio<<endl;
    Mat out;
    resize(res, out, Size(res.cols/ratio,res.rows/ratio),INTER_AREA);

    return out;
}

int main(int argc, char* argv[])
{
    std::vector<cv::Mat> Images;
    std::vector<cv::Mat> Labels;
    int mode = 0;

    ///请在此处读入N 张照片,例子如下:
    cv::Mat Label;
  

    mode = atoi(argv[1]);

    if(mode != 0 && mode != 3 ){
        ///set all the labels to undefined
        for(int i=2;i<argc;i++){
            Images.push_back(read(argv[i]));
        }
        Label = Mat(Images[0].rows, Images[0].cols, CV_8SC1);
        Label.setTo(PhotoMontage::undefined);
        ///set the labels according to the Labels read
    }
    else{
        int numOfInput = (argc-2)/2; // size of images and labels.
        for(int i=2 ; i < 2+numOfInput ; i++){
            Images.push_back(read(argv[i]));
        }
        for(int i=2+numOfInput ; i < argc ; i++){
            if(strcmp(argv[i],"PLATE") == 0){
                Mat tempPlate(Images[0].rows, Images[0].cols, CV_8SC1);
                tempPlate.setTo(1); 
                Labels.push_back(tempPlate);
                cout<<"plate label pushed"<<endl;
            }
            else if(strcmp(argv[i],"UNDEFINED") == 0){
                Mat tempPlate(Images[0].rows, Images[0].cols, CV_8SC1);
                tempPlate.setTo(0);
                Labels.push_back(tempPlate);
                cout<<"undefined pushed"<<endl;
            }
            else{
                Labels.push_back(read(argv[i]));
                cout<<"label pushed"<<endl;
            }
        }

        Label = Mat(Images[0].rows, Images[0].cols, CV_8SC1);
        Label.setTo(PhotoMontage::undefined);
        int height = Images[0].rows;
        int width = Images[0].cols;
        FILE *fp = fopen("index.txt","w+");
        for (int label_idx = 0 ; label_idx < Images.size(); label_idx++)
        {
            // stringstream stream;  
            // stream << label_idx;
            // string windowName = stream.str();
            //imshow(windowName,Labels[label_idx]);
            for (int y = 0; y < height; y++)
            {
                for (int x = 0 ; x < width; x++)
                {
                    if (Labels[label_idx].at<cv::Vec3b>(y,x)(0) > 0)
                    {
                        
                        //assert(label_idx!=0);
                        Label.at<uchar>(y,x) = label_idx;
                        if(label_idx!=1){
                             fprintf(fp, "x:%d,y%d:,index:%d\n",x,y,label_idx );
                        }
                    }
                }
            }
        }
    }


     imshow("label",Label);
         waitKey(0); 


    
    PhotoMontage PM;
    time_t start = std::time(NULL);
    PM.Run(Images,Label,ERASE );
    time_t end = std::time(NULL);
    std::cout<<end-start<<std::endl;
    FILE * fp = fopen("finish.txt","w+");
    fprintf(fp, "%d", int(end-start));
    fprintf(fp, "done\n" );
    return 0;

    ///set all the labels to undefined
    // cv::Mat Label(Images[0].rows, Images[0].cols, CV_8SC1);
    // Label.setTo(PhotoMontage::undefined);


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
}

