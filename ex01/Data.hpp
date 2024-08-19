/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:02:40 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 18:25:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdint.h> 

struct Data {
	std::string s1;
	int n;
	double d;
	float f;

	Data();
};

#endif