#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "Filter.h"

class FilterLinear: public Filter
{
protected:
	math::Vec3<float> a;
	math::Vec3<float> c;
public:

	FilterLinear(math::Vec3<float> a, math::Vec3<float> c, const Image & src);

	//~FilterLinear();
	Image operator<<(const Image& image) override;
};


 inline FilterLinear::FilterLinear(math::Vec3<float> a, math::Vec3<float> c, const Image & src )
{
	this->a = a;
	this->c = c;
	imageBuffer = new Image(src);
}

// inline FilterLinear::~FilterLinear()
//{
//	delete[] imageBuffer;
//}

 inline Image FilterLinear::operator<<(const Image& image)
{
	//delete[] imageBuffer;
	imageBuffer = nullptr;
	imageBuffer = new Image(image);

	math::Vec3<float> temp;
	int height= imageBuffer->getHeight();
	int width = imageBuffer->getWidth();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			temp = imageBuffer->getVector(x, y);
			temp = a * temp + c;
			temp=temp.clampToLowerBound(0);
			temp=temp.clampToUpperBound(1);

			imageBuffer->setVector(x, y, temp);
		}
	}
	return *imageBuffer;
}



#endif
