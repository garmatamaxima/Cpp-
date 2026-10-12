#include <iostream>
#include "io.h"

#include <chrono>
#include <thread>


namespace io
{
   int readnumber()
   {
   int x{};
   std::cin >> x;
   return x;
   }

   void writeAnswer(int variable_Read)
   {
   std::cout << variable_Read << '\n';
   }

   void semanticErrorCannon(int input)
   {
       float iterator{1};
       std::cout << "hi im bum \n";
       while (iterator >-1.0)
       {
          iterator -= 0.1;
          std::cout << "in/iter: " << input / iterator << " in: " << iterator << '\n';
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
       }
   }
}
