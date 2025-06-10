#include <string>

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

unsigned char* readImage(std::string imageName, int* width, int* height, int* channels);

void writeImage(std::string imageName, std::string fileExt, unsigned char* imgData, int width, int height, int channels);

void openImage(std::string imageName);

void selectImage(unsigned char*& imgData, int* width, int* height, int* channels);

#endif