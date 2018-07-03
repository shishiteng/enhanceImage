#include <string.h>

#include "enhance.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
  string file;
  switch(argc) {
  case 1:
    file = string("test.png");
  case 2:
    file = string(argv[1]);
    break;
  default:
    break;
  }
  
  Mat image = imread(file);
  if(image.empty()) {
    printf("params invalid,you should input like this:\n");
    printf(" test [xxx.png]\n");
    return -1;
  }

  
  Mat imageLog,imageLaplace,imageGamma,imageEqualize;
  enhanceImage(image,imageLog,LOG);
  enhanceImage(image,imageLaplace,LAPLACE);
  enhanceImage(image,imageGamma,GAMMA);
  enhanceImage(image,imageEqualize,EQUALIZE);
  
  imshow("src", image);
  imshow("log", imageLog);
  imshow("lapace", imageLaplace);
  imshow("gamma", imageGamma);
  imshow("equlize", imageEqualize);

  
  waitKey(0);
  return 0;
}
