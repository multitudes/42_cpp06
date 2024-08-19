/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:02:20 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 18:30:20 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

/**
 * @brief private constructor
 */
Serializer::Serializer() {}

/**
 * @brief private destructor
 */
Serializer::~Serializer() {}

/**
 * @brief private copy constructor
 * @param copy
 */
Serializer::Serializer(const Serializer& copy) { (void)copy; }

/**
 * @brief private assignment operator
 * @param assign
 * @return Serializer&
 */
Serializer& Serializer::operator=(const Serializer& assign) { (void)assign; return *this; }

/**
 * @brief 
 * 
 * @param data 
 * @return uintptr_t 
 */
uintptr_t Serializer::serialize(Data* data) {
	return (uintptr_t)data;
}

/**
 * @brief 
 * 
 * @param raw 
 * @return Data* 
 */
Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}

