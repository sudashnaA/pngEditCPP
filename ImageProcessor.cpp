#include "ImageProcessor.h"
#include "imagePNG.h"
#include <memory>
#include <vector>
#include <algorithm>

std::unique_ptr<ImagePNG> ImageProcessor::applyColorTint(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue) {
    return applyRGBFilter(image, red, green, blue);
}

std::unique_ptr<ImagePNG> ImageProcessor::adjustBrightness(const std::unique_ptr<ImagePNG>& image, int val) {
    return applyRGBFilter(image, val, val, val);
}

std::unique_ptr<ImagePNG> ImageProcessor::applyRGBFilter(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue)
{
    const int RED_INDEX = 0;
    const int GREEN_INDEX = 1;
    const int BLUE_INDEX = 2;

    std::vector<unsigned char> data { image->getImageData() };

    for (int i = 0; i < image->getWidth() * image->getHeight() * image->getChannels(); i += image->getChannels())
    {
        data[i + RED_INDEX] = std::clamp(static_cast<int>(data[i + RED_INDEX]) + red, 0, 255);
        data[i + GREEN_INDEX] = std::clamp(static_cast<int>(data[i + GREEN_INDEX]) + green, 0, 255);
        data[i + BLUE_INDEX] = std::clamp(static_cast<int>(data[i + BLUE_INDEX]) + blue, 0, 255);
    }

    auto imageCopy{ std::make_unique<ImagePNG>(image->getName(), data.data(), image->getHeight(), image->getWidth(), image->getChannels())};
    return imageCopy;
}