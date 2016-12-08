cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

project(BagFromImages)

rosbuild_init()

FIND_PACKAGE(OpenCV REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

rosbuild_add_executable(stereo
stereo.cc
Thirdparty/DLib/FileFunctions.cpp)
target_link_libraries (stereo
${OpenCV_LIBS})

rosbuild_add_executable(monocular
monocular.cc
Thirdparty/DLib/FileFunctions.cpp)
target_link_libraries (monocular
${OpenCV_LIBS})
