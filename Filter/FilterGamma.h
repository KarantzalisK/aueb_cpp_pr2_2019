#ifndef _FILTERGAMMA
#define _FILTERGAMMA

#include "Filter.h"
#include <math.h>
class FilterGamma : public Filter
{
protected:
	float gamma;
	
public:
	Image * imageBuffer;
	FilterGamma(float gamma):Filter()
	{
		this->gamma = gamma;
		imageBuffer = new Image();
	}

	~FilterGamma() {
		delete imageBuffer;
	}

	Image operator<<(const Image& image) override;

	//~FilterGamma() { delete[] imageBuffer; }
};



inline Image FilterGamma::operator<<(const Image& image)
{
	//imageBuffer = new Image(image);
	*imageBuffer = image;
	math::Vec3<float> temp;
	int height = (*imageBuffer).getHeight();
	int width = (*imageBuffer).getWidth();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			temp = (*imageBuffer).getVector(x, y);
			temp.r= pow(temp.r,gamma);
			temp.g= pow(temp.g, gamma);
			temp.b= pow(temp.b, gamma);


			temp = temp.clampToLowerBound(0.0);
			temp = temp.clampToUpperBound(1.0);

			(*imageBuffer).setVector(x, y, temp);
		}
	}
	return *imageBuffer;
}

#endif