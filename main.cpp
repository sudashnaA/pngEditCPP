#include "imagePNG.h"
#include "Editor.h"
#include "ConsoleUI.h"
#include "ImageProcessor.h"
#include "ImageEditorActions.h"
#include "inputoutput.h"
#include <iostream>
#include <memory>
#include <string>

int main()
{
    auto editor{ std::make_unique<Editor>() };
    auto consoleUI{ std::make_unique<ConsoleUI>() };

    std::string filePath{ consoleUI->getValidImagePathFromUser() };
    // Read the image into memory
    editor->readImage(filePath);
   
    bool editing{ true };
    while (editing)
    {
        auto imageProcessor{ std::make_unique<ImageProcessor>() };

        consoleUI->displayEditMenu();

        int option{consoleUI->getIntFromUser("\nEnter an option\n")};

        switch (option)
        {
        case 1:
        {
            const int brightness{ consoleUI->getRGBValueFromUser("Enter brightness (0, 255) ") };
            auto imageWithBrightnessAdjusted{ imageProcessor->adjustBrightness(editor->getLatestImage(), brightness) };

            editor->addToImageEditsHistory(std::move(imageWithBrightnessAdjusted));
        }
            break;
        case 6:
        {
            const int red{ consoleUI->getRGBValueFromUser("Enter red value (0, 255) ") };
            const int green{ consoleUI->getRGBValueFromUser("Enter green value (0, 255) ") };
            const int blue{ consoleUI->getRGBValueFromUser("Enter blue value (0, 255) ") };
            auto imageWithColorFilter{ imageProcessor->applyColorTint(editor->getLatestImage(), red, green, blue) };

            editor->addToImageEditsHistory(std::move(imageWithColorFilter));
        }
            break;
        case 99:
            editor->resetImageEditsHistory();
            std::cout << "Reset all edits\n";
            break;
        case 88:
            editor->writeEdits();
            editor->openImage(editor->getLatestImage()->getName());
            break;
        case 77:
            editor->clearImageEditsHistory();
            filePath = consoleUI->getValidImagePathFromUser();
            editor->readImage(filePath);
            break;
        case 66:
            editing = false;
            break;
        default:
            std::cout << "Invalid option\n";
            break;
        }
    }

    return 0;
}