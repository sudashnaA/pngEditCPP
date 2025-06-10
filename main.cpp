#include "interface.h"
#include "inputoutput.h"
#include "filters.h"
#include <iostream>
#include <string>

constexpr int MIN_OPTION = 1;
constexpr int MAX_OPTION = 9;

int main()
{
    int height{};
    int width{};
    int channels{};

    unsigned char* imgData{};

    selectImage(imgData, &width, &height, &channels);

    size_t size{ static_cast<size_t>(width * height * channels) };
    unsigned char* imgDataCopy = new unsigned char[size];

    if (!imgData || size <= 0) 
    {
        std::cerr << "Failed to allocate or copy image data.\n";
    }
    else
    {
        std::memcpy(imgDataCopy, imgData, size);
    }

    bool editing{ true };

    while (editing)
    {
        displayEditingMenu();

        int option{getIntFromUser("\nEnter an option\n")};

        switch (option)
        {
        case 1:
            {
            int brightness{ getIntFromUser("Enter brightness value ") };
            adjustBrightness(imgData, width, height, channels, brightness);
            }
            break;
        case 6:
            {
            int red{ getRGBValueFromUser("Enter red value ( must be between 0 and 255 ) ") };
            int green{ getRGBValueFromUser("Enter green value ( must be between 0 and 255 ) ") };
            int blue{ getRGBValueFromUser("Enter blue value ( must be between 0 and 255 ) ") };
            addRGBFilter(imgData, width, height, channels, red, green, blue);
            }
            break;
        case -7:
            std::memcpy(imgData, imgDataCopy, size);
            std::cout << "Reset edits\n";
            break;
        case -8:
            {
            std::string outputName{ getStringFromUser("Enter output file name ") };
            writeImage(outputName, ".png", imgData, width, height, channels);
            openImage(outputName + ".png");
            }
            break;
        case -1:
            editing = false;
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid option\n";
            break;
        }

    }

    delete[] imgData;
    delete[] imgDataCopy;

    return 0;
}