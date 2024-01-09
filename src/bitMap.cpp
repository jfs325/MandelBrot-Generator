//For I/O (mostly during testing)
#include <iostream>
//For writing the binary image
#include <fstream>
//For easy file names
#include <string>
#include <complex>
#include "bitMap.h"

int z(long double x, long double y, int t){ 
    //Create Values
    std::complex<long double> c(x,y); 
    std::complex<long double> current(0,0); 
    //Run Iteratively
    for(int i=1; i < t; i++){ 
        current = current*current+c; 
        if(std::abs(current) > 4){
            return i ; 
        }
    }
    //Never got above 4
    return t ; 
}

void drawThread(
	unsigned char* red,
	unsigned char* green,
	unsigned char* blue,
	int start,
	int stop,
	long double x1,
	long double y1,
	int width,
	double scale
) {
	//for each pixel in image
	for(int i=start; i < stop; i++){
		//get row and col using constant width size
		long double row = i / width;
		long double col = i % width;
		//use row and col to get x and y coordinate of mandelbrot set
		long double x = x1 + (col * scale);
		long double y = y1 + (row * scale);
		//calculate whether x,y point converges or diverges
		int result = z(x,y,100);
		int color;
		// use result to get grayscale color
		if(result == 100){
			color = 255; 
		} else{
			color = result * (255 / 100);
		}
		red[i] = color;
		green[i] = color;
		blue[i] = color;
	}
}

void writeHeader(std::ofstream &image, int height, int width){
	//How many pixel does the image have
	int pixels = height*width;
	//Make the header. It is always 14 bytes
	int headerSize = 14;
	//Array to store the header
	char* header = new char[headerSize];
	//The header is 14 Bytes
	//The DIB is 40 bytes
	int offset = headerSize + 40;
	//Each Pixel is another 3 bytes
	int totalBits = pixels*3+offset;
	//Make the Header
	//First 2 Bytes are BM for bitmap
	header[0] = 'B';
	header[1] = 'M';
	//Next 4 bytes are the total size of the file
	header[2] = getByte(totalBits,0);
	header[3] = getByte(totalBits,1);
	header[4] = getByte(totalBits,2);
	header[5] = getByte(totalBits,3);
	//Next for bits are 0 (reserved for other uses)
	header[6] = 0;
	header[7] = 0;
	header[8] = 0;
	header[9] = 0;
	//Last 4 bytes are offset
	//Where do the pixels start
	header[10] = getByte(offset,0);
	header[11] = getByte(offset,1);
	header[12] = getByte(offset,2);
	header[13] = getByte(offset,3);
	//Write the Header to the file in binary
	image.write(header, headerSize);
	//Exit the Function
	return;
}

void writeDIB(std::ofstream &image, int height, int width, int dpi){
	//Convert DPI to Pixels Per Meter
	int resolution = dpiToPPM(dpi);
	//Fixed Size of 40 Bytes
	int sizeDIB = 40;
	//Make array of bytes
	char* DIB = new char[sizeDIB];
	//Set Values
	//First 4 bytes are header size of this header (40)
	DIB[0] = getByte(40,0);
	DIB[1] = getByte(40,1);
	DIB[2] = getByte(40,2);
	DIB[3] = getByte(40,3);
	//Bitmap Width (4 bytes)
	DIB[4] = getByte(width,0);
	DIB[5] = getByte(width,1);
	DIB[6] = getByte(width,2);
	DIB[7] = getByte(width,3);
	//Height (4 bytes)
	DIB[8] = getByte(height,0);
	DIB[9] = getByte(height,1);
	DIB[10] = getByte(height,2);
	DIB[11] = getByte(height,3);
	//Color Plane (2 bytes) is always 1
	DIB[12] = 1;
	DIB[13] = 0;
	//Color Depth (2 bytes) we are using 24 (three 8 bit colors)
	DIB[14] = getByte(24,0);
	DIB[15] = getByte(24,1);
	//Compression (4 bytes) 0 means none
	DIB[16] = 0;
	DIB[17] = 0;
	DIB[18] = 0;
	DIB[19] = 0;
	//Uncompressed Size (4 bytes)
	//0 because we aren't using compression
	DIB[20] = 0;
	DIB[21] = 0;
	DIB[22] = 0;
	DIB[23] = 0;
	//Horizontal Resolution (4 bytes)
	//Pixel per meter
	DIB[24] = getByte(resolution, 0);
	DIB[25] = getByte(resolution, 1);
	DIB[26] = getByte(resolution, 2);
	DIB[27] = getByte(resolution, 3);
	//Vertical Resolution (4 bytes)
	//Pixel per meter
	DIB[28] = getByte(resolution, 0);
	DIB[29] = getByte(resolution, 1);
	DIB[30] = getByte(resolution, 2);
	DIB[31] = getByte(resolution, 3);
	//Color Pallet (4 bytes)
	//0 means all
	DIB[32] = 0;
	DIB[33] = 0;
	DIB[34] = 0;
	DIB[35] = 0;
	//Number of important colors
	//0 mean all equal
	DIB[36] = 0;
	DIB[37] = 0;
	DIB[38] = 0;
	DIB[39] = 0;
	//Write the Header to the file in binary
	image.write(DIB, sizeDIB);
	//Exit the Function
	return;
}

void writePixels(std::ofstream &image,
	unsigned char* red,
	unsigned char* green,
	unsigned char* blue,
	int pixels)
{
	char* pixel = new char[3];
	for(int i=0; i < pixels; i++)
	{
		pixel[2] = red[i];
		pixel[1] = green[i];
		pixel[0] = blue[i];
		image.write(pixel, 3);
	}
	return;
}

char getByte(int value, int byte){
	int newValue = value;
	unsigned char rem;
	for(int i=0; i <= byte; i++)
	{
		rem = static_cast<unsigned char>( newValue%256 );
		newValue = newValue/256;
	}
	return rem;
}

//Convesion
//x pixels/inches * C inches/meter = y pixels/meter
int dpiToPPM(int dpi){
	float inchesPerMeter = 39.3701/1;
	float convert = dpi*inchesPerMeter;
	return static_cast<int>(convert);
}

void setColor(unsigned char* array, unsigned char color, int pixels){
	for(int i=0; i < pixels; i++)
	{
		array[i] = color;
	}
}