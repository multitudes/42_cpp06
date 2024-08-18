# 42_cpp06

## Exploring the limits header
The <limits> header was introduced in C++98 and provides information about the limits of various numerical data types. It defines constants that represent the minimum and maximum values for different types, such as int, float, double, etc.

Key constants and their meanings:

- numeric_limits<T>::min(): Returns the minimum value representable by the type T.
- numeric_limits<T>::max(): Returns the maximum value representable by the type T.
- numeric_limits<T>::lowest(): Returns the most negative value representable by the type T.
- numeric_limits<T>::digits(): Returns the number of base-2 digits in the significand of the type T.
- numeric_limits<T>::digits10(): Returns the number of base-10 digits in the significand of the type T.
- numeric_limits<T>::is_integer(): Returns true if the type T is an integer type.
- numeric_limits<T>::is_signed(): Returns true if the type T is signed.
- numeric_limits<T>::is_specialized(): Returns true if the numeric_limits template is specialized for the type T.

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
But if I can helas overflow an integer.


## casting values to different types
We are going to practice casts in C++. First of all we need to know what a re the limits of the types we are going to use. We can use the `limits` library to get the limits of the types.

Example:
```cpp
#include <limits>
#include <iostream>



## ex00