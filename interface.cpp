#include <string>
#include <string_view>
#include <iostream>

void displayEditingMenu()
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
    std::cout << "-7. Reset Edits\n";
    std::cout << "-8. Save Image\n";
    std::cout << "-9 Select Another Image\n";
    std::cout << "-1. Exit\n";
}

int getIntFromUser(std::string_view message)
{
    int input{};
    std::cout << message;

    bool validInt = false;
    while (!validInt)
    {
        std::cin >> input;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
        else
        {
            validInt = true;
        }
    }

    return input;
}

int getRGBValueFromUser(std::string_view message)
{
    int input{};
    bool valid{ false };
    while (!valid)
    {
        input = getIntFromUser(message);
        if (input >= 0 and input <= 255)
        {
            valid = true;
        }
        else
        {
            std::cout << "Invalid input\n";
        }
    }
    return input;
}

std::string getStringFromUser(std::string_view message)
{
    std::string input{};
    std::cout << message;
    std::getline(std::cin >> std::ws, input);

    return input;
}