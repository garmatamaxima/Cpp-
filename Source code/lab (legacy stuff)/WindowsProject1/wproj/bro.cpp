
#include <cstdint> // for std::uint8_t
#include <iostream>
#include <string>
#include <string_view>
#include <cassert> // for assert
#include <limits> // for std::numeric_limits
#include <stdlib.h>
#include <iomanip>

using namespace std;

// A safer (but slower) version of powint() that checks for overflow
// note: exp must be non-negative
// Returns std::numeric_limits<std::int64_t>::max() if overflow occurs
constexpr std::int64_t powint_safe(std::int64_t base, int exp)
{
	assert(exp >= 0 && "powint_safe: exp parameter has negative value");

	// Handle 0 case
	if (base == 0)
		return (exp == 0) ? 1 : 0;

	std::int64_t result{ 1 };

	// To make the range checks easier, we'll ensure base is positive
	// We'll flip the result at the end if needed
	bool negativeResult{ false };

	if (base < 0)
	{
		base = -base;
		negativeResult = (exp & 1);
	}

	while (exp > 0)
	{
		if (exp & 1) // if exp is odd
		{
			// Check if result will overflow when multiplied by base
			if (result > std::numeric_limits<std::int64_t>::max() / base)
			{
				std::cerr << "powint_safe(): result overflowed\n";
				return std::numeric_limits<std::int64_t>::max();
			}

			result *= base;
		}

		exp /= 2;

		// If we're done, get out here
		if (exp <= 0)
			break;

		// The following only needs to execute if we're going to iterate again

		// Check if base will overflow when multiplied by base
		if (base > std::numeric_limits<std::int64_t>::max() / base)
		{
			std::cerr << "powint_safe(): base overflowed\n";
			return std::numeric_limits<std::int64_t>::max();
		}

		base *= base;
	}

	if (negativeResult)
		return -result;

	return result;
}

constexpr bool isEven(int input)
{
	return input % 2 == 0;
}

// Relative epsilon scales with magnitude of biggest value input
bool fequality(float operand1, float operand2, float relativeEpsilon, float Epsilon)
{
	// check if within range of Epsilon
	if (std::abs(operand1 - operand2) <= Epsilon) { return true; }
	// check if within range of relative epsilon (Donald Knuth's algorithm)
	return (std::abs(operand1 - operand2) <= ( std::max( std::abs(operand1), std::abs(operand2) ) * relativeEpsilon));
}

int add(int x, int y)
{
	return x + y;
}

int main()
{
	std::cout << '\n';
	float xf{ 0.10f };
	float yf{ 0.20f };
	float zf{ 0.30f };
	float outputlist[100];
	bool noTrue{ false };
	std::cout << std::setprecision(9) << std::fixed ;
	short concatcounter{ 0 };

	for (short i{ 0 }; i < 99; ++i)
	{
		xf += 0.1f;
		outputlist[i] = xf;
		
		if (concatcounter > 4)
		{
			std::cout << '\n';
			concatcounter = 0;
		}

		std::cout << outputlist[i] << ' ';
		concatcounter += 1;

	}
	

	return 0;
}



/*
std::int16_t getUserAge()
{
	std::int16_t age{};
	std::cout << "enter your age: ";
	std::cin >> age;
	return age;
}

std::string getUserName()
{
	std::string name{};
	std::cout << "enter your name: ";
	std::getline(std::cin >> std::ws, name);
	return name;
}

void miniprogram_agefordriving()
{
	std::string uin_name1, uin_name2;
	int uin_age1, uin_age2;
	constexpr int age_limit{ 16 };


	uin_name1 = getUserName();
	uin_age1 = getUserAge();

	uin_name2 = getUserName();
	uin_age2 = getUserAge();

	if (uin_age1 <= age_limit)
	{
		std::cout << "your age is insufficient for driving a car mr." << uin_name1 << '\n';
	}
	else
	{
		std::cout << "your age is sufficient for driving a car mr." << uin_name1 << '\n';
	}

	if (uin_age2 <= age_limit)
	{
		std::cout << "your age is insufficient for driving a car mr." << uin_name2 << '\n';
	}
	else
	{
		std::cout << "your age is sufficient for driving a car mr." << uin_name2 << '\n';
	}
}

int getValue()
{
	std::cout << "Enter an integer: ";

	int x{};
	std::cin >> x;
	return x;
}

void printCalculation(int x, int y, int z)
{
	std::cout << x + (y * z);
}

constexpr float divis(float x, int y)
{
	return x / y;
}

int main()
{
	int int_x{ 7 }, int_y{ 4 };
	float f_x{ 7.0f }, f_y{ 4.0f };

	cout << "int 4 / int 7 = " << int_y / int_x << '\n';
	cout << "float 7 / int 4 = " << divis(f_x, int_y) << '\n';

	

	return 0;
}
*/