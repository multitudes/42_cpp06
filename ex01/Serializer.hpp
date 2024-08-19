/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:01:59 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 18:26:33 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <iostream>

class Serializer {

	public:
		static uintptr_t serialize(Data* data);
		static Data* deserialize(uintptr_t raw);

	private:
		Serializer();
		~Serializer();
		Serializer(const Serializer& copy);
		Serializer& operator=(const Serializer& assign);
};

#endif