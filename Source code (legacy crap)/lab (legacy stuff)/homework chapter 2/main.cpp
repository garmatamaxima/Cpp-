
#include <iostream>
#include "io.h"

int main()
{
   io::writeAnswer( io::readnumber() );

   io::semanticErrorCannon(1);

   int meh{};
   std::cin >> meh;

   return 0;
}
