#include "imagePNG.h"
#include <string>
#include <memory>

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

void writeImage(std::string imageName, std::string fileExt, unsigned char* imgData, int width, int height, int channels);

void openImage(std::string imageName);

std::unique_ptr<ImagePNG> selectImage();

std::unique_ptr<ImagePNG> readImage(std::string imageName);

#endif