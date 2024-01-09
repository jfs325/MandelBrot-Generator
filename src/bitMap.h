#ifndef _BITMAP_H_
#define _BITMAP_H_

/**
 @mainpage CS361 - Blue Square
 @section description
 
 This code makes a blue rectangle. It shows how raw bitmaps are generated.
 */

/**
 @file
 @author Mark Boady <mwb33@drexel.edu>
 @date 2021-2022
 @section Description
 
 This file demos how to make a raw Bitmap by coloring it blue.
 */

//For I/O (mostly during testing)
#include <iostream>
//For writing the binary image
#include <fstream>
//For easy file names
#include <string>

/**
Mandelbrot Z Function .
Returns the number of iterations needed to
reach 4 or threshold if bounded.
We use long double for maximum accuracy
@param x is the x coordinate
@param y is the y coordinate
@param t is the threshold
@return Threshold if point in set otherwise
number of iterations to determine not in set
*/
int z(long double x, long double y, int t);

/**
 Draw the mandelbrot set for specified boundaries in a thread.
 @param red is red of RGB
 @param green is green of RGB
 @param blue is blue of RGB
 @param start is start index of bit image
 @param stop is stop index of bit image
 @param x1 is x1 param given by user
 @param y1 is y1 param given by user
 @param width is width of image - 1500
 @param scale is scale of x y plane for mandelbrot compared to bitMap image
 */
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
);

/**
 Write Header of a Bitmap Image
 @param image is a reference to the file containing our image
 @param height is number of pixels tall the image is
 @param width is the number of pixels wide the image is
*/
void writeHeader(std::ofstream &image, int height, int width);
/**
 Write DIB header of a Bitmap Image. The DIB is metadata for the image.
 @param image is a reference to the file we are writing into
 @param height is number of pixels tall the image is
 @param width is the number of pixels wide the image is
 @param dpi is the dots per inch of the image when printed
*/
void writeDIB(std::ofstream &image, int height, int width, int dpi);

/**
 Write Pixels from a collection of arrays. All three arrays must be the same size.
 @param image is a reference to the file we are writting into
 @param red is an array storing the red component of each pixel
 @param green is an array storing the green component of each pixel
 @param blue is an array storing the blue component of each pixel
 @param pixels is the number of elements in the array
*/
void writePixels(std::ofstream &image,
	unsigned char* red,
	unsigned char* green,
	unsigned char* blue,
	int pixels);

/**
 Take an integer (32 bit) and break it up into bytes (8bit).
 @param value is the integer to break up
 @param byte is which byte you want (0 to 4)
 @return the byte requested as a char
 */
char getByte(int value, int byte);
/**
 Convert Dots Per Inch to Pixels Per Meter. Both are useful formats, but dpi is more commom. Bitmaps use PPM.
 @param dpi is the dots per inch
 @return equivelant measurement in pixels per meter
 */
int dpiToPPM(int dpi);

/**
 Set every value in an array to be the same
 @param array to set colors in
 @param color is the color to put in each position
 @param pixels is the number of pixels in the array
 */
void setColor(unsigned char* array, unsigned char color, int pixels);

#endif