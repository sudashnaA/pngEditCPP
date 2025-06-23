#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "imagePNG.h"
#include <memory>

struct HSV {
	double hue;
	double saturation;
	double value;
};

struct RGB {
	int red;
	int green;
	int blue;
};

class ImageProcessor {
public:
	std::unique_ptr<ImagePNG> applyColorTint(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue);
	std::unique_ptr<ImagePNG> adjustBrightness(const std::unique_ptr<ImagePNG>& image, int val);
	std::unique_ptr<ImagePNG> applyGrayscaleFilter(const std::unique_ptr<ImagePNG>& image);
private:
	std::unique_ptr<ImagePNG> applyRGBFilter(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue);
	HSV rgbToHSV(int r, int g, int b);
	RGB hsvToRGB(HSV input);
};

#endif 
