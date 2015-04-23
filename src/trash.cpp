#include "trash.h"

Trash::Trash(){
	xPos = 0;
	yPos = 0;
	type = "";
	setType("trash");
	setColour(Scalar(0,0,0));
}
Trash::Trash(std::string name){

	setType(name);
	
	if(name=="sprite can"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(0,0,0));
		setHSVmax(Scalar(255,255,255));
		setRGBmin(Scalar(46,83,24));
		setRGBmax(Scalar(118,236,152));

		//BGR value for Green:
		setColour(Scalar(0,255,0));

	}
	if(name=="pepsi can"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(46,83,24));
		setHSVmax(Scalar(118,236,152));

		//BGR value for Blue:
		setColour(Scalar(255,255,0));

	}
	if(name=="coke can"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(0,152,42));
		setHSVmax(Scalar(60,238,203));

		//BGR value for Red:
		setColour(Scalar(0,0,255));

	}



}


void Trash::setXPos(int x){
	xPos = x;
}
int Trash::getXPos(){
	return xPos;	
}
void Trash::setYPos(int y){
	yPos = y;
}
int Trash::getYPos(){
	return yPos;	
}
Scalar Trash::getHSVmin(){

	return HSVmin;

}
Scalar Trash::getHSVmax(){

	return HSVmax;
}
Scalar Trash::getRGBmin(){

	return RGBmin;

}
Scalar Trash::getRGBmax(){

	return RGBmax;
}

void Trash::setHSVmin(Scalar min){

	HSVmin = min;
}


void Trash::setHSVmax(Scalar max){

	HSVmax = max;
}
void Trash::setRGBmin(Scalar min){

	RGBmin = min;
}


void Trash::setRGBmax(Scalar max){

	RGBmax = max;
}

double Trash::getDistance(){

	double dist;
	dist = sqrt( pow(FRAME_HEIGHT - yPos, 2) + pow(FRAME_WIDTH/2 - xPos, 2));
	dist = (dist * 150)/(FRAME_WIDTH) ;
	return dist;

}

double Trash::getAngle(){
	
	double opp = (FRAME_WIDTH/2 - xPos);
	double hyp = sqrt( pow(FRAME_HEIGHT - yPos, 2) + pow(FRAME_WIDTH/2 - xPos, 2));
	double angle = asin(opp/hyp) * (180/M_PI);
	return angle;
}


//names that will appear at the top of each window
const std::string windowName = "Original Image";
const std::string windowName1 = "HSV Image";
const std::string windowName2 = "Thresholded Image";
const std::string windowName3 = "After Morphological Operations";
const std::string trackbarWindowName = "Trackbars";
