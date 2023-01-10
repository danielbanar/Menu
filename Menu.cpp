#include "menu.h"
Menu::Menu() : iSelectedElement(INVALID) {}
void Menu::AddLabel(const std::string& text)
{
	this->vecElements.push_back(MenuElement(text));
}
void Menu::AddCheckBox(const std::string& text, bool state)
{
	this->vecElements.push_back(MenuCheckBox(text, state));
}
void Menu::CreateBuffer()
{
	this->buffer.clear();
	for (auto it = vecElements.begin(); it != vecElements.end(); it++)
	{
		auto i = std::distance(vecElements.begin(), it);
		if (i == iSelectedElement)
			buffer += Invert(it->sLabel) + '\n';
		else
			buffer += it->sLabel + '\n';
	}
}
void Menu::ManageInput()
{
	if (!vecElements.size())
		return;
	if (iSelectedElement == INVALID)
		iSelectedElement = 0;
	if (GetAsyncKeyState(VK_DOWN) & 1)
		iSelectedElement++;
	if (GetAsyncKeyState(VK_UP) & 1)
		iSelectedElement--;
	if (iSelectedElement < 0)
		iSelectedElement = vecElements.size() - 1;
	else if (iSelectedElement >= vecElements.size())
		iSelectedElement = 0;
}
std::string Invert(std::string& str)
{
	return "\033[7m" + str + "\033[0m";
}