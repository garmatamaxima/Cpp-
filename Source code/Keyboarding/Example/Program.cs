using System;
using System.Text;

namespace Example_LKN
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.Unicode;
            
            // Введення рядка (string) з клавіатури, результат знаходиться у змінній s
            Console.Write("Введіть якийсь рядок: ");
            string s = Console.ReadLine();
            /* попередні два рядки коду можна (якщо потрібно) об'єднати в один:
               string s = Console.ReadLine(); */
            Console.WriteLine("Введено рядок - {0}", s);
            Console.WriteLine();


            // Введення цілого числа з клавіатури, результат знаходиться у змінній number
            Console.Write("Введіть ціле число: ");
            int number = Convert.ToInt32(Console.ReadLine());
            /* попередні два рядки коду можна (якщо потрібно) об'єднати в один:
               int number = Convert.ToInt32(Console.ReadLine()); */
            Console.WriteLine($"Введено число {number}");
            Console.WriteLine();


            // Введення дійсного числа з клавіатури, результат знаходиться у змінній fnumber
            Console.Write("Введіть дійсне число: ");
            double fnumber;
            fnumber = Convert.ToDouble(Console.ReadLine());
            /* попередні два рядки коду можна (якщо потрібно) об'єднати в один:
               double fnumber = Convert.ToDouble(Console.ReadLine()); */
            Console.WriteLine("Введено число {0}", fnumber);
                        
            Console.ReadKey();
        }
    }
}
