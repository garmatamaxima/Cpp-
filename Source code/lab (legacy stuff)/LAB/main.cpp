#include <iostream>
#include <string>

const std::string& getProgramName()
{
    const std::string programName{ "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName(); // undefined behavior

    return 0;
}