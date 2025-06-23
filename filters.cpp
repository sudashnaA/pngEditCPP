#include <algorithm>

//void adjustHSV(unsigned char* imgData, int width, int height, int channels, int hue, int saturation, int value)
//{
//    const int RED_INDEX{ 0 };
//    const int GREEN_INDEX{ 1 };
//    const int BLUE_INDEX{ 2 };
//
//    for (int i = 0; i < width * height * channels; i += channels)
//    {
//        int RED_VALUE{ imgData[i + RED_INDEX] };
//        int GREEN_VALUE{ imgData[i + GREEN_INDEX] };
//        int BLUE_VALUE{ imgData[i + BLUE_INDEX] };
//
//        HSV hsvValues{ rgbToHsv(RED_VALUE, GREEN_VALUE, BLUE_VALUE) };
//
//    }
//}

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