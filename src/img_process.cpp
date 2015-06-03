#include "ros/ros.h"
const std::string windowName = "Original Image";
const std::string windowName1 = "HSV Image";
const std::string windowName2 = "Thresholded Image";
const std::string windowName3 = "After Morphological Operations";
const std::string trackbarWindowName = "Trackbars";

/**
Function gets called whenever a trackbar position 
is changed
   @return		void
*/
void on_trackbar( int, void* )
{
	
}

/**
Function converts integer to string
   @param number	int
   @return		std::string
*/
std::string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}
/**
Function to create trackbars

   @return	void
*/
void createTrackbars(){
	
	namedWindow(trackbarWindowName,0);
	char TrackbarName[50];

	sprintf( TrackbarName, "H_MIN", H_MIN);
	sprintf( TrackbarName, "H_MAX", H_MAX);
	sprintf( TrackbarName, "S_MIN", S_MIN);
	sprintf( TrackbarName, "S_MAX", S_MAX);
	sprintf( TrackbarName, "V_MIN", V_MIN);
	sprintf( TrackbarName, "V_MAX", V_MAX);
	sprintf( TrackbarName, "R_MIN", R_MIN);
	sprintf( TrackbarName, "R_MAX", R_MAX);
	sprintf( TrackbarName, "G_MIN", G_MIN);
	sprintf( TrackbarName, "G_MAX", G_MAX);
	sprintf( TrackbarName, "B_MIN", B_MIN);
	sprintf( TrackbarName, "B_MAX", B_MAX);
   
	createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
	createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
	createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
	createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
	createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
	createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );
	createTrackbar( "R_MIN", trackbarWindowName, &R_MIN, R_MAX, on_trackbar );
	createTrackbar( "R_MAX", trackbarWindowName, &R_MAX, R_MAX, on_trackbar );
	createTrackbar( "G_MIN", trackbarWindowName, &G_MIN, G_MAX, on_trackbar );
	createTrackbar( "G_MAX", trackbarWindowName, &G_MAX, G_MAX, on_trackbar );
	createTrackbar( "B_MIN", trackbarWindowName, &B_MIN, B_MAX, on_trackbar );
	createTrackbar( "B_MAX", trackbarWindowName, &B_MAX, B_MAX, on_trackbar );


}

/**
Function to calculate if x-coordinate of object is in pickup zone
Pickup zone currently defined in between areaRight and areaLeft
   @param X 		int
   @return inZone	bool
*/
bool pickupZone(int X) {
	bool inZone;	
	if (X < areaRight && X > areaLeft) 
		inZone = true;
	else inZone = false;
	return inZone;
}

/**
Function to calculate if x-coordinate of object is to the left of pickup zone
Pickup zone currently defined in between areaRight and areaLeft
   @param X 		int
   @return inZone	bool
*/
bool Left(int X){
	bool inZone;
	if (X > 0 && X < areaLeft)
		inZone = true;
	else inZone = false;
	return inZone;
}

/**
Function to calculate if x-coordinate of object is to the right of pickup zone
Pickup zone currently defined in between areaRight and areaLeft
   @param X 		int
   @return inZone	bool
*/
bool Right(int X){
	bool inZone;
	if (X > areaLeft && X < FRAME_WIDTH)
		inZone = true;
	else inZone = false;
	return inZone;
}

/**
Function that takes in vector of Trash objects and openCV Mat image
   @param trash 	std::vector<Trash>
   @param &frame	cv::Mat
   @return	void
*/
void findObject(std::vector<Trash> trash, Mat &frame){
	for (int i = 0; i < trash.size(); i++){
		cv::circle(frame,cv::Point(trash.at(i).getXPos(),trash.at(i).getYPos()),5,cv::Scalar(0,0,255));
		cv::putText(frame,intToString(trash.at(i).getXPos())+ " , " 
		+ intToString(trash.at(i).getYPos()),cv::Point(trash.at(i).getXPos(), trash.at(i).getYPos()+20),1,1,Scalar(0,255,0));
		cv::putText(frame,"Distance: "+ intToString(trash.at(i).getDistance()) 
		+ " cm",cv::Point(trash.at(i).getXPos()+10,trash.at(i).getYPos()-10),1,1,trash.at(i).getColor());
		cv::putText(frame,trash.at(i).getType(),cv::Point(trash.at(i).getXPos(),trash.at(i).getYPos()-30),1,2,trash.at(i).getColor());
		cv::putText(frame,"Angle: "+ intToString(trash.at(i).getAngle()) 
		+ " degrees",cv::Point(trash.at(i).getXPos()+5,trash.at(i).getYPos()+10),1,1,trash.at(i).getColor());
	}
}

/**
Function that takes in vector of Trash objects and openCV Mat image
   @param trash 	std::vector<Trash>
   @param &frame	cv::Mat
   @return	void
*/
void drawObject(std::vector<Trash> trash, Mat &frame){
	
	for (int i = 0; i < trash.size(); i++){
	
	int distance = trash.at(i).getDistance();
	int angle = trash.at(i).getAngle();

	cv::circle(frame,cv::Point(trash.at(i).getXPos(),trash.at(i).getYPos()),5,cv::Scalar(0,0,255));
	cv::putText(frame,intToString(trash.at(i).getXPos())+ " , " 
		+ intToString(trash.at(i).getYPos()),cv::Point(trash.at(i).getXPos(), trash.at(i).getYPos()+20),1,1,Scalar(0,255,0));
	cv::putText(frame,"Distance: "+ intToString(trash.at(i).getDistance()) 
		+ " cm",cv::Point(trash.at(i).getXPos()+10,trash.at(i).getYPos()-10),1,1,trash.at(i).getColor());
	cv::putText(frame,trash.at(i).getType(),cv::Point(trash.at(i).getXPos(),trash.at(i).getYPos()-30),1,2,trash.at(i).getColor());
	cv::putText(frame,"Angle: "+ intToString(trash.at(i).getAngle()) 
		+ " degrees",cv::Point(trash.at(i).getXPos()+5,trash.at(i).getYPos()+10),1,1,trash.at(i).getColor());
	ROS_INFO("\n\n\t\t\t\tDistance: %i Angle: %i", distance, angle);

	if (pickupZone(trash.at(i).getXPos())) {
		ROS_INFO("Trash in pickup zone");
	}
	else if (Left(trash.at(i).getXPos())){
		ROS_INFO("Trash detected to the left of pickup zone");
	}
	else if (Right(trash.at(i).getXPos())){
		ROS_INFO("Trash detected to the right of pickup zone");
	}
	}
}

/**
Function to erode and dilate whitespace
   @param &thresh 	cv::Mat
   @return	void
*/
void morphOps(Mat &thresh){

	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(4,4));
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(10,10));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);

	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
}

/**
Function to be used with calibrate node for tracking objects
   @param threshold 	cv::Mat
   @param HSV		cv::Mat
   @param &cameraFeed	cv::Mat
   @return	void
*/
void trackFilteredObject(Mat threshold, Mat HSV, Mat &cameraFeed){

	std::vector<Trash> sodacans;

	Mat temp;
	threshold.copyTo(temp);
	std::vector< std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );

	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				if(area>MIN_OBJECT_AREA){

					Trash soda;

					soda.setXPos(moment.m10/area);
					soda.setYPos(moment.m01/area);

					sodacans.push_back(soda);
				
					objectFound = true;

				}else objectFound = false;


			}
		
			if(objectFound ==true){
				
				findObject(sodacans,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

/**
Function to be used with object_tracking node for tracking trash objects
   @param trash		Trash
   @param threshold 	cv::Mat
   @param HSV		cv::Mat
   @param &cameraFeed	cv::Mat
   @return	void
*/
void trackFilteredObject(Trash trash,Mat threshold,Mat HSV, Mat &cameraFeed){

	
	std::vector <Trash> sodacans;

	Mat temp;
	threshold.copyTo(temp);
	
	std::vector< std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;
	
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		
		if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				if(area>MIN_OBJECT_AREA){

					Trash soda;
					
					soda.setXPos(moment.m10/area);
					soda.setYPos(moment.m01/area);
					soda.setType(trash.getType());
					soda.setColor(trash.getColor());

					sodacans.push_back(soda);
					//ROS_INFO("Distance: %d\tAngle: \n", soda.getDistance(),soda.getAngle());

					objectFound = true;

				}else objectFound = false;


			}
			if(objectFound ==true){

				drawObject(sodacans,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}
