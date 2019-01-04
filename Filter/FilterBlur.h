#pragma once
#ifndef _FILTERBLUR
#define _FILTERBLUR
#include "Array.h"
#include "Vec3.h"
#include "Filter.h"

class FilterBlur: public math::Array<math::Vec3<float>> , public Filter
{
protected:
	unsigned int sizeN;
	Image * imageBuffer;
	std::vector<math::Vec3<float>> vecF;
public:
	FilterBlur(unsigned int sizeN, const Image & src);
	Image operator<<(const Image& image) override;
};

inline FilterBlur::FilterBlur(unsigned sizeN, const Image& src)
{
	 this->sizeN = 2*sizeN+1;
	 imageBuffer = new Image(src);
	 vecF.clear();
	 vecF=std::vector<math::Vec3<float>>(12, (float)1 / 9);
}

inline Image FilterBlur::operator<<(const Image & image)
{
	//float myf = (1.0 / 9.0);
	//math::Vec3<float> divider1 = math::Vec3<float>(myf);
	//for (int y = 1; y < (int)imageBuffer->getHeight()-1; y++) {
	//	for (int x = 1; x < (int)imageBuffer->getWidth()-1; x++)
	//	{
	//		math::Vec3<float> total = 0;
	//		int iterations = 0;
	//		int fy = y - 1;
	//		int fx = x - 1;
	//		int targetFy = y + 1;
	//		int targetFx = x + 1;
	//		//if (fy < 0) fy = 0;
	//		//if (fx < 0) fx = 0;
	//		//if (targetFy >= (int)imageBuffer->getHeight())targetFy= imageBuffer->getHeight() - 1;
	//		//if (targetFx >= (int)imageBuffer->getWidth()) targetFx = imageBuffer->getWidth() - 1;
	//		while(fy<= targetFy)
	//		{
	//			while(fx<= targetFx && iterations<9)
	//			{
	//				total += imageBuffer->getVector(fx, fy)*myf;
	//				fx++;
	//				iterations++;
	//			}
	//			fy++;
	//			fx = 0;
	//		}
	//		imageBuffer->setVector(x, y, total);
	//	}
	//}

	int myWidth = (int)imageBuffer->getWidth();
	int myHeight = (int)imageBuffer->getHeight();

	for(int y=1; y< myHeight-1;y++)
	{
		for (int x = 1; x < myWidth-1; x++)
		{
			math::Vec3<float> total(0);
			int ksize = 3;
			for (int fy = -1; fy <= 1; fy++)
				for (int fx = -1; fx <= 1; fx++)
				{
					int tx = x + fx;
					int ty = y + fy;
					
						total += imageBuffer->getVector(tx,ty);
					
				}

			
			total = total / 9;
			imageBuffer->setVector(x, y, total);

		}

	}



	return *imageBuffer;
}

#endif
