#pragma once
#ifndef _FILTER
#define _FILTER
#include "Image.h"
using namespace imaging;

class Filter
{
public:
	Image * imageBuffer;

public:
	//Default Constructor
	Filter(){ imageBuffer = nullptr;}

	//Copy Constructor
	Filter(const Image & src){ imageBuffer = new Image(src);}

	//Operator <<
	virtual Image operator << (const Image & image)=0;

};



#endif
