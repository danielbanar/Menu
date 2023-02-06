#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void cls(HANDLE);
#define INVALID -1
struct MenuElement
{
public:
	MenuElement() {}
	virtual ~MenuElement() {}
	MenuElement(const std::string& str) : sLabel(str) {}
	std::string sLabel;
	std::string tag;
};
struct CheckBox : public MenuElement
{
	CheckBox() : bValue(false) {}
	CheckBox(const std::string& str, bool state) : bValue(state) { sLabel = str; }
	bool bValue;
};
struct FloatBar : public MenuElement
{
	FloatBar() : fValue(0.f), fMin(FLT_MIN), fMax(FLT_MAX), fStep(1.f) {}
	FloatBar(const std::string& str, float defaultValue, float min, float max, float step) : fValue(defaultValue), fMin(min), fMax(max), fStep(step) { sLabel = str; }
	float fValue, fMin, fMax, fStep;
};
struct ProgressBar : public MenuElement
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
	void AddFloatBar(const std::string& text, float defaultValue, float min, float max, float step);
	void CreateBuffer();
	void ManageInput();
	void Update();
	std::string buffer;
private:
	std::vector<MenuElement*> vecElements;
	int iSelectedElement;
	HANDLE firstBuffer;
	HANDLE secondBuffer;
};
std::string Invert(const char*);
std::string Invert(const std::string str);