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

## Float and doubles bit mappings
Check the blog article by Fabien Sanglard (link below) for the explanation of floats mappings...  for completeness I add the special cases here

### Special Values in IEEE Floating-Point Arithmetic

**IEEE 754** defines several special values in floating-point arithmetic to handle exceptional cases and represent certain mathematical concepts. These values are distinct from ordinary numbers and have specific interpretations:

### Zero

* **Representation:** An exponent of all 0s and a mantissa of all 0s.
* **Values:** Both positive and negative zero (`+0` and `-0`) are distinct values, but they are considered equal in most comparisons.

### Denormalized Numbers

* **Representation:** An exponent of all 0s and a non-zero mantissa.
* **Purpose:** Denormalized numbers are used to represent values that are smaller than the smallest normalized number. They do not have an implicit leading 1 before the binary point.

### Infinity

* **Representation:** An exponent of all 1s and a mantissa of all 0s.
* **Values:** Both positive and negative infinity (`+∞` and `-∞`) are represented. Operations with infinity are defined in IEEE 754 to follow mathematical conventions.

### Not a Number (NaN)

* **Representation:** An exponent of all 1s, a zero sign bit, and a non-zero mantissa.
* **Purpose:** `NaN` represents a result that cannot be represented as a valid number, such as the result of an invalid operation (e.g., dividing by zero). There are two types of `NaN`: signaling `NaN` (sNaN) and quiet `NaN` (qNaN).

| Operation | Result |
|---|---|
| ±∞ ÷ ±∞ | NaN |
| 0 ÷ ±∞ | 0 |
| ±∞ × ±∞ | ±∞ (sign depends on operands) |
| ±∞ × ±0 | NaN |
| ±∞ ÷ ±0 | ±∞ (sign depends on operands) |
| ±nonZero ÷ ±∞ | 0 |
| ±∞ + ∞ | ±∞ (sign depends on operands) |
| ±∞ - ∞ | ±∞ (sign depends on operands) |
| ±∞ + ±finite | ±∞ (sign depends on operands) |
| ±∞ - ±finite | ±∞ (sign depends on operands) |
| ±0 ÷ ±0 | NaN |
| ±∞ ÷ ±∞ | NaN |
| ±∞ × 0 | NaN |
| NaN == NaN | False |

Additional Notes
- NaN Propagation: If any operand in an operation is NaN, the result will also be NaN.
- Sign Preservation: In operations involving infinity, the sign of the result is determined by the signs of the operands, following standard mathematical rules.
- Indeterminate Forms: Some operations, such as 0/0 or ∞ - ∞, result in indeterminate forms and produce NaN as the result.

# ex00 - static_cast

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
But this was not enough. There is a mistake in the previous code. The `errno` is not reset to 0 before the call to `strtoll()`.  And moreover the double is cast to a long long but a double can be much bigger so who can tell me if the long long would overflow? There is a small trick. A float would fit in a long long so I can cast the double to a float and if this produces an `inf` then I know that the double was too big for my int anyway. if the cast to float succeeded then I can cast the float to a long long and check if it is in the range of an int.
```cpp
static bool is_int(const std::string& str) {
	errno = 0;
	char* endptr;
	if (isinf(std::strtof(str.c_str(), &endptr)) || isnan(std::strtof(str.c_str(), &endptr))) {
		return false;
	}
    long long value = std::strtoll(str.c_str(), &endptr, 10);
    return *endptr == '\0' && errno == 0 && (value >= INT_MIN && value <= INT_MAX);
} 
```
Another problem was that passing a `nan` to the `strtof()` is undefined behaviour. So I need to check for this too, with `isnan()`.

For floats I would use the same but keeping in mind that `strtof` and `strtod` will set the errno to the value of 34 if the conversion is out of range or `inf` or `nan`. But I do accept `inf` and `nan` as valid floats. So I remove the check for `errno == 0`. Also I consider floats strings that are ending with an `f`. Otherwise I consider them doubles. `nanf` and `inff` are valid floats.  `nan` and `inf` are valid doubles.
So:
```cpp
static bool is_float(const std::string& str) {
  	char* endptr;
	std::strtof(str.c_str(), &endptr);
    return *endptr == 'f';
}
```
Ops the above again was too simplistic... depending of the implementations the `strtof()` will not accept the 'f' at the end as part of the float? Also what if I pass ff or fff? I am ok if is an out of bound float.
```cpp
// updated implementation
static bool is_float(const std::string& str) {
	errno = 0;
	char* endptr;

	// has to end with f
	if (str[str.size() - 1] != 'f') {
		return false;
	}

	// once the above is checked we can remove the f but str is a const so we need to create a copy
	std::string modified_str = str.substr(0, str.size() - 1);
	// if there is nothing left after removing the f something is fishy
	if (modified_str.empty()) {
		return false;
	}
	// verify that the string is a valid float/dounle
	float value = std::strtof(modified_str.c_str(), &endptr);

	// is the string a valid float then would not have any other chars in it
	if (*endptr != '\0') {
		return false;
	}
	return true;
}
```

So I found out that i did not have to hardcode the inf and nan values passed in the converter if i pass them to the float or double conversion functions. The values are not supposed to be char or int anyway.  

The order nmaters though, so i check if int or char first (char being a substype kind of int) and then if it is a float or double.

### INT overflow? 

Checking for INT overflow above I used the trick to convert my interger to long long:
```cpp
static bool is_int(const std::string& str) {
	[...]
    long long value = std::strtoll(str.c_str(), &endptr, 10);
    return *endptr == '\0' && errno == 0 && (value >= INT_MIN && value <= INT_MAX);
}  
```
but in the subject they really say this:
> Allowed functions : Any function to convert from a string to an int, a float or a double. This will help, but won’t do the whole job...

Ok... Ah these tricky subjects at 42... So apparently using strtoll ia not allowed? I can do without!

I was thinking to convert my string to a double and then check for the overflow. But does my double have enough precision? We can print the precision of a float and a double with the following code:
```cpp
std::cout << "Precision of float: " << std::numeric_limits<float>::digits10 << std::endl;
std::cout << "Precision of double: " << std::numeric_limits<double>::digits10 << std::endl;
```
So a float has a precision of 6 digits! My int_max has 10 digits, hehe, so this is not working. But a double has 15 digits precision. So I can convert my string to a double and then check if it is in the range of an int.  
I print the INT_MAX and INT_MAX -1 converted to a double and a float...
```cpp
double value = std::strtod(mystr.c_str(), &endptr);
double value2 = std::strtod(mystr2.c_str(), &endptr);
std::cout << std::fixed << std::setprecision(0) << "Value overflow: " << value << std::endl;
std::cout << std::fixed << std::setprecision(0) <<"Value2 not overflow: " << value2 << std::endl;
std::cout << "Precision of double: " << std::numeric_limits<double>::digits10 << std::endl;

float value3 = std::strtof(mystr.c_str(), &endptr);
float value4 = std::strtof(mystr2.c_str(), &endptr);
std::cout << std::fixed << std::setprecision(0) << "Value overflow: " << value3 << std::endl;
std::cout << std::fixed << std::setprecision(0) <<"Value2 not overflow: " << value4 << std::endl;
std::cout << "Precision of float: " << std::numeric_limits<float>::digits10 << std::endl;
```
and get:
```
// for a double (it is working!)
Value overflow: 2147483648
Value2 not overflow: 2147483647
Precision of double: 15
// for a float (it is not working!)
Value overflow: 2147483648
Value2 not overflow: 2147483648
Precision of float: 6
```

So my updated implementation for the overflow check is some kind of:
```cpp
...
	// check if the string is an integer
    double converted_double = std::strtod(str.c_str(), &endptr);
	// check if I am in the range for int
    if (*endptr == '\0' && errno == 0 && \
		(converted_double >=  std::numeric_limits<int>::min() && \
		converted_double <=  std::numeric_limits<int>::max())) {
			...
	}
```

And this should make even the most pedantic evaluators here happy :)


# ex01 - reinterpret_cast

The subject:
>Implement a class Serializer, who will not be initializable by the user by any way,
with the following static methods:  
`uintptr_t serialize(Data* ptr);  `
It takes a pointer and converts it to the unsigned integer type uintptr_t.  
`Data* deserialize(uintptr_t raw);`
It takes an unsigned integer parameter and converts it to a pointer to Data.

Serialization is the process of converting an object's state into a format that can be stored or transmitted. This format is often a sequence of bytes, which can be easily written to a file, sent over a network, or stored in memory.  

The goal of serialization is to preserve the object's data and its structure so that it can be reconstructed later in the same or a different process. This is essential for tasks like saving data to disk, sending data over a network, or passing objects between different parts of a program.  

In this exercise we use `reinterpret_cast` to convert a pointer to an integer value and vice versa. Not a difficult exercise, but to understand why we need to reinterptret_cast... the static_cast would npot be allowed in this case.  
In C we would just cast. But in cpp everything has become more nuanced. To cast my data pointer:
```c
// in C
(uintptr_t)data;
```
and in cpp we need to use reinterpret_cast:
```cpp
reinterpret_cast<uintptr_t>(data);
```

# ex02 - dynamic_cast

> mplement a Base class that has a public virtual destructor only. Create three empty
classes A, B and C, that publicly inherit from Base. Implement the following functions:
Base * generate(void);
It randomly instanciates A, B or C and returns the instance as a Base pointer. Feel free
to use anything you like for the random choice implementation.
void identify(Base* p);
It prints the actual type of the object pointed to by p: "A", "B" or "C".
void identify(Base& p);
It prints the actual type of the object pointed to by p: "A", "B" or "C". Using a pointer
inside this function is forbidden.
Including the typeinfo header is forbidden.

This was farly straightforward. I have a base class `Base` and three derived classes `A`, `B` and `C`. 
`dynamic_cast` is especially made for polymorphic classes. It is used to convert a pointer or reference to a base class to a pointer or reference to a derived class. If the conversion is not possible, it returns a null pointer in the case of a pointer, or throws an exception in the case of a reference.   
