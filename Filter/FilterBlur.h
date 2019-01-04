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
	std::vector<math::Vec3<float>> vecF;
public:
	FilterBlur(unsigned int sizeN, const Image & src);
	Image operator<<(const Image& image) override;
};

inline FilterBlur::FilterBlur(unsigned sizeN, const Image& src)
{
	 this->sizeN = sizeN;
	 imageBuffer = new Image(src);
	 vecF.clear();
	 vecF=std::vector<math::Vec3<float>>(12, (float)1 / 9);
}

inline Image FilterBlur::operator<<(const Image & image)
{
	return Image();
}

#endif
