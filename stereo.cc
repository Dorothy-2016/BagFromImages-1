#include<iostream>
#include<ros/ros.h>
#include<rosbag/bag.h>
#include<rosbag/view.h>
#include<sensor_msgs/Image.h>
#include<std_msgs/Time.h>
#include<std_msgs/Header.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include "Thirdparty/DLib/FileFunctions.h"



using namespace std;


void LoadImages(const string &strPathToSequence, vector<string> &vstrImageLeft,
                vector<string> &vstrImageRight, int nframe)
{
    
    vstrImageLeft.resize(nframe);
    vstrImageRight.resize(nframe);
    for(int i=0; i<nframe; i++)
    {
        stringstream ss;
        ss <<""<< setfill('0') << setw(4) << i;
        vstrImageLeft[i] = strPathToSequence + "left_"   + ss.str() + ".png";
        vstrImageRight[i] = strPathToSequence + "right_" + ss.str() + ".png";
        cout<<vstrImageLeft[i]<<endl;
    }
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "BagFromImages");

    if(argc!=5)
    {
        cerr << "Usage: rosrun BagFromImages BagFromImages <path to image directory> <frame Num> <frequency> <path to output bag>" << endl;
        return 0;
    }

    ros::start();


    int nframe = atoi(argv[2]);
    vector<string> vstrImageLeft;
    vector<string> vstrImageRight;
    vector<double> vTimestamps;
    LoadImages(string(argv[1]), vstrImageLeft, vstrImageRight,nframe);


    // Frequency
    double freq = atof(argv[3]);

    // Output bag
    rosbag::Bag bag_out(argv[4],rosbag::bagmode::Write);

    ros::Time t = ros::Time::now();

    const float T=1.0f/freq;
    ros::Duration d(T);

    for(int i=0;i<nframe;i++)
    {
        if(!ros::ok())
            break;

        cv::Mat im_right = cv::imread(vstrImageRight[i],CV_LOAD_IMAGE_COLOR);
        cv::Mat im_left = cv::imread(vstrImageLeft[i],CV_LOAD_IMAGE_COLOR);
        cv_bridge::CvImage cvImage_right;
        cv_bridge::CvImage cvImage_left;
        cvImage_right.image = im_right;
        cvImage_left.image = im_left;
        cvImage_right.encoding = sensor_msgs::image_encodings::RGB8;
        cvImage_left.encoding = sensor_msgs::image_encodings::RGB8;
        cvImage_right.header.stamp = t;
        cvImage_left.header.stamp = t;
        bag_out.write("/stereo/right/image_raw",ros::Time(t),cvImage_right.toImageMsg());
        bag_out.write("/stereo/left/image_raw",ros::Time(t),cvImage_left.toImageMsg());
        t+=d;
        cout << i << endl;
    }

    bag_out.close();

    ros::shutdown();

    return 0;
}
