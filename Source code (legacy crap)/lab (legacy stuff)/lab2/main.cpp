
#include <iostream>
#include <random>

#define DEBUG_THIS_PROGRAM
#define INFINITE_CYCLE_THIS_PROGRAM

void stopBeforeExit()
{
   int stopvariable{ };
   std::cin >> stopvariable;
}

void randomGeneratorScript()
{
   std::random_device rd;
   std::mt19937 gen(rd());

   int a[10];

   for (int i = 0; i < 5; ++i)
   {
       a[i] = gen();

       #ifdef DEBUG_THIS_PROGRAM
       std::cout << "rand: " << i << " output: " << a[i] << '\n';
       #endif
   }
   std::cout << std::endl;
}


int main()
{
   int mainloop{0};

   #ifdef INFINITE_CYCLE_THIS_PROGRAM
   mainloop = 1;
   #endif

   while (mainloop)
   {
      stopBeforeExit();
      randomGeneratorScript();
   }
   stopBeforeExit();
}
