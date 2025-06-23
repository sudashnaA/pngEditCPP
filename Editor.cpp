#define _CRT_SECURE_NO_WARNINGS

// Suppress specific warnings around STB includes
#pragma warning(push)
#pragma warning(disable: 4244) // conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable: 4267) // conversion from 'size_t' to 'type', possible loss of data
#pragma warning(disable: 4996) // 'function': was declared deprecated
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4706) // assignment within conditional expression
#pragma warning(disable: 26819) // Unannotated fallthrough
#pragma warning(disable: 6262) // bytes of stack

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#pragma warning(pop)

#include "Editor.h"
#include <filesystem>
#include <vector>
#include <iostream>
#include <Windows.h>

Editor::Editor() : ImageEditsHistory() {}
Editor::~Editor() {}

// Reads a valid image with stbi_load, then creates an image object with the data and adds it to the image edits history vector
void Editor::readImage(std::string imagePath)
{
    int width{};
    int height{};
    int channels{};
    unsigned char* imgData{ stbi_load(imagePath.c_str(), &width, &height, &channels, 0) };

    if (!imgData) {
        std::cerr << "Failed to load image.\n";
        return;
    }
        
    std::cout << "Successfully read image, h: " << height << " w: " << width << " n: " << channels << "\n";

    std::filesystem::path path(imagePath);
    std::string imageName = path.filename().string();

    // convert imgData to a std::vector as we are using std::vector to store the data in the image class
    std::vector<unsigned char> imgDataVector(imgData, imgData + (height * width * channels));

    auto image{ std::make_unique<ImagePNG>(imageName, imgDataVector, height, width, channels) };
    ImageEditsHistory.push_back(std::move(image));
}

void Editor::writeEdits()
{
    const std::unique_ptr<ImagePNG>& latest{ getLatestImage() };

    std::string filePath{ "images\\" + latest->getName() };
    int width{ latest->getWidth() };
    int height{ latest->getHeight() };
    int channels{ latest->getChannels() };
    std::vector<unsigned char> imageData{ latest->getImageData() };
    int strideBytes = width * channels;

    stbi_write_png(filePath.c_str(), width, height, channels, imageData.data(), strideBytes);
}

void Editor::openImage(std::string imageName)
{
    std::string filePath{ "images\\" + imageName };
    if (reinterpret_cast<intptr_t>(ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL)) < 32)
    {
        std::cerr << "Failed to open output image.\n";
    }
}

const std::unique_ptr<ImagePNG>& Editor::getLatestImage() {
    if (!ImageEditsHistory.empty()) {
        return ImageEditsHistory.back();
    }

    throw std::runtime_error("Image history is empty");
}

void Editor::clearImageEditsHistory() {
    ImageEditsHistory.clear();
}

void Editor::resetImageEditsHistory() {
    while (ImageEditsHistory.size() > 1) {
        ImageEditsHistory.pop_back();
    }
}

void Editor::addToImageEditsHistory(std::unique_ptr<ImagePNG> image) {
    ImageEditsHistory.push_back(std::move(image));
}