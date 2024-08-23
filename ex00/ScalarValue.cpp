/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarValue.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:22:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/23 12:22:36 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarValue.hpp"
#include <iostream>
#include <limits>
#include <math.h> 
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <string>

/**
 * @brief constructor
 * 
 * I use this struct to keep track of my conversions and overflows
 */
ScalarValue::ScalarValue(std::string origInput, unsigned char c, int i, float f, double d, bool intOverflow, bool charOverflow): origInput(origInput), c(c), i(i), f(f), d(d), intOverflow(intOverflow), charOverflow(charOverflow)  {};

/**
 * @brief count the number of decimal digits
 */
int countDigitsAfterDot(std::string str) {
	int precision = 1;
	std::size_t dotPos = str.find('.');
	if (dotPos == std::string::npos) {
		return 0;
	}
	precision = static_cast<int>(str.size() - dotPos - 1);
	if (str.at(str.size() - 1) == 'f') {
		precision -= 1;
	}
	return precision;
}

/**
 * @brief print the scalar value
 * 
 * We will print the scalar value taking care of the overflows for int and char
 * which are not handled by their types. Float and doubles will print inf and nan 
 * automatically
 */
void ScalarValue::printScalar(ScalarValue& value) {
	// int precision = 1;
	if (!value.charOverflow) {
		if (isprint(value.c)) {
			std::cout << "Char value: " << value.c << std::endl;
		} else {
			std::cout << "Char value: Non displayable" << std::endl;
		}
	} else {
		std::cout << "Char value: impossible" << std::endl;
	}
	if (value.intOverflow) {
		std::cout << "Int value: impossible" << std::endl;
	} else {
		std::cout << "Int value: " << value.i << std::endl;
	}
	// Floats and doubles will automatically print inf in case of overflow
	// and nan in case of nan
	// Set precision to at least one digit after the decimal point
    std::cout << std::setprecision(1) << std::fixed;

    // Check if the value has more than one decimal digit
    if (std::cout.precision() < countDigitsAfterDot(value.origInput)) {
		// Increase precision to match the number of decimal digits
        std::cout << std::setprecision(countDigitsAfterDot(value.origInput));
    }
	std::cout << "Float value: " << value.f << "f" << std::endl;
	std::cout << "Double value: " << value.d << std::endl;
}


bool ScalarValue::convert_if_is_int_or_char(const std::string &str)
{
	errno = 0;
	char* endptr;
	ScalarValue value(str, 0, 0, 0, 0, false, false);
	// check if the string has a dot in it
	if (str.find('.') != std::string::npos) {
		return false;
	}
	// nan and inf are properties of float and double so we will not consider them
	if (isinf(std::strtof(str.c_str(), &endptr)) || isnan(std::strtof(str.c_str(), &endptr))) {
		return false;
	}
	// check if the string is an integer
    double converted_double = std::strtod(str.c_str(), &endptr);
	// check if I am in the range for int
    if (*endptr == '\0' && errno == 0 && \
		(converted_double >=  std::numeric_limits<int>::min() && \
		converted_double <=  std::numeric_limits<int>::max())) {
		value.i = atoi(str.c_str());
		// check if by chance could be a char
		if (value.i >= 0 && value.i <= 255) {
			std::cout << "========= I assume the string is a char =========" << std::endl;
			value.c = static_cast<unsigned char>(atoi(str.c_str()));
			// this case is promotion so i dont need casting
			value = ScalarValue(str, value.c, value.c, value.c, value.c, false, false);
			printScalar(value);
			return true;
		}
		// char overflows but int is fine
		std::cout << "========= I assume the string is an int =========" << std::endl;
		value = ScalarValue(str, ' ', value.i, static_cast<float>(value.i), static_cast<double>(value.i), false, true);
		printScalar(value);
		return true;
	}
	return false;
}

/**
 * @brief check if the string is a double
 * 
 * We will check if the string can be a double and then cast it to the other types
 */
bool ScalarValue::convert_if_double(const std::string& str) {
    errno = 0;
	char* endptr;
	ScalarValue value(str, 0, 0, 0, 0, false, false);

	std::strtod(str.c_str(), &endptr);

    if (*endptr == '\0') {
		std::cout << "========= I assume the string is a double =========" << std::endl;
		// my double is in the range of double but my int?
		value.d = std::strtod(str.c_str(), &endptr);
		if (value.d <  std::numeric_limits<int>::min() || value.d > std::numeric_limits<int>::max() || isnan(value.d) || isinf(value.d)) {
			// int overflows
			value = ScalarValue(str, ' ', 0, static_cast<float>(value.d), value.d, true, true );
		} else {
			// but maybe char is possible?
			if (static_cast<int>(value.d) >= 0 && static_cast<int>(value.d) <= 255) {
				value.c = static_cast<unsigned char>(static_cast<int>(value.d));
				value = ScalarValue( str, value.c, static_cast<int>(value.d), static_cast<float>(value.d), value.d, false, false);
			} else {
			value = ScalarValue(str, ' ', static_cast<int>(value.d), static_cast<float>(value.d), value.d, false, true);
			}
		}
		printScalar(value);
		return true;
	}
	return false;
}


/**
 * @brief check if the string is a float
 * 
 * We will check if the string is ending with f and then if it is a float and 
 * since float is a subset of double we will check if it is a double first after removing the f
 * if so even if it overflows it is a valid float and will print the float value
 * and cast the float value to the other types
 */
bool ScalarValue::convert_if_float(const std::string& str) {
	errno = 0;
  	char* endptr;
	ScalarValue value(str, 0, 0, 0, 0, false, false);

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
	std::strtof(modified_str.c_str(), &endptr);

	// is the string a valid float then would not have any other chars in it
    if (*endptr != '\0') {
        return false;
    }

	std::cout << "========= I assume the string is a float =========" << std::endl;
	// my float is in the range of float but my int?
	value.f = std::strtof(str.c_str(), &endptr);
	// check for int casting overflows
	if (static_cast<long>(value.f) > std::numeric_limits<int>::max() || \
		static_cast<long>(value.f) < std::numeric_limits<int>::min()  || 
		isnan(value.f) || isinf(value.f)) {
		value = ScalarValue(str, 0, 0, value.f, value.f, true, true);
	} else {
		// but maybe char is possible?
		if (static_cast<int>(value.f) >= 0 && static_cast<int>(value.f) <= 255) {
			value.c = static_cast<unsigned char>(static_cast<int>(value.f));
			value = ScalarValue(str, value.c, static_cast<int>(value.f), value.f, value.f, false, false);
		} else {
			value = ScalarValue(str, 0, static_cast<int>(value.f), value.f, value.f, false, true);
		}
	}
	printScalar(value);
	return true;
}

