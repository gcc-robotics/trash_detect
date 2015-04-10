#include <image_transport/image_transport.h>
#include "ros/ros.h"

#ifndef __TrashDetector_H_
#define __TrashDetector_H_

class TrashDetector
{
private:
	ros::NodeHandle node;
	// image_transport::ImageTransport imageTransport;
	ros::Subscriber subscriber;
	ros::Publisher publisher;

public:
	TrashDetector(ros::NodeHandle rosNode);
	void test();

	void processImage(const sensor_msgs::ImageConstPtr& msg);

};

#endif
