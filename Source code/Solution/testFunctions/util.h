
#ifndef UTIL_H
#define UTIL_H
#include <typeinfo>
#include <iostream>

void sort2(int& left, int& right);

enum ColorEnum
{
	RED,
	GREEN,
	BLUE,
};

class penis
{
public:
	float getsize()
	{
		return size + 5;
	}

private:
	float size{ 10 };
	float width{ 5 };
};

struct Color
{
	std::uint8_t red{ 0 };
	std::uint8_t green{ 0 };
	std::uint8_t blue{ 0 };
};

std::ostream& operator<<(std::ostream& to_stream, const Color& color_object);



Color colorSelector(ColorEnum color);
#endif // !UTIL_HEADER