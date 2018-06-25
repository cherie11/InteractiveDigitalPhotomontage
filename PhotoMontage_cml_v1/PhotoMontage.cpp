//#include "stdafx.h"
#include "PhotoMontage.h"
#include "GCoptimization.h"
#include "Eigen/Sparse"
#include <iostream>
#include "Eigen/SparseCholesky"
#include <pthread.h>
#include <cmath>

// #include "Eigen/CholmodSupport"
// #include "Eigen/SparseExtra"

using namespace cv;
using namespace std;

const double large_penalty = 1000.0;
Mat _data;
int currentMode = 0;
double user_coefficient = 0;
double euc_dist(const Vec3b & a, const Vec3b & b)
{
    Vec3b double_diff = a - b;
    return sqrt( double_diff[0] * double_diff[0] + double_diff[1] * double_diff[1] + double_diff[2] * double_diff[2]);
}

struct __ExtraData
{
    std::vector<cv::Mat> Images;
    cv::Mat Label;
    cv::flann::Index * kdtree;
    
};

/*--------------Data penalty-------------*/
/*************************************************
 Description:
 Calculate data penalty by the distance to the image objective.
 We use
 (1)Designated image:   ----for user defined stroke
 0 if L(p) = u, where Su is a user-specified source image,
 a large penalty otherwise.
 (2)Minimum (maximum) luminance ----for auto blending
 Distance in luminance from the minimum (maximum) luminance
 pixel in a pixels span.
 (3)Erase : the color most different from that of the current composite
 Input:
 p: coordinate
 l: label to be verified
 data: struct of images and labels
 Return:
 penalty for point p
 *************************************************/


double dataFn_user(int p, int l, void *data) {
    //Designated image data function
    
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    if (Label.at<char>(y,x) != PhotoMontage::undefined) // user specified
    {
        if ( Label.at<char>(y,x)!=0&&Label.at<char>(y,x) == l)   // 0 if u=L(p)
        {
            return 0.0;
        }
        else
        {
            return large_penalty;
        }
    }
    else
    {
        return large_penalty;
    }
    
}

double dataFn_max_likelihood(int p, int l, void *data) {
    //Max Likelihood
    
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    // 20 bins for histgram
    const int bin_num=30;
    int bin_rgb[3];
    
    int user_idx[3];
    
    
    float delta=255.0/bin_num;
    cv::Mat &  user_img=img_vec[l];
    for(int i=0;i<3;i++){
        bin_rgb[i]=0;
        user_idx[i]=int(floor(user_img.at<Vec3b>(y,x)[i]/delta));
    }
    
    
    
    for(auto p: img_vec){
        for(int i=0;i<3;i++){
            int idx=floor(p.at<Vec3b>(y,x)[i]/delta);
            if(idx==user_idx[i]){
                bin_rgb[i]+=1;
            }
        }
    }
    
    float bin_avg=(bin_rgb[0]+bin_rgb[1]+bin_rgb[2])/3.0;
    if(bin_avg==img_vec.size()){
        return 0;
    }
    return (1-bin_avg/img_vec.size())*large_penalty;   // make label approach to the max_likelihood
    
}


double dataFn_min_likelihood(int p, int l, void *data) {
    //Max Likelihood
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    double max_lumin=0;
    double l_lumin=0;
    
    // 20 bins for histgram
    const int bin_num=20;
    int bin_rgb[3];
    
    int user_idx[3];
    
    
    float delta=255.0/bin_num;
    const cv::Mat & user_img=img_vec[l];
    for(int i=0;i<3;i++){
        bin_rgb[i]=0;
        user_idx[i]=int(floor(user_img.at<Vec3b>(y,x)[i]/delta));
    }
    
    for(auto p: img_vec){
        for(int i=0;i<3;i++){
            int idx=floor(p.at<Vec3b>(y,x)[0]/delta);
            if(idx==user_idx[i]){
                bin_rgb[i]+=1;
            }
        }
    }
    float bin_avg=(bin_rgb[0]+bin_rgb[1]+bin_rgb[2])/3.0;

    return (bin_avg/img_vec.size())*large_penalty;     // make label approach to the min_likelihood
    
}

double dataFn_max_lumin(int p, int l, void *data) {
    //Max Luminance selection
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    double max_lumin=0;
    double l_lumin=0;
    int cnt=0;
    
    
    
    for(auto p: img_vec){
        //YUV : V=0.299*R+0.587*G+0.114*B
        double lumin= 0.299*p.at<Vec3b>(y,x)[2]+0.587*p.at<Vec3b>(y,x)[1]+0.114*p.at<Vec3b>(y,x)[0];
        if(cnt++==l){
            l_lumin=lumin;
        }
        max_lumin=lumin>max_lumin?lumin:max_lumin;
    }
    
    return (max_lumin-l_lumin)*10;   // make label approach to the max_lumin
    
    
    
    
}

double dataFn_min_lumin(int p, int l, void *data) {
    //Min Luminance selection
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    double min_lumin=0;
    double l_lumin=0;
    int cnt=0;
    
    
    
    for(auto p: img_vec){
        //YUV : V=0.299*R+0.587*G+0.114*B
        double lumin= 0.299*p.at<Vec3b>(y,x)[2]+0.587*p.at<Vec3b>(y,x)[1]+0.114*p.at<Vec3b>(y,x)[0];
        if(cnt++==l){
            l_lumin=lumin;
        }
        min_lumin=lumin<min_lumin?lumin:min_lumin;
    }
    
    return (l_lumin-min_lumin)*10;   // make label approach to the max_lumin
    
    
    
    
}


double dataFn_erase(int p, int l, void *data) {
    //Erase mode for max defferent pixel
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    double max_pixel=0;
    double l_pixel=0;
    int cnt=0;
    double penalty=0;
    double dis,max_dis=0;
    

    if (Label.at<char>(y,x) != PhotoMontage::undefined) // user specified
    {
       //  for(auto p: img_vec){
       //  //std::cout<<img_vec[l].at<Vec3b>(y,x)<<std::endl;
       //      dis=euc_dist(img_vec[Label.at<char>(y,x)].at<Vec3b>(y,x),p.at<Vec3b>(y,x));
       //      assert(dis>=0);
       //      max_dis=dis>max_dis?dis:max_dis;
       //  }
       //  dis=euc_dist(img_vec[Label.at<char>(y,x)].at<Vec3b>(y,x), img_vec[l].at<Vec3b>(y,x));
       //  assert(max_dis>=dis);
    

       //  cv::Vec3b u_pixel=img_vec[Label.at<char>(y,x)].at<Vec3b>(y,x); // user specified label
       //  cv::Vec3b l_pixel=img_vec[l].at<Vec3b>(y,x);   //label by experiment
        
       //  penalty=max_dis-dis;
       // // std::cout<<penalty<<std::endl;
       //  return penalty*10000;   // make label approach


        if (Label.at<char>(y,x) != l)   // 0 if u=L(p)
        {
            return 0.0;
        }
        else
        {
            return large_penalty/5;
        }
    }
    else
    {   

        return large_penalty/5;
    }
    

 }

double dataFn_max_diff(int p, int l, void *data) {
    //Max Difference selection
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);
    
    double max_dis=0;
    double dis;
    
    for(auto p: img_vec){
        //std::cout<<img_vec[l].at<Vec3b>(y,x)<<std::endl;
        dis=norm(img_vec.back().at<Vec3b>(y,x),p.at<Vec3b>(y,x));
        assert(dis>=0);
        max_dis=dis>max_dis?dis:max_dis;
    }
    dis=norm(img_vec.back().at<Vec3b>(y,x), img_vec[l].at<Vec3b>(y,x));
    assert(max_dis>=dis);
    //std::cout<<(max_dis-dis)*100<<std::endl;
    return (max_dis-dis)*50;   // make label approach to the max_diff
    
    
}

      
      
      
      
std::vector<Mat> GaussianBlurImages;
double dataFn_contrast(int p, int l, void *data) {
    //Erase mode for max contrast pixel
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    //cv::flann::Index * ptr_kdtree = ptr_extra_data->kdtree;
        cv::Mat & Label = ptr_extra_data->Label;

    std::vector<cv::Mat> & img_vec = ptr_extra_data->Images;
    
    int width = Label.cols;
    int height = Label.rows;
    
    int y = p / width;
    int x = p % width;
    
    assert(l >= 0);

    double diff = 0;
    // cout<<"here"<<endl;

    for(int i=0; i < img_vec.size();i++){
        if(i != l){
            continue;
        }
        // Mat tmp3,tmp5;
        // GaussianBlur(img_vec[i],tmp3,Size(3,3),0);
        // GaussianBlur(img_vec[i],tmp5,Size(5,5),0);
        if(i == l){
            diff += cv::norm(GaussianBlurImages[i].at<Vec3b>(y,x),img_vec[i].at<Vec3b>(y,x));
        }
        //size must be odd
    }
    
    return -10*diff;
}



void cal_grad(const Mat & image,int x,int y,double grad[]){
    //return 6D grad with X,Y direction on all channel
    int flag=0;
    double l,ld,r,rd,ru,lu,u,d;
    l=ld=r=rd=ru=lu=u=d=0;
    for(int i =0;i<image.channels();i++){
        if(x==0){
            l=0;
            ld=0;
            lu=0;
        }
        else if(x==image.cols-1){
            r=0;
            rd=0;
            ru=0;
        }
        else{
            l=image.at<Vec3b>(y, x-1)[i];
            r=image.at<Vec3b>(y, x+1)[i];
            flag=1;
        }
        if (y==0){
            u=0;
            lu=0;
            ru=0;
        }
        else if(y==image.rows-1){
            d=0;
            ld=0;
            rd=0;
        }
        else{
            if(flag==1){
                lu=image.at<Vec3b>(y-1, x-1)[i];
                ld=image.at<Vec3b>(y+1, x-1)[i];
                ru=image.at<Vec3b>(y-1, x+1)[i];
                rd=image.at<Vec3b>(y+1, x+1)[i];
                
            }
            u=image.at<Vec3b>(y-1, x)[i];
            d=image.at<Vec3b>(y+1, x)[i];
            
            
        }
        
        grad[i]=ru+2*r+rd-2*l-ld-lu;
        grad[i+3]=lu+2*u+ru-ld-2*d-rd;
        
    }
    return ;
    
}

/*************************************************
 
 Description:
 Define interaction penalty Ci over all pairs of neighboring pixels p, q
 Seam objective to be 0 if L(p) = L(q). Otherwise, we implement following calculation:
 (1)Matching color
 ||S_i(p)-S_i(q)|| + ||S_j(p)-S_j(q)||
 (2)Matching color & gradient
 ||G_i(p)-G_i(q)|| + ||G_j(p)-G_i(q)||
 i is ith image,p&q are different point,S is pixel,G is gradient(by Sobel)
 Input:
 p: seam pixel for img A
 q: seam pixel for img B
 lp: label for p
 lq: label for q
 data: struct of images and labels
 Return:
 smooth value
 *************************************************/
double smoothFn(int p, int q, int lp, int lq, void * data)
{
#if 1
    if (lp == lq)
    {
        return 0.0;
    }
    
    assert(lp != lq);
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    std::vector<cv::Mat> & Images = ptr_extra_data->Images;
    int n_label = Images.size();
    assert(lp < n_label && lq < n_label);
    
    int width = Label.cols;
    int height = Label.rows;
    
    int yp = p / width;
    int xp = p % width;
    int yq = q / width;
    int xq = q % width;
    
    double X_term1 = euc_dist(Images[lp].at<Vec3b>(yp,xp), Images[lq].at<Vec3b>(yp,xp));
    double X_term2 = euc_dist(Images[lp].at<Vec3b>(yq,xq), Images[lq].at<Vec3b>(yq,xq));
    assert(X_term1 + X_term1 >= 0.0);
    //int ch=Images[lp].channels();
    double grad_p[6];
    double grad_q[6];
    for(int i=0;i<6;i++){
        grad_p[i]=0;
        grad_q[i]=0;
    }
    cal_grad(Images[lp], xp, yp,grad_p);
    cal_grad(Images[lq], xp, yp,grad_q);
    double diff_grad=0;
    double diff_grad1=0;
    for(int k=0;k<6;k++){
        diff_grad+=pow(grad_p[k]-grad_q[k],2);
    }
    diff_grad=sqrt(diff_grad);
    
    cal_grad(Images[lp], xq, yq,grad_p);
    cal_grad(Images[lq], xq, yq,grad_q);
    
    for(int k=0;k<6;k++){
        diff_grad1+=pow(grad_p[k]-grad_q[k],2);
    }
    
    diff_grad1=sqrt(diff_grad1);
    int coefficient = 2;
    if(user_coefficient > 0){
        coefficient*=user_coefficient;
    }
    else{
        if(currentMode == 0 || currentMode == 8){
            coefficient*=2.5;
        }
        else if(currentMode == 3){
            coefficient*=1;
        }
        else if(currentMode == 6){
            coefficient *=5 ;
        } 
        else if (currentMode == 4 || currentMode == MAX_DIFF){
            coefficient *= 10;
        }
    }
    
    //std::cout<<(X_term1 + X_term2)<<" "<<diff_grad<<"  "<<diff_grad1<<std::endl;
    return ((X_term1 + X_term2) * coefficient + diff_grad * coefficient + diff_grad1 * coefficient);
#endif
    
    
#if 0
    if (lp == lq)
    {
        return 0.0;
    }
    
    assert(lp != lq);
    __ExtraData * ptr_extra_data = (__ExtraData *)data;
    cv::Mat & Label = ptr_extra_data->Label;
    std::vector<cv::Mat> & Images = ptr_extra_data->Images;
    int n_label = Images.size();
    assert(lp < n_label && lq < n_label);
    
    int width = Label.cols;
    int height = Label.rows;
    
    int yp = p / width;
    int xp = p % width;
    int yq = q / width;
    int xq = q % width;
    //calculate the distance of pixel value
    double X_term1 = euc_dist(Images[lp].at<Vec3b>(yp,xp), Images[lq].at<Vec3b>(yq,xq));
    double X_term2 = euc_dist(Images[lp].at<Vec3b>(yq,xq), Images[lq].at<Vec3b>(yp,xp));
    assert(X_term1 + X_term1 >= 0.0);
    return (X_term1 + X_term2);
    
    
#endif
}


void PhotoMontage:: Run( const std::vector<cv::Mat> & Images, const cv::Mat & Label,int mode,double user_coe)
{
    assert(Images[0].rows == Label.rows);
    assert(Images[0].cols == Label.cols);
    currentMode = mode;   
    user_coefficient = user_coe; 
    cout<<"mode is:"<<mode<<endl;
    BuildSolveMRF( Images, Label,mode);
    // for(int i=0;i<Label.rows;i++){
    //     for(int j=0;j<Label.cols;j++){
    //         std::cout<<int(Label.at<char>(j,i))<<" ";
    //     }
    //     std::cout<<std::endl;
    // }
    
}


void PhotoMontage::BuildSolveMRF( const std::vector<cv::Mat> & Images, const cv::Mat & Label,int mode)
{
    const int n_imgs = Images.size();
    __ExtraData extra_data;
    extra_data.Images.resize(n_imgs);
    for (int i = 0 ; i < n_imgs; i++)
    {
        extra_data.Images[i] = Images[i];
    }
    extra_data.Label = Label;
    //extra_data.kdtree = AddInertiaConstraint( Label );
    int width = Label.cols;
    int height = Label.rows;
    int n_label = n_imgs;
    
    
    try
    {
        VisResultLabelMap(Label,n_label);
        
        GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,n_imgs);
        
        // set up the needed data to pass to function for the data costs
        switch(mode){
             case USER_SPECIFY_P:
                std::cout<<"Using user specified penalty with possion!"<<std::endl;
                gc->setDataCost(&dataFn_user,&extra_data);
                break;
            case USER_SPECIFY:
                std::cout<<"Using user specified penalty!"<<std::endl;
                gc->setDataCost(&dataFn_user,&extra_data);
                break;

            case MAX_LUMIN:
                std::cout<<"Using max luminance penalty!"<<std::endl;
                gc->setDataCost(&dataFn_max_lumin,&extra_data);
                break;
            case MIN_LUMIN:
                std::cout<<"Using min luminance penalty!"<<std::endl;
                gc->setDataCost(&dataFn_min_lumin,&extra_data);
                break;
            case ERASE:
                std::cout<<"Using erase penalty!"<<std::endl;
                gc->setDataCost(&dataFn_erase,&extra_data);
                break;
            case MAX_LIKEHOOD:
                std::cout<<"Using max Likelihood penalty!"<<std::endl;
                gc->setDataCost(&dataFn_max_likelihood,&extra_data);
                break;
            case MIN_LIKEHOOD:
                std::cout<<"Using min Likelihood penalty!"<<std::endl;
                gc->setDataCost(&dataFn_min_likelihood,&extra_data);
                break;
            case CONTRAST:
                std::cout<<"Using contrast penalty!"<<std::endl;

                for(int i=0;i<Images.size();i++){
                    Mat tmp;
                    GaussianBlur(Images[i],tmp,Size(3,3),0);
                    GaussianBlurImages.push_back(tmp);
                }
                gc->setDataCost(&dataFn_contrast,&extra_data);
                break;
             case MAX_DIFF:
                std::cout<<"Using maxx diff penalty!"<<std::endl;
                gc->setDataCost(&dataFn_max_diff,&extra_data);
                break;
               
                
            default:
                break;
        }
        
        
        
        // smoothness comes from function pointer
        gc->setSmoothCost(&smoothFn,&extra_data);
        
        printf("\nBefore optimization energy is %f",gc->compute_energy());
        gc->swap(10);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
        printf("\nAfter optimization energy is %f",gc->compute_energy());
        
        Mat result_label(height, width, CV_8UC1);
        
        for (int y = 0 ; y < height ; y++)
        {
            for (int x = 0 ; x < width; x++)
            {
                int idx = y * width + x;
                
                result_label.at<uchar>(y,x) = gc->whatLabel(idx);
            }
        }
        delete gc;
        
        VisResultLabelMap( result_label, n_label );
        if(currentMode == 8 ){
            BuildSolveGradientFusion(Images, result_label);
        }
        else{
            VisCompositeImage( result_label, Images );

        }
        // BuildSolveGradientFusion(Images, result_label);
        
        
        
        
    }
    catch (GCException e)
    {
        e.Report();
    }
}

void PhotoMontage::GradientAt( const cv::Mat & Image, int x, int y, cv::Vec3f & grad_x, cv::Vec3f & grad_y )
{
    
    Vec3i color1 = Image.at<Vec3b>(y, x);
    Vec3i color2 = Image.at<Vec3b>(y, x + 1);
    Vec3i color3 = Image.at<Vec3b>(y + 1, x);
    grad_x = color2 - color1;
    grad_y = color3 - color1;
    
}



void* PhotoMontage::thread_function(void *arg_raw)
{
    struct thread_param* arg = ( struct thread_param*)arg_raw;
    printf("new thread:%d",arg->id);
    PhotoMontage::SolveChannel( arg->channel_idx, arg->constraint, arg->color_gradient_x, arg->color_gradient_y ,arg->output);
    return((void*)0);
}


void PhotoMontage::BuildSolveGradientFusion( const std::vector<cv::Mat> & Images, const cv::Mat & ResultLabel )
{
    
    int width = ResultLabel.cols;
    int height = ResultLabel.rows;
    Mat color_result(height, width, CV_8UC3);
    Mat color_gradient_x(height, width, CV_32FC3);
    Mat color_gradient_y(height, width, CV_32FC3);
    
    for (int y = 0 ; y < height - 1; y++)
    {
        for (int x = 0 ;x < width - 1; x++)
        {
            GradientAt( Images[ResultLabel.at<uchar>(y,x)], x, y, color_gradient_x.at<Vec3f>(y,x), color_gradient_y.at<Vec3f>(y,x) );
        }
    }
    Vec3b color0 = Images[0].at<Vec3b>(0,0);
    
    struct thread_param para1{1, 0, color0[0], color_gradient_x, color_gradient_y , color_result};
    struct thread_param para2{2, 1, color0[1], color_gradient_x, color_gradient_y , color_result};
    struct thread_param para3{3, 2, color0[2], color_gradient_x, color_gradient_y , color_result};
    
    pthread_create(&pid1,NULL,thread_function,&para1);
    pthread_create(&pid2,NULL,thread_function,&para2);
    pthread_create(&pid3,NULL,thread_function,&para3);
    
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    pthread_join(pid3,NULL);
    
    // cout<<color_gradient_x<<endl;
    // cout<<color_gradient_y<<endl;
    
    
    
    
    // SolveChannel( 0, color0[0], color_gradient_x, color_gradient_y , color_result );
    // SolveChannel( 1, color0[1], color_gradient_x, color_gradient_y , color_result );
    // SolveChannel( 2, color0[2], color_gradient_x, color_gradient_y , color_result );
    
    
    
    
    
    //cout<<color_result<<endl;
    
    imwrite("compositeimage.png",color_result);
    
}



void PhotoMontage::VisResultLabelMap( const cv::Mat & ResultLabel, int n_label )
{
    int width = ResultLabel.cols;
    int height = ResultLabel.rows;
    Mat color_result_map(height, width, CV_8UC3);
    std::vector<Vec3b> label_colors;
    for (int i = 0 ; i < n_label; i++)
    {
        label_colors.push_back(Vec3b(rand()%256,rand()%256,rand()%256));
    }
    //label_colors.push_back(Vec3b(255,0,0));
    //label_colors.push_back(Vec3b(0,255,0));
    //label_colors.push_back(Vec3b(0,0,255));
    //label_colors.push_back(Vec3b(255,255,0));
    //label_colors.push_back(Vec3b(0,255,255));
    
    
    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0 ; x < width ; x++)
        {
            if(int(ResultLabel.at<char>(y,x))==undefined){
                color_result_map.at<Vec3b>(y,x)=0;
            }
            else{
            color_result_map.at<Vec3b>(y,x) = label_colors[ResultLabel.at<uchar>(y,x)];}
        }
    }
    
    imwrite("resultlabels.png",color_result_map);
}

void PhotoMontage::VisCompositeImage( const cv::Mat & ResultLabel, const std::vector<cv::Mat> & Images )
{
    int width = ResultLabel.cols;
    int height = ResultLabel.rows;
    Mat composite_image(height, width, CV_8UC3);
    
    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0 ; x < width ; x++)
        {
            composite_image.at<Vec3b>(y,x) = Images[ResultLabel.at<uchar>(y,x)].at<Vec3b>(y,x);
        }
    }
    
    // imshow("compositeimage",composite_image);
    imwrite("compositeimage.png",composite_image);

    // waitKey(-1);
}

cv::flann::Index *  PhotoMontage::AddInertiaConstraint( const cv::Mat & Label )
{
    int height = Label.rows;
    int width = Label.cols;
    std::vector<Point2f> _data_vec;
    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0 ; x < width; x++)
        {
            if (Label.at<char>(y,x) > 0)
            {
                _data_vec.push_back(Point2f(x,y));
            }
        }
    }
    
    _data.create(_data_vec.size(),2,CV_32FC1);
    for (int i = 0 ; i < _data_vec.size(); i++)
    {
        _data.at<float>(i,0) = _data_vec[i].x;
        _data.at<float>(i,1) = _data_vec[i].y;
    }
    cv::flann::KDTreeIndexParams indexParams;
    return new cv::flann::Index(_data, indexParams);
    
    //std::vector<int> indices(1);
    //std::vector<float> dists(1);
    //Mat query(1,2,CV_32FC1);
    //query.at<float>(0,0) = 522;
    //query.at<float>(0,1) = 57;
    //kdtree->knnSearch(query, indices, dists, 1,cv::flann::SearchParams(64));
}

void PhotoMontage::SolveChannel( int channel_idx, int constraint, const cv::Mat &color_gradient_x, const cv::Mat &color_gradient_y , cv::Mat & output )
{
#if 1
    int width = color_gradient_x.cols;
    int height = color_gradient_x.rows;
    
    
    int NumOfUnknownTerm = 2 * width * height + 1;
    std::vector<Eigen::Triplet<double> > NonZeroTerms;
    Eigen::VectorXd b(NumOfUnknownTerm);
    for (int y = 0 ; y < height - 1; y++)
    {
        for (int x = 0 ;x < width - 1; x++)
        {
            int unknown_idx = y * width + x;
            
            /// gradient x
            int eq_idx1 = 2 * unknown_idx;
            NonZeroTerms.push_back(Eigen::Triplet<double>(eq_idx1,unknown_idx,-1));
            int other_idx1 = y * width + (x + 1);
            NonZeroTerms.push_back(Eigen::Triplet<double>(eq_idx1,other_idx1,1));
            Vec3f grads_x = color_gradient_x.at<Vec3f>(y,x);
            b(eq_idx1) = grads_x[channel_idx];
            
            /// gradient y
            int eq_idx2 = 2 * unknown_idx + 1;
            NonZeroTerms.push_back(Eigen::Triplet<double>(eq_idx2,unknown_idx,-1));
            int other_idx2 = (y + 1) * width + x;
            NonZeroTerms.push_back(Eigen::Triplet<double>(eq_idx2,other_idx2,1));
            Vec3f grads_y = color_gradient_y.at<Vec3f>(y,x);
            b(eq_idx2) = grads_y[channel_idx];
        }
    }
    
    
    ///constraint
    int eq_idx = width * height * 2;
    NonZeroTerms.push_back(Eigen::Triplet<double>(eq_idx, 0, 1));
    b(eq_idx) = constraint;
    
    
    
    Eigen::SparseMatrix<double> A(NumOfUnknownTerm, width * height);
    // cout<<"SizeA："<<A.rows()<<","<<A.cols()<<endl;
    A.setFromTriplets(NonZeroTerms.begin(),NonZeroTerms.end());
    NonZeroTerms.erase(NonZeroTerms.begin(),NonZeroTerms.end());
    
    Eigen::SparseMatrix<double> ATA(width * height, width * height);
    ATA = A.transpose() * A;
    Eigen::VectorXd ATb = A.transpose() * b;
    
    cout<<"SizeATA："<<ATA.rows()<<","<<ATA.cols()<<","<<ATA.nonZeros()<<endl;
    printf("\nSolving...\n");
    
    Eigen::ConjugateGradient <Eigen::SparseMatrix<double> > newSolver(ATA);
    Eigen::VectorXd solution = newSolver.solve(ATb);
    
    
    // Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > CGSolver(ATA); solution all 0
    // Eigen::VectorXd solution = CGSolver.solve(ATb);
    printf("Solved!\n");
    
    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0 ; x < width ; x++)
        {
            Vec3b & temp = output.at<Vec3b>(y,x);
            temp[channel_idx] = uchar(std::max(std::min(solution(y * width + x),255.0),0.0));
            // printf("%d,%d,  %f, %f\n",y,x, solution(y * width + x), ATb(y*width + x));
            //system("pause");
        }
    }
    
    //imshow("output",output);
    //waitKey(-1);
#endif
    
    ///请同学们填写这里的代码，这里就是实验中所说的单颜色通道的Gradient Fusion
}
