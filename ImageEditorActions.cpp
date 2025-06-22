#include "filters.h"
#include "inputoutput.h"
#include <iostream>

//void increaseBrightness(unsigned char*& imgData, int width, int height, int channels)
//{
//    int brightness{ getIntFromUser("Enter brightness value ") };
//
//    // Increasing brightness is the same as increasing each RGB channel by the same amount
//    addRGBFilter(imgData, width, height, channels, brightness, brightness, brightness);
//}
//
//void applyColorTint(unsigned char*& imgData, int width, int height, int channels)
//{
//    int red{ getRGBValueFromUser("Enter red value ( must be between 0 and 255 ) ") };
//    int green{ getRGBValueFromUser("Enter green value ( must be between 0 and 255 ) ") };
//    int blue{ getRGBValueFromUser("Enter blue value ( must be between 0 and 255 ) ") };
//    addRGBFilter(imgData, width, height, channels, red, green, blue);
//}
//
//void resetEdits(unsigned char*& imgData, unsigned char*& imgDataCopy, size_t size)
//{
//    std::memcpy(imgData, imgDataCopy, size);
//    std::cout << "Reset edits\n";
//}
//
//void saveImage(unsigned char*& imgData, int width, int height, int channels)
//{
//    std::string outputName{ getStringFromUser("Enter output file name ") };
//    writeImage(outputName, ".png", imgData, width, height, channels);
//    openImage(outputName + ".png");
//}
//
//bool exitProgram()
//{
//    std::cout << "Exiting program...\n";
//    return false;
//}