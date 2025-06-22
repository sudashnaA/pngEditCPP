#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "imagePNG.h"
#include <memory>

class ImageProcessor {
public:
	std::unique_ptr<ImagePNG> applyColorTint(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue);
	std::unique_ptr<ImagePNG> adjustBrightness(const std::unique_ptr<ImagePNG>& image, int val);
private:
	std::unique_ptr<ImagePNG> applyRGBFilter(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue);
};

#endif 
