#pragma once
#include <vector>
#include <iostream>
#include <windows.h>
#include <string>  
#define INVALID -1
struct MenuElement
{
	MenuElement() {}
	MenuElement(const std::string& str) : sLabel(str) {}
	std::string sLabel;
};
struct MenuCheckBox : public MenuElement
{
	MenuCheckBox() : bValue(false) {}
	MenuCheckBox(const std::string& str, bool state) : bValue(state) { sLabel = str; }
	bool bValue;
};
struct MenuProgressBar : public MenuElement
{
	float fValue;
};
class Menu
{
public:
	Menu();
	void AddLabel(const std::string& text);
	void AddCheckBox(const std::string& text, bool defaultState);
	void AddProgressBar(const std::string& text, float defaultValue);
	void CreateBuffer();
	void ManageInput();
	std::string buffer;
private:
	std::vector<MenuElement> vecElements;
	int iSelectedElement;
};
std::string Invert(std::string& str);