#include "util.h"


void sort2(int& left, int& right)
{
	if (left > right) { std::swap(left, right); }
}

std::ostream& operator<<(std::ostream& to_stream, const Color& color_object)
{
	to_stream << "r" << (short)(color_object.red) << " g" << (short)(color_object.green) << " b" << (short)(color_object.blue);
	return to_stream;
}

Color colorSelector(ColorEnum color)
{
	Color output;

	switch (color)
	{
	case RED: 
		output.red = 255;
		output.blue = 0;
		output.green = 0;
		return output;
	case GREEN:
		output.red = 0;
		output.blue = 0;
		output.green = 255;
		return output;
	case BLUE:
		output.red = 0;
		output.blue = 255;
		output.green = 0;
		return output;
	default:
		output.red = 90;
		output.blue = 90;
		output.green = 90;
		return output;
	}
}