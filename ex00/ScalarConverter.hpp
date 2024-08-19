/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:04:46 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 17:22:17 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>


/**
 * 
 * 
 * I will use the class without instantiating it
 */
class ScalarConverter {

	public:
		static void convert(const std::string& str);

	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter& operator=(const ScalarConverter& assign);
};

#endif