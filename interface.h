#include <string>
#include <string_view>

#ifndef INTERFACE_H
#define INTERFACE_H

void displayEditingMenu();
	
int getIntFromUser(std::string_view message);

int getRGBValueFromUser(std::string_view message);

std::string getStringFromUser(std::string_view message);

#endif