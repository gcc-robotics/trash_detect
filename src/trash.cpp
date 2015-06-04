#include "trash.h"

/**
Default Constructor for Trash class
*/
Trash::Trash()
{
	xPos = 0;
	yPos = 0;
	type = "";
	setType("trash");
	setColor(Scalar(0,0,0));
}

Trash::Trash(std::string name)
{
	setType(name);
	
	if(name=="pepsi can")
	{
		setHSVmin(Scalar(46,83,24));
		setHSVmax(Scalar(118,236,152));
		setColor(Scalar(255,255,0));

	}
	if(name=="coke can")
	{
		setHSVmin(Scalar(0,192,0));
		setHSVmax(Scalar(256,256,256));
		setColor(Scalar(0,0,255));
	}
}

void Trash::setXPos(int x)
{
	xPos = x;
}

int Trash::getXPos()
{
	return xPos;	
}

void Trash::setYPos(int y)
{
	yPos = y;
}

int Trash::getYPos()
{
	return yPos;	
}

Scalar Trash::getHSVmin()
{
	return HSVmin;
}

Scalar Trash::getHSVmax()
{
	return HSVmax;
}

Scalar Trash::getRGBmin()
{
	return RGBmin;
}

Scalar Trash::getRGBmax()
{
	return RGBmax;
}

void Trash::setHSVmin(Scalar min)
{
	HSVmin = min;
}

void Trash::setHSVmax(Scalar max)
{
	HSVmax = max;
}

void Trash::setRGBmin(Scalar min)
{
	RGBmin = min;
}

void Trash::setRGBmax(Scalar max)
{
	RGBmax = max;
}

double Trash::getDistance()
{
	double dist;
	dist = sqrt( pow(FRAME_HEIGHT - yPos, 2) + pow(FRAME_WIDTH/2 - xPos, 2));
	dist = (dist * 150)/(FRAME_WIDTH) ;
	return dist;
}

double Trash::getAngle()
{
	double opp = (FRAME_WIDTH/2 - xPos);
	double hyp = sqrt( pow(FRAME_HEIGHT - yPos, 2) + pow(FRAME_WIDTH/2 - xPos, 2));
	double angle = asin(opp/hyp) * (180/M_PI);
	return angle;
}


