#include <iostream>
#include <string>  
#include <fstream>
#include "ppm.h"

using namespace std;
namespace imaging {

	//Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data. 
	float * ReadPPM(const char * filename, int * w, int * h) {

		float *theArray = nullptr;
		bool noError = true;

		ifstream myfile;

		myfile.open(filename, ios::binary);

		if (!myfile.is_open()) {
			cout << "Error, file " << filename << " didn't open." << endl;
			noError = false;
		}
		else {

			for (int i = 0; i < 4; i++) {
				string line;
				myfile >> line;
				if (line[0] == 'P' && line[1] != '6') {
					cout << "Error! Format Type Must Be P6." << endl;
					noError = false;
					break;
				}
				else if (i == 1) {
					*w = stoi(line);
				}
				else if (i == 2) {
					*h = stoi(line);
				}
				else if (i == 3) {
					if (stoi(line) > 255) {
						cout << "Error! Invalid pixel size input." << endl;
						noError = false;
						break;
					}
				}
			}

			if (noError) {
				int floats = 3 * (*w) * (*h);
				theArray = new float[floats];   //allocates new float array
				char* color = new char[floats]; //buffer
				myfile.read(color, floats);     //buffer holds the curent byte we read
				for (int i = 0; i < floats; i++) {
					unsigned char currentPointer = (unsigned char)color[i];
					theArray[i] = currentPointer / 255.f; // float literal
				}
				delete []color;
				color = 0;
				myfile.close(); // closes file

				return theArray;
			}
			else {
				myfile.close(); // closes file
				return theArray;
			}
		}
		return nullptr;
	}

	//Writes an image buffer as a PPM file.
	bool WritePPM(const float * data, int w, int h, const char * filename) {
		ofstream myfile;
		myfile.open(filename, ios::binary);

		if (!myfile.is_open()) {
			cout << "Could not create file " << filename << endl;
			return false;
		}
		else if (data == nullptr) {
			myfile.close();
			return false;
		}
		else {
			myfile << "P6" << endl;   //Writes the header in the file 
			myfile << w << endl;
			myfile << h << endl;
			myfile << 255 << endl;
			int size = w * h * 3;
			char rgb;
			for (int i = 0; i < size; i++) {
				rgb = data[i] * 255; 
				myfile.write(&rgb, 1);
			}
		}
		myfile.close();
		delete[]data;
		data = 0;
		return true;

	}
}

