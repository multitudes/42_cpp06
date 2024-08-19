/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarValue.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:19:13 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 18:08:44 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SCALARVALUE_HPP
#define SCALARVALUE_HPP

#include <string>

/**
 * @brief ScalarValue struct
 * 
 * This utility struct will hold the 4 values I wanna print
 */
struct ScalarValue {

	unsigned char c;
	int i;
	float f;
	double d;
	bool intOverflow;
	bool charOverflow;

	//constructor
	ScalarValue(unsigned char c, int i, float f, double d, bool intOverflow, bool charOverflow);

	/* also use static functions visible in this file only */
	static bool convert_if_is_int_or_char(const std::string& str);
	static bool convert_if_double(const std::string& str);
	static bool convert_if_float(const std::string& str);
	static void printScalar(ScalarValue& value);
	
};

#endif