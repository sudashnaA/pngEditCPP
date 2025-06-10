#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include "interface.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include <string>
#include <iostream>
#include <Windows.h>

unsigned char* readImage(std::string imageName, int* width, int* height, int* channels)
{
    unsigned char* imgData{ stbi_load(imageName.c_str(), width, height, channels, 0) };

    (!imgData)
        ?
        std::cerr << "Failed to load image.\n"
        :
        std::cout << "Successfully read image, h: " << *height << " w: " << *width << " n: " << *channels << "\n";

    return imgData;
}

void writeImage(std::string imageName, std::string fileExt, unsigned char* imgData, int width, int height, int channels)
{
    stbi_write_png(("images\\" + imageName + fileExt).c_str(), width, height, channels, imgData, width * channels);
}

void openImage(std::string imageName)
{
    if ((int)ShellExecuteA(NULL, "open", ("images\\" + imageName).c_str(), NULL, NULL, SW_SHOWNORMAL) < 32)
    {
        std::cerr << "Failed to open output image.\n";
    }
}

void selectImage(unsigned char*& imgData, int* width, int* height, int* channels)
{
    bool hasSelectedImage{ false };

    while (!hasSelectedImage)
    {
        imgData = readImage(getStringFromUser("Enter the image name: "), width, height, channels);
        if (imgData)
        {
            hasSelectedImage = true;
        }
    }
}