/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:07:57 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/23 11:11:32 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "ScalarValue.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib> 
#include <climits>
#include <limits>
#include <cerrno>
#include <cfloat>
#include <math.h> 


/* I will use the ScalarConverter class as static class only */

/**
 * private constructor
 */
ScalarConverter::ScalarConverter() {

}

/**
 * private destructor
 */
ScalarConverter::~ScalarConverter() {

}

/**
 * private copy constructor
 */
ScalarConverter::ScalarConverter(const ScalarConverter& copy) {
	(void)copy;
}

/**
 * private assignment operator
 */
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& assign) {
	(void)assign;
	return *this;
}

/**
 * @brief 
 * 
 * I will check the assumed type of the input and based on this I 
 * will cast the string to float double or int...or char
 * but char will be just the ascii value of a character so
 * unless it is only one digit long I will not be able to 
 * cast to char...
 */
void ScalarConverter::convert(const std::string& str) {
	std::cout << "\n========= converting >" << str << "< ==========" << std::endl;
	if (ScalarValue::convert_if_is_int_or_char(str) || \
		ScalarValue::convert_if_double(str) || \
		ScalarValue::convert_if_float(str))
		return ;
	std::cout << "Error: Not a valid type." << std::endl;
}
