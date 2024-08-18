# 42_cpp06

## Exploring the limits header
The <limits> header was introduced in C++98 and provides information about the limits of various numerical data types. It defines constants that represent the minimum and maximum values for different types, such as int, float, double, etc.

Key constants and their meanings:

- `numeric_limits<T>::min()`: Returns the minimum value representable by the type T.
- `numeric_limits<T>::max()`: Returns the maximum value representable by the type T.
- `numeric_limits<T>::lowest()`: Returns the most negative value representable by the type T.
- `numeric_limits<T>::digits()`: Returns the number of base-2 digits in the significand of the type T.
- `numeric_limits<T>::digits10()`: Returns the number of base-10 digits in the significand of the type T.
- `numeric_limits<T>::is_integer()`: Returns true if the type T is an integer type.
- `numeric_limits<T>::is_signed()`: Returns true if the type T is signed.
- `numeric_limits<T>::is_specialized()`: Returns true if the numeric_limits template is specialized for the type T.

From here we can test the limits of the types we are gonna use in the exercises.

```cpp
std::cout << "Limit checks -----------------"  << std::endl;
float inf = std::numeric_limits<float>::infinity();
double inf_double = std::numeric_limits<double>::infinity();
float nan = std::numeric_limits<float>::quiet_NaN();
double nan_double = std::numeric_limits<double>::quiet_NaN();

std::cout << "Positive infinity for float: " << inf << std::endl;
std::cout << "Positive infinity for double: " << inf_double << std::endl;
std::cout << "Negative infinity for float: " << -inf << std::endl;
std::cout << "Negative infinity for double: " << -inf_double << std::endl;

std::cout << "NaN for float: " << nan << std::endl;
std::cout << "NaN for double: " << nan_double << std::endl;

// Trying to use infinity with an integer will result in undefined behavior
int int_inf = std::numeric_limits<int>::max(); // This will give the maximum int value
int neg_int_inf = std::numeric_limits<int>::min(); // This will give the minimum int value
std::cout << "Integer infinity (just int max): " << int_inf << std::endl;
std::cout << "Negative integer infinity (just int min): " << neg_int_inf << std::endl;

```
The above will print 
```
Limit checks -----------------
Positive infinity for float: inf
Positive infinity for double: inf
Negative infinity for float: -inf
Negative infinity for double: -inf
NaN for float: nan
NaN for double: nan
Integer infinity (just int max): 2147483647
Negative integer infinity (just int min): -2147483648
```

Surprisingly I cannot overlof a float or double, it will just return infinity.  
But I can helas overflow an integer.

## What is NaN 
NaN (Not a Number) is a special floating-point value used to represent undefined or non-representable results in mathematical operations. It can occur due to various reasons, such as:
- Division by zero: 0.0 / 0.0
- Square root of a negative number: `sqrt(-1.0)`
- Operations involving infinity: infinity + infinity, infinity - infinity
- Certain trigonometric functions with invalid arguments `atan2(0, 0)`

### Generating NaN:

C++ provides the `nan()` function in the <cmath> header to create NaN values. It takes an optional string argument that can be used to distinguish different NaN values (implementation-specific).

Example:
```C++

#include <iostream>
#include <cmath>

int main() {
    float nan_value = std::nanf("invalid"); // Create a NaN value

    // Check if the value is NaN
    if (std::isnan(nan_value)) {
        std::cout << "Value is NaN" << std::endl;
    } else {
        std::cout << "Value is not NaN" << std::endl;
    }

    // Operations with NaN
    float result = 10.0 / nan_value;
    std::cout << "Result: " << result << std::endl; // Output: NaN

    return 0;
}
```
Output:
```
Value is NaN
Result: nan
```

### Remember:
- `std::nan()` creates a NaN value.
- The `std::isnan()` function can be used to check if a value is NaN.
- Arithmetic operations involving NaN usually result in NaN.
- NaN values are often used to indicate error conditions or undefined results.
- NaN values are not equal to themselves. Comparing a NaN value with itself using == will always return false.
- To check if a value is NaN, use `std::isnan()`.

## casting values to different types
In this module we are going to practice casts in C++.  

### Promotion casting
It occurs **automatically** in C++ when a value of a narrower data type is used in an expression with a wider data type.  
In general doesnt lose information except for some cases of large integer to floating point.
Example: 
- Integer promotion: When an integer type (e.g., char, short, int) is used in an expression with a wider integer type (e.g., long, long long), the narrower type is promoted to the wider type.  
- Floating-point promotion: When a floating-point type (e.g., float) is used in an expression with a wider floating-point type (e.g., double, long double), the narrower type is promoted to the wider type.
- Integral promotion to floating-point: When an integer type is used in an expression with a floating-point type, the integer type is promoted to the floating-point type. This can result in a loss of precision if the integer type has more significant digits than the floating-point type can represent!

```cpp
	int i = 42;
	long l = i; // implicit promotion from int to long
	float d = i; // implicit promotion from int to float - might be lossy
```
### Demotion casting
Generally not recommended, as it can result in loss of information or precision. Ex a float to int cast will truncate the decimal part of the float.  
```cpp
	double d = 3.14;
	int i = d; // implicit demotion from double to int - lossy
```

## Explicit casting
C++ provides several casting operators to convert values from one data type to another. Here's a breakdown of the most common ones:

### Static Cast `static_cast<T>(expr)`:

- Similar to the C style cast `(T)expr`, but with additional type checking at compile time and the advantage of a clear syntax.

### C-Style Cast `(T)expr`:
- The one we know and love :) 
    
### Dynamic Cast `dynamic_cast<T>(expr)`:
- Used for runtime type identification and safe downcasting.
- Only works with polymorphic types (classes with virtual functions).
- Returns nullptr if the cast is unsuccessful.

### Reinterpret Cast (reinterpret_cast<T>(expr)):

- Used for low-level type conversions, such as reinterpreting an integer as a pointer.

### Const Cast (const_cast<T>(expr)):

- Used to remove or add the const qualifier from a variable.

Examples:
```cpp
int x = 10;
double y = static_cast<double>(x); // Convert int to double
char c = (char)x; // C-style cast

int* ptr = new int[10];
void* voidPtr = reinterpret_cast<void*>(ptr);

const int z = 5;
int* mutableZ = const_cast<int*>(z); // Remove const qualifier - requires a pointer as input
```

## Undefined behavior by casting
There are things to be carefule when casting values.
Example with reinterpret casting:
```cpp
reinterpret_cast<int*>(0); // Undefined behavior: dereferencing a null pointer
// or
int* intPtr = new int;
char* charPtr = reinterpret_cast<char*>(intPtr); // Undefined behavior: accessing an object through a pointer of a different type
```

Interestingly the `const_cast` can have unexpected behaviour too. Lets see this:
```cpp
const int x = 42; // x is a constant integer
const int* p = &x; // p is a pointer to a constant integer

int* q = const_cast<int*>(p); // Remove const qualifier from p

*q = 24; // Attempt to modify the value of x through q

std::cout << "x: " << x << std::endl; // Undefined behavior: the value of x is not guaranteed to be 24
std::cout << "*q: " << *q << std::endl; // Undefined behavior: the value of *q is not guaranteed to be 24
```

## ex00 - Conversion of scalar types

>Write a class ScalarConverter that will contain only one static methods "convert" that will takes as parameter a string representation of a C++ literal in its most common form and output its value in the following serie of scalar types : char, int, float, double.  
As this class doesn’t need to store anything at all, this class must not be instanciable by users. You have to first detect the type of the literal passed as parameter, convert it from string to its actual type, then convert it explicitly to the three other data types.  

Example:
```
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
./convert nan
char: impossible
int: impossible
float: nanf
double: nan
./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
```

### Learned
The most interesting I learned from this exercise is that I can pass `inf` and `nan` to a double or float and it will be handled correctly.  See above for the limits...
This means that I do not need to handle a string with hardcoded values for `inf` and `nan` as I can just pass them as a string to the float or double conversion function and it will be handled correctly.
For float conversion I will use:
```cpp
float f = std::strtof(str.c_str(), &endptr);
```
And for doubles:
```cpp
double d = std::strtod(str.c_str(), &endptr);
```
The `endptr` is a pointer to a char that will be set to the first character that is not part of the number. This is for error checking.  
Both functions will return 0.0 if the conversion fails. Therefore I need to check for the error to see if I am out of range.

Example:
```cpp
float f = std::strtof(str.c_str(), &endptr);

```

`strtod()` will return `std::numeric_limits<double>::infinity()` (or `inf`) when the input string represents a number that is too large to be represented as a finite double value. This is often referred to as overflow.

Similarly, `strtod()` will return `-std::numeric_limits<double>::infinity()` (or -inf) when the input string represents a number that negative and too large to be represented as a finite double value. This is referred to as underflow.

Same for the floats. The `strtof()` will return `std::numeric_limits<float>::infinity()` (or `inf`) when the input string represents a number that is too large to be represented as a finite float value. This is often referred to as overflow. But as alias I can pass `inff` and -inff` to the float conversion function.

## is this an INT? a naive check and a better one
How to check if a string is an integer in C++?  
Naively and because I come from C I would check if the string is an Int by checking if the characters are all digits.  
```cpp
bool isInteger(const std::string& str) {
	std::string::size_type start = 0;
	if (str[0] == '-' || str[0] == '+') {
		start = 1;
	}
	for (std::string::size_type i = start; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

```
but really There is a better way using the limits header.
```cpp
bool isInteger(const std::string& str) {
 	char* endptr;
    long long value = std::strtoll(str.c_str(), &endptr, 10);

    return *endptr == '\0' && errno == 0 && (value >= INT_MIN && value <= INT_MAX);
}
```