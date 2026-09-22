
#include <cstdint> // for std::uint8_t
#include <iostream>

int main()
{
  std::cout << "How old are you?\n";

  std::uint8_t age{};
  std::cin >> age;

  std::cout << "Allowed to drive a car in Texas: ";

  if (age >= 16)
      std::cout << "Yes";
  else
      std::cout << "No";

  std::cout << ".\n";

  return 0;
}

/*
int main() 
{
	std::string fullName;
	int age;
	std::cout << "enter your full name" <<  '\n' ;
	std::getline(std::cin >> std::ws, fullName);
	std::cout << "enter your age" <<  '\n' ;
	std::cin >> age;

	std::cout << "your age + lenght of name == " << age + static_cast<int>( fullName.length() ) <<  '\n' ;
	return 0;
}
*/
/*
int main()
{

	
	std::string mstrin{"xxx"s}



	std::string uinput{};
	std::getline(std::cin >> std::ws, uinput); // std::ws input manipulator allows to ignore leading whitespaces
	// aka: whitespace char's that are placed in front of any useful text chars.
	
	std::string dookiepoop{"ok"};
	std::cout << dookiepoop.length() <<  '\n' ;

	std::int64_t first_uint, second_uint;
	std::cout << "input value that contains between 1 and 15? input like that: first_input second_input" <<  '\n' ;
	std::cin >> first_uint >> second_uint;

	if (i32clamp(first_uint)  < 1 && i32clamp(second_uint) > 15)
	{
		std::cout << "true!" <<  '\n' ;
	}
	else 
	{
	std::cout << "false!" <<  '\n' ;
	}
	return 0;
}
*/
