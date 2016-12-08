# BagFromImages

Base on https://github.com/raulmur/BagFromImages/blob/master/main.cc

Add a function to create bag from stereo camera.

## Installation

In your ROS_PACKAGE_PATH (check your environment variable ROS_PACKAGE_PATH):

    git clone https://github.com/scomup/BagFromImages.git BagFromImages
    
    cd BagFromImages
    mkdir build
    cd build
    cmake ..
    make

## Usage:

    Format of image file name.
      left_<04%id>.png
      right_<04%id>.png

    rosrun BagFromImages stereo PATH_TO_IMAGES FRAME_NUMBER FREQUENCY PATH_TO_OUPUT_BAG
  
 - `PATH_TO_IMAGES`: Path to the folder with the images
 - `FRAME_NUMBER`: The number of frames.
 - `FREQUENCY`: Frames per second.
 - `PATH_TO_OUTPUT_BAG`: Path to save the bag (including the filename e.g. directory/filename.bag)

    Ex. rosrun BagFromImages stereo /home/liu/workspace/Datasets/stereo/ 400 10 /home/liu/q.bag

