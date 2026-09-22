#TODO - записати значення у нотатку???
```
In lesson [1.3 -- Introduction to objects and variables](https://www.learncpp.com/cpp-tutorial/introduction-to-objects-and-variables/), we discussed how a variable definition such as `int x;` causes the variable to be instantiated when this statement is executed. Function parameters are created and initialized when the function is entered, and variables within the function body are created and initialized at the point of definition.
```

#TODO - Сенс термінів instantiated та assigned,  не зрозумілий у цьому нотатнику, важливо опиратись на learncpp.com. Тре перенести цю фігню у цей файл. declared та defined також не розкриті в своєму значенні повністю у [[#**VARIABLES**]]. 

#TODO - повний список термінів потребуючих запису:

- [ ] Defined - глобальний
- [ ] Declared - глобальний
- [ ] Assigned - глобальний
ЗМІННІ
- [x] Defined 
- [x] Declared 
- [ ] Assigned 
- [ ] Instantiated
- [x] Initalised змінні
ФУНКЦІЇ
- [ ] lifetime
- [ ] pass by value
 ЦЕЙ TODO НЕ повний


---
## **VARIABLES**

In C++ direct acess to memory is discouraged (as a good practice), instead objects are used,  An *object* represents a region of storage (typically RAM or a CPU register) that can hold a value. Although objects in C++ can be unnamed (anonymous), more often we name our objects using an identifier. An object with a name is called a **variable**.

This is a statement containing **declaration** and **definition** of a variable with an **identifier** of `"my_variable"` and a **type** of `int`, then **initalised** with an initial default value using [[#**List - Initalisation or direct List - Initalisation **| list initalisation]]

```
int my_variable{};
```

"{}" is an list-initializer (The process of specifying an initial value for an object)


### *Kinds of variable initalisations in C++*

###### **List  Initalisation or direct List  Initalisation, Value Initalisation or Zero Initalisation:**

```
int alpha{ 10 };
```

`{}` is the initaliser syntax.

```
int value{};
```

zero initalisation, where no initial value for list initaliser is specified, compiler usually puts a zero value for an integer or float data types, or just nothing for a string or a char data types. 
a **good practice**, because initalising a variable with no specified initaliser leaves variable to have unknown value that was used in that part of RAM, leading to **unindentified behaviour**.
 
###### **Copy  Initalisation:** 

```
int beta = 10;
```

`=` is an assignment operator, in that case acts as initaliser for variable named `"beta"`

###### **Direct  Initalisation:**

```
int x();
```

`()` syntax acts as initaliser, unsafe as it can be mistaken by a compiler with function declaration syntax like `myFunction()`. 
### *Instantiation:*

---
## **FUNCTIONS**

### *Local scope:*

Variables defined in a body of a function are called *local variables*, function parameters are also considered to be local variables

### *Function lifetimes:*

Variables defined inside a body of a function are called "**Local variables**", function parameters are also considered to be local variables.
When a function is called, its parameters are created and initalised, and variables within the function body are created and initialized at the point of definition.
Local variables are **destroyed in the opposite order of creation** at the end of the set of curly braces in which it is defined.

```
int exampleLifetime(int A, int B) // parameters A and B take the argument values from the caller function,  are created and initalised as local variables inside the function.
{
    int o{0}; // o is created and initalised as local variable
    return o + A + B;

} // o, A, B variables created inside this function are destroyed, their lifetime ends here.

```


`!!!`  variable creation and destruction happen when the program is at runtime, not at compile time. **Lifetime is a runtime property**.
Any use of an object after it was destroyed will result in undefined behaviour.
at some time after destruction of an object, the memory will be "deallocated" (freed for reuse in RAM).
