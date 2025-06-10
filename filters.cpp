#include <algorithm>



void addRGBFilter(unsigned char* imgData, int width, int height, int channels, int red, int green, int blue)
{
    const int RED_INDEX = 0;
    const int GREEN_INDEX = 1;
    const int BLUE_INDEX = 2;

    for (int i = 0; i < width * height * channels; i += channels)
    {
        imgData[i + RED_INDEX] = std::clamp(static_cast<int>(imgData[i + 0]) + red, 0, 255);
        imgData[i + GREEN_INDEX] = std::clamp(static_cast<int>(imgData[i + 1]) + green, 0, 255);
        imgData[i + BLUE_INDEX] = std::clamp(static_cast<int>(imgData[i + 2]) + blue, 0, 255);
    }
}