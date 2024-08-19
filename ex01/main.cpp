/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:13:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 18:26:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <stdint.h> 

int main() {
	Data data;
	
	uintptr_t p = Serializer::serialize(&data);

	std::cout << "Data pointer: " << &data << std::endl;
	std::cout << "Serialized pointer: " << p << std::endl;

	Data* d = Serializer::deserialize(p);

	std::cout << "Deserialized pointer: " << d << std::endl;
	std::cout << "Deserialized s1: " << d->s1 << std::endl;
	std::cout << "Deserialized n: " << d->n << std::endl;
	std::cout << "Deserialized d: " << d->d << std::endl;
	std::cout << "Deserialized f: " << d->f << std::endl;
	



}
