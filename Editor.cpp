#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include "stb_image_write.h"
#include "stb_image.h"

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

    auto image{ std::make_unique<ImagePNG>(imageName, imgData, height, width, channels) };
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
    if ((int)ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL) < 32)
    {
        std::cerr << "Failed to open output image.\n";
    }
}

const std::unique_ptr<ImagePNG>& Editor::getLatestImage() {
    if (!ImageEditsHistory.empty()) {
        return ImageEditsHistory.back();
    }
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