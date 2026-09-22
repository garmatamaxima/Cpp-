


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

int foo() // <-- THIS IS function declaration, known as function header. !!! Tells the compiler the function’s name, return type, and parameters.
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

//  First option is to reorder function




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
