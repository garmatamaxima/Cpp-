
#include <cmath>
#include <string>
#include <iostream>

#define DEBUG 1

void OutputFormatted(char* text, int indexSize)
{
	for (int i{ 0 }; i < indexSize; ++i)
	{
		if ((short)(text[i]) > 9)
		{
			char outputhex{};
			switch (text[i])
			{
			case 10: { outputhex = 'A'; break; }
			case 11: { outputhex = 'B'; break; }
			case 12: { outputhex = 'C'; break; }
			case 13: { outputhex = 'D'; break; }
			case 14: { outputhex = 'E'; break; }
			case 15: { outputhex = 'F'; break; }
			case 16: { outputhex = 10; break; }
			}
			std::cout << outputhex;
		}
		else
		{
			std::cout << static_cast<short>(text[i]);
		}

	}
	std::cout << '\n';
}

template <typename T>
void base10convert(T value, int targetBase)
{
	T temporaryOriginalValue{value};

	constexpr int sizetype{sizeof(T)*8};

	char buffer[ sizetype ] {};
	for (int i1{ sizetype-1 }; i1 >= 0  ; --i1)
	{
		buffer[i1] = std::abs(value % targetBase);
		value /= targetBase;
	}

	std::cout << temporaryOriginalValue << " to base" << targetBase << " -> ";
	OutputFormatted( buffer, sizetype );
}

template <typename T, typename Y>
void baseconvert(char* text, int text_size)
{

}



int main()
{
	base10convert(279i16, 2 );
	base10convert(279i16, 8);
	base10convert(279i16, 16);
	std::cout  << '\n';
	base10convert(1591i16, 2);
	base10convert(1591i16, 8);
	base10convert(1591i16, 16);
	std::cout << '\n';
	base10convert(9092008i32, 2);
	base10convert(9092008i32, 8);
	base10convert(9092008i32, 16);
	std::cout << '\n';
	


	return 0;
}