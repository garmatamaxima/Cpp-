 
#TODO Вирізка інформації з learning.cpp - [[ch1]] та [[ch2]]. треба переписати цю інформацію сюди в цей блокнот і вставити в <mark style="background: #BBFABBA6;">CHAPTER 1 та CHAPTER 2</mark>.

#TODO inline functions, inline variables. що це

## Assumptions:
compiler toolkit - g++, clang
CPU - x64 bit

# **TERMINOLOGIES**
### *CHAR* 
Character data types are: single digit -> 'A' taking 1 byte and string "I am a string, hi" taking more than 1 byte
Values that are placed directly into the source code are called literals
!!! Leading whitespace characters are spaces, tabs, and newlines.
### *OBJECTS*
In C++, we use objects to access memory. A named object is called a variable. Each variable has an identifier (a name), a type,
and a value
A variable’s type is used to determine how the value in memory should be interpreted.
### *INSTANTIATION*
The term instantiation means that a variable has been created (allocated)
and initialized (this includes default initialization)
declaration introduces a variable name to the computer program and assigns it to a datatype.

### *STATEMENTS*
### *DATA TYPE*
### *IDENTIFIER*
### *SIDE EFFECTS*
### *UNDEFINED BEHAVIOUR*

# **POINTS OF INTEREST**

CH1
##### [[#^3aeab3|Compiler warning levels]] - Compiler arguments meant to catch more errors

CH2
##### [[#One definition rule (ODR) |One definition rule (ODR)]]  - the rule that prevents naming collisions
##### [[#**Definition** and **Declaration**|Definition and Declaration]] - methods of introducing objects to program
##### [[#Compiling it|Compiling a multi file program]]
##### [[#^33cf99|Naming collisions]]
##### [[#^235c54|Scope resolution operator ::]]
##### [[#^49acb7|Translation unit]]
##### [[#^a80905|Including paired header files to source files]]
##### [[#^861673 |Include directories / where std comes from]]
##### [[#^b8be34|Header guards]] - A technique to prevent ODR violations and repeating header includes
##### [[#^52f271|How to design a program]] 

CH3
##### [[#^72040d|How to debug using VS Code]] 
##### [[#^4894b0|The call stack explanation]] 

CH4 
##### [[#^cd24be|Integral (integer) data type]],  [[#^63210c|Fundamental data types table]] 
##### [[#^ce9f81|Fundamental data types size assumptions or standarts]] 
##### [[#^0c22ff|signed keyword]],  [[#^ea88aa|signed integer range]]
##### [[#^40beae | Counting signed integers, why the range is -16  to 15]]
##### [[#^1191b7|overflow leads to undefined behaviour]

##### [[#^874074| Converting numbers to scientific notation]]

##### [[#^dc9f62 | floats are implemented using IEEE 754]]
##### [[#^b2202a| floating point sizes and ranges]]
##### [[#^6588f9| f suffix in values]] - for example `1.01f`
# **MISTAKES AND BUGS**

##### [[#^83565d|Redefinition of a function]]
##### [Over-optimisation mistake](https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/#:~:text=New,substantive)
##### [[#^a0e56c | integer division drops fractional part]]
##### [[#^48655e| signed and unsigned integer math narrowing conversion to unsigned]]


# **CHAPTER 1 ** ...

### COMPILER WARNING LEVELS

^3aeab3

https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-warning-and-error-levels/

# **CHAPTER 2** Headers & preprocessor

### FORWARD DECLARATION AND DEFINITION
##### This program wont compile.

```cpp
#include <iostream>

main()
{
	std::cout << adder(5,5); // this function were not declared nor defined before.
	return 0;
}

float adder(float A, float B)
{
	return A+B;
}
```

Function `adder()` can be reordered so it is declared before `main()`

```cpp
#include <iostream>

float adder(float A, float B)
{
	return A+B;
}

main()
{
	std::cout << adder(5,5); // now compiler were provided with a valid declaration and definition of adder()
	return 0;
}
```

But that method <mark style="background: #FF5582A6;">is limited</mark>, because in some cases functions can call each other, ordering them isnt possible. This is a **circular dependency**.

```cpp
#include <iostream>

void callerOne(int input)
{
	std::cout << input + callerTwo(input); // both functions call each other.
}

void callerTwo(int input)
{
	std::cout << input + callerOne(input);
}

main() { callerTwo(callerOne);  return 0; }
```

---
##### A **forward declaration** allows to declare an identifier before defining it.
To write a forward declaration for a function, we use a **function declaration** statement (also called a **function prototype**). ^b6dea4

``` cpp
float Adder(float Abc, float Bca); // function declaration includes: a return type, identifier and parameters (optional).

float Substract(float,float); // parameter names are optional in function declarations.
```

<mark style="background: #BBFABBA6;">Best practice:</mark> Naming parameters in function declarations.
Forward declaring a function and then not to defining it later will produce a **linker error**

```cpp
int function(int A, int B);

main() 
{
	function(2,3) + function(1,2); // Linker could not find a definition.
}
```

There are different kinds of forward declarations, specific to variables and types.  // #REMINDER 

---
##### Definition and Declaration

A declaration tells the compiler about the existence of an identifier and its associated type. While definition actually implements (for functions and types) or instantiates (for variables) the identifier. **In C++, all definitions are declarations**.

```cpp
void Foo(); // function forward declaration, pure declaration

void Moo() 
{

} // function definition

int X; // variable definition

int O{}; // initalisation
```

![[definitionAnddeclaration| 100%x80]]

---
##### One definition rule (ODR)

<mark style="background: #ABF7F7A6;">1.</mark>
Within a _file_, each function, variable, type, or template in a given scope can only have one definition. Definitions occurring in different scopes (e.g. local variables defined inside different functions, or functions defined inside different namespaces) do not violate this rule.
<mark style="background: #ABF7F7A6;">2.</mark>
Within a _program_, each function or variable in a given scope can only have one definition. This rule exists because programs can have more than one file (we’ll cover this in the next lesson). Functions and variables not visible to the linker are excluded from this rule
<mark style="background: #ABF7F7A6;">3.</mark>
Types, templates, inline functions, and inline variables are allowed to have duplicate definitions in different files, so long as each definition is identical. . ^e89dae


### PROGRAMS WITH MULTIPLE CODE FILES
##### Programs with multiple code files allow to split program's **source code** into different modules
That allows for better design practices.

**The order in which compiler compiles files is not relevant**

<mark style="background: #FFF3A3A6;">!!!</mark>  Compiler compiles each code file individually, so each file has to include preprocessor direcrtives like `#include <some header>` or `#include some_file.cpp`, that ensures each file compiles and links to those external files.

 When an identifier is used in an expression, the identifier must be connected to its definition.
 
- If the compiler has seen neither a forward declaration nor a definition for the identifier in the file being compiled, it will error at the point where the identifier is used.
- Otherwise, if a definition exists in the same file, the compiler will connect the use of the identifier to its definition.
- Otherwise, if a definition exists in a different file (and is visible to the linker), the linker will connect the use of the identifier to its definition.
- Otherwise, the linker will issue an error indicating that it couldn’t find a definition for the identifier.


<mark style="background: #CACFD9A6;">hello.cpp</mark>
```cpp
int helloFunction()
{
   return 12345;
}
```

<mark style="background: #CACFD9A6;">main.cpp</mark>
```cpp
#include <iostream>

int helloFunction(); // Function prototype

main()
{
   std::cout << "I am using a function that exist inside other file: " << helloFunction();
   return 0;
}

```

---
##### Compiling it 
A specific command in powershell is needed:
```powershell
g++ main.cpp hello.cpp -0 program.exe
```

`g++` is the program being called in terminal.
`main.cpp hello.cpp` are files used in **compile line**
`-o` is an **optimisation flag**
`program.exe` is a name of a program

<mark style="background: #FF5582A6;">A mistake:</mark>
```powershell
g++ main.cpp -o program.exe
```

a linker error will appear -> ``undefined reference to `helloFunction()' `` , while function prototype `int helloFunction()` was given, no actual definition of `helloFunction()` body were given
Because it is located in a different code file.


### NAMESPACES
##### In c++ two identical identifiers are not allowed
this produces an error called **naming collision** or **naming conflict**.  ^33cf99

<mark style="background: #CACFD9A6;">main.cpp</mark>
```cpp
int myFunc() // a working code file 
{
	return 0;
}

int main() 
{ 
	myFunc();
	return 0;
}
```

<mark style="background: #CACFD9A6;">a.cpp</mark>
```cpp
int myFunc() // a working code file too, the problem will arise in improper compilation or linking
{
	return 0;
}
```

compiling it like this `g++ main.cpp a.cpp -o program.cpp`  will produce a linker error error. Linker will notice a redefinition of `myFunc()` and throw an error.

<mark style="background: #FF5582A6;">linker error</mark>
will occur in cases if there were defined two identical named functions or global variables in one program.
<mark style="background: #FF5582A6;">compiler error</mark>
will occur in cases if there were defined two identical named functions or global variables in one file.

---
##### Scope regions
Two identifiers with the same name are allowed be declared in different scope regions. But within a scope region all identifiers must be unique

<mark style="background: #FFF3A3A6;">!!!</mark> The body of a function is a scope region
```cpp
void apples() 
{
	double x{}, y{}, z{};
}
void bananas() 
{
	double x{}, y{}, z{}; // no naming collision! they live in different scopes
}
```

---
##### Namespaces
provide a scope region called **namespace scope**, names declared in namespaces are isolated from other scopes. Two functions with identical declarations can be defined inside different namespaces, and no [[#^33cf99| naming collision]] will occur.

In c++ any name/identifier that is not defined inside a class, function or a namespace is a part of a **global namespace** or **global scope** 

![[scope_namespace|620x220]]

<mark style="background: #ABF7F7A6;">1.</mark> identifiers declared inside the global scope are in scope from the poin of declaration to the end of file.
<mark style="background: #ABF7F7A6;">2.</mark> variables can be defined in global scope, but this is <mark class="hltr-red">bad practice</mark>

The `::` symbol is an operator called the **scope resolution operator**, the identifier to the left of the symbol identifies namespace, the symbol to the right of `::` operator is the identifier inside this namespace. 
When an identifier includes a namespace prefix, the identifier is called a **qualified name**. ^235c54

##### Using namespace std
a way to access identifiers inside a namespace is to use a **using-directive statement**, it allows to acces the names inside a namespace without using a namespace prefix. 

This is <mark style="background: #FF5582A6;">bad practice</mark> to use identifiers from [[#std library|std library]]. If standart library will get updated in the next version of c++, new names/identifiers will conflict with old ones in the global namespace.

<mark style="background: #CACFD9A6;">main.cpp</mark>
```cpp
#include <iostream> // imports declaration of std::cout into the global scope

using namespace std; // this is a using-directive that allows us to access names in the std namespace with no namespace prefix

int main()
{
    cout << "Hello world!";
    return 0;
}
```

--- 
##### Curly braces and intended code
are often used to delineate a scope region that is nested within another scope region,braces are also used for some non-scope-related purposes, such as list initialization

```cpp
int foo(int A, int B) // parameters are within scope of this function
{ // braces used to delineate nested scope region for function foo()
	return A + B; 
} // A and B go out of scope here

int main()
{ // braces used to delineate nested scope region for function main()
    foo(5);

    int x { 6 }; // x is defined within the scope of main()
    std::cout << x << '\n';

    return 0;
} // x goes out of scope here
// foo and main (and std::cout) go out of scope here (the end of the file)
```

### PREPROCESSOR

each code file goes through the preprocessor first, then compiler.  The stage where preprocessor works is called **Preprocessing phase**, when preprocessor runs it scans through code file searching for **preprocessor directives**. <mark class="hltr-yellow">!</mark> preprocessor does not use C++ syntax  

The final output of the preprocessor contains no directives -- only the output of the processed directive is passed to the compiler. The final output of preprocessor is called **translation unit**
Preprocessor also removes comments and ends each translation unit in a newline character ^49acb7

All preprocessor directives end on a newline, not a semicolon (the statement).

##### `#Include`
is a preprocessor directive used for including header files. Preprocessor then replaces the directive with the contents of a file included. 
<mark style="background: #FFF3A3A6;">!</mark> Preprocessor can process directives recursively, if included file has directives, it will process them too.

`#include` directive can include: Header files, source code files, std headers.

```cpp
#include <iostream> // preprocessor will replace this directive with contents of iostream header
#include "adder.h" // can also include header files
#include "friend.cpp" // and cpp files

using namespace std

int main() 
{
	cout << "im lucky bon bon"
	return 0;
}
```

<mark class="hltr-orange">An important reminder</mark> - preprocessor directly inserts contents of an included files, replacing the `#include` directive.

##### `#define`
The `#define` directive can be used to create a macro. In C++, a **macro** is a rule that defines how input text is converted into replacement output text.
There are two basic types of macros: _object-like macros_, and _function-like macros_.

Macros are useful in a technique called **header guard**, that allows to use `#ifndef` directive to include header contents only once.

```cpp

#define MACRO "name" // will replace each MACRO by "name"

```
##### `#if`
 #TODO на learn.cpp є матеріал глава 2.10
##### `#endif`
#TODO на learn.cpp є матеріал глава 2.10

##### `#ifndef`
Is a directive that means "If not defined", it is useful in a technique called **header guard**, to prevent including header files more than once ^b8be34

<mark class="hltr-grey">myHeader.h</mark>
```cpp
#ifndef MY_IDENTIFIER // if this preprocessor identifier were not defined, it will execute that preprocessor command
#define MY_IDENTIFIER // defines identifier that later will prevent preprocessor logic from uncluding this block untill #endif

int functionA(int,float); // function prototype.
#endif // ends preprocessor if logical block.
```

##### `#pragma`
other version of header guard. я лінийвий щоб писати 😭 #TODO 


### HEADER FILES

Header files have .h extension, but in some cases they can have .hpp or no file extension at all
<mark class="hltr-yellow">!</mark> header files are used to add a bunch of related forward declarations into a code file 

what problem do they solve? - manually adding [[#^b6dea4| function prototypes]] into every source code file is tedious, so it was automated using preprocessor and header files. <mark class="hltr-purple">!</mark> They mainly allow to link libraries together.

```cpp
#include <iostream> //including std header file

#include "adder.h" //including user defined header file
```

<mark class="hltr-green">Good practice: </mark> - to pair .cpp and .h files together with same name. Source files (.cpp) should `#include` their headers. This allows to pinpoint some redefinition bugs that can appear. ^a80905

---
**When  `<>` and `""` are used**
When including headers, headers that are not written inside this program are included using angled brackets (`<>`) while headers that are part of this program and its main folder are included using quotation marks (`""`). 

Angled brackets `<>` specify to preprocessor to search for header files inside **include directories**. The include directories are part of compiler settings, come from directories containing the header files that come with compiler toolchain and/or OS ^861673

![[preprocessor include rules | 500x400]]

---
##### Redefinition errors when including header files

^83565d

**Defining same function 2 times**
putting variables and function bodies/definitions into header files can lead to [[#^e89dae| One definition rule violations]]

<mark class="hltr-grey">demo.h</mark>
```cpp
int redefinitionDemo(double Xx)
{
   return Xx;
}
```

<mark class="hltr-grey">main.cpp</mark>
```cpp
#include "hello.h"
#include <iostream>

int redefinitionDemo(double Yy)
{
   return Yy;
}

int main()
{

   std::cout << redefinitionDemo(5);
	return 0;
}
```

leads to `error: redefinition of 'int redefinitionDemo(double)'` error when compiled using terminal `g++ main.cpp hello.h -o program.exe `

**Another example:**

**Declaring same function with different return types that results in redeclaration error!**
when add.cpp and add.h are paired, they can help to catch redefinition error

<mark class="hltr-grey">add.h</mark>
```cpp
int add(int x, int y);
```

<mark class="hltr-grey">add.cpp</mark>
```cpp
#include "add.h"         // copies forward declaration from add.h here

double add(int x, int y) // oops, return type is double instead of int
{
    return x + y;
}
```

<mark class="hltr-grey">main.cpp</mark>
```cpp
#include "add.h"
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

when compiled using g++ in terminal: `g++ main.cpp add.cpp add.h -o program.cpp `  // <mark class="hltr-yellow">reminder:</mark> `.cpp files should be also included with .h files, so linker can reach actual definition`

it will produce an error `error: ambiguating new declaration of 'double add(int, int)'` - compiler computes that function declaration inside .h file and definition inside .cpp file do not match, so it throws an error.

#Note_for_future  this doesn’t work if it is a parameter with a different type instead of a return type. This is because C++ supports overloaded functions (functions with the same name but different parameter types), so the compiler will assume a function with a mismatched parameter type is a different overload.  <mark class="hltr-cyan">source: </mark> [learn.cpp](https://www.learncpp.com/cpp-tutorial/header-files/#:~:text=Unfortunately,all)

##### Source files should not be included
this can lead to redefinition errors / naming collisions. 

##### Why doesnt Iostream have an .h extension?
#TODO пройтись по цьому матеріалу [learn.cpp](https://www.learncpp.com/cpp-tutorial/header-files/#:~:text=Why%20doesn%E2%80%99t%20iostream%20have%20a%20%2Eh%20extension) Та також вся 2.11 глава після цього теж

### **How to design a program**

^52f271

https://www.learncpp.com/cpp-tutorial/how-to-design-your-first-programs/

# **CHAPTER 3** Debug

### **SYNTAX AND SEMANTIC ERRORS**

##### Syntax errors
Syntax errors occur when statements that are not valid according to grammatic rules of  C++ language, 
<mark class="hltr-yellow">!</mark> The compiler catches syntax errors and highlights them in console.

```cpp
#include <iostream>

int main( // missing closing brace
{
    int 1x; // variable name can't start with number
    std::cout << "Hi there"; << x +++ << '\n'; // extraneous semicolon, operator+++ does not exist
    return 0 // missing semicolon at end of statement
}
```

##### Semantic errors
error in meaning, either violates the rules of the language, or a statement does a wrong action alltogether

```cpp
int main()
{
    5 = x; // x not declared, cannot assign a value to 5
    return "hello"; // "hello" cannot be converted to an int
}
```

these can appear at runtime, which is the worst case of  an semantic error. 

### DEBUG INSIDE SOURCE CODE

##### placing `std::cerr` inside a code file to debug

#TODO 
##### Debug method: narrowing down the problem using hi-lo method

#TODO 
##### using `ifdef` to insert debug code

#TODO 
##### using logging, `std::clog`

#TODO 

### DEBUG USING DEBUGGER

<mark class="hltr-green">USING VS CODE</mark>
 **step into** command executes the next statement in the normal execution path of the program, and then pauses execution of the program so we can examine the program’s state using the debugger. This debugger tool shows an pointer arrow that marks the next execution step  ^72040d

The **step over** command executes the next statement in the normal execution path of the program. However, whereas _step into_ will enter function calls and execute them line by line, _step over_ will execute an entire function without stopping and return control to you after the function has been executed.

![[Pasted image 20260729000716.png]]

<mark class="hltr-cyan">VS CODE RMB menu commands</mark>
**Set next statement** - command allows us to change the point of execution to some other statement (sometimes informally called _jumping_). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.
##### The watch window

allows to add variables that will be continuously inspected by a debugger, adding a variable to watch window is done through RMB click menu on a variable in source code file.

![[Pasted image 20260729002838.png]]

<mark class="hltr-pink">source of reference for vscode debugging</mark>  https://code.visualstudio.com/docs/debugtest/debugging

### THE CALL STACK

^4894b0

When a program calls a function, it bookmarks the current location, makes the function call, and then returns. The program uses **call stack** to keep track of called functions in memory.

The **call stack** is a list of all the active functions that have been called to get to the current point of execution. The call stack includes an entry for each function called, as well as which line of code will be returned to when the function returns. Whenever a new function is called, that function is added to the top of the call stack. When the current function returns to the caller, it is removed from the top of the call stack, and control returns to the function just below it.

 <mark class="hltr-yellow">!</mark> ==stack is a data structure==

![[call stack | 500x500]]

### Not making errors while coding

- Follow best practices.
- Don’t program when tired or frustrated. Take a break and come back later.
- Understand where the common pitfalls are in a language (all those things we warn you not to do).
- Don’t let your functions get too long.
- Prefer using the standard library to writing your own code, when possible.
- Comment your code liberally.
- Start with simple solutions, then layer in complexity incrementally.
- Avoid clever/non-obvious solutions.
- Optimize for readability and maintainability, not performance.

#TODO занотувати це https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/

# **CHAPTER 4 Data types, integers and floats, basic control flow

### Introduction to fundamental data types
Computers use **RAM** to store data temporarily, a unit of data for a modern computer is **binary digit** (also called a **bit**) which can hold a value 1 or 0, hense the name binary. 

Memory is organized into sequential units called **memory addresses**. Each memory adress holds a **byte**, A **byte** is a group of bits that are operated on as one unit. <mark class="hltr-yellow">!</mark> ==The modern standard is that a byte is comprised of 8 sequential bits.==

![[8 bit adresses | 700x200]]
##### Fundamental data types
Because all data on a computer is just a sequence of bits, we use a **data type** (often called a **type** for short) to tell the compiler how to interpret the contents of memory in some meaningful way. You have already seen one example of a data type: the integer. When we declare a variable as an integer, we are telling the compiler “the piece of memory that this variable uses is going to be interpreted as an integer value”.

When you give an object a value, the compiler and CPU take care of encoding your value into the appropriate sequence of bits for that data type, which are then stored in memory (remember: memory can only store bits). For example, if you assign an integer object the value `65`, that value is converted to the sequence of bits `0100 0001` and stored in the memory assigned to the object.

**Fundamental data** types or **basic types** table  ^63210c

|                                                                                    |                      |                                                  |         |
| ---------------------------------------------------------------------------------- | -------------------- | ------------------------------------------------ | ------- |
| float  <br>double  <br>long double                                                 | Floating Point       | a number with a fractional part                  | 3.14159 |
| bool                                                                               | Integral (Boolean)   | true or false                                    | true    |
| char  <br>wchar_t  <br>char8_t (C++20)  <br>char16_t (C++11)  <br>char32_t (C++11) | Integral (Character) | a single character of text                       | ‘c’     |
| short int  <br>int  <br>long int  <br>long long int (C++11)                        | Integral (Integer)   | positive and negative whole numbers, including 0 | 64      |
| std::nullptr_t (C++11)                                                             | Null Pointer         | a null pointer                                   | nullptr |
| void                                                                               | Void                 | no type                                          | n/a     |

##### Integer vs integral types
in math an integer is a number with no fractional part,  NOT `4.5`, `0.0032`. The term “integral” has several different meanings, but in the context of C++ is used to mean “like an integer”. ^cd24be

- The **standard integer types** are `short`, `int`, `long`, `long long` (including their signed and unsigned variants).
- The **integral types** are `bool`, the various char types, and the standard integer types.

 <mark class="hltr-yellow">!</mark> ==non-fundamental types (such as enum and enum class) are not integral types  ==
##### Other sets of types
*Built in types are:* fundamental types and compound data types #link_later
*external types are:* standart library types

 **strings:** in modern C++, strings are part of the standard library. they will 

##### The `_t` suffix
Many of the types defined in newer versions of C++ use `_t` suffix, it is a shorthand for type, this is not really consistent huh

### Void type

#void-type

void means no type, void is an **incomplete type**. Incomplete types cannot be instantiated for use in variables (that would be pointless), void types are used in other use cases.

##### Void functions

```cpp
void functionA()
{
	// no return statement.
	// using return statement in void function will result in compiler error.
}
```

<mark class="hltr-grey">deprecated:</mark>  the original language C has syntax to indicate that a function does not take any parameters
```cpp
void func1(void) // this will compile in c++ too (for backward compatibility reasons)
{
	// 
}

void func2() // this is preffered in c++
{
	// 
}
```

<mark class="hltr-orange">!</mark> ==Other uses of void== -  The void keyword has a third (more advanced) use in C++ - void pointers. source - [19.5 -- Void pointers](https://www.learncpp.com/cpp-tutorial/void-pointers/).

### Object sizes and the sizeof operator
most objects in c++ use more than one byte of memory. **The amount of memory object uses depends on its data type**. memory acess in c++ is often done using variable names (and not directly via memory addresses) When a variable is used in source code (.cpp, .h files) the compiler automatically handles how many bytes should be used for that object based on a type of that object.

<mark class="hltr-grey">The more memory an object has, the more data it can hold</mark>
![[bits exponential growth | 900x200]]

8 bits (one byte) can hold $2^8$ = 256 different values. 
An object that uses 2 bytes can hold 2^16 (65536) different values.
So, **objects that utilize more bytes can store a larger number of unique values.**

computers have a finite amount of free memory. Every time we define an object, a small portion of that free memory is used for as long as the object is in existence. Because modern computers have a lot of memory, this impact is usually negligible. However, for programs that need a large amount of objects or data (e.g. a game that is rendering millions of polygons), the difference between using 1 byte and 8 byte objects can be significant.

##### Fundamental data type sizes and assumptions

^ce9f81
#char #float #bool 
#integral #int #signed-integers

<mark class="hltr-cyan">C++ standart:</mark>
- An object must occupy at least 1 byte (so that each object has a distinct memory address).
- A byte must be at least 8 bits.
- The integral types `char`, `short`, `int`, `long`, and `long long` have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
- `char` and `char8_t` are exactly 1 byte (at least 8 bits).

<mark class="hltr-cyan">Some assumptions have to be made, because computer architectures can differ, most modern computers assume...</mark>
- A byte is 8 bits.
- Memory is **byte addressable** (we can access every byte of memory independently).
- Floating point support is [IEEE-754](https://en.wikipedia.org/wiki/IEEE_754)  compliant.
- We are on a 32-bit or 64-bit architecture.

|Category|Type|Minimum Size|Typical Size|
|---|---|---|---|
|Boolean|bool|1 byte|1 byte|
|Character|char|1 byte (exactly)|1 byte|
||wchar_t|1 byte|2 or 4 bytes|
||char8_t|1 byte|1 byte|
||char16_t|2 bytes|2 bytes|
||char32_t|4 bytes|4 bytes|
|Integral|short|2 bytes|2 bytes|
||int|2 bytes|4 bytes|
||long|4 bytes|4 or 8 bytes|
||long long|8 bytes|8 bytes|
|Floating point|float|4 bytes|4 bytes|
||double|8 bytes|8 bytes|
||long double|8 bytes|8, 12, or 16 bytes|
|Pointer|std::nullptr_t|4 bytes|4 or 8 bytes|

For maximum portability,  objects shouldnt be assumed to be larger than the specified minimum size.

`static_assert` can be used for compiler to fail a build if it is compiled on an architecture where this assumption is not true. Source -  [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/#static_assert).

##### **Fundamental data type performance**
On modern machines, objects of the fundamental data types are fast, so performance while using or copying these types should generally not be a concern.

CPUs are often optimized to process data of a certain size (e.g. 32 bits), and types that match that size may be processed quicker. On such a machine, a 32-bit int could be faster than a 16-bit short or an 8-bit char.

##### The `sizeof()` operator

#sizeof-operator

In order to determine the size of data types on a particular machine, C++ provides an operator named `sizeof`. The **sizeof operator** is a unary (one variable being operated on) operator that takes either a type or a variable, and returns the size of an object of that type (in bytes).

```cpp
#include <iostream>

using namespace std // for code visual comfort

int main()
{
    cout << "using sizeof operator to get size of int - " << sizeof(int) << '\n';
    cout << "using sizeof operator to get size of char - " << sizeof(char) << '\n';
    cout << "using sizeof operator to get size of long - " << sizeof(long) << '\n';
    cout << "using sizeof operator to get size of float - " << sizeof(float) << '\n';
	 return 0;
}
```

<mark class="hltr-grey">outputs:</mark> 
```
using sizeof operator to get size of int - 4
using sizeof operator to get size of char - 1
using sizeof operator to get size of long - 4
using sizeof operator to get size of float - 4
```

**sizeof also can be used on variable names!**

```cpp
int main()
{
    char A[10]; // defining an array
    std::cout << "created array named A \n";
    std::cout << "using sizeof to get size: " << sizeof(A) <<'\n'; //using sizeof on variable.

	 // second example
    char B[10000];
    std::cout << "created array named A \n";
    std::cout << "using sizeof to get size: " << sizeof(B) <<'\n';

	 return 0;
}
```

<mark class="hltr-grey">outputs:</mark>
```
created array named A 
using sizeof to get size: 10
created array named A 
using sizeof to get size: 10000
```

### Signed integers

#signed-integers

signed integers are values that can hold both + values and - values, the sign is stored as part of value
==signed integers give half of their range to negative sign==, the first bit becomes a **sign bit** #fact_check_this

| Type          | minimal size |                                           |
| ------------- | ------------ | ----------------------------------------- |
| short int     | 16 bits      |                                           |
| int           | 16 bits      | Typically 32 bits on modern architectures |
| long int      | 32 bits      |                                           |
| long long int | 64 bits      |                                           |

<mark class="hltr-green">good practice</mark> - using `short, long, long long` instead of `short int, long int, long long int` will be preffered, because its more readable and has less chance to introduce a typo. 

A `signed` keyword can be added to indicate that type of this variable will be signed. still, most fundamental types are signed by default. ^0c22ff

###### Signed integer counting starts from zero

^40beae

A 5-bit number can support 2^5 = 32 unique values. For a signed integer, these are split almost evenly amongst positive and negative numbers, with negative receiving an extra value. So the range would be -16 to 15.

==A zero is included in positive part of signed integer==, That makes sense in programming because very often 0 is a first number when counting. 
so that would be:


![[Pasted image 20260803180056.png]]

##### Signed integer ranges

#signed-integer-range

The range of signed integer is 2^(n-1), where n is amount of digits (each digit is equal to one bit), and substraction is done because one digit is reserved for a sign digit. ^ea88aa

![[signed 1 byte int | 400x300]]


| Size / Type   | Range                                                   |
| ------------- | ------------------------------------------------------- |
| 8-bit signed  | -128 to 127                                             |
| 16-bit signed | -32,768 to 32,768                                       |
| 32-bit signed | -2,147,483,648 to 2,147,483,647                         |
| 64-bit signed | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 |

##### signed Integer Overflow
if variable gets evaluated outside the range of its type, this will result in undefined behaviour - “If during the evaluation of an expression, the result is not mathematically defined or not in the range of representable values for its type, the behavior is undefined”.

A sign holds + or - side of the value, in case of overflow cpu flips the **sign bit**
```cpp
int main()
{
    int x{2147483647}; // at the limit of range, 2^31.
    x = x + 1; // will overflow into sign bit, and will flip to -2147483648
    x = x - 1; // overflows back into positive values and becomes 2147483647
    return 0;
}
```

==overflow resuts in information being lost==, because 2147483647 + 1 should be 2147483648, not -2147483648. ^1191b7

### Unsigned integers
unsigned integers dont store a sign, so they get full bit range to store value. To define unsigned integer `unsigned` keyword is used:
```cpp
unsigned int x{};
unsigned long long y{};
```

==By convention `unsigned` keyword is first in a statement, then type keyword.==

| Size/Type       | Range                           |
| --------------- | ------------------------------- |
| 8 bit unsigned  | 0 to 255                        |
| 16 bit unsigned | 0 to 65,535                     |
| 32 bit unsigned | 0 to 4,294,967,295              |
| 64 bit unsigned | 0 to 18,446,744,073,709,551,615 |

An n-bit unsigned variable has a range from 0 to (2^n)-1.

##### Unsigned integer overflow
 Any number bigger than the largest number representable by the type wraps around (called **modulo wrapping**), If an unsigned value is out of range, it is divided by largest number of that type, for example `255` for unsigned 1 bit int, and the reminder is then what is output.

<mark class="hltr-cyan">formula:</mark>
`x % 2^n` is the formula, where x is a value, 2^n is a maximum bit size of this type.

<mark class="hltr-cyan">examples:</mark>
257 % 2^8 = 257 % 256 = 1 `// modulo operator outputs reminder after division`

```cpp
int main()

{
    unsigned short x{65535}, y{65535};
    x = x+1; // 65535+1 % 65536 = 65536 % 65536 = 0.
    y = y+15; // 65535 + 15 % 65535 = 65545 % 65536 = 1.
    return 0;

}
```

==A very important detail to notice==, binary counting starts from 0, so the actual range will be 65535, not 2^16 = 65535.

![[unsigned integer wraparound | 900x400]]
##### Doing calculations on unsigned and signed integers

^48655e

Unexpected behaviour can result when doing operations on signed and unsigned integer types. the signed integer will  be converted to an unsigned integer. And the result will be unsigned.

==bug case 1==
```cpp
#include <iostream>

int main()

{
    unsigned int u{ 2 };
    signed int s{ 3 };
    
    std::cout << u - s << '\n'; // 2 - 3 != 4294967295
    u = u - s; // the wraparound happens with assignment too.
    return 0;

}
```

==bug case 2==
```cpp
#include <iostream>

int main()
{
    signed int s { -1 };
    unsigned int u { 1 };

    if (s < u) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes

    return 0;
}
```

<mark class="hltr-green">Best practice</mark> is to not use unsigned integers for holding a value, using as function parameter or doing mathematical operations.

### Integer division

^a0e56c
#integer-division #gotcha

When doing division with two integers (called **integer division**), C++ always produces an integer result. Since integers can’t hold fractional values, any fractional portion is simply dropped (not rounded!).

```cpp
int main()
{
	int x{20}, y{5}, z{0};
	z = x / y; // will evaluate to 4, no fractional part (the 0.0)
	return 0;
}
```

```cpp
int main()
{
	int x{8}, y{3}, z{0};
	z = x / y; // will evaluate to 2, cpu dropped fractional part.  
	return 0;
}
```

**Doing division with integers without loosing fractional part** - [Source material]([Source](https://www.learncpp.com/cpp-tutorial/arithmetic-operators/#:~:text=Using%20static%5Fcast%3C%3E%20to%20do%20floating%20point%20division%20with%20integers))  #TODO

### Fixed size integers

#cstdint-header #int_t

since `C++11` there are a set of integer types that guarantee fixed size on any architecure they are called **fixed-width integers**.
The fixed-width integers are defined (in the `<cstdint>`\ header) 

fixed width integers are aliases for fundamental integer types like `short, int, long`, header `<cstdint>` will try to guarantee that `std::int16_t` will become one of types that are 16 bits in size.

![[Pasted image 20260805212929.png]]

```cpp
#include <iostream>
#include <cstdint>

int main()

{
    // Compilers usually guarantee that those types have exact sizes
    std::cout << sizeof(std::int32_t);
    std::cout << sizeof(std::int_fast64_t);
    return 0;

}
```

#TODO [Source](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=Fast%20and%20least%20integral%20types)

### Scientific notation and Floating point numbers

#scientific-notation 

For scientific notation letter E is used as the "**times ten to the power of**"
`1.25 * 10^2` = `1.25e2`
#### How to convert decimal numbers to scientific notation

^874074

- exponent starts at zero.
- If the number has no explicit decimal point (e.g. `123`), it is implicitly on the right end (e.g. `123.`)
- Slide the decimal point left or right so there is only one non-zero digit to the left of the decimal.
    - Each place you slide the decimal point to the left increases the exponent by 1.
    - Each place you slide the decimal point to the right decreases the exponent by 1.
- Trim off any leading zeros (on the left end of the significand)
- Trim off any trailing zeros (on the right end of the significand) (trailing zeros can be significant, depends on use in program)

#### Floating point types/value

#float 

https://float.exposed/ 

**Floating point** data types can hold values that contain numbers with a fractional component. Floating point types are always signed

C++ has three fundamental floating point data types: a single-precision `float`, a double-precision `double`, and an extended-precision `long double`. As with integers, C++ does not define the actual size of these types.

**Floating point size** ^b2202a

| C++ Type    | Typical Size       |
| ----------- | ------------------ |
| float       | 4 bytes            |
| double      | 8 bytes            |
| long double | 8, 12, or 16 bytes |
**Floating point range**

|   |   |   |
|---|---|---|
|IEEE 754 single-precision (4 bytes)|±1.18 x 10-38 to ±3.4 x 1038 and 0.0|6-9 significant digits, typically 7|
|IEEE 754 double-precision (8 bytes)|±2.23 x 10-308 to ±1.80 x 10308 and 0.0|15-18 significant digits, typically 16|
|x87 extended-precision (80 bits)|±3.36 x 10-4932 to ±1.18 x 104932 and 0.0|18-21 significant digits|
|IEEE 754 quadruple-precision (16 bytes)|±3.36 x 10-4932 to ±1.18 x 104932 and 0.0|33-36 significant digits|

---

floating point types on modern architectures (x64-x86, arm) are implemented following an [IEEE 754 standart]([https://en.wikipedia.org/wiki/IEEE_754](https://en.wikipedia.org/wiki/IEEE_754)) ^dc9f62

When using floating point literals, including one decimal place (even if the decimal is 0) makes the compiler identify the variable type as float. 
```cpp
float c { 5.0f }; // 5.0 is a floating point literal, 
```

`5.0f`  with suffix  `f` means its the float value. ^6588f9

==Best practice== the type of literals  should match the type of the variables they’re being assigned to or used to initialize. Otherwise an unnecessary conversion will result, possibly with a loss of precision.

###### Floating point type behaviour demonstration
```cpp
#include <iostream>
int main()

{
    std::cout << 5.0 << '\n';
    std::cout << 6.7f << '\n';
    std::cout << 9876543.21 << '\n';
    return 0;
}
```
This program outputs
```cpp
5 // std::cout truncates trailing zeros (leftover zeros).
6.7 
9.87654e+06 // value was truncated and std::cout prints scientific notation by default.
```

#### Floating point precision
The **precision** of a floating point type defines how many significant digits it can represent without information loss.

#TODO [learncpp.com source material](https://www.learncpp.com/cpp-tutorial/floating-point-numbers/#:~:text=Floating%20point%20precision)

### Boolean types, bool returning operators, if statements

#bool

**boolean data type** holds 2 states - either true or false, 1 or 0. In c++ it takes minimum of one byte (and in most implementations one byte).

```cpp
#include <iostream>
int main()
{
	bool x{true} // keyword true means 1
	bool y{false} // keyword false means 0
	
	x = 0 // assings false to x
	y = 1 // assigns true to y
	
	if (y) // if is a switch statement that executes if condition is boolean true, if not just skips the code block
	{
	// something here
	}
	
	if (5) // integers that are larger than one will convert to true in boolean demanding application
	{
		std::cout >> "hello im true \n";
	}
	return 0;
}
```

#### If chaining, early return

#if-statement #if-keyword #loop

`if` statements can be chained using `else` statements. 

An **if chain** checks in order (from top to bottom) starting with first `if`, if that condition is not true, CPU continues to the next `else if`  (if it is present) that will run its own condition, else if's can be chained too.  `else`  keyword is used as last element of chain, that will always execute its branch. 

```cpp
#include <iostream>
int main()
{
	bool x_b{true}, y_b{0}; // declaring 2 bool variables
	
	if (x_b)
	{
		std::cout << "x_b is true";
	}
	else if (y_b && x_b) // !0 = 1, aka not false = true
	{
		// this branch wont be triggered as first condition is true, because x_b is a literal that is initalised as true. 
	}
	else 
	{
	   return 0; // returns the function early, will end main() function before the last return
	}
	
	return 0;
}
```


#### Bool returning operators/ Operators that evaluate to bool.

#logical-operators #comparison-operators

<mark class="hltr-grey">Logical operators </mark>
Logical AND `&&` - Returns true if both operands are true, otherwise false <mark class="hltr-orange">binary operator</mark>
Logical OR `||` - Returns true if one of operands is true. When none are true, returns false <mark class="hltr-orange">binary operator</mark>
Logical NOT `!` - Returns true if operand is false. Reverses the result <mark class="hltr-green">unary operator</mark>

- [Short circuit evaluation of logic operators](https://www.geeksforgeeks.org/linux-unix/short-circuiting-in-c-and-linux/#:~:text=Short%2Dcircuiting%20in%20C%2B%2B%0AIn,value%20of%20the%20right%2Dhand%20side.)

<mark class="hltr-grey">Comparison Operators</mark>
Equal `==` - Returns true if both operands are equal, otherwise false <mark class="hltr-orange">binary operator</mark>
NOT equal `!=` - Returns true of both operands are NOT equal, otherwise false <mark class="hltr-orange">binary operator</mark>

Greater than `>` - Returns true if first operand is greater than second, otherwise false <mark class="hltr-orange">binary operator</mark>
Less than `<` - Returns true if first operand is less than second, otherwise false <mark class="hltr-orange">binary operator</mark>

Greater than or equal to `>=` - Returns true if first operand is greater than second or both are equal <mark class="hltr-orange">binary operator</mark>
Less than or equal to `<=` - Returns true if first operand is Less than second or both are equal <mark class="hltr-orange">binary operator</mark>


### Implicit type conversions, explicit type conversion with static_cast

#type-conversion 

The process of converting data from one type to another type is called **type conversion**, when c++ compiler automatically converts types, it is called **Implicit type conversion**. example:
```cpp
void func(int x)
{
	return x;
}
int main()
{
	func(10.05f); // literal 10 is an float, will be narrowed down to int 10, fractional part will be dropped.
}

```
compiler flag `-Werror` detects it with error message: `-Werror=float-conversion` 

(implicit - not explained but assumed to be known, while explicit means known. українською: implicit - неявний, implicit - явний  )

#### <mark class="hltr-grey">3 ways to trigger an implicit type conversion</mark>
Creating an int variable and initalising it with char value
```cpp  
int x{'a'}; // ASCII code for a is 97
```

passing a different type value to function
```cpp
int func(int x)
{
	return int;
}
int main()
{
	func(true) // implcit conversion from true to 1
}
```

returning a different type value
```cpp
char func(int ch)
{
	return ch
}
int main()
{
	func(40) // conversion from 40 (int) to char.
}
```

#### `static_cast<type> (expression)` allows to explicitly convert types which is controlled and <mark class="hltr-green">good practice </mark>

#static_cast

static cast is a template object in c++
==Static cast can create narrowing conversions and other type related bugs when/if used==

```cpp
void print(char myChar) // print takes a double parameter
{
    std::cout << myChar << '\n';
}

int main()
{
    print( static_cast<char>( true + 54 ) ); // converting expression in parentheses into char type. will evaluate to 55, is an ASCII code for 7
    return 0;
}
```


### Char
#TODO
# **CHAPTER 5 const, constexpr, std::String

### CONSTANT VARIABLES / Constant function parameters

#const #const-keyword

constant value is a value that can not be changed during the program's execution. C++ supports two different kinds of constants:

- **Named constants** - variables with identifiers that have constant type.
- **Literal constants** - literals that have a constant type.

to declare a constant variable a `const` keyword is used (called a “const qualifier”).
==Const variables must be initialized, otherwise compiler will output an error==

<mark class="hltr-grey">example</mark>
```cpp
int main()
{
	float x{0.1f}; // non constant variable declaration.
	const float earthGrav{9.81f}; // constant float type variable declaration.
	
	float const someConst{1.0f}; // that also works, but not conventional ordering in english language. This ordering is called “east const”

	someConst = 5.0f; // will result in error: "Cannot assign to variable 'input' with const-qualified type 'const int'"

	return 0;
}
```

`fact:` The type of an object includes the const qualifier, so when  `const double gravity { 9.8 };` is defined, the type of `gravity` is `const double`.

[Nomenclature](https://www.learncpp.com/cpp-tutorial/constant-variables-named-constants/#:~:text=Nomenclature%3A%20type%20qualifiers)

#### Compile time and runtime constants

#runtime-constant #compile-time-constant #may-be-changed

A **compile-time constant** is a constant whose value is known at compile-time. 
- Literals.
- Constant objects whose initializers are compile-time constants.

A **runtime constant** is a constant whose value is determined in a runtime context. Examples include:
- Constant function parameters.
- Constant objects whose initializers are non-constants or runtime constants.

#### Constant function parameters
function parametets can also be made constant using `const` keyword.

<mark class="hltr-grey">example</mark>
```cpp
void func(const int input) // on function call this parameter will be created and initalised with value of used argument
{
	input = 100 // will result in error: "Cannot assign to variable 'input' with const-qualified type 'const int'"
	return input + input;
}

int main()
{
	int x{1};
	func(x);
	return 0;
}
```

==using const variables in functions is useful when doing pass by value or pass by reference==

Using `const` when returning by value is possible
```cpp
const int func(int input) 
{
	return input + input; // will return a const type temporary variable
}
```

const type temporary variables are usually useless.

#### Variables should be made constant
it is a good practice to declare most variables constant 
- It reduces chances of bugs (value cant be changed accidentally).
- Compilers can optimise machine code better for constant variables.
- Knowing a constant variable cannot be changed is useful for debugging and reasoning.

#### Object like macros create constant values
Object like macros should not be preffered to use as they have a variety of issues.
```cpp
#include <iostream>
#define AGE 15

int main()
{
    std::cout << "My age is: " << AGE << '\n'; // will create a constant integer literal. 
    return 0;
}
```


### LITERALS

#literals 

**Literals** are values that are inserted directly into the code, literals have types and values, but no identifier.

```cpp
const int x{5}; // constant integer variable with value 5 literal used as initaliser.
float y{0.5f} // float variable with value literal 0.5.
```

| Literal value        | Examples        | Default literal type | Note                           |
| -------------------- | --------------- | -------------------- | ------------------------------ |
| integer value        | 5, 0, -3        | int                  |                                |
| boolean value        | true, false     | bool                 |                                |
| floating point value | 1.2, 0.0, 3.4   | double (not float!)  |                                |
| character            | ‘a’, ‘\n’       | char                 |                                |
| C-style string       | “Hello, world!” | const char[14]       | C-style string literal  string |

#### Literal suffixes
a type of a literal value can be specified using a suffix

#literal-suffixes

| Data type      | Suffix                                 | Meaning                                   |
| -------------- | -------------------------------------- | ----------------------------------------- |
| integral       | u or U                                 | unsigned int                              |
| integral       | l or L                                 | long                                      |
| integral       | ul, uL, Ul, UL, lu, lU, Lu, LU         | unsigned long                             |
| integral       | ll or LL                               | long long                                 |
| integral       | ull, uLL, Ull, ULL, llu, llU, LLu, LLU | unsigned long long                        |
| integral       | z or Z                                 | The signed version of std::size_t (C++23) |
| integral       | uz, uZ, Uz, UZ, zu, zU, Zu, ZU         | std::size_t (C++23)                       |
| floating point | f or F                                 | float                                     |
| floating point | l or L                                 | long double                               |
| string         | s                                      | std::string                               |
| string         | sv                                     | std::string_view                          |
|                |                                        |                                           |

==By default, floating point literals have a type of `double`.==
so to avoid compiler warning and unwanted conversions, this example works:
```cpp
float x{0.5} // compiler will convert double 0.5 into float 0.5, bad practice
float y{0.5f} // initalising with float literal, good
```

#### Scientific notation for floating point literals

#scientific-notation

scientific notation also works for initalising float type variables
```cpp
double c{ 2.99792458e8 }; // e means * 10^8
```

#### С String literals

#string #c-string

a **string** is a collection of sequential characters.
A single char is placed inside single quotes `'a'` while a string is placed into double quotes `"abc"`

c++ inherits its basic strings from c language, C has no strings as type so an **array** has to be used, example of C string declaration and initalisation:
```cpp
int main()
{
    char myText[] = "my string"; // creates an array with index size of 10 chars, last char in a string is a null terminator
    return 0;
}
```

**null terminator** - a char value `\000`, used to indicate that string ends. A string that ends with a null terminator is called a **null-terminated string**.


#### Magic numbers
A magic number is a literal that has unclear meaning and is ambiguious to debug
```cpp
double controller(4.0,0.0, 15.0f) // hard to read the meaning what those literals should do.
```

### AS IF RULE / compiler optimisation

#as-if-rule #compiler-optimisations

The [**as-if rule**](https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/#:~:text=The%20as%2Dif%20rule%20says%20that%20the%20compiler%20can%20modify%20a%20program%20however%20it%20likes%20in%20order%20to%20produce%20more%20optimized%20code%2C%20so%20long%20as%20those%20modifications%20do%20not%20affect%20a%20program%E2%80%99s%20%E2%80%9Cobservable%20behavior%E2%80%9D%2E) says that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program’s observable behavior.

#Compile-time-evaluation
#Constant-folding
#Constant-propagation
#Dead-code-elimination

### Constant expressions / compile time programming

#compile-time-programming #constant-expressions #runtime-expressions
[cppreference](https://en.cppreference.com/cpp/language/constant_expression)

A **constant expression** is a non-empty sequence of literals, constant variables, operators, and function calls. ==that must be evaluated at compile time== *constant expressions* allow to optimise programs for faster execution OR checking if the expression is valid at compile time.

An expression that is not a constant expression is called **runtime expression**

---

<mark class="hltr-grey">Constat expressions contain</mark> #fact_check_this 
- Literals (e.g. ‘5’, ‘1.2’) `// an expression consisting of a literal is a constant expression.`
- Most operators with constant expression operands (e.g. `3 + 4`, `2 * sizeof(int)`).
- Const integral variables with a constant expression initializer (e.g. `const int x { 5 };`). This is a historical exception -- in modern C++, constexpr variables are preferred.
- Constexpr variables (discussed in upcoming lesson [5.6 -- Constexpr variables](https://www.learncpp.com/cpp-tutorial/constexpr-variables/)).
- Constexpr function calls with constant expression arguments (see [F.1 -- Constexpr functions](https://www.learncpp.com/cpp-tutorial/constexpr-functions/)).
<mark class="hltr-grey">Constant expressions can also contain:</mark>
- Non-type template parameters (see [11.9 -- Non-type template parameters](https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/)).
- Enumerators (see [13.2 -- Unscoped enumerations](https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/)).
- Type traits (see the [cppreference page for type traits](https://en.cppreference.com/w/cpp/header/type_traits)).
- Constexpr lambda expressions (see [20.6 -- Introduction to lambdas (anonymous functions)](https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/)).

<mark class="hltr-orange">these cannot be used in a constant expression</mark>
- Non-const variables, like: `int x{0} //`
- Const non-integral variables, even when they have a constant expression initializer (e.g. `const double d { 1.2 };`). To use such variables in a constant expression, define them as constexpr variables instead (see lesson [5.6 -- Constexpr variables](https://www.learncpp.com/cpp-tutorial/constexpr-variables/)).
- The return values of non-constexpr functions (even when the return expression is a constant expression).
- Function parameters (even when the function is constexpr).
- Operators with operands that are not constant expressions (e.g. `x + y` when `x` or `y` is not a constant expression, or `std::cout << "hello\n"` as `std::cout` is not a constant expression).
- Operators `new`, `delete`, `throw`, `typeid`, and `operator,` (comma).

---

#rough-sketch & #fact_check_this 

constexpr function - precompile output if arguments are constant expressions
constexpr if -  #TODO 
constexpr statement - evaluates if operands / variables are known at compile time 
rule of thumb - non <mark class="hltr-green">constexpr functions</mark> cannot be used in constexpr (constant expressions).

If constexpr is used as part of function prototype, it allows this function to be used as part of constant expression. IF constexpr is used as part of expression, it has to guarantee this expression will be precompiled

### std::string
#std-string #string 

`std::string` is a type that is defined in the `<string>` header.
```cpp
#include <string>
int main()
{
	std::string mystring{"Hi, i am string"}; // defining a variabled
	return 0;
}
```

like C string (defined using arrays), an `std::string` is automatically compiled with null terminator as the last char.

`std::string object dynamically resizes itself once reassigned`
```cpp
int main()
{
	std::string mystring2{"Abc"};
	
	mystring2 = "banana, apple"; // reassigning with different size.
	
	return 0;
}
```

if `string` has not enough memory it will automatically request additional memory (at runtime) using a form of memory allocation known as dynamic memory allocation.

#### std::cout input specifics
#std-cout #std-getline #std-ws #iostream-header

when using operator>> to extract string into `std::cin`, `operator>>` only returns characters up to the first whitespace it encounters. Any other characters are left inside `std::cin`, waiting for the next extraction.

`std::getline(std::cin, input) should be used`
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string uinput{};
    std::getline(std::cin >> std::ws, uinput); // std::ws input manipulator allows to ignore leading whitespaces
    // aka: whitespace char's that are placed in front of any useful text chars.
    // std::ws is not saved, so needs to be done for all std::getline calls
    std::cout << uinput <<  '\n' ;

}
```

#### std::string.lenght(), std::ssize()
#string-lenght #member-function

the `length()` is a **member function** and it is declared inside of `std::string`, it is sometimes written as `std::string::length()` in documentation. In function calls it is written as string type object call `identifier.lenght()`

- `std::string::length()` returns an unsigned integral value
- Initializing a `std::string` in function parameters is expensive (its an class object)
- Passing `std::string` by value is expensive (on function call a copy is created) 

```cpp
#include <iostream>
#include <string>
int main()
{
    std::string name{"somename"};
    std::cout << name.lenght(); // member function of string object (the function that is part of string object class)
    return 0;
}
```

`std::string` is required to be null-terminated (as of C++11), ==the returned length of a `std::string` does not include the implicit null-terminator character==.

#std-ssize
`std::ssize()` is a function defined in #cpp20, returns size of string.

#### std::string literals
#literals-string_literals

- provided by `<xstring>`

`std::string` literals can be created using `s` suffix imported from `std::string_literals` namespace.
``` cpp
#include <string>
int main()
using namespace std::string_literals;
{
	std::string cppliteral{"abc"s}; // string literal using suffix s from std
	char cliteral[] {"abc"}; // an array of chars, 3 chars + 1 null terminator
	return 0;
}
```

#### std::string_view
#TODO

# CHAPTER 6

### OPERATOR PRECEDENCE
#operator-precedence #operator-associativity 

**Operator precedence** - is an order in which operators will be evaulated. higher precedence operators are evaluated first.

**Operator associativity** - is a rule that determines whether equal precedence operators are evaluated left - right or right - left.
<mark class="hltr-grey">example:</mark>
```
x = 3 + 4 - 2 // addition and substraction have associativity Left to Right and same precedence of 6
// 3 + 4 first then 7 - 2 then assignment =operator  x = 7
```

#operator-precedence-associativity-table #precedence

| Prec/Ass | Operator                                                                                                                                                                                               | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                             | Pattern                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1 L->R   | ::  <br>::                                                                                                                                                                                             | Global scope (unary)  <br>Namespace scope (binary)                                                                                                                                                                                                                                                                                                                                                                                                                      | ::name  <br>class_name::member_name                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| 2 L->R   | ()  <br>()  <br>type()  <br>type{}  <br>[]  <br>.  <br>->  <br>++  <br>––  <br>typeid  <br>const_cast  <br>dynamic_cast  <br>reinterpret_cast  <br>static_cast  <br>sizeof…  <br>noexcept  <br>alignof | Parentheses  <br>Function call  <br>Functional cast  <br>List init temporary object (C++11)  <br>Array subscript  <br>Member access from object  <br>Member access from object ptr  <br>Post-increment  <br>Post-decrement  <br>Run-time type information  <br>Cast away const  <br>Run-time type-checked cast  <br>Cast one type to another  <br>Compile-time type-checked cast  <br>Get parameter pack size  <br>Compile-time exception check  <br>Get type alignment | (expression)  <br>function_name(arguments)  <br>type(expression)  <br>type{expression}  <br>pointer[expression]  <br>object.member_name  <br>object_pointer->member_name  <br>lvalue++  <br>lvalue––  <br>typeid(type) or typeid(expression)  <br>const_cast<type>(expression)  <br>dynamic_cast<type>(expression)  <br>reinterpret_cast<type>(expression)  <br>static_cast<type>(expression)  <br>sizeof…(expression)  <br>noexcept(expression)  <br>alignof(type) |
| 3 R->L   | +  <br>-  <br>++  <br>––  <br>!  <br>not  <br>~  <br>(type)  <br>sizeof  <br>co_await  <br>&  <br>*  <br>new  <br>new[]  <br>delete  <br>delete[]                                                      | Unary plus  <br>Unary minus  <br>Pre-increment  <br>Pre-decrement  <br>Logical NOT  <br>Logical NOT  <br>Bitwise NOT  <br>C-style cast  <br>Size in bytes  <br>Await asynchronous call  <br>Address of  <br>Dereference  <br>Dynamic memory allocation  <br>Dynamic array allocation  <br>Dynamic memory deletion  <br>Dynamic array deletion                                                                                                                           | +expression  <br>-expression  <br>++lvalue  <br>––lvalue  <br>!expression  <br>not expression  <br>~expression  <br>(new_type)expression  <br>sizeof(type) or sizeof(expression)  <br>co_await expression (C++20)  <br>&lvalue  <br>*expression  <br>new type  <br>new type[expression]  <br>delete pointer  <br>delete[] pointer                                                                                                                                   |
| 4 L->R   | ->*  <br>.*                                                                                                                                                                                            | Member pointer selector  <br>Member object selector                                                                                                                                                                                                                                                                                                                                                                                                                     | object_pointer->*pointer_to_member  <br>object.*pointer_to_member                                                                                                                                                                                                                                                                                                                                                                                                   |
| 5 L->R   | *  <br>/  <br>%                                                                                                                                                                                        | Multiplication  <br>Division  <br>Remainder                                                                                                                                                                                                                                                                                                                                                                                                                             | expression * expression  <br>expression / expression  <br>expression % expression                                                                                                                                                                                                                                                                                                                                                                                   |
| 6 L->R   | +  <br>-                                                                                                                                                                                               | Addition  <br>Subtraction                                                                                                                                                                                                                                                                                                                                                                                                                                               | expression + expression  <br>expression - expression                                                                                                                                                                                                                                                                                                                                                                                                                |
| 7 L->R   | <<  <br>>>                                                                                                                                                                                             | Bitwise shift left / Insertion  <br>Bitwise shift right / Extraction                                                                                                                                                                                                                                                                                                                                                                                                    | expression << expression  <br>expression >> expression                                                                                                                                                                                                                                                                                                                                                                                                              |
| 8 L->R   | <=>                                                                                                                                                                                                    | Three-way comparison (C++20)                                                                                                                                                                                                                                                                                                                                                                                                                                            | expression <=> expression                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| 9 L->R   | <  <br><=  <br>>  <br>>=                                                                                                                                                                               | Comparison less than  <br>Comparison less than or equals  <br>Comparison greater than  <br>Comparison greater than or equals                                                                                                                                                                                                                                                                                                                                            | expression < expression  <br>expression <= expression  <br>expression > expression  <br>expression >= expression                                                                                                                                                                                                                                                                                                                                                    |
| 10 L->R  | ==  <br>!=                                                                                                                                                                                             | Equality  <br>Inequality                                                                                                                                                                                                                                                                                                                                                                                                                                                | expression == expression  <br>expression != expression                                                                                                                                                                                                                                                                                                                                                                                                              |
| 11 L->R  | &                                                                                                                                                                                                      | Bitwise AND                                                                                                                                                                                                                                                                                                                                                                                                                                                             | expression & expression                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| 12 L->R  | ^                                                                                                                                                                                                      | Bitwise XOR                                                                                                                                                                                                                                                                                                                                                                                                                                                             | expression ^ expression                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| 13 L->R  | \|                                                                                                                                                                                                     | Bitwise OR                                                                                                                                                                                                                                                                                                                                                                                                                                                              | expression \| expression                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| 14 L->R  | &&  <br>and                                                                                                                                                                                            | Logical AND  <br>Logical AND                                                                                                                                                                                                                                                                                                                                                                                                                                            | expression && expression  <br>expression and expression                                                                                                                                                                                                                                                                                                                                                                                                             |
| 15 L->R  | \| \|<br>or                                                                                                                                                                                            | Logical OR  <br>Logical OR                                                                                                                                                                                                                                                                                                                                                                                                                                              | expression \| expression  <br>expression or expression                                                                                                                                                                                                                                                                                                                                                                                                              |
| 16 R->L  | throw  <br>co_yield  <br>?:  <br>=  <br>*=  <br>/=  <br>%=  <br>+=  <br>-=  <br><<=  <br>>>=  <br>&=  <br>\|=  <br>^=                                                                                  | Throw expression  <br>Yield expression (C++20)  <br>Conditional  <br>Assignment  <br>Multiplication assignment  <br>Division assignment  <br>Remainder assignment  <br>Addition assignment  <br>Subtraction assignment  <br>Bitwise shift left assignment  <br>Bitwise shift right assignment  <br>Bitwise AND assignment  <br>Bitwise OR assignment  <br>Bitwise XOR assignment                                                                                        | throw expression  <br>co_yield expression  <br>expression ? expression : expression  <br>lvalue = expression  <br>lvalue *= expression  <br>lvalue /= expression  <br>lvalue %= expression  <br>lvalue += expression  <br>lvalue -= expression  <br>lvalue <<= expression  <br>lvalue >>= expression  <br>lvalue &= expression  <br>lvalue \|= expression  <br>lvalue ^= expression                                                                                 |
| 17 L->R  | ,                                                                                                                                                                                                      | Comma operator                                                                                                                                                                                                                                                                                                                                                                                                                                                          | expression, expression                                                                                                                                                                                                                                                                                                                                                                                                                                              |

<mark class="hltr-green">good practice</mark>  - using parentheses to specify order of operations (looking up operator table takes time)
```cpp
x = y || b && a // b and a or y. logical and has higher precedence than logical or.
x = (y || b) && a; // makes it easy to read that y and b or a, without looking up operator precedence table
```

#### Value computation
#value-computation
The C++ standard uses the term **value computation** to mean the execution of operators in an expression to produce a value. The precedence and association rules determine the order in which value computation happens.

For example, given the expression `4 + 2 * 3`, due to the precedence rules this groups as `4 + (2 * 3)`. The value computation for `(2 * 3)` must happen first, so that the value computation for `4 + 6` can be completed.

#### Evaluation of operands
#evaluation-of-operands
The C++ standard (mostly) uses the term **evaluation** to refer to the evaluation of operands (not the evaluation of operators or expressions!). For example, given expression `a + b`, `a` will be evaluated to produce some value, and `b` will be evaluated to produce some value. These values can be then used as operands to `operator+` for value computation.

- term “evaluates” usually means evaluation of a full expression, not parts of it (subexpressions).

#### The order of evaluation of operands (including function arguments) is mostly unspecified

<mark class="hltr-grey">example:</mark> `a * b + c * d

the precedence and associativity rules ==only tell us== how operators and operands are grouped and the order in which value computation will occur. ==They do not tell us== the order in which the operands or subexpressions are evaluated. ==The compiler is free to== evaluate operands `a`, `b`, `c`, or `d` in any order. The compiler is also free to calculate `a * b` or `c * d` first.

- The Clang compiler evaluates arguments in left-to-right order. The GCC compiler evaluates arguments in right-to-left order. This is **implementation defined behaviour**


```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z);
}

int main()
{
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous
    // compiler is free to evaluate in any order

    return 0;
}
```
instead this main function will be more deterministic
```cpp
int main()
{
    int x getValue();
    int y getValue();
    int z getValue();
    // this ordering is determinstic on any compiler
    
    printCalculation(x,y,z); // ok.
    return 0;
}
```

<mark class="hltr-green">Conclusion</mark>
- Operands, function arguments, and subexpressions may be evaluated in any order.
- Precedence and associativity is used only to determine how operands are grouped with operators, and the order of value computation.

### ARITHMETIC OPERATORS
#addition #unary-minus #substraction #multiplication #division #remainder #division-by-zero

**UNARY**
are operators that take one operand

Unary `-operator` and `+operator`  
- unary -operator returns `operand * -1` 
- unary + operator returns same number
<mark class="hltr-green">For readability</mark> both operators should be placed like this `-x`, `+x`

**BINARY**
are operators that take two operands

|Operator|Symbol|Form|Operation|
|---|---|---|---|
|Addition|+|x + y|x plus y|
|Subtraction|-|x - y|x minus y|
|Multiplication|*|x * y|x multiplied by y|
|Division|/|x / y|x divided by y|
|Remainder|%|x % y|The remainder of x divided by y|

#### Integer and floating point division
==If either== (or both) of the operands are floating point values, the _division operator_ performs floating point division. **Floating point division** returns a floating point value, and the fraction is kept.

==If both== operators are integral values,  /operator performs integer division (fractional part is ignored!)!.
 
```cpp
#include <iostream>
using namespace std;

int main()
{
	int int_x{ 7 }, int_y{ 4 };
	float f_x{ 7.0f }, f_y{ 4.0f };

	cout << "int 4 / int 7 = " << int_y / int_x << '\n'; // outputs 0, fractional part ignored.
	cout << "float 7 / int 4 = " << f_x / int_y << '\n'; // outputs 1.75, output type = float.
	return 0;
}
```

- `static_cast<>()` should be used to perform explicit floating point division

#### Division by 0, division by 0.0

#TODO

### Increment / decrement operators `++x` `x++` 
#increment-operator-prefix #increment-operator-postfix 

|Operator|Symbol|Form|Operation|
|---|---|---|---|
|Prefix increment (pre-increment)|++|++x|Increment x, then return x|
|Prefix decrement (pre-decrement)|––|––x|Decrement x, then return x|
|Postfix increment (post-increment)|++|x++|Copy x, then increment x, then return the copy|
|Postfix decrement (post-decrement)|––|x––|Copy x, then decrement x, then return the copy|

- The prefix increment/decrement operators are very straightforward. First, the operand is incremented or decremented, and then expression evaluates to the value of the operand. 

- The postfix increment/decrement operators ==are trickier==. First, a copy of the operand is made. Then the operand (not the copy) is incremented or decremented. Finally, the copy (not the original) is evaluated

#### Side effects, not deterministic outputs
#side-effects
A function or expression is said to have a **side effect** if it has some observable effect beyond producing a return value.
```cpp
x = 5; // the assignment operator has side effect of changing value of x
++x; // operator++ has side effect of incrementing x
std::cout << x; // operator<< has side effect of modifying the state of the console
```

#warning
==Side effects can cause order of evaluation issues== The C++ standard does not define the order in which function arguments are evaluated.
```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int x { 5 };
    int value{ add(x, ++x) }; // undefined behavior: is this 5 + 6, or 6 + 6?
    // It depends on what order compiler evaluates the function arguments in

    std::cout << value << '\n'; // value could be 11 or 12, depending on how the above line evaluates!

    return 0;
}
```

When `x` is initialized to `1`, Visual Studio and GCC evaluate this as 6 + 6, and Clang evaluates it as `5 + 6`! This is due to differences in when the compilers apply the side effect of incrementing `x`.

These problems can generally _all_ be avoided by ensuring that any variable that has a side-effect applied is used ==no more than once== in a given statement.

### Comma operator `,`
#comma-operator

| Operator | Symbol | Form | Operation                             | Precedence  |
| -------- | ------ | ---- | ------------------------------------- | ----------- |
| Comma    | ,      | x, y | Evaluate x then y, returns value of y | 17 (lowest) |

in c++ comma symbol is also used as separator in function calls/prototypes

### Conditional operator `x ? y : z`
#conditional-operator
The conditional operator evaluates as part of an expression

| Operator    | Form      | Meaning                                                                | pattern                                | associativity/precedence |
| ----------- | --------- | ---------------------------------------------------------------------- | -------------------------------------- | ------------------------ |
| Conditional | c ? x : y | If conditional `c` is `true` then evaluate `x`, otherwise evaluate `y` | c ? expression true : expression false | 16 R -> L                |

variables defined inside if statements `if() {}` are destroyed at the end of braces `}` , so conditional operator `c ? x : y` is useful inside expression evaluations.

- The type of the second and third operand must match.
- The compiler must be able to find a way to convert one or both of the second and third operands to matching types. The conversion rules the compiler uses are fairly complex and may yield surprising results in some cases.
- one or both of the second and third operands is allowed to be a throw expression.

### Relational operators and floating point comparisons
|Operator|Symbol|Form|Operation|
|---|---|---|---|
|Greater than|>|x > y|true if x is greater than y, false otherwise|
|Less than|<|x < y|true if x is less than y, false otherwise|
|Greater than or equals|>=|x >= y|true if x is greater than or equal to y, false otherwise|
|Less than or equals|<=|x <= y|true if x is less than or equal to y, false otherwise|
|Equality|==|x == y|true if x equals y, false otherwise|
|Inequality|!=|x != y|true if x does not equal y, false otherwise|
good practice
```cpp
if (b1 == true); // using redundant equality operators 

if (b1); // should be this for readability

if (b1 == false); //redundant

if (!b1) //unary not, good.
```

**floating point values should not be compared using `==` or `!=` operators!** floating point values are imprecise and a tiny calculation error at the last right digit is expected

It is safe to compare a floating point literal with a variable of the same type that has been initialized with a literal of the same type, so long as the number of significant digits in each literal does not exceed the minimum precision for that type. Float has a minimum precision of 6 significant digits, and double has a minimum precision of 15 significant digits.

It is generally ==not safe== to compare floating point literals of different types.

### Logical operators
#todo short circuiting and xor stuff..

### BITWISE
#TODO круто

# CHAPTER 7 

A good practice to define globals inside a namespace.
<mark class="hltr-grey">globals.cpp</mark>
```cpp
#include "bitsets.h"

namespace global // user defined namespace
{
	// external linkage constant global variable - visible in other translation units (TU's) due to being external, 
	// value cant be changed (global).
	// lifetime - created at the beginning of a program before main(), destroyed when program terminates
	// scope - visible in any block.
	// linkage - external, can be acessed in other TU's.
	extern const float xoo{ 0.1f }; 
	
	// internal linkage constant global variable - visible inside this TU, value cant be changed (global).
	// lifetime - created at the beginning of a program before main(), destroyed when program terminates
	// scope - visible in any block.
	// linkage - internal, can be acessed in this file.
	static const int yoo{ 15 };

	// constexpr global variable -  visible inside this TU, cant be changed (constexpr variables need to guarantee being constant)
	// lifetime - created at the beginning of a program before main(), destroyed when program terminates
	// scope - visible in any block.
	// linkage - internal, can be acessed in this file.
	constexpr int voo{ 0 };

	// const global variable -  visible inside this TU, cant be changed (globals enforce read only)
	// lifetime - created at the beginning of a program before main(), destroyed when program terminates
	// scope - visible in any block.
	// linkage - internal, can be acessed in this file.
	const int im_maximalistic_person{ INT32_MAX };
}
```

<mark class="hltr-grey">globals.h</mark>
```cpp
//// header file is needed to propagate declarations to other files

#ifndef BITSETS_H_INCLUDES
#define BITSETS_H_INCLUDES

namespace global
{
	extern const float xoo; // the definition of this variable is located in paired source code file. This is declaration used to be seen in other source files.
}
#endif
```

--- 

==NOTE==: In order for variables to be usable in compile-time contexts, such as array sizes, the compiler has to see the variable’s definition (not just a forward declaration). `extern const float xoo` in `globals.h`cant be made made constexpr.

Because the compiler compiles each source file individually, it can only see variable definitions that appear in the source file being compiled (which includes any included headers). For example, variable definitions in _constants.cpp_ are not visible when the compiler compiles _main.cpp_. For this reason, constexpr variables cannot be separated into header and source file, they have to be defined in the header file.

==header file==, this is usable in c++17
```cpp

#ifndef CONSTANTS_H
#define CONSTANTS_H
inline constexpr myConstant{1}; // allows to propagate constexpr myConstant variable into files that include it.
#endif
```

---

**Qualified and unqualified names:** 
Qualified - inside of namespace `std::cout`
unqualified - not namespaced `x`

**Using keyword :**
Using directives and using declarations are scoped inside of block they were defined in:
```cpp
{
	using std::cout; // cout can be used without namespace qualifier operator here
	cout << "123";
} // cout no longer can be used without using declaration
```

**using directives:**
make identifiers inside of scope being used as visible:
```cpp
using namespace std;

int somevariable{};

cout << "123" // can now be acessed in that scope
cin >> somevariable 

// this is unsafe as it brings all identifiers into the scope
```

**using declarations:**
allows to use members of a namespace inside that block:
```cpp
{
	using std::cout; // now cout can be used without 
	cout << "123";
	
	// this is safer, as it allows to select what identifier to use in that scope.
}
```

==Do not use using-statements in header files (especially in the global namespace of header files).==

---

**Anonymous namespace:**
A namespace that provides internal linkage, and allows to avoid typing `static` keyword every time, usually used below `#include`  and above `main()`
```cpp
namespace
{
	void foo() {}; // function with internal linkage
	int xmyb{}; // variable with internal linkage
}
```

**Inline anonymous namespace:**
anonymous namespace that allows multiple definitions of same name identifiers, can be used for versioning
```cpp
inline namespace version1_11 // older version
{
	int foo() {return 0;}
}

inline namespace version1_2 // current version
{
	int foo() {return 2;}
}

version1_2::foo(); // new version called
```

# CHAPTER 8 Control Flow

|Category|Meaning|Implemented in C++ by|
|---|---|---|
|Conditional statements|Causes a sequence of code to execute only if some condition is met.|if, else, switch|
|Jumps|Tells the CPU to start executing the statements at some other location.|goto, break, continue|
|Function calls|Jump to some other location and back.|function calls, return|
|Loops|Repeatedly execute some sequence of code zero or more times, until some condition is met.|while, do-while, for, ranged-for|
|Halts|Terminate the program.|std::exit(), std::abort()|
|Exceptions|A special kind of flow control structure designed for error handling.|try, throw, catch|

**if statements:**
1. if(condition1) {statement1} else {statement1}
-  if first condition1 is true execute first statement1, otherwise execute second statement2 (single branch)

2. if(condition1) {statement1} else if (condition2) {statement2}
-  if condition1 is true execute statement1. If condition1 is false execute condition2, if condition2 is true - execute statement2. (two branches)

1. if(condition1) {statement1} if(condition2) {statement2}
-  if condition1 is true execute statement1. If condition2 is true execute condition2. (two branches)

Use ==if-else== when you only want to execute the code after the first `true` condition.
Use ==if-if== when you want to execute the code after all `true` conditions.

If statements can be constexpr (c++17)
```cpp
constexpr double gravity(9.81);

if constexpr (gravity > 9.7 && gravity < 9.9) { std::cout << "ok" }; // this if statement will be evaluated at compile time.
```

**Switch statement:**
- if variable being evaluated is equal to case, this case's branch is executed.
- variable must be an integral or enumerated type.
- if there is default branch, it is always executed.
- if there is no default, and no switch matched, switch statement is skipped.
- `default` should be located after all `case` keywords.
- `break` and `return` keywords can be used to end switch conditional.

```cpp
int x{5};
std::cin >> x;

switch (x)
{
case 0:
	std::cout << "0";
	break;	
case 1:
	std::cout << "1";
	break;
case 2:
	std::cout << "2";
	break;
default:
	std::cout << "default";
}
```

**Switch fallthrough:**
if switch cause has no `break;` terminating it, it will execute all instructions sequentially after it.
```cpp
int x{1};
switch (x)
{
case 1:
	cout << "1!"; // will get executed because x == 1.
case 2:
	cout << "2!"; // also executed
case 3:
	cout << "3!"; // also executed
}
```

`[[fallthrough]]`
```cpp
int x{1};
switch (x)
{
case 1:
	cout << "1!"; // will get executed because x == 1.
	[[fallthrough]]; // [[fallthrough]]; attribute ending with a null statement can be used to allow fallthrough
case 2:
	cout << "2!"; // also executed
	[[fallthrough]];
case 3:
	cout << "3!"; // also executed
	}
```

---

**for loop**:
equivalent to
```cpp
{
	init_statement;
	while (condition;)
	{
		statement;
		end_statement;
	}
}
```

and structure is
```cpp
for (init_statement; condition; end_statement)
```

mostly sugar for while loop.

multiple variables ==can== be can initalised and created in init_statement
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        {
	        std::cout << x << ' ' << y << '\n';
	     }
    return 0;
}
```

facts:
- creating a variable is very cheap
- initalising a variable is more expensive
- there is no difference between initalising and assigning a variable in cost.

---

**Prefer for-loops over while-loops when there is an obvious loop variable.  **
Prefer while-loops over for-loops when there is no obvious loop variable.

---

**Break:** terminates loops like `if`, `while`, `do while`, also terminates `switch` statements
**Continue:** ends current iteration, jumps to next iteration. for loops still execute their `end_statement`.
```cpp
for (int count{ 0 }; count < 10; ++count)
{
   // if the number is divisible by 4, skip this iteration
   if ((count % 4) == 0)
      continue; // go to next iteration

   // If the number is not divisible by 4, keep going
   std::cout << count << '\n';

   // The continue statement jumps to here
}
```

---

**Halting programs:**
https://www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/

`std::exit` - is a function that terminates the program, defined in `cpp <cstdlib> `, it does not clean up variables so can cause bugs.

# CHAPTER 9 

### **Code testing:** 
testing code is obligatory to ensure that a function block behaves like desired by a programmer.

**Statement coverage:**
Percentage or number of statements in a code snippet that were tested.

**Branch coverage:**
percentage of branches taken in a tested code snippet

**Loop coverage** 
(informally called **the 0, 1, 2 test**) says that if you have a loop in your code, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times. If it works correctly for the 2-iteration case, it should work correctly for all iterations greater than 2. These three tests therefore cover all possibilities (since a loop can’t execute a negative number of times).

**Testing different categories of inputs**
for a function `int foo(int x, int y)` test inputs are: (1, -1) ,(0,0) ( 500, 500), (INT32_MAX, INT32_MIN) etc.

**Assert**
A macro that is defined inside `<cassert>` header.
```cpp
assert(/*condition that evaluates to false*/ && /*error text string here*/) // if assert is true, it does not produce an error message
```

- assert is useful to set up conditions that allow to catch errors at runtime.
- ==assert halts the program==, without ability to recover, ==that can corrupt data ==.
- assert should be used in debug build, if preprocessor macro `NDEBUG` is defined, assert is excluded from compilation

**`assert()` expressions should have no side effects, as the assert expression won’t be evaluated when `NDEBUG` is defined (and thus the side effect won’t be applied).**

# CHAPTER 10

|Category|Meaning|Link|
|---|---|---|
|Numeric promotions|Conversions of small integral types to `int` or `unsigned int`, and of `float` to `double`.|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric conversions|Other integral and floating point conversions that aren’t promotions.|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Qualification conversions|Conversions that add or remove `const` or `volatile`.||
|Value transformations|Conversions that change the value category of an expression|[12.2 -- Value categories (lvalues and rvalues)](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)|
|Pointer conversions|Conversions from `std::nullptr` to pointer types, or pointer types to other pointer types||

|Category|Standard Conversion|Description|Also See|
|---|---|---|---|
|Value transformation|Lvalue-to-rvalue|Converts lvalue expression to rvalue expression|[12.2 -- Value categories (lvalues and rvalues)](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)|
|Value transformation|Array-to-pointer|Converts C-style array to pointer to first array element (a.k.a. array decay)|[17.8 -- C-style array decay](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)|
|Value transformation|Function-to-pointer|Converts function to function pointer|[20.1 -- Function Pointers](https://www.learncpp.com/cpp-tutorial/function-pointers/)|
|Value transformation|Temporary materialization|Converts value to temporary object||
|Qualification conversion|Qualification conversion|Adds or removes `const` or `volatile` from types||
|Numeric promotions|Integral promotions|Converts smaller integral types to `int` or `unsigned int`|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric promotions|Floating point promotions|Converts `float` to `double`|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric conversions|Integral conversions|Integral conversions that aren’t integral promotions|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Floating point conversions|Floating point conversions that aren’t floating point promotions|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Integral-floating conversions|Converts integral and floating point types|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Boolean conversions|Converts integral, unscoped enumeration, pointer, or pointer-to-memver to bool|[4.10 -- Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/)|
|Pointer conversions|Pointer conversions|Converts `std::nullptr` to pointer, or pointer to void pointer or base class||
|Pointer conversions|Pointer-to-member conversions|Converts `std::nullptr` to pointer-to-member  <br>or pointer-to-member of base class to pointer-to-member of derived class||
|Pointer conversions|Function pointer conversions|Converts pointer-to-noexcept-function to pointer-to-function||

---

**type promotion**
Compiler automatically converts smaller sized type like `short` to fit CPU and RAM architecturally. 
`short` 16bit -> `int` 32 bit 
`char`  8bit-> `int` 32 bit

This conversion ==is== value preserving and can be converted back (if value werent changed to overflow initial smaller size)

**Reinterpretive conversions**
unsafe numeric conversions where the converted value may be different than the source value, but no data is lost.
```cpp
 int n1 { 5 };
 unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

 int n2 { -5 };
 unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

```

==out-of-range conversion will produce modulo wrapping==

**Lossy conversions**
unsafe numeric conversions where data may be lost during the conversion.

`double x = 3` - okay, int to double conversion is value preserving
`int y = 3.5` - lossy conversion from double to integer, fractional part is truncated.

converting short and char to double is safe as short is 8 bits and char is 16 bits, while double is 64 bits. All values can be preserved. But ==converting long long to double will result in lossy conversion==

---

**In C++, a **narrowing conversion is a potentially unsafe numeric conversion where the destination type may not be able to hold all the values of the source type.**

- From a floating point type to an integral type.
- From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range of the destination type (even if the destination type doesn’t have the precision to store all the significant digits of the number).
- From an integral to a floating point type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.
- From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type. This covers both wider to narrower integral conversions, as well as integral sign conversions (signed to unsigned, or vice-versa).

---

**Arithmetic type conversions**
for expressions that contain different types to evaluate, compiler uses implicit arithmetic conversions. 

operators: arithmetic `+` `-` `*` `/` `%`, logic `> < <= >= == !=`, bitwise `& ^ |` - Require operand types to be the same

compiler ==converts operands of different types to== **common type** using a hierarchy from int to long double.

int -> long -> long long -> float -> double -> long double (highest rank)

```cpp
#include <type_traits> // adds std::common_type

std::cout << std::common_type_t<int,double> // returns common type of int and double 
```

```cpp
#include <typeinfo> // adds typeid class

std::cout << typeid(5u - 10).name << '\n'; // typeid.name returns "unsigned int 4294967291"
```

---

**Type deduction** #type_deduction
`auto` keyword can be used for a compiler to automatically select type of a variable
```cpp
auto x{ 5.5 + 25 * std::pow(4,4) }; //  x will evaluate to double type.
```

- type deduction ==drops== `const` from deduced types.
```cpp
const int a{5};
auto b{a}; // will be non const.
```

type deduction can be used with function return values.

**Trailing return type syntax** 
allows alternative way to display return type of a function (looks better)
```cpp
auto compare(int, double) -> std::common_type_t<int, double>; // easier to read 
{
// code here.
}
```

# CHAPTER 11

...
# CHAPTER 12 

**C++ supports these compound types:**
- Functions
- C-style Arrays
**Pointer types**:
| Pointer to object
| Pointer to function
**Pointer to member types**:
| Pointer to data member
| Pointer to member function
**Reference types**:
| L-value references
| R-value references
**Enumerated types**:
| Unscoped enumerations
| Scoped enumerations
**Class types**:
| Structs
| Classes
| Unions

---
### **lvalue** #lvalue
a value that can be identified using ==identifier, reference, or pointer,== and its storage duration is longer than one expression or statement.
| **modifiable lvalue** - `int myx{};`
| **non modifiable lvalue** - `const int myx{};` or `constexpr int myx{};`

### rvalue
a value that is **temporary**. Rvalues aren’t identifiable (meaning they have to be used immediately), and only exist within the scope of the expression in which they are used.

An lvalue will implicitly convert to an rvalue. This means an lvalue can be used anywhere an rvalue is expected.  
An rvalue, on the other hand, will not implicitly convert to an lvalue.
```cpp
x = 5; // rvalue to lvalue conversion, literal 5 is rvalue, operator= automatically converts.
```

---
## **referencing** #reference #alias
a reference is alias for existing object `int& ` - lvalue reference and `int&&` - rvalue reference,  reference is just different identifier for same data.

#### **variable being referenced and reference variable can have different lifetime.** / **Dangling references**
When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists. Such a reference is called a **dangling reference**.==Accessing a dangling reference leads to undefined behavior==.

| A reference can be destroyed before the object it is referencing.
|The object being referenced can be destroyed before the reference.

**const lvalue references**
lvalue reference can bind to modifiable lvalues, using const keywoard in reference definition prevents modifying the reffered to object, making the reference an read-only.
```cpp
int x{100};
const x_ref{ x }; // read only.

std::cout << x_ref << '\n'; // prints 100
x = 150;
std::cout << x_ref << '\n'; // prints 150
x_ref = 150; // no.

```

**lvalue reference cant bind to a value of different type** / *lvalue reference cant bind to rvalues.*
```cpp
int x{1};
double& invalidRef{ x }; // x is int type, compiler can try to convert it to double but converted values are rvalue.
								 // lvalue reference can only bind to a modifiable lvalue.
								 
const double& yes{ x }   // x is converted to double and becomes rvalue, it is an const lvalue reference, can bind
								 // to rvalues for read only purposes.

double y{2.0};
double& ok{y} // ok.
```

**rvalue reference is created using `&&` symbol.**
```cpp
template <typename T>
bool isrvalue( T&& ) { return true; } // this is overloaded function that refers to rvalues

template <typename T>
bool isrvalue( T& ) { return false; } // this is overloaded function that refers to lvalues

int main()
{
    double x{0.5};
    std::cout << "variable x is " << (isrvalue(x) ? "rvalue" : "lvalue") << '\n';
    std::cout << "literal 5 is " << (isrvalue(5) ? "rvalue" : "lvalue") << '\n';
}
```
outputs:
```
variable x is lvalue
literal 5 is rvalue
```

when function is overloaded, compiler chooses the function that fits the type of parameter (or converts types), ==template metaprogramming== generates a function that can support both int and double type, but rvalue and lvalue are different and will be routed to their respective alias types.

**nomenclature**
	A type that specifies a reference (e.g. `int&`) is called a **reference type**. The type that can be referenced (e.g. `int`) is called the **referenced type**.
	The process by which such a reference is bound (attached to object) is called **reference binding**. The object (or function) being referenced is sometimes called the **referent**.

---

Pointer and reference combinatorics. `Type of int uses for all examples

| Value              | pointer                                           | explanation                                                                                                                      |
| ------------------ | ------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| int x{}            | int* ptr{ &x }                                    | pointer to lvalue, ok                                                                                                            |
| int x{}            | int* const ptr{ &x }                              | const pointer to non const lvalue, const pointer's adress cant be changed.                                                       |
| int x{}            | const int* ptr{ &x }                              | pointer to const lvalue at adress of x, where x is treated as const if dereferenced using pointer's identifier                   |
| int x{}            | const int* const ptr{ &x }                        | const pointer to non const lvalue that is treated as const if dereferenced using a pointer's identifier                          |
| const int x{}      | int* ptr{ &x }                                    | pointer to non const cant point to const lvalue: COMPILATION ERROR                                                               |
| const int x{}      | int* const ptr{ &x }                              | const pointer to const lvalue without using const keyword behind the type: COMPILATION ERROR                                     |
| const int x{}    . | const int* prt{ &x }                .             | pointer to const lvalue at adress of x                                                                                           |
| const int x{}      | const int* const ptr{ &x }                        | const pointer to const lvalue at adress of x                                                                                     |
| .                  | int* ptr{ } or int* ptr{nullptr}                . | pointer that holds nullpointer (value with no adress), implicitly converts to false bool allowing to check if pointer is nullptr |

| Value                        | reference                           | explanation                                                                                                                                                                     |
| ---------------------------- | ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| int x{}        .             | int& ref{x}                         | reference to x, x can be read and written through ref                                                                                                                           |
| int x{}                      | const int& ref{x}                 . | const reference to x, can read value of x only, changing x through ref is disallowed. const reference can bind to: const lvalues, lvalues, rvalues (creating temporary objects) |
| const int x{}              . | int& ref{x}                         | cant bind modifiable reference to const lvalue: COMPILATION ERROR                                                                                                               |
| const int x{}                | const int& ref{x}                   | okay, can bind const reference to const lvalue.                                                                                                                                 |
| 5                            | const  int& ref{x}                  | can bind to rvalues creating temporary values, WARNING: compiler can do implicit conversions, which is not desired.                                                             |

---

**NULLPOINTER** #nullptr #nullptr_t
`int* ptr{ } or int* ptr{ nullptr }`
pointer that holds nullpointer (value with no adress), implicitly converts to false bool allowing to check if pointer is invalid.

`nullptr_t` is a type that can hold one value - nullpointer.

checking for nullpointer
```cpp

if (ptr) // any valid pointer adress converts to boolean true
{
	*prt += 1; // ok
}
else
{
	// evaluated to false, so pointer holds nullptr, should not be dereferenced.
}

```

even better alternative
```cpp
template <typename T>
void checkpointer(T* ptr)
{
	assert(ptr && "nullpointer passed" );
}
```

**PASSING BY ADRESS**
possible in two ways
```cpp
void modifyYourID( const int* id ) { *id += 1; }

int user{ 10 };

modifyYourID( &user ); // passing adress of user to const pointer.

```

```cpp
void modifyYourID( const int* id ) { *id += 1; }

int user{ 10 };
int* user_ptr{ user };

modifyYourID( user_ptr ); // passing pointer that already holds adress of user.

```

**PASSING BY ADRESS DOES NOT CHANGE ARGUMENT**
when passing adresses to functions that have pointer parameters, changing pointer inside of function changes what function's pointer points to, not what argument pointer does
```cpp
#include <iostream>

void nullify( int* ptr2)
{
    ptr2 = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    nullify(ptr); // ptr wont be nullified, only ptr2 will, but ptr2 is a pointer inside of function.
    return 0;
}
```

**PASSING BY REFERENCE TO POINTER**
yep
```cpp
#include <iostream>

void nullify( int*& ptr2) // reference to pointer type variable
{
    ptr2 = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

	 nullify(ptr) // function has reference to ptr, any changes applied to ptr2 are done to ptr. Will be nullptr.
	 return 0;
}
```

---

**RETURNING BY REFERENCE / POINTER**
==Important note== - **References or pointers returned by functions are temporary values (rvalues)!**

```cpp
#include <iostream>

int* fooPtr(int* adress) // accepts adress as argument and stores it in pointer variable, returns that same pointer type variable
{
	*adress *= 10;
	return adress;
}

int& fooRef(int& adress) // binds reference to variable argument, then returns that same reference.
{
	adress *= 10;
	return adress;
}

int main()
{
	int x{2};
	int y{3};

	std::cout << fooRef( x ) << '\n'; // return value is reference to x.
	std::cout << *fooPtr( &y ) << '\n'; // return value is pointer to x, which is dereferenced to read value of x.

	std::cout << '\n' << x << '\n'; // x was modified by fooRef
	std::cout << y << '\n'; // y was modified by fooPtr
	return 0;
}
```

**The object being returned by reference must be valid after function returns** - local variables created inside functions or temporary values will be destroyed after function terminates, that would leave pointers or references **dangling** and pointing to garbage bytes ( undefined behaviour ).

**Lifetime extension doesn’t work across function boundaries** - returning a reference (const or modifiable) to temporary value leads to **UB**, as temporary values are destroyed after function scope ends.

**Rvalues passed via const reference can be returned back via const reference**
```cpp
const std::string& pass(const std::string& string)
{
	return string;
}
// this function uses const reference as argument to then return same const reference.
```

Return value is rvalue.

**If function returns non const reference, the caller can modify value of an argument.**
```cpp
#include <iostream>

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7
    // function were passed variables max(a,b), b is > than a, so function returned reference to b, then b was assigned to 7. 

    std::cout << a << b << '\n'; // returns 57

    return 0;
}
```

**return by adress**
the object being returned by address must outlive the scope of the function returning the address, otherwise the caller will receive a dangling pointer. ==Pointer can return a== `nullptr`, that can be used to signify that object does not exist.

---

**Type deduction with const, references and pointers** #type_deduction #auto_keyword
when using `auto` keyword, the type of a variable is deduced from variable initaliser or literal initaliser. `const` is dropped.
```cpp
double a{ 7.7 };
auto b{ a } // compiles with double type.
const auto c // compiles with const double type.
```

type deduction drops **references** too
```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref { getRef() }; // type deduced as std::string (not std::string&)
	 auto& ref2 { getRef() }; // type deduced as std::string, then bound to reference again. 
    return 0;
}
```

#### Top-level const and low-level const

| A **top-level const** is a const qualifier that applies to an object itself.
```cpp
const int x;    // this const applies to x, so it is top-level
int* const ptr; // this const applies to ptr, so it is top-level
// references don't have a top-level const syntax, as they are implicitly top-level const
```

| a **low-level const** is a const qualifier that applies to the object being referenced or pointed to:
```cpp
const int& ref; // this const applies to the object being referenced, so it is low-level
const int* ptr; // this const applies to the object being pointed to, so it is low-level
```

# CHAPTER 13

**Structs:**
an object that contains data, and locates it in its own namespace.
```cpp
struct Color
{
	unsigned char red{};
	unsigned char green{};
	unsigned char blue{};
};
```
struct members should be default initalised using `{}`, copy init and direct init also works. 
Explicit initialization values take precedence over default values
```cpp
int main()
{
	Color pants{} // default initalises all member variables.
	Color shirt{210, 100, 0} // assigning values to red, green, blue.
	Color gloves{23, 100} // assigning values to red, green, blue is default initalised.
	return 0;
}
```

**Acessing struct member variables:**
```cpp
#include <iostream>

int main()
{
	Color pen{1,2,3};
	std::cout << pen.red; // acessing red from color user type.
	return 0;
}
```

**Aggregate:**
an aggregate in C++ is either a C-style array
or a class type (struct, class, or union) that has:
- No user-declared constructors ([14.9 -- Introduction to constructors](https://www.learncpp.com/cpp-tutorial/introduction-to-constructors/))
- No private or protected non-static data members ([14.5 -- Public and private members and access specifiers](https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/))
- No virtual functions ([25.2 -- Virtual functions and polymorphism](https://www.learncpp.com/cpp-tutorial/virtual-functions/))
==documentation here== https://en.cppreference.com/cpp/language/aggregate_initialization

**Creating rvalue structs, deducing type by user-type initaliser signature**
```cpp
#include <iostream>

struct Player
{
	float health{100};
	float speed{5.5f};
	float damage{25.0f};
};

bool checkPlayerDeath( const Player& player)
{
	if ( player.health < 1 ) 
	{ 
	// play death animation and return..
	}
}

int main()
{
	checkPlayerDeath( Player {0,5,5} ); // creating rvalue variable with type Player and initial data.
	
	// This is bad. this form is considered an implicit conversion.
	bool isDead2{ checkPlayerDeath( { 25,5,5 } )}; // type deduced from type signature, but its very ambiguous..
	return 0;
}
```

==temporary objects: they are created and initialized at the point of definition, and are destroyed at the end of the full expression in which they are created. And evaluation of a temporary object is an rvalue expression, it can only be used in places where rvalues are accepted. When a temporary object is used as a function argument, it will only bind to parameters that accept rvalues. This includes pass by value and pass by const reference, and excludes pass by non-const reference and pass by address.==

**Returning structs**
```cpp
struct Player
{
	float health{100};
	float speed{5.5f};
	float damage{25.0f};
};

Player createDefaultPlayer()
{
	return Player{100.0f,10.0f,15.0f} // returning an copy of rvalue Player type;
}

```

**overloading operator<< to print struct data with help of std::cout**:
```cpp
//struct containing colors.
struct Color
{
	std::uint8_t red{ 0 };
	std::uint8_t green{ 0 };
	std::uint8_t blue{ 0 };
};

// std::ostream is a default output stream object (to console).
std::ostream& operator<<(std::ostream& to_stream, const Color& color_object)
{
	// converting uint8_t (Which is treated as char by iostream library) to short (to make it read as number) 
	to_stream << "r" << (short)(color_object.red) << " g" << (short)(color_object.green) << " b" << (short)(color_object.blue);
	return to_stream; // returning modified ostream to expression which called it!
}
```
