#pragma once
#ifndef _FILTERBLUR
#define _FILTERBLUR
#include "Array.h"
#include "Vec3.h"
#include "Filter.h"

class FilterBlur: public math::Array<float> , public Filter
{
protected:
	int sizeN;
	Image * imageBuffer;
	Array<float> ArrayF;
public:
	FilterBlur()
	{
		sizeN = 0;
		imageBuffer = new Image();
	}

	FilterBlur(unsigned int sizeN);
	Image operator<<(const Image& image) override;

	~FilterBlur() {
		delete imageBuffer;
	}
};



inline FilterBlur::FilterBlur(unsigned int sizeN)
{
	this->sizeN = sizeN;
	imageBuffer = new Image();
	ArrayF.getRawDataPtr()->clear();
	ArrayF.getRawDataPtr()->shrink_to_fit();
	ArrayF=Array<float>(sizeN,sizeN);
	float myVar = 1.0 / sizeN/sizeN;
	for (int x=0; x<sizeN; x++)
	{
		for(int y = 0; y < sizeN; y++)
		{
			ArrayF.setVector(x, y, myVar);
		}
	}
	
}

inline Image FilterBlur::operator<<(const Image & image)
{
	delete imageBuffer;
	imageBuffer = new Image(image);
	int myWidth = (int)imageBuffer->getWidth();
	int myHeight = (int)imageBuffer->getHeight();

	for(int y=0; y< myHeight;y++)
	{
		for (int x = 0; x < myWidth; x++)
		{
			math::Vec3<float> total(0);
			
			for (int fy = -(sizeN/2); fy <= (sizeN/2); fy++)
				for (int fx = -(sizeN / 2); fx <= (sizeN / 2); fx++)
				{
					int tx = x + fx;
					int ty = y + fy;	
					total += imageBuffer->getVector(tx, ty)*ArrayF.getVector(fx + (sizeN / 2), fy + (sizeN / 2));	
				}
			imageBuffer->setVector(x, y, total);
		}
	}
	return *imageBuffer;
}

#endif
