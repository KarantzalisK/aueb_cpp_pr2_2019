#pragma once
#ifndef _FILTERLAPLACE
#define _FILTERLAPLACE
#include "FilterBlur.h"

class FilterLaplace: public FilterBlur
{
public:
	FilterLaplace();
	Image operator<<(const Image& image) override;

};

inline FilterLaplace::FilterLaplace()
{
	ArrayF.getRawDataPtr()->clear();
	ArrayF.getRawDataPtr()->shrink_to_fit();
	std::vector<float> myVec = std::vector<float>{0,1,0,1,-4,1,0,1,0};
	ArrayF = Array<float>(3,3,&myVec);

}

inline Image FilterLaplace::operator<<(const Image & image)
{
	delete imageBuffer;
	imageBuffer = new Image(image);
	int myWidth = (int)imageBuffer->getWidth();
	int myHeight = (int)imageBuffer->getHeight();

	for (int y = 0; y < myHeight; y++)
	{
		for (int x = 0; x < myWidth; x++)
		{
			math::Vec3<float> total(0);

			for (int fx = -1; fx <= 1; fx++) {
				for (int fy = -1; fy <= 1; fy++)
				{
					int tx = x + fx;
					int ty = y + fy;
					total += imageBuffer->getVector(tx, ty)*ArrayF.getVector(fx + 1, fy + 1);
				}
			}
			total = total.clampToUpperBound(1);
			total = total.clampToLowerBound(0);
			
			imageBuffer->setVector(x, y, total);
		}
	}
	return *imageBuffer;
}



#endif
