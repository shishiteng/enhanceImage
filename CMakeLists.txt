cmake_minimum_required(VERSION 2.6)
project(enhanceImage)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(OpenCV 3 REQUIRED )

include_directories(
  include
  ${OpenCV_INCLUDE_DIR}
)


# library
add_library(enhanceImage SHARED
  src/enhance.cpp
)
target_link_libraries(enhanceImage
  ${OpenCV_LIBRARIES}
)

# exe
add_executable(test
  src/test.cpp)
target_link_libraries(test
  ${OpenCV_LIBRARIES}
  enhanceImage
)
	
add_dependencies(test enhanceImage)

INSTALL(TARGETS enhanceImage LIBRARY DESTINATION lib)
INSTALL(DIRECTORY include DESTINATION .)
INSTALL(FILES src/test.cpp DESTINATION example)
INSTALL(FILES readme.txt DESTINATION .)
