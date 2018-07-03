#include <opencv2/opencv.hpp>
#include <string.h>
#include "enhance.h"

using namespace std;
using namespace cv;

//参考：https://blog.csdn.net/dcrmg/article/details/53677739

//对数变换，对灰度扩展，分两种情况：
// 1.把低灰度部分拉伸，显示更多细节
// 2.把高灰度部分压缩，减少高灰度细节
void Log(Mat src, Mat &dst, float v=10.0)
{
  Mat imageLog(src.size(),CV_32FC1);
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++){
      unsigned char r = src.at<unsigned char>(i, j);
      imageLog.at<float>(i, j)  = log(1 + v * r/255.0);
    }
  }
  
  //归一化到0~255,并转换成8bit图像显示    
  normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
  convertScaleAbs(imageLog, imageLog);
  dst = imageLog.clone();
}

//直方图均衡化是通过调整图像的灰阶分布，使得在0~255灰阶上的分布更加均衡
//对比度较低的图像适合使用直方图均衡化方法来增强图像细节。
void Equalize(Mat src, Mat &dst, double clipLimit=3.0, short win_size=8)
{
  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(clipLimit, cv::Size(win_size, win_size));
  clahe->apply(src, dst);
}

//拉普拉斯变换，锐化增强图像
void Laplace(Mat src, Mat &dst)
{
  Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
  filter2D(src, dst, CV_8UC1, kernel);
}


//伽马变换,主要用于图像的校正，将灰度过高或者灰度过低的图片进行修正，增强对比度。
// 变换公式就是对原图像上每一个像素值做乘积运算：s=c*r^y
void Gamma(Mat src, Mat &dst, float y=3.0)
{
  Mat imageGamma(src.size(),CV_32FC1);
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      unsigned char r = src.at<unsigned char>(i, j);
      imageGamma.at<float>(i, j)  = powf(r/255.0,y);
    }
  }
  //归一化到0~255,转换成8bit图像显示  
  normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
  convertScaleAbs(imageGamma, imageGamma);
  dst = imageGamma.clone();
}

//过度曝光测试
void ExposureOver(Mat src, Mat &dst)
{
  Mat imageOver(src.size(),CV_8UC1);
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      unsigned char r = src.at<unsigned char>(i, j);
      imageOver.at<unsigned char>(i, j)  = r > (255-r) ? (255-r) : r;
    }
  }
  dst = imageOver.clone();
}

int enhanceImage(Mat src, Mat &dst,ALGORITHM_TYPE algorithm)
{

  if(src.empty()) {
    printf("[enhance] input image is empty\n");
    return -1;
  }

  Mat image(src.size(),CV_8UC1);
  if(src.type() != CV_8UC1) {
    cvtColor(src,image,CV_BGR2GRAY);
  }else {
    image = src;
  }
  
  switch(algorithm) {
  case LOG:
    Log(image,dst);
    break;
  case EQUALIZE:
    Equalize(image,dst);
    break;
  case LAPLACE:
    Laplace(image,dst);
    break;
  case GAMMA:
    Gamma(image,dst);
    break;
  default:
    Equalize(image,dst);
    break;
  }
 
  return 0;
}

int test_all(int argc, char *argv[])
{
  string file;
  float v = 1.0;
  switch(argc) {
  case 2:
    file = string(argv[1]);
    break;
  case 3:
    file = string(argv[1]);
    v = atof(argv[2]);
    break;
  default:
    file = string("test.png");
    break;
  }
  
  Mat image = imread(file,0);
  if(image.empty()) {
    printf("params invalid,you should input like this:\n");
    printf(" enhance [image] [...]\n");
    return -1;
  }

  Mat imageLog,imageLaplace,imageGamma,imageEqualize,imageExposure;

  Log(image,imageLog);
  Laplace(image,imageLaplace);
  Gamma(image,imageGamma,v);
  Equalize(image,imageEqualize);
  ExposureOver(image,imageExposure);

  imshow("src", image);
  imshow("log", imageLog);
  imshow("lapace", imageLaplace);
  imshow("gamma", imageGamma);
  imshow("equlize", imageEqualize);
  imshow("over exposure", imageExposure);
  
  waitKey();	
  return 0;
}
