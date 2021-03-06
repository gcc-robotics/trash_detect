#include <image_transport/image_transport.h>
#include "ros/ros.h"

#ifndef __calibrate_H_
#define __calibrate_H_


class Calibrate
{
private:
	ros::NodeHandle node;
	// image_transport::ImageTransport imageTransport;
	ros::Subscriber subscriber;
	ros::Publisher publisher;

public:
	Calibrate(ros::NodeHandle rosNode);

	void processImage(const sensor_msgs::ImageConstPtr& msg);

};

#endif
