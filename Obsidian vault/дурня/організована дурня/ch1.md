

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
    "std::cout" is a statement (оператор), std:: means we take a function from standart library, cout is the part of iostream library
     inside standart library
    "<<" INSERTION OPERATOR: allows to display information on console and concatenate (connect strings together, обєднувати рядки у один)
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
