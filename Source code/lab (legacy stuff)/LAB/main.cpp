#include <iostream>
#include <string>
#include "random.h"
#include <chrono>
#include <vector>
#include <numeric>

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

bool checkDiff(const TimeInterval* timer)
{
    if (timer->end_ > timer->start_) { return 1; };
    return 0;
}

std::string getProgramName()
{
    static std::string programName{ "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

volatile inline int sink; // prevents optimization

void do_some_work(std::size_t size)
{
    std::vector<int> v(size, 42);
    sink = std::accumulate(v.begin(), v.end(), 0); // ensures side effect
}

void test1()
{
    TimeInterval MainClock{};
    TimeInterval* clock_ptr{ &MainClock };

    std::cout << std::fixed << std::setprecision(9) << std::left;
    for (unsigned long long size{ 1ull }; size < 1000'000'0000ull; size *= 100)
    {
        MainClock.startInteval();
        do_some_work(size);
        MainClock.endInterval();

        std::cout << "diff = " << MainClock.difference_ << "; size = " << size << '\n';
    }
}


int main()
{
    TimeInterval clock{};
    TimeInterval* clock_ptr{ &clock };
    
    clock.startInteval();
    test1();
    clock.endInterval();

    std::cout << checkDiff(&clock) << " " << (*clock_ptr).difference_ << '\n';

    return 0;
}