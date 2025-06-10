#include <string>

#ifndef FILTERS_H
#define FILTERS_H

void addRGBFilter(unsigned char* imgData, int width, int height, int channels, int red, int green, int blue);

void adjustBrightness(unsigned char* imgData, int width, int height, int channels, int brightness);

#endif#
