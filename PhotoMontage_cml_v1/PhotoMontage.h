#pragma once
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/flann/flann.hpp"

#define USER_SPECIFY 0
#define MAX_LUMIN 1
#define MIN_LUMIN 2
#define ERASE 3
#define MAX_LIKEHOOD 4
#define MIN_LIKEHOOD 5
#define CONTRAST 6
#define MAX_DIFF 7
#define USER_SPECIFY_P 8




class PhotoMontage
{
public:
    void BuildSolveMRF(const std::vector<cv::Mat> & Images, const cv::Mat & Label,int mode);
    void VisResultLabelMap(const cv::Mat & ResultLabel, int n_label);
    void VisCompositeImage(const cv::Mat & ResultLabel, const std::vector<cv::Mat> & Images);
    void BuildSolveGradientFusion(const std::vector<cv::Mat> & Images, const cv::Mat & ResultLabel);
    
    static void SolveChannel( int channel_idx, int constraint, const cv::Mat &color_gradient_x, const cv::Mat &color_gradient_y , cv::Mat & output  );
    
    void GradientAt(const cv::Mat & Image, int x, int y, cv::Vec3f & grad_x, cv::Vec3f & grad_y);
    static void* thread_function(void *arg_raw);
    
public:

    void Run(const std::vector<cv::Mat> & Images, const cv::Mat & Label,int mode=USER_SPECIFY,double user_coe = 0);
private:
    cv::flann::Index * AddInertiaConstraint( const cv::Mat & Label );
public:
    
    pthread_t pid1,pid2,pid3;
    
    
    struct thread_param
    {
    public:
        int id;
        int channel_idx;
        int constraint;
        const cv::Mat &color_gradient_x;
        const cv::Mat &color_gradient_y ;
        cv::Mat & output;
        
        
        //  thread_param(int id,int channel_idx,int constraint,const cv::Mat &color_gradient_x,const cv::Mat &color_gradient_y,cv::Mat & output ){
        //     this->id = id;
        //     this->channel_idx = channel_idx;
        //     this->constraint = constraint;
        //     this->color_gradient_x = color_gradient_x;
        //     this->color_gradient_y = color_gradient_y;
        //     this->output = output;
        // }
    };
    
    enum
    {
        undefined = -1,
        plate = 1,
    };
};
