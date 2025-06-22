#include "imagePNG.h"
#include <vector>
#include <string>

ImagePNG::ImagePNG(std::string name, unsigned char* imgData, int height, int width, int channels) 
	:
	name(name), imgData(imgData, imgData + static_cast<size_t>(width*height*channels)), height(height), width(width), channels(channels), size(static_cast<size_t>(width* height* channels))
{}

ImagePNG::~ImagePNG(){

}

const std::string& ImagePNG::getName() {
	return name;
}

std::vector<unsigned char> ImagePNG::getImageData() {
	return imgData;
}

void ImagePNG::setImageData(std::vector<unsigned char> imgData) {
	this->imgData = imgData;
}

int& ImagePNG::getHeight() {
	return height;
}

int& ImagePNG::getWidth() {
	return width;
}

int& ImagePNG::getChannels() {
	return channels;
}

size_t& ImagePNG::getSize() {
	return size;
}