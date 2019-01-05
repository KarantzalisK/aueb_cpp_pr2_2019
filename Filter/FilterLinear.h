#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "Filter.h"

class FilterLinear: public Filter
{
protected:
	math::Vec3<float> a;
	math::Vec3<float> c;
	Image * imageBuffer;
public:

	FilterLinear(math::Vec3<float> a, math::Vec3<float> c);

	Image operator<<(const Image& image) override;
	~FilterLinear();
};

inline FilterLinear::~FilterLinear()
{
	delete imageBuffer;
}

 inline FilterLinear::FilterLinear(math::Vec3<float> a, math::Vec3<float> c)
{
	this->a = a;
	this->c = c;
	imageBuffer=new Image();
}


 inline Image FilterLinear::operator<<(const Image& image)
{
	delete imageBuffer;
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
