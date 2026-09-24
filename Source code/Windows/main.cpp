#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include <Windows.h>

#undef UNICODE
#define UNICODE

namespace
{
	// type aliases.
	using high_resolution_clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::high_resolution_clock::time_point;
	using milliseconds = std::chrono::milliseconds;
	using microseconds = std::chrono::microseconds;
	using steady_clock = std::chrono::steady_clock;

class Interval
{
	

public:

	void setStart()
	{
		startInterval = high_resolution_clock::now();
	}

	void setEnd()
	{
		endInterval = high_resolution_clock::now();
		deltaTime_ms = (std::chrono::duration_cast<milliseconds>(endInterval - startInterval)).count();
		deltaTime_micros = (std::chrono::duration_cast<microseconds>(endInterval - startInterval)).count();
	}

	const auto& getStart()
	{
		return startInterval;
	}
	
	const auto& getEnd()
	{
		return endInterval;
	}

	const float& deltaTime_ms_{ deltaTime_ms };
	const float& deltaTime_micros_{ deltaTime_micros };

private:

	// initalises time points with values of current time.
	high_resolution_clock::time_point startInterval{ high_resolution_clock::now() };
	high_resolution_clock::time_point endInterval{ high_resolution_clock::now() };

	// gets the delta time
	float deltaTime_ms{};
	float deltaTime_micros{};

};

}

int WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nShowCmd) {	

	bool endProgram{ false };
	Interval clock{};
	std::wstring output { L"elapsed" };

	clock.setStart();
	std::this_thread::sleep_for(milliseconds(1000));
	clock.setEnd();

	std::cout << clock.deltaTime_micros_;

	MessageBoxW(0, L"working", output.c_str(), MB_OK);

	using high_resolution_clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::high_resolution_clock::time_point;

	auto start = std::chrono::high_resolution_clock::now();
	time_point end = std::chrono::high_resolution_clock::now();

	auto duration = end - start;

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
