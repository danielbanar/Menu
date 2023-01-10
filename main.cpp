#include <iostream>
#include <windows.h>
#include "menu.h"
#include "console.h"
#include <thread>
#include <chrono>
// Driver Code
int main()
{
	Menu menu;
	menu.AddLabel("text1");
	menu.AddLabel("text2");
	menu.AddLabel("text3");
	menu.AddCheckBox("bulo1", true);
	menu.AddCheckBox("bulo2", true);
	menu.AddCheckBox("bulo3", true);
	HANDLE firstBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE secondBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	while (true)
	{
		//Clear Back Buffer
		cls(secondBuffer);
		menu.ManageInput();
		//Write to back buffer
		menu.CreateBuffer();
		//WriteConsoleOutputCharacterA
		WriteConsoleA(secondBuffer, &menu.buffer[0], menu.buffer.size(),nullptr,nullptr);
		//swap buffers
		std::swap(firstBuffer, secondBuffer);
		//Set first buffer active
		SetConsoleActiveScreenBuffer(firstBuffer);
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(50ms);
	}
	return 0;
}

