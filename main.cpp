#include "ImageEditorActions.h"
#include "interface.h"
#include "inputoutput.h"
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
            increaseBrightness(imgData, width, height, channels);
            break;
        case 6:
            applyColorTint(imgData, width, height, channels);
            break;
        case -7:
            resetEdits(imgData, imgDataCopy, size);
            break;
        case -8:
            saveImage(imgData, width, height, channels);
            break;
        case -1:
            editing = exitProgram();
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