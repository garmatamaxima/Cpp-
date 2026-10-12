
#include <string>
#include "random.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <thread>

#include <iostream>
#include <fstream>

class TimeInterval
{
    using steadyClock = std::chrono::steady_clock;

public:

    const steadyClock::time_point& start_{start};
    const steadyClock::time_point& end_{ end };
    const std::chrono::duration<double>& difference_{ diff };

    void startInteval()
    {
        start = steadyClock::now();
    }

    // ending interval updates difference too. returns 1 if new difference was used, returns 0 if no changes.
    bool endInterval()
    {
        end = steadyClock::now();
        std::chrono::duration<double> newDiff = end - start;
        if (newDiff != diff)
        {
            diff = newDiff;
            return 1;
        }
        return 0;
    }

private:
    steadyClock::time_point start{};
    steadyClock::time_point end{};
    std::chrono::duration<double> diff{};
};

int main()
{

    return 0;
} 