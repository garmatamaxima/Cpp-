
#include "util.h"
#include <iostream>

void stairPrinter(int lenghtx, int lenghty)
{
    using std::cout;

    for (short i1{ 0 }; i1 < lenghty; ++i1)
    {
        for (short i2{ 0 }; i2 < lenghtx; ++i2)
        {
            cout << i2 + 1 << ' ';
        }
        lenghtx -= 1;
        cout << '\n';
    }
}

void fill_end_printer(int lenx, int leny, int fillx)
{
    short emptyfill{};
    short fullfill{};

    for (short i1{ 0 }; i1 < leny; ++i1)                         // y coordinate loop
    {
        emptyfill = clampmin(lenx - fillx, 0);
        fullfill = lenx - emptyfill;
        for (short emptyi{ 0 }; emptyi < emptyfill; ++emptyi)   // x coordinate empty fill
        {
            std::cout << "  ";
        }
        for (short fulli{ 0 }; fulli < fullfill; ++fulli)       // x coordinate full full with numbers.
        {
            std::cout << clamp(fulli + 1, 0, 9) << ' ';
        }
        std::cout << '\n';

        if (fillx < lenx)
        {
            fillx += 1;                                        // add one to fill demand.
        }

    }
}

void fill_beginning_printer(int lenx, int leny, int fillx)
{
    short emptyfill{};
    short fullfill{};

    for (short i1{ 0 }; i1 < leny; ++i1)                         // y coordinate loop
    {
        emptyfill = clampmin(lenx - fillx, 0);
        fullfill = lenx - emptyfill;
        for (short fulli{ 0 }; fulli < fullfill; ++fulli)       // x coordinate full full with numbers.
        {
            std::cout << clamp(fulli + 1, 0, 9) << ' ';
        }
        for (short emptyi{ 0 }; emptyi < emptyfill; ++emptyi)   // x coordinate empty fill
        {
            std::cout << "  ";
        }

        std::cout << '\n';

        if (fillx < lenx)
        {
            fillx += 1;                                        // add one to fill demand.
        }

    }
}

void fizzbuzz(int range)
{
    for (int i1{ 1 }; i1 <= range; ++i1)
    {
        if (i1 % 3 != 0 && i1 % 5 != 0)
        {
            std::cout << i1;
        }
        else if (i1 % 3 == 0)
        {
            std::cout << i1 << " is fizz";
        }

        if (i1 % 5 == 0)
        {
            std::cout << "buzz";
        }

        std::cout << '\n';
    }
}

void fizzbuzzpop(int range)
{
    bool condition_satisfied{ false };
    for (int i1{ 1 }; i1 <= range; ++i1)
    {
        condition_satisfied = false;
        if (i1 % 3 == 0)
        {
            std::cout << "fizz";
            condition_satisfied = true;
        }
        if (i1 % 5 == 0)
        {
            std::cout << "buzz";
            condition_satisfied = true;
        }
        if (i1 % 7 == 0)
        {
            std::cout << "pop!";
            condition_satisfied = true;
        }
        if (!condition_satisfied) { std::cout << i1; }
        std::cout << '\n';
    }   // checking whether fizz or buzz or pop is independent of each other, so if loops dont need to be if-else chained
        // because if else is exclusive. Meaning that if first condition is true, then second doesnt even execute!
}

void fizzbuzzpop_alt(int range)
{
    for (int i1{ 1 }; i1 <= range; ++i1)
    {
        if (i1 % 3 != 0 && i1 % 5 != 0 && i1 % 7 != 0)
        {
            std::cout << i1 << '\n';
            continue; // skips evaluating next stuff.
        }

        if (i1 % 3 == 0)
        {
            std::cout << "fizz";

        }
        if (i1 % 5 == 0)
        {
            std::cout << "buzz";

        }
        if (i1 % 7 == 0)
        {
            std::cout << "pop!";

        }
        std::cout << '\n';

    }
}

