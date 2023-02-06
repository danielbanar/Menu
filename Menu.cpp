#include "menu.h"
Menu::Menu() : iSelectedElement(INVALID)
{
	firstBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	secondBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
}
void Menu::AddLabel(const std::string& text)
{
	this->vecElements.push_back(new MenuElement(text));
}
void Menu::AddCheckBox(const std::string& text, bool state)
{
	this->vecElements.push_back(new CheckBox(text, state));
}
void Menu::AddFloatBar(const std::string& text, float defaultValue, float min, float max, float step)
{
	this->vecElements.push_back(new FloatBar(text, defaultValue, min, max, step));
}
void Menu::CreateBuffer()
{
	this->buffer.clear();
	for (auto it = vecElements.begin(); it != vecElements.end(); it++)
	{
		auto i = std::distance(vecElements.begin(), it);
		i == iSelectedElement ? buffer += Invert((*it)->sLabel) :
			buffer += (*it)->sLabel;

		if (CheckBox* checkbox = dynamic_cast<CheckBox*>(*it))
		{
			buffer += std::string("\t[") + (checkbox->bValue ? "ON" : "OFF") + ']';
		}
		else if (FloatBar* bar = dynamic_cast<FloatBar*>(*it))
		{
			char buf[16];
			sprintf_s(buf, "\t%.3f", bar->fValue);
			buffer += buf;
		}

		buffer += '\n';
	}
}
void Menu::ManageInput()
{
	static bool bLeft, bRight, bUp, bDown, bEnter;
	bLeft = GetAsyncKeyState(VK_LEFT) & 1;
	bRight = GetAsyncKeyState(VK_RIGHT) & 1;
	bUp = GetAsyncKeyState(VK_UP) & 1;
	bDown = GetAsyncKeyState(VK_DOWN) & 1;
	bEnter = GetAsyncKeyState(VK_RETURN) & 1;
	if (!vecElements.size())
		return;
	if (iSelectedElement == INVALID)
		iSelectedElement = 0;

	if (CheckBox* checkbox = dynamic_cast<CheckBox*>(vecElements[iSelectedElement]))
	{
		if (bEnter || bLeft || bRight)
			checkbox->bValue = !checkbox->bValue;
	}

	if (FloatBar* bar = dynamic_cast<FloatBar*>(vecElements[iSelectedElement]))
	{
		if (bLeft)
			bar->fValue -= bar->fStep;
		if (bRight)
			bar->fValue += bar->fStep;

		//Experimental direct entering
		if (bEnter)
			std::cin >> bar->fValue;

		//Clamping
		if (bar->fValue < bar->fMin)
			bar->fValue = bar->fMin;
		else if (bar->fValue > bar->fMax)
			bar->fValue = bar->fMax;
	}
	if (bDown)
		iSelectedElement++;
	if (bUp)
		iSelectedElement--;

	//Rollover
	if (iSelectedElement < 0)
		iSelectedElement = vecElements.size() - 1;
	else if (iSelectedElement >= vecElements.size())
		iSelectedElement = 0;
}
void Menu::Update()
{
	//Clear Back Buffer
	cls(secondBuffer);
	ManageInput();
	//Write to back buffer
	CreateBuffer();
	WriteConsoleA(secondBuffer, &buffer[0], buffer.size(), nullptr, nullptr);
	//swap buffers
	std::swap(firstBuffer, secondBuffer);
	//Set first buffer active
	SetConsoleActiveScreenBuffer(firstBuffer);
}
std::string Invert(const char* str)
{
	return std::string("\033[7m") + str + "\033[0m";
}
std::string Invert(const std::string str)
{
	return "\033[7m" + str + "\033[0m";
}

void cls(HANDLE handle)
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(handle, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(handle, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(handle, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(handle, topLeft);
}