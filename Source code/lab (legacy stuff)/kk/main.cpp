
#include "util.h"
#include "constants.h"
#include "random.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <type_traits>

#define DEV

namespace cinhelper
{
    /* HELPER FUNCTION, checks if extraction failed, in case of failure clears and ignores cin buffer */
    void extraction_failure_check()
    {
        if (!std::cin)
        {
            std::cin.clear(); // resets an internal error flag 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore all characters in buffer.
        }
    }
    /* HELPER FUNCTION, True is valid input. False if input is invalid */
    bool check_invalid_input() 
    {
        if (!std::cin.eof() && std::cin.peek() != '\n') // If there is extraneous input, treat as failure case
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore all characters in buffer.
            return false;
        }
        return true;
    }

    double getDouble()
    {
        while (true) // Loop until user enters a valid input
        {
            cinhelper::extraction_failure_check();

            std::cout << "Enter a decimal number: ";
            double x{};
            std::cin >> x;

            if (!cinhelper::check_invalid_input())
            {
                continue;
            }

            return x;
        }
    }
    char getOperand()
    {
        char operand{};


        while (true)
        {
            cinhelper::extraction_failure_check();

            std::cout << "input operand: ";
            std::cin >> operand;

            switch (operand)
            {
            case '+': return '+';
            case '-': return '-';
            case '*': return '*';
            case '/': return '/';
            case '%': return '%';
            default:
                if (!cinhelper::check_invalid_input())
                {
                    continue;
                }
            }
        }
    }
}

double safedivision(double x, double y)
{
    assert( !(y == 0) && "INVALID MATH OPERATION, y is equal to 0.");
    assert( x / y < std::pow(2,53) && "OUT OF BOUNDS, output is higher value than allowed");
    assert(x / y > std::pow(2, -53) && "OUT OF BOUNDS, output is lower value than allowed");
    return x / y;
}

double evaluateInputs(double x, char operand, double y)
{
    switch (operand)
    {
    case '+': return x + y;
    case '-': return x - y;
    case '/': return safedivision(x,y);
    case '*': return std::clamp(x * y, DBL_MIN, DBL_MAX);
    case '%': return std::remainder(x, y);
    default : 
        std::cout << "\ninvalid operand!\n"; return 0.0;
    }
}

bool compareDBL(double x, double y) 
{ 
    return std::abs(x-y) < math::precisionTiny;
}

void hiioGame()
{
GameRestart:
    bool gamewin{false};
    int userguess{};
    int randomguess{};
    int tries_counter{};


    randomguess = Random::get(1,100);

#ifdef DEV
        std::cout << "DEV: random number -- " << randomguess << '\n';
#endif

    std::cout << "I chose a number between 1 and 100, try to guess it, you have 7 tries" << '\n';
    while (!gamewin)
    {  
        if (tries_counter != 0)
        {
            std::cout << "tries = " << tries_counter << '\n';
        }
        if (tries_counter >= 7)
        {
            std::cout << "defeat\n\n";
            goto GameRestart;
        }

        std::cout << "your guess? ";
        userguess = std::clamp( static_cast<int>(cinhelper::getDouble()), 1,100);

        if (userguess == randomguess) 
        { 
            std::cout << "You won!\n\n"; 
            tries_counter = 0;
            gamewin = true;
        }
        else if (userguess > randomguess)
        {
            std::cout << "Too high!" << '\n';
            tries_counter += 1;
        }
        else 
        {
            std::cout << "too low!\n"; 
            tries_counter += 1;
        }
    }
}

void calculator()
{
    double x{ cinhelper::getDouble() };
    char operand{ cinhelper::getOperand() };
    double y{ cinhelper::getDouble() };

    double output{ evaluateInputs(x,operand,y) };

    std::cout << std::setprecision(7) << std::fixed << x << ' ' << operand << ' ' << y << " = " << output << '\n';
    // double division precision for x = 1 and y = 0.00000000000000000001 is around 21 digits for y!
}


double get( double matrix[9], int i, int j,  int rowsize)
{
    int acess{ (j + (i - 1) * rowsize) -1 };
    return matrix[ acess ];
}

template <typename T>
bool isrvalue(T&&) { return true; } // this is overloaded function that refers to rvalues

template <typename T>
bool isrvalue(T&) { return false; } // this is overloaded function that refers to lvalues

int main()
{
    int x{};
    std::cout << "variable x is " << (isrvalue(x) ? "rvalue" : "lvalue") << '\n';
    std::cout << "literal 5 is " << (isrvalue(5) ? "rvalue" : "lvalue") << '\n';
}
