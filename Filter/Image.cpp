#include <iostream>
#include "ppm/ppm.h"
#include "Image.h"
#include "Vec3.h"


using namespace imaging;


bool isValidFormat(const std::string& filename,const std::string& format)
{
	if (filename.length()<format.length())
	{
		return false;
	}

	for (int i=0; i<format.length(); i++)
	{
		if(tolower(filename[filename.length() - format.length() + i])!=tolower(format[i]))
		{
			return false;
		}
	}
	

	if(!tolower(filename[filename.length() - format.length() - 1]) == '.')
	{
		return false;
	}

	if (!(format.length() == 3 && tolower(format[0])=='p' && tolower(format[1]) == 'p' && tolower(format[2]) == 'm' )) {
		std::cout << "Error: Wrong file extension" << std::endl;
		std::cout << "Only PPM is supported for now" << std::endl;
		return false;
	}
	return true;



}


/*! Loads the image data from the specified file, if the extension of the filename matches the format string.*/
bool Image::load(const std::string& filename, const std::string& format)
{
	if(isValidFormat(filename,format))
	{
		width = 0;
		height = 0;

		float *components = ReadPPM(filename.c_str(), (int*)&width, (int*)&height);		//The raw_array with rgb compoments

		if (components == nullptr) {
			return false;
		}

		buffer.clear();
		buffer.shrink_to_fit();
		int pos = 0;

		//ReadPPM also have a white-space character so we start from i=1; instead of 0

		for (int i = 1; i < width*height * 3; i += 3) {
			math::Vec3<float> color (components[i], components[i + 1], components[i + 2]);	//Convert rgb compoments to Color
			buffer.push_back(color);
			pos++;
		}
		delete[]components;
		components = 0;

		return true;
	}
	return false;
}



/*! Stores the image data to the specified file, if the extension of the filename matches the format string.*/
bool Image::save(const std::string& filename, const std::string& format)
{
	if (width*height > 0 && !buffer.empty() &&isValidFormat(filename, format)){

		float *newImg= new float[width*height * 3];
		int pos = 0;

		for (int i = 0; i < width*height * 3; i += 3) {
			math::Vec3<float> color = buffer.data()[i/3];

			newImg[i] = color.r;
			newImg[i + 1] = color.g;
			newImg[i + 2] = color.b;
			pos++;
		}
		return WritePPM(newImg, width, height, filename.c_str());
	}
	return false;
}


