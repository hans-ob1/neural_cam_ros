#DetectNet ROS Package
#Choose -DSUBIMAGES to subscribe a image node over ROS pipline
cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

rosbuild_init()

find_package(OpenCV REQUIRED)
find_package(CUDA 8.0 REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS})

link_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})

rosbuild_genmsg()

add_definitions(-DGPU -DCUDNN)

# Compile Darknet link Library:
file(GLOB SOURCES "src/detector/*.c" "src/detector/*.cu" "src/detector/*.h")
cuda_add_library(neurlib ${SOURCES} OPTIONS -arch sm_61)
TARGET_LINK_LIBRARIES(neurlib m pthread stdc++ cublas curand cudnn)

# Compile detector
rosbuild_add_executable(detector 
	                    src/detector/main.cpp 
	                    src/detector/supportfunc.cpp 
	                    src/detector/supportfunc.hpp
	                    )
	                        
rosbuild_add_compile_flags(detector -std=c++11)
TARGET_LINK_LIBRARIES(detector ${OpenCV_LIBS} neurlib)



