#include "ImageProcessor.h"
#include "imagePNG.h"
#include <memory>
#include <vector>
#include <algorithm>

constexpr int RED_INDEX = 0;
constexpr int GREEN_INDEX = 1;
constexpr int BLUE_INDEX = 2;

HSV ImageProcessor::rgbToHSV(int red, int green, int blue) {
    double fCMax = std::max(std::max(red, green), blue);
    double fCMin = std::min(std::min(red, green), blue);
    double fDelta = fCMax - fCMin;

    HSV converted;

    if (fDelta > 0) {
        if (fCMax == red) {
            converted.hue = 60 * (fmod(((green - blue) / fDelta), 6));
        }
        else if (fCMax == green) {
            converted.hue = 60 * (((blue - red) / fDelta) + 2);
        }
        else if (fCMax == blue) {
            converted.hue = 60 * (((red - green) / fDelta) + 4);
        }

        if (fCMax > 0) {
            converted.saturation = fDelta / fCMax;
        }
        else {
            converted.saturation = 0;
        }

        converted.value = fCMax;
    }
    else {
        converted.hue = 0;
        converted.saturation = 0;
        converted.value = fCMax;
    }

    if (converted.hue < 0) {
        converted.hue = 360 + converted.hue;
    }

    return converted;
}

RGB ImageProcessor::hsvToRGB(HSV input) {
    double fC = input.value * input.saturation; // Chroma
    double fHPrime = fmod(input.hue / 60.0, 6);
    double fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    double fM = input.value - fC;

    RGB output;

    if (0 <= fHPrime && fHPrime < 1) {
        output.red = fC;
        output.green = fX;
        output.blue = 0;
    }
    else if (1 <= fHPrime && fHPrime < 2) {
        output.red = fX;
        output.green = fC;
        output.blue = 0;
    }
    else if (2 <= fHPrime && fHPrime < 3) {
        output.red = 0;
        output.green = fC;
        output.blue = fX;
    }
    else if (3 <= fHPrime && fHPrime < 4) {
        output.red = 0;
        output.green = fX;
        output.blue = fC;
    }
    else if (4 <= fHPrime && fHPrime < 5) {
        output.red = fX;
        output.green = 0;
        output.blue = fC;
    }
    else if (5 <= fHPrime && fHPrime < 6) {
        output.red = fC;
        output.green = 0;
        output.blue = fX;
    }
    else {
        output.red = 0;
        output.green = 0;
        output.blue = 0;
    }

    output.red += fM;
    output.green += fM;
    output.blue += fM;

    return output;
}

std::unique_ptr<ImagePNG> ImageProcessor::applyColorTint(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue) {
    return applyRGBFilter(image, red, green, blue);
}

std::unique_ptr<ImagePNG> ImageProcessor::adjustBrightness(const std::unique_ptr<ImagePNG>& image, int val) {
    return applyRGBFilter(image, val, val, val);
}

std::unique_ptr<ImagePNG> ImageProcessor::applyRGBFilter(const std::unique_ptr<ImagePNG>& image, int red, int green, int blue){
    std::vector<unsigned char> data { image->getImageData() };

    for (int i = 0; i < image->getWidth() * image->getHeight() * image->getChannels(); i += image->getChannels())
    {
        data[i + RED_INDEX] = std::clamp(static_cast<int>(data[i + RED_INDEX]) + red, 0, 255);
        data[i + GREEN_INDEX] = std::clamp(static_cast<int>(data[i + GREEN_INDEX]) + green, 0, 255);
        data[i + BLUE_INDEX] = std::clamp(static_cast<int>(data[i + BLUE_INDEX]) + blue, 0, 255);
    }

    auto imageCopy{ std::make_unique<ImagePNG>(image->getName(), data, image->getHeight(), image->getWidth(), image->getChannels())};
    return imageCopy;
}

std::unique_ptr<ImagePNG> ImageProcessor::applyGrayscaleFilter(const std::unique_ptr<ImagePNG>& image) {
    std::vector<unsigned char> data{ image->getImageData() };

    for (int i = 0; i < image->getWidth() * image->getHeight() * image->getChannels(); i += image->getChannels())
    {
        int red{ data[i + RED_INDEX] };
        int green{ data[i + GREEN_INDEX] };
        int blue{ data[i + BLUE_INDEX] };

        HSV hsv{ rgbToHSV(red, green, blue) };
        hsv.saturation = 0;
        RGB rgb{ hsvToRGB(hsv) };

        data[i + RED_INDEX] = rgb.red;
        data[i + GREEN_INDEX] = rgb.green;
        data[i + BLUE_INDEX] = rgb.blue;
    }

    auto imageCopy{ std::make_unique<ImagePNG>(image->getName(), data, image->getHeight(), image->getWidth(), image->getChannels()) };
    return imageCopy;
}
