//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _ARRAY
#define _ARRAY

//#include "Color.h"
#include <string>
#include <vector>
/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
*/

namespace math
{

	//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	*
	* It holds the actual buffer of the Vector values and provides methods for accessing them,
	* either as individual Vectors or as a memory block. The Image class alone does not provide
	* any functionality for loading and storing an image, as it is the result or input to such a procedure.
	*
	* The internal buffer of an image object stores the actual bytes (data) of the color image as
	* a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
	* width X height X sizeof(Color) bytes.
	*
	* All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	* intensity ranges, each color component is within the range [0.0, 1.0].
	*/
	template <typename T>
	class Array
	{
	public:

	protected:
		std::vector<T> buffer;         //! Holds the image data.

		unsigned int width, 			 //! The width of the image (in Vectors)
			height;		    //! The height of the image (in Vectors)

	public:
		// metric accessors

		/*! Returns the width of the image
		*/
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		*/
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a pointer to the internal data.
		*
		*  This is NOT a copy of the internal image data, but rather a pointer
		*  to the internally allocated space, so DO NOT attempt to delete the pointer.
		*/
		std::vector<T> * getRawDataPtr();

		/*! Obtains the color of the image at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the Vector to get.
		*  \param y is the (zero-based) vertical index of the Vector to get.
		*
		*  \return The color of the (x,y) Vector as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		*/
		T getVector(unsigned int x, unsigned int y) const;

		// data mutators

		/*! Sets the RGB values for an (x,y) Vector.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the Vector to set.
		*  \param y is the (zero-based) vertical index of the Vector to set.
		*  \param value is the new color for the (x,y) Vector.
		*/
		void setVector(unsigned int x, unsigned int y, T & value);

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const std::vector<T> * & data_ptr);

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		*/
		Array<T>();

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		*/
		Array<T>(unsigned int width, unsigned int height);

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		* \param data_ptr is the source of the data to copy to the internal image buffer.
		*
		* \see setData
		*/
		Array<T>(unsigned int width, unsigned int height, const std::vector<T> * data_ptr);

		/*! Copy constructor.
		*
		* \param src is the source image to replicate in this object.
		*/
		Array<T>(const Array<T> &src);

		/*! The Image destructor.
		*/
		~Array<T>();

		/*! Copy assignment operator.
		*
		* \param right is the source image.
		*/
		Array<T> & operator = (const Array<T> & right);

		T & operator()(unsigned int x, unsigned int y) ;

	};
	//C:\Users\petro\Desktop\filter super\ExampleImages\Image01.ppm
	

	/*! Obtains a pointer to the internal data. */
	template <typename T>
	std::vector<T>* Array<T>::getRawDataPtr()
	{
	    return &buffer; //returns address of the initial element
	}

	/*! Obtains the color of the image at location (x,y). */
	template<typename T>
	T Array<T>::getVector(unsigned int x, unsigned int y) const
	{
		//return buffer.data()[..]
		if ((x < width) && (y < height) && (x * y >= 0))
		{
			return buffer[y * width + x]; //y*width+x represents where the Vector (Color) is on 1D array (buffer)
		}
		return T();
	}

	/*! Sets the RGB values for an (x,y) Vector. */
	template<typename T>
	inline void Array<T>::setVector(unsigned int x, unsigned int y, T & value)
	{
		if ((x < width) && (y < height) && (x * y >= 0))
		{
			buffer[y * width + x] = value; //y*width+x represents where the Vector (Color) is on 1D array (buffer)
		}
	}

	/*! Copies the image data from an external raw buffer to the internal image buffer. */
	template <typename T>
	void Array<T>::setData(const std::vector<T>*& data_ptr)
	{
		if (width* height > 0 && data_ptr != nullptr)
		{
			buffer.assign(data_ptr->begin(), data_ptr->end());
		}
	}

	/*! Default constructor. */
	template <typename T>
	Array<T>::Array() :  width(0), height(0),buffer(0){}

	/*! Constructor with width and height specification. */
	template <typename T>
	Array<T>::Array(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
		buffer= std::vector<T>(width*height);
	}

	template <typename T>
	/*! Constructor with data initialization. */
	Array<T>::Array(unsigned int width, unsigned int height, const std::vector<T>* data_ptr)
	{
		this->width = width;
		this->height = height;
		buffer.assign(data_ptr->begin(), data_ptr->end());
	}

	template <typename T>
	/*! Copy constructor. */
	Array<T>::Array(const Array<T>& src)
	{
		width = (src.width);
		height = (src.height);
		buffer.assign(src.buffer.begin(), src.buffer.end());
	}

	/*! The Image destructor. */
	template <typename T>
	Array<T>::~Array<T>()
	{
		buffer.clear();
		buffer.shrink_to_fit();
	}

	//Operator =
	template <typename T>
	Array<T>& Array<T>::operator=(const Array<T>& right)
	{
		width = right.width;
		height = right.height;
		buffer.assign(right.buffer.begin(), right.buffer.end());
		return *this;
	}

	//Operator () 
	template<typename T>
	T & Array<T>::operator()(unsigned int x, unsigned int y) 
	{
		return buffer[y * width + x];
	}

	
} 

#endif