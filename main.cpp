#include <iostream>
#include <windows.h>
#include "menu.h"

// Driver Code
int main()
{
	Menu menu;
	menu.AddLabel("text1");
	menu.AddLabel("text2");
	menu.AddLabel("text3");
	menu.AddCheckBox("bulo1", true);
	menu.AddCheckBox("bulo2", false);
	menu.AddCheckBox("bulo3", true);
	menu.AddFloatBar("val", 69, 0, 100, 1);
	while (true)
	{
		menu.Update();
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1ms);
	}
	return 0;
}

