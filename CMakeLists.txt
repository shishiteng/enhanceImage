cmake_minimum_required(VERSION 2.6)
project(imageEnhance)

#add_definitions(-DSHOW_DEBUG_IMAGES)

find_package(OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIR})
link_directories(${OpenCV_LIBRARY_DIR})


add_executable(enhance
./src/enhance.cpp
)

target_link_libraries(enhance
  ${OpenCV_LIBRARIES}
)


