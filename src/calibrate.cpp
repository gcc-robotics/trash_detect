#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "calibrate.h"
#include "trash.cpp"
#include "img_process.cpp"

Calibrate::Calibrate(ros::NodeHandle rosNode)
{
	this->node = rosNode;

	// Subscribe to the camera feed and advertise trash locations
	this->subscriber = this->node.subscribe("/image_raw", 1, &Calibrate::processImage, this);
}

void Calibrate::processImage(const sensor_msgs::ImageConstPtr& msg)
{
	// Convert the ROS image to an OpenCV Image
	cv_bridge::CvImagePtr cv_ptr;

	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch(cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
	Mat camerafeed = cv_ptr->image;
	Mat threshold;
	Mat HSV;

	// Calibrate the threshed image
	createTrackbars();
	cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);

	cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);
	inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX), threshold);
	morphOps(threshold);
	imshow(windowName2,threshold);
	trackFilteredObject(threshold,HSV,cv_ptr->image);
	
	imshow(windowName,cv_ptr->image);
	waitKey(3);

}
