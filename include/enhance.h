#ifndef _ENHANCE_H_
#define _ENHANCE_H_

#include <opencv2/opencv.hpp>

typedef enum { 
  LOG,
  EQUALIZE,
  LAPLACE,
  GAMMA
}ALGORITHM_TYPE;

int enhanceImage(cv::Mat src, cv::Mat &dst, ALGORITHM_TYPE algorithm=EQUALIZE);

#endif
