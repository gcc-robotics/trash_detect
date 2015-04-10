#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "trash_detect/trash_location.h"
#include "TrashDetector.h"

TrashDetector::TrashDetector(ros::NodeHandle rosNode)
{
	this->node = rosNode;

	// Subscribe to the camera feed and advertise trash locations
	this->subscriber = this->node.subscribe("/camera/image_raw", 1, &TrashDetector::processImage, this);
	this->publisher = node.advertise<trash_detect::trash_location>("/trash_location", 1);
}

void TrashDetector::processImage(const sensor_msgs::ImageConstPtr& msg)
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

	// Do things to the image
	if(cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
	{
		cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));
	}
	
	// Publish sample trash location
	trash_detect::trash_location locationMsg;

	locationMsg.distance = 5;
	locationMsg.angle = 7;

	this->publisher.publish(locationMsg);
}
