#pragma once
#include <chrono>

inline namespace
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
		const double& deltaTime_micros_{ deltaTime_micros };

	private:

		// initalises time points with values of current time.
		high_resolution_clock::time_point startInterval{ high_resolution_clock::now() };
		high_resolution_clock::time_point endInterval{ high_resolution_clock::now() };

		// gets the delta time
		float deltaTime_ms{};
		double deltaTime_micros{};

	};

}