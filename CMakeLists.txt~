cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

rosbuild_init()

find_package(CUDA 8.0 REQUIRED)
find_package(OpenCV 3.1 REQUIRED)

#rosbuild_genmsg()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

INCLUDE(FindCUDA)

INCLUDE_DIRECTORIES(/usr/local/cuda/include)

set(
    CUDA_NVCC_FLAGS
    ${CUDA_NVCC_FLAGS};
    -O3 -gencode arch=compute_52,code=sm_52
    )

add_definitions(-DGPU -DCUDNN)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c" "src/*.cu" "src/*.h")

cuda_add_library(darknetlib ${SOURCES} OPTIONS -arch sm_52)
TARGET_LINK_LIBRARIES(darknetlib m pthread stdc++ cublas curand cudnn)

cuda_add_library(supportlib src/supportfunc.cpp src/supportfunc.hpp)

rosbuild_add_executable(main src/main.cpp)
rosbuild_add_compile_flags(main -std=c++11)

TARGET_LINK_LIBRARIES(main m pthread stdc++ cublas curand ${OpenCV_LIBS} darknetlib supportlib)

