/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:13:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/23 12:17:45 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "iostream"
#include <limits>
#include <cstdlib>
#include <iomanip>

std::string intMinStr = "-2147483648";
std::string intMaxStr = "2147483647";
// std::string floatMaxStr = "3.40282e+38";
// std::string doubleMaxStr = "1.79769e+308";
std::string floatMaxStr = "340282000000000000000000000000000000000f";
std::string minfloatMaxStr = "-340282000000000000000000000000000000000f";
std::string doubleMaxStr = "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.";
std::string doubleMaxStrINT = "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368";
std::string doubleBIG = "17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351438246423432132688946418276846754670353751698604991057655128207624549009038932894407586850845513394230458323690322294816580855933212334827479782620414472316873817718091929988125040402618412485836811.";
std::string mindoubleBIG = "-17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351438246423432132688946418276846754670353751698604991057655128207624549009038932894407586850845513394230458323690322294816580855933212334827479782620414472316873817718091929988125040402618412485836811.";
std::string mindoubleBIGFLOAT = "-17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351438246423432132688946418276846754670353751698604991057655128207624549009038932894407586850845513394230458323690322294816580855933212334827479782620414472316873817718091929988125040402618412485836811f";
std::string pi = "3.14159265358";

int main(int argc, char **argv) {
	(void)argv;
	
	if (argc != 2) {
		std::cout << "Usage: ./convert [string]" << std::endl;
		return 1;
	}
	// ScalarConverter::convert(argv[1]);
	ScalarConverter::convert(intMinStr);
	ScalarConverter::convert(intMaxStr);
	ScalarConverter::convert(floatMaxStr);
	ScalarConverter::convert(minfloatMaxStr);
	ScalarConverter::convert(doubleMaxStr);
	ScalarConverter::convert(doubleMaxStrINT);
	ScalarConverter::convert(doubleBIG);
	ScalarConverter::convert(mindoubleBIG);
	ScalarConverter::convert(mindoubleBIGFLOAT);

	ScalarConverter::convert("nan");
	ScalarConverter::convert("-nan");
	ScalarConverter::convert("nanf");
	ScalarConverter::convert("42.0");
	ScalarConverter::convert("42f");
	ScalarConverter::convert("256");
	ScalarConverter::convert("256");
	ScalarConverter::convert("256f");
	ScalarConverter::convert("256.0");
	ScalarConverter::convert("10.0f");	
	ScalarConverter::convert("10.0");
	ScalarConverter::convert("10");	
	ScalarConverter::convert("f");	
	ScalarConverter::convert("ff");	
	ScalarConverter::convert("inf");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("inff");
	ScalarConverter::convert("-inff");

	// Infinity
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


    // const char* str1 = "std::numeric_limits<double>::infinity()"; // Too large
    const char* str2 = "-1e309"; // Too small
	const char* str3 = "1e-610"; // Too tiny
    double f1 = std::numeric_limits<double>::infinity();
    double f2 = std::strtod(str2, NULL);
	double f3 = std::strtod(str3, NULL);

    std::cout << "f1: " << f1 << std::endl;
    std::cout << "f2: " << f2 << std::endl;
	std::cout << "f3: " << f3 << std::endl;

	// check if my string is bigger than int max without using long
	std::cout << "Precision of float: " << std::numeric_limits<float>::digits10 << std::endl;
    std::cout << "Precision of double: " << std::numeric_limits<double>::digits10 << std::endl;
	
	std::string mystr("2147483648");
	std::string mystr2("2147483647");
	char *endptr;
	double value = std::strtod(mystr.c_str(), &endptr);
	double value2 = std::strtod(mystr2.c_str(), &endptr);
	
	std::cout << std::fixed << std::setprecision(0) << "Value overflow: " << value << std::endl;
	std::cout << std::fixed << std::setprecision(0) <<"Value2 not overflow: " << value2 << std::endl;

	float value3 = std::strtof(mystr.c_str(), &endptr);
	float value4 = std::strtof(mystr2.c_str(), &endptr);
	std::cout << std::fixed << std::setprecision(0) << "Value overflow: " << value3 << std::endl;
	std::cout << std::fixed << std::setprecision(0) <<"Value2 not overflow: " << value4 << std::endl;

	std::cout << "pi " << pi << std::endl;
	ScalarConverter::convert(pi);

	ScalarConverter::convert("42.42");
	ScalarConverter::convert("42.42f");
	// ScalarConverter::convert("hey");
	// ScalarConverter::convert(" ");
	// ScalarConverter::convert("98");
	// ScalarConverter::convert("-98.f");
	// ScalarConverter::convert("-98");	
	// ScalarConverter::convert("0");	
	// ScalarConverter::convert("-0");
	// ScalarConverter::convert("98.01f");	
	// ScalarConverter::convert("-98.01");	
	// ScalarConverter::convert("-98.01");	
	// ScalarConverter::convert("98.01");	

	// ScalarConverter::convert("-inff");	
	// ScalarConverter::convert("-inf");	
	// ScalarConverter::convert("inf");	
	// ScalarConverter::convert("inff");	
	// ScalarConverter::convert("2147483648");	
	// ScalarConverter::convert("2147483647");	
}

