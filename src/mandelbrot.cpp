//For I/O (mostly during testing)
#include <iostream>
//For writing the binary image
#include <fstream>
//For easy file names
#include <string>
#include <thread>

#include "bitMap.h"

int main(int argc, char** argv)
{
	long double x1;
	long double x2;
	long double y1;
	long double y2;
	char* filename;

	//error checking for user input 
    try {
        if (argc == 6) {
			//convert char* to long doubles
            x1 = std::stold(argv[1]);
            x2 = std::stold(argv[2]);
            y1 = std::stold(argv[3]);
            y2 = std::stold(argv[4]);
            filename = argv[5];
        } else {
            throw argc;
        }
    } catch (int argCount) {
        printf("Input: ./main x1 x2 y1 y2 filename\n");
    }

	//Initial Setup
	int width = 1500;//pixels
	// scale for drawThread function. Scales mandelbrot set to image dimensions
	long double scale = (x2 - x1) / 1500;
	//height is taken from scale and ratio of height to width
	int height = abs((y2 - y1) / scale);
	int dpi = 150;//pixel per inch
	
	//Open File
	std::ofstream image(filename,std::ios::binary);
	//Make the Bitmap Header
	writeHeader(image, height, width);
	writeDIB(image,height,width,dpi);
	
	//Arrays to Store the Three Colors of a Pixel
	int pixels = height*width;
	unsigned char* red = new unsigned char[pixels];
	unsigned char* green = new unsigned char[pixels];
	unsigned char* blue = new unsigned char[pixels];

	// Draw mandelbrot set with 4 threads - taken from colorThread.zip files from BlackBoard 
	int stepSize = pixels/4;
	std::thread* myThreads = new std::thread[4];
	myThreads[0] = std::thread(drawThread,red,green,blue,0,stepSize,x1,y1,width,scale);
	myThreads[1] = std::thread(drawThread,red,green,blue,stepSize+1,2*stepSize,x1,y1,width,scale);
	myThreads[2] = std::thread(drawThread,red,green,blue,2*stepSize+1,3*stepSize,x1,y1,width,scale);
	myThreads[3] = std::thread(drawThread,red,green,blue,3*stepSize+1,pixels,x1,y1,width,scale);
	
	for(int i=0; i < 4; i++){
		myThreads[i].join();
	}

	//Write the pixels to file
	writePixels(image, red, green, blue, pixels);
	//Close the File
	image.close();
	
	//Exit the Program
	std::cout <<"Made Image " << filename << std::endl;
	return 0;
}
