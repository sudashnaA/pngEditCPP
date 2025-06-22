#include "ConsoleUI.h"
#include <filesystem>
#include <iostream>

void ConsoleUI::displayEditMenu()
{
    std::cout << "\n";
    std::cout << "Image Editing Options:\n";
    std::cout << "1. Adjust Brightness\n";
    std::cout << "2. Adjust Saturation\n";
    std::cout << "3. Adjust Hue\n";
    std::cout << "4. Apply Grayscale Filter\n";
    std::cout << "5. Apply Sepia Filter\n";
    std::cout << "6. Apply Color Tint\n";

    std::cout << "\n";
    std::cout << "99. Reset Edits\n";
    std::cout << "88. Save Image\n";
    std::cout << "77 Select Another Image\n";
    std::cout << "66. Exit\n";
}

std::string ConsoleUI::getStringFromUser(std::string_view message)
{
    while (true) {
        std::string input{};
        std::cout << message;
        std::getline(std::cin, input);

        if (clearFailedExtraction()) {
            std::cout << "Invalid Input";
            continue;
        }

        return input;
    }
}

std::string ConsoleUI::getValidImagePathFromUser() {
    // Get the path to a valid image from the user
    while (true) {
        std::string filePath{ getStringFromUser("Enter an image file path ") };

        if (isValidImage(filePath)) {
            return filePath;
        }

        std::cout << "Not a valid image file path! \n";
    }
}

int ConsoleUI::getIntFromUser(std::string_view message)
{
    while (true) {
        int input{};
        std::cout << message;
        std::cin >> input;

        if (clearFailedExtraction()) {
            std::cout << "Invalid Input";
            continue;
        }

        ignoreLine();
        return input;
    }
}

int ConsoleUI::getRGBValueFromUser(std::string_view message)
{
    int input{};
    while (true)
    {
        input = getIntFromUser(message);
        if (input >= 0 and input <= 255)
        {
            break;
        }

        std::cout << "Input out of range (0, 255)\n";

    }
    return input;
}

bool ConsoleUI::isValidImage(std::string imagePath) {
    return std::filesystem::exists(imagePath);
}

void ConsoleUI::ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool ConsoleUI::clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}