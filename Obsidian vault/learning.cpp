
//C++20

//To use the functionality defined within the iostream library, we need to include the iostream header at the top of any code file
// that uses the content defined in iostream
// This is preprocessor directive

#include <cstdio>
#include <iostream>
#include <string>


/// -------------------- CHAPTER 1 LEARNCPP.COM -------------------- ///

/*
    // ---- CHAR: ----
    Character data types are: single digit -> 'A' taking 1 byte and string "I am a string, hi" taking more than 1 byte
    Values that are placed directly into the source code are called literals
    !!! Leading whitespace characters are spaces, tabs, and newlines.

    // ---- OBJECTS: ----
    In C++, we use objects to access memory. A named object is called a variable. Each variable has an identifier (a name), a type,
     and a value
    A variable�s type is used to determine how the value in memory should be interpreted.

    // ---- INSTANTIATION: ----
    The term instantiation is a fancy word that means a variable has been created (allocated)
    and initialized (this includes default initialization)
    !!! declaration introduces a variable name to the computer program and assigns it to a datatype.

    // ---- DECLARATION: ----

    // ---- DEFINITION: ----

    // ---- SIDE EFFECTS: ---- #TODO -> side effects of expressions and not only them.

    // ---- UNDEFINED BEHAVIOUR: ----

*/

using std::string;

void statements() {
  // TODO
}

void asignment_and_initalisation()
{
    std::cout << "/ This is Assignment and Initalisation outputs: \n";

    // ---- DIRECT LIST INITALISATION, or just LIST INITALISATION: ----

    /*
    this is definition, declaration and initalisation of a variable,
    "=" is an assignment operator
    "{}" is an initializer (The process of specifying an initial value for an object)
    */

    // (Plain english) -- define a variable named "first" of type integer then initalise it with initial value 1.
    int first {1};

    std::cout << "list init >>" << first << "\n";

    // ---- ZERO INITALISATION, VALUE INITALISATION: ----

    int width{}; // will implicitly initialize the variable to zero

    std::cout << "zero init >> " << width << "\n";


    // ---- COPY LIST INITALISATION: ----

    // Rarely used

    // (Plain english) -- define a variable named "alpha" of type integer then initalise it with initial value 1.
    int alpha = { 1 };

    std::cout << "copy list init >> " << alpha << "\n";

    // ---- COPY INITALISATION: ----

    // different syntax for initalising a variable
    // (Plain english) -- define a variable named "second" of type integer then initalise it with initial value of 1
    int second = 1;

    std::cout << "copy init >> " << second << "\n";

    // ---- DIRECT INITALISATION: ----

    // Potentially dangerous!
    // (Plain english) -- define a variable named "third" of type integer then initalise it with initial value of 1
    int third (1);

    std::cout << "direct init >> " << third << "\n";

    // ---- ASSIGNMENT: ----

    // this is assignment of a variable named "first", assignment is done to existing variable only
    // (Plain english) -- variable "first" is equal to 3
    first = 3;

    std::cout << "Assignment of variable to different value >> " << first << "\n";

    // ---- IMPORTANT TO KNOW!!!: ----

    /* (Narrowing conversions) --

    * Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold
    * such a conversion is a narrowing conversion, since the fractional part of the value will be lost, compiler will gladly convert
     4.5 to 4.
    * LIST INITALISATION will throw an compile error, because it does not allow it.

    */
}

void may_be_unused()
{
    // ---- MAY BE UNUSED: ----

    /*
    Some values can be unused which is undesirable
    But sometimes you can have a list of variables that have to be saved for later use
    */
    // [[maybe_unused]] is an attribute, which tells compuler that variable is okay to be unused
    [[maybe_unused]] double pi{ 3.14159 };
    [[maybe_unused]] double randomsomething{ 2323.54359 };
    [[maybe_unused]] int one{ 1 }, two{ 2 }, three{ 3 };

    // legal but bad practice
    int i_am_useless{ 1 };

}

void iostream()
{
    float a_variable {123};
    float your_age{};
    float age_left{};
    int x{};
    int y{}; // define variable y to hold user input (and value-initialize it)


    // ---- COUT, CHARACTER OUT: ----
    /*
    "std::cout" is a statement (��������), std:: means we take a function from standart library, cout is the part of iostream library
     inside standart library
    "<<" INSERTION OPERATOR: allows to display information on console and concatenate (connect strings together, ��������� ����� � ����)
    "\n" is a format specifier, it allows for walking to a next string in console, moves console cursor to new line
    "std::endl" also moves console cursor to new line + flushes the buffer of a console (is slow)
    */
    std::cout << "Hello World!, i am std::cout function!" << std::endl;
    std::cout << "numbers... " << 1 << ", " << 1.001 << ", " << a_variable << "\n";
    std::cout << "enter your age please. \n";

    // this syntax is also valid
    std::cout << "first part -"
        " and a second part! \n";


    // ---- CIN, CHARACTER IN: ----
    /*
    ">>" EXTRACTION OPERATOR: allows to put the input data from keyboard into console INTO a variable (which can be used in subsequent
     statements).
    !!! cin works like a conveyor belt, it takes inputs be it single extraction operator ">>" or n (multiple) of them, then it reads the
     first value and puts it in a buffer, then processes, then allocates into a variable. extraction stops at a leading whitespace number
     like space, tab and "\n" (newline) . chaining extraction operators allows to input multiple values, that cin reads through them

    IOSTREAM library expects Enter key input to send data to cin.
    !!! Enter key sends '\n' special character into cin buffer

    !!! WHEN EXTRACTION FAILS CIN DOES NOT FLUSH ITS BUFFER and always outputs 0
    */
    std::cin >> your_age;

    std::cout << your_age << "\n";

    /*
    In this example CIN attempts to extract multiple variables from inputs, How it works?
    CIN reads first value digit by digit, when it encounters a white line character like Space or Tab it starts
     extracting to the next variable. When any non integer is encountered extraction is failed, next variables will be set to 0.
    */
    int u{}, i{}, o{};
    std::cin >> u >> i >> o;
    std::cout << u << ' ' << i << ' ' << o << '\n';
}

void formatting()
{
    // operators should be put at the beginning of a new line.
    std::cout << 1 + 2
        + 2
        * 2
        / 2;

    // GOOD PRACTICE: Using whitespaces for aligning operators
    int cost      = 62;
    int item_id   = 133;

}

void literals()
{
    // Data written inside of source code is called "literal constant" or just "literal"
    std::cout << "i am literal - " << 5;
}

void operators()
{
//  Operator is a process involving zero or more input values called "operands" that produces a new value called "output value"
//  the specific operation to be performed is denoted by a symbol called operator, the output value
//  of an operation is often called "return value"
//  Math (arithmetic) operators are executed in order called PEMDAS.

    /*
     ARITHMETIC OPERATORS:   addition +, substraction -, multiplication *, division /, modulo, reminder % (integer reminders only)
     TYPES OF OPERATORS:
     Unary - acts on one operand, -x is an unary operand.
     Binary - act on two operands, left and right value. x + y is an binary operand.
     Ternary - same logic, acts on three operands.
     Nullary - operand acts on zero operands
    */

    /*
    Side effects: Most operators produce side effects, x=5 has the side effect of assigning value 5 to variable x.
     The change in variable is observable even when operator ended its execution.
    !!! Operators = and << return their leftmost operand.
    */



    std::cout << "Operands 5 and 2, multiplying them -> " << 5 * 2;

}

void expressions()
{
//  ---- EXPRESSIONS: ----
//  Exression is a non empty sequence of literals, variables, operators and function calls that calculates a value.
//  the process of executing an expression is called "evaluation". The resulting value produced is called "result" or "return value"
//  !!! The last value after executing an evaluation is result.

    int a{ (2 * 3) + 5 };


//  Expressions do not end in semicolon, so compiler wont compile them.
//  Exressions are always evaluated as part of statements!

//  WRONG: compiler wont compile
//  2 + 5

//  RIGHT: EXPRESSION STATEMENT
    int x = {};
    x = 12 + 12; // evaluates to x.

    /*

    2 //          2 is a literal that evaluates to value 2
    a = 5 //      operator+ uses operands a and 5. a evaluates to value 5.
    "hi" //       is a literal that evaluates to "hi"
    literals() // evaluates to return value of a function
    x = 5; // x=5 has side effect of assigning 5 to x, evaluates to x
    x = 2 + 3; // has side effect of assigning 5 to x, evaluates to x.

    */

//  SYNTAX MEANING:
    int y{ 3 + 2 }; // type identifier { expression }

//  SUBEXRPRESSIONs are expressions used as an operands, for example subexressions of x = 4 + 5 are x and 4+5.
//  FULL EXRPESSIONs are expressions that are not subexpressions, 2, 2+3, x=2+3 are full expressions. They can contain zero to more
//  subexpressions.
//  COMPOUND EXPRESSIONs are expressions that contain 2 or more operators, x = 4 + 5 is a compound expression (uses + and = operators)

//  ---- SUMMING IT UP: ----
//  statements are used when we want the program to perform and action. Expressions are used when we want the program to calculate
//  a value.



}

void program1()
{
    int user_input1{};
    int user_input2{};

    std::cout << "Enter an integer: ";
    std::cin >> user_input1;

    std::cout << "Enter another integer: ";
    std::cin >> user_input2;

    std::cout << user_input1 << " + " << user_input1 << " is " << user_input1 + user_input2 << '\n';
    std::cout << user_input1 << " - " << user_input1 << " is " << user_input1 - user_input2 << '\n';
}

// ---- CHAPTER 2 LEARNCPP.COM ----


// ==== FUNCTIONS: ====

//  The function initiating the function call is the "caller" and the function being executed is "callee".
//  A function call is also sometimes called an invocation, with the caller invoking the callee.

//  USER DEFINED FUNCTIONs:
//  Syntax:
//  "return type" (what will function return) "function Name"() <- this is the function header that tells compiler about existence of function
//     {
//     This is the function "body"
//     }

//  !!! In C++ Nested functions are not supported

//  ---- DEFINITION AND DECLARATION OF FUNCTIONS: ----

int foo() // <-- THIS IS function declaration, known as function header. !!! Tells the compiler the function�s name, return type, and parameters.
{
    // This is function definition, known as function body. !!! contains the actual code
    return 0;
}


//  ---- VALUE RETURNING FUNCTIONS: ----

//  return statement can return any valid expression that evaluates to a value type specified in function's definition, for example this function:

float valueReturningFunction(float first_input, float second_input, float third_input)
{
    return (first_input + second_input + third_input) / 3;
}

//  Value returning functions return one value only.
//  !!! A value returing function will produce undefined behaviour if it has no return statement (modern compilers sometimes dont catch the problem).

//  !!! main() function will return 0 if no return statements are provided.
//  main() always has to return a value, 0 is sucessful termination of a program while non 0 values are exit failures.
//  C++ defines meaning of 3 status (exit codes): 0, "EXIT_SUCESS" and "EXIT_FAILURE"
//  The status code is passed back to the OS, which in turn will pass that code to whichewher program started the program returning the status code.

//  ---- VOID FUNCTIONS: ----

//  Void functions dont return values to the caller, but do execute statements in the body of a function.
//  Also void returning functions are called "non-value returning function"

//  putting return statement at the end of a void statement is useful to exit execution earlier.

/*
    Using return statement to exit 3 state condition earlier if x is larger than 10, also an example of good practice as it avoids redundant return and if statements.
    !!! returning a value using void function is forbidden. Return only can be a breaking the function statement.
*/
void voidReturnDemo()
{
    std::cout << "enter a value: ";
    int x{};
    std::cin >> x;

    if (x > 10) {

        std::cout << x << " Is larger than 10\n";
        return;
    }
    else if (x < 10) {

        std::cout << x << " Is Less than 10\n";
    }
    else {

        std::cout << x << " Is 10!\n";
    }
}

//  ---- ARGUMENTS AND PARAMETERS: ----

//  A function parameter is a variable used in the header of a function. They define what kind of data will be passed to function to work with, all parameters must have
//  a data type.

/*
    !!! when a function is called, all of parameters defined in it are created as variables and initalised with arguments using copy initalisation.
    This process is called "pass by value", function parameters that utilize pass by value are called value parameters.
    any valid expression can be passed to parameter.
    The number of arguments must match the number of function parameters
*/

//  For example, when function is called with arguments Xoo and Yoo, function's parameter x is created and initialized with the value of Xoo
//  and parameter y is created and initialized with the value of Yoo.
//  An example call --> parameterDemoFunction(Xoo,Yoo);

int parameterDemoFunction(int x, int y)
{
    return x + y;
}

//  ---- LOCAL VARIABLE LIFETIMES: ----

/*
    Variables defined inside a body of a function are called **Local variables**, function parameters are also considered to be local variables.
    When a function is called its parameters are created and initalised, and variables within the function body are created and initialized at the point of definition.
    Local variables are destroyed in the opposite order of creation at the end of the set of curly braces in which it is defined.
*/
int exampleLifetime(int A, int B) // parameters A and B take the argument values from the caller function, are created and initalised as local variables inside the function.
{
    int o{0}; // o is created and initalised as local variable
    return o + A + B;

} // o, A, B variables created inside this function are destroyed, their lifetime ends here.

//   !!! variable creation and destruction happen when the program is at runtime, not at compile time. **Lifetime is a runtime property**.
//   Any use of an object after it was destroyed will result in undefined behaviour.
//   at some time after destruction of an object, the memory will be "deallocated" (freed for reuse in RAM).

//  ---- LOCAL SCOPE, BLOCK SCOPE: ----

//   Identifiers scope determines whether it can be seen and used within the source code. If identifier can be seen and used, it is considered **in scope**.
//   When an identifier can not be seen, we can not use it, and we say it is **out of scope**.
//   if there is variables x and y defined inside main(), they can be seen and used within main(), not outside it (thats why we pass arguments to other functions).

//   Scope is a compile-time property, and trying to use an identifier when it is not in scope will result in a compile error.

//  Local scope is technically called block scope.
//  !!! The identifier of a local variable has local scope. Local variables defined in one function are also not in scope in other functions that are called.

//  An identifier with local scope is usable from the point of definition to the end of the innermost curly brace containing the identifier (for function parameters, at the end of
//  a function). This ensures local variables cannot be used before the point of definition (even if the compiler opts to create them before then), or after they are destroyed

int blockScopeDemo(int A)

{
    // variable Goo is out of scope and cant be used. identifier "Goo" is unknown to compiler

    int Goo{10}; // Goo is created and initalised. it now exists within local scope of this function

    return Goo + A;

} // Goo and A become **out of scope** here and cant be used. the term for that is **going out of scope**

void something()
{
    // variable Goo is out of scope here.
}

//  ---- FUNCTIONAL SEPARATION: ----

//  Identifiers x can be declared in two different functions, due to local scope they will not interfere with eachother, this is called **Functional separation**. Important to know
//  that they will point to separate variables.

int exampleSeparation1()
{
    int x{5};
    return x;
}

int exampleSeparation2()
{
    int x{10};
    return x;
}

//  exampleSeparation2() and exampleSeparation1() both have identifiers x in their local scope, but they point to different variables with different values
//  that exist within those functions.

//  **good practice**: defining local variables close to their use.

//  ---- TEMPORARY OBJECT: ----

//  temporary objects are created by a compiler automatically when they are needed. They are unnamed objects with no identifier(name).

void temporaryObjectDemo()
{
   std::cout << 15 - exampleSeparation1(); // when exampleSeparation1() function ends, it returns its value to the temporary object that compiler creates.
}
// So, return by value returns a temporary object (that holds a copy of the return value) to the caller.
// temporary objects have no scope (scope is tied to identifier) and are destroyed at the end of a full expression they were created in.

//  ---- FORWARD DECLARATION AND DEFINITION: ----

//  This setup will produce an compilation error, because compiler works sequentially.

void forwardDeclaration_demoProblem()
{
   std::cout << adder_demoProblem(5,5);
}


float adder_demoProblem(float x, float y)
{
   return x+y;
}






int main()
{
  int mainloop_iteration{1};

  while (mainloop_iteration <= 10) {

    voidReturnDemo();

    std::cout << "\nMainloop iteration: " << mainloop_iteration << " out of 10."
              << "\n\n";
    mainloop_iteration += 1;
  }

    return 0;
}
