#include <algorithm>

void addRGBFilter(unsigned char* imgData, int width, int height, int channels, int red, int green, int blue)
{
    for (int i = 0; i < width * height * channels; i += channels)
    {
        imgData[i + 0] = std::clamp(static_cast<int>(imgData[i + 0]) + red, 0, 255);
        imgData[i + 1] = std::clamp(static_cast<int>(imgData[i + 1]) + green, 0, 255);
        imgData[i + 2] = std::clamp(static_cast<int>(imgData[i + 2]) + blue, 0, 255);
    }
}

void adjustBrightness(unsigned char* imgData, int width, int height, int channels, int brightness)
{
    for (int i = 0; i < width * height * channels; i += channels)
    {
        imgData[i + 0] = std::clamp(static_cast<int>(imgData[i + 0]) + brightness, 0, 255);
        imgData[i + 1] = std::clamp(static_cast<int>(imgData[i + 1]) + brightness, 0, 255);
        imgData[i + 2] = std::clamp(static_cast<int>(imgData[i + 2]) + brightness, 0, 255);
    }
}