依赖：
opencv3

编译：
cd enhanceImage
mkdir build
cd build
cmake ..
make

运行：
./build/test ./data/1.bmp


接口说明：
int enhanceImage(cv::Mat src, cv::Mat &dst, ALGORITHM_TYPE algorithm=EQUALIZE);
  src:输入图像，可以是彩色图和灰度图
  dst:输出图像，单通道8bit的灰度图
  algorithm：增强图像的算法，支持对数拉伸、拉普拉斯拉伸、直方图均衡化、伽玛变换，默认是直方图均衡化(推荐使用)

其他：
模块在ubuntu16.04下测试通过。
