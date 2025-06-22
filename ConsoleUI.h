#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>

class ConsoleUI {
public:
	void displayEditMenu();
	int getIntFromUser(std::string_view message);
	int getRGBValueFromUser(std::string_view message);
	std::string getStringFromUser(std::string_view message);
	std::string getValidImagePathFromUser();

	bool isValidImage(std::string imageName);
	bool clearFailedExtraction();
	void ignoreLine();

private:

};

#endif 
