
//// header file is needed to propagate declarations to other files

#ifndef BITSETS_H_INCLUDES
#define BITSETS_H_INCLUDES

#include <bitset>

// FUNCTION DECLARATIONS
std::bitset<8> leftrotate(std::bitset<8> bitset_);

std::bitset<4> rotl(std::bitset<4> bits);

void bitset_miniprogram();

// This is inline function that will be included into source files that #include this header file.
// Inline functions are used in header files (useless to be used in .cpp), they give definitions to all translation units that use this header file
// That makes it possible for compiler to inline this function in each source file that aqquires this function definition ( avoids function call overhead ).

// NOTE: add function definitions in header files that are inline, do not add function definitions that arent inline.
// Inline functions are allowed to be defined more than once and they are identical copies.
inline constexpr int adder(int x, int y, int& z_ref)
{
	return z_ref = x + y;
}

// This is inline variable (c++17), it will be included into every source file that includes this header file. Also allowed to be defined multiple times.
inline int bumvariable{ 100 };




// VARIABLE DECLARATIONS

extern const int g_y; // the definition of this variable is located in paired source code file. This is declaration with a purpose to let other files see it.

namespace global
{
	extern const float xoo; // the definition of this variable is located in paired source code file. This is declaration.
}
#endif


