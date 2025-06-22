#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include "imagePNG.h"
#include "interface.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include <string>
#include <memory>
#include <iostream>
#include <Windows.h>

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