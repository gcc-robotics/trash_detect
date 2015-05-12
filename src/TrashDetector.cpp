#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "trash_detect/trash_location.h"
#include "TrashDetector.h"
#include "trash.cpp"
#include "img_process.cpp"

TrashDetector::TrashDetector(ros::NodeHandle rosNode)
{
	this->node = rosNode;

	// Subscribe to the camera feed and advertise trash locations
	this->subscriber = this->node.subscribe("/image_raw", 1, &TrashDetector::processImage, this);
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
	Mat camerafeed = cv_ptr->image;
	Mat threshold;
	Mat HSV;

	// Do things to the image
	bool calibrate = false;
	

	if(calibrate)
	{
		createTrackbars();
	}
	cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);

	if(calibrate==true)
	{
		cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);
		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX), threshold);
		morphOps(threshold);
		imshow(windowName2,threshold);
		trackFilteredObject(threshold,HSV,cv_ptr->image);
	}

	else
	{
		Trash pepsi("pepsi can");
		Trash coke("coke can");

		cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);
		inRange(HSV,pepsi.getHSVmin(),pepsi.getHSVmax(),threshold);
		morphOps(threshold);
		trackFilteredObject(pepsi,threshold,HSV,cv_ptr->image);

		//cvtColor(cv_ptr->image,HSV,COLOR_BGR2HSV);
		//inRange(HSV,coke.getHSVmin(),coke.getHSVmax(),threshold);
		//morphOps(threshold);
		//trackFilteredObject(coke,threshold,HSV,cv_ptr->image);
	}
	
	imshow(windowName,cv_ptr->image);
	waitKey(3);

	// Publish sample trash location
	trash_detect::trash_location locationMsg;

	locationMsg.distance = 20;
	locationMsg.angle = 30;

	this->publisher.publish(locationMsg);
}
