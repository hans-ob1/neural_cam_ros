cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

option(CUDA "compile with cuda" ON)
option(DETECTOR "compile detector" ON)
option(CALIBRATION "compile calibration" OFF)

rosbuild_init()

find_package(OpenCV 3.1 REQUIRED)

rosbuild_genmsg()

#wildcard additions:
file(GLOB SOURCES "src/detector/*.c" "src/detector/*.cu" "src/detector/*.h")

if(CUDA)
	find_package(CUDA 7.5 REQUIRED)
	INCLUDE(FindCUDA)
	INCLUDE_DIRECTORIES(/usr/local/cuda/include)
	add_definitions(-DGPU -DCUDNN)
	set(
	    CUDA_NVCC_FLAGS
	    ${CUDA_NVCC_FLAGS};
	    -O3 -gencode arch=compute_61,code=sm_61
	    )

	message("Compiling with CUDA ON")
	cuda_add_library(neurlib ${SOURCES} OPTIONS -arch sm_61)
	TARGET_LINK_LIBRARIES(neurlib m pthread stdc++ cublas curand cudnn)
else()
	add_library(neurlib ${SOURCES})
	TARGET_LINK_LIBRARIES(neurlib m pthread stdc++)
	message("Compiling with CUDA OFF")
endif()

if(DETECTOR)
	#compile detector
	rosbuild_add_executable(detector src/detector/main.cpp src/detector/supportfunc.cpp src/detector/supportfunc.hpp)
	rosbuild_add_compile_flags(detector -std=c++11)
	TARGET_LINK_LIBRARIES(detector ${OpenCV_LIBS} neurlib)
endif()


