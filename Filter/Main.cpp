#include <iostream>
#include <string>
#include "Image.h"
#include "Color.h"
#include "Filter.h"
#include "FilterLinear.h"
#include "Filter.h"
#include "FilterGamma.h"
#include "Array.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
using namespace std;
using namespace imaging;

void caclulateNegative(Image & Image,int & width,int & height);
	

	int main(int argc, char* argv[]) {
		int w;
		int h;

		string input;
		string first;
		string second;
		string inputfile;
		string filterfile;
		bool firstExecution = true;
		Image myImage = Image();
		string option;
		if(argc==2)
		{
			input = argv[1];

		}else if(argc==1)
		{
			cout << "File name of the image to load: ";
			getline(cin >> std::ws, input);
		}else
		{
			cout << "Sorry the arguments that you entered are not valid" << endl;
			cout << "File name of the image to load: ";
			getline(cin >> std::ws, input);
		}

		do {


			if (!firstExecution)
			{
				
				input.clear();
				cout << "File name of the image to load: ";
				getline(cin >> std::ws, input);
			}
			firstExecution = false;


			int dotPos = -1;

			do {

				for (int i = input.length() - 1; i >= 0; i--)
				{
					if (input[i] == '.')
					{
						dotPos = i;
						break;
					}
				}

				if (dotPos == -1)
				{
					cout << "Sorry the filename that you entered is not valid" << endl;
					cout << "File name of the image to load: ";
					getline(cin >> std::ws, input);
				}
			} while (dotPos == -1);




			first = input.substr(0, dotPos);
			second = input.substr(dotPos + 1, input.length() - dotPos);



			inputfile = first + '.' + second; // file name to read
			filterfile = first + "_neg" + "." + second; //file name to write negative


			
			if (myImage.load(inputfile, second))
			{
				w = myImage.getWidth();
				h = myImage.getHeight();
				cout << "Image dimensions are: " << w << " x " << h << endl;


				//caclulateNegative(myImage, w, h);


				/*FilterGamma myFilter2 = FilterGamma(0.7,myImage);
				myFilter2 << myImage;

				math::Vec3<float> a = math::Vec3<float>(1,0.8,0.3);
				math::Vec3<float> c = math::Vec3<float>(0.1, 0.1, 0.3);
				FilterLinear myFilter = FilterLinear(a,c,myImage);

				myFilter << *myFilter2.imageBuffer;

				FilterGamma myFilter3 = FilterGamma(1.2,myImage);
				myFilter3 << *myFilter.imageBuffer;*/

				//myFilter3.imageBuffer->save(filterfile, second);

				//FilterBlur myFilterBlur(3, myImage);
				//myImage=myFilterBlur << myImage;
				math::Vec3<float> a = math::Vec3<float>(-2, -2, -2);
				math::Vec3<float> c = math::Vec3<float>(1, 1, 1);
				FilterLinear myFilter = FilterLinear(a, c);
				FilterLaplace myFilter2=FilterLaplace();

				myImage = myFilter2 << myImage;
				/*myImage = myFilter << myImage;*/
				myImage = myFilter << myImage;

				myImage.save(filterfile, second);
			}

			

			do {
				cout << "Do you want to load another image?" << endl;
				cout << "1) Load new Image" << endl;
				cout << "2) Exit" << endl;
				cin >> option;
				if (option == "1")
				{
					cout << "OK Lets load a new image" << endl<<endl;
				}
				else if (option == "2")
				{
					cout << "OK BYE!" << endl;
				}
				else
				{
					cout << "Invalid Input" << endl;
				}
			} while (!(option == "1" || option == "2"));

		} while (option=="1");


	


		system("pause");
		return 0;
	}


	void caclulateNegative(Image & myImage, int & width, int & height)
	{
		math::Vec3<float> totalWhite = math::Vec3<float>(1, 1, 1);
		math::Vec3<float> temp;
		for(int y = 0; y < height; y++){
			for (int x = 0; x < width; x++)
			{
				temp = myImage.getVector(x, y);
				temp = totalWhite - temp;
				myImage.setVector(x, y, temp);
			}
		}
	}

	