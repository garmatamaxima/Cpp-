#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include <Windows.h>

#include "time.h"

/*int WinMain
	(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd 
) {*/	

int main()
{
	bool endProgram{ false };
	Interval clock{};
	std::wstring output { L"elapsed" };

	clock.setStart();
	// std::this_thread::sleep_for(milliseconds(1000));
	clock.setEnd();

	// MessageBoxW(0, L"working", output.c_str(), MB_OK);

	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// second argument wAttributes is specified by two hex digits, first - background color, second - text color. 
	SetConsoleTextAttribute(stdHandle, 0x0C);
	
	std::cout << "first message, fucks";

	while (!endProgram)
	{
		for (int vkey{ 0 }; vkey < 255; ++vkey)
		{
			// if we match one of vkeys and first bit is set true.
			if (GetAsyncKeyState(vkey) & 0b1)
			{
				switch (vkey)
				{
				case VK_ESCAPE: { endProgram = true; }
				}
			}
		}
	}


	return 0;
}
