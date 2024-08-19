/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:13:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/19 22:47:46 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>

/**
 * @brief Base class
 */
class Base {
	public:
		virtual ~Base() {}
};

/**
 * @brief A B C empty classes
 */
class A : public Base {};
class B : public Base {};
class C : public Base {};

/** 
 * @brief E empty class to check for error
 */
class E: public Base {};

/**
 * @brief Generate a random class A B or C
 * 
 * @return Base* 
 */
Base* generate(void) {
	srand(static_cast<unsigned int>(time(NULL)));
	int random = rand() % 3;
	if (random == 0) {
		std::cout << "A generated" << std::endl;
		return new A;
	}
	else if (random == 1) {
		std::cout << "B generated" << std::endl;
		return new B;
	}
	else {
		std::cout << "C generated" << std::endl;
		return new C;
	}
}

/**
 * @brief Identify the class with the pointer
 * 
 * @param p pointer to the class
 */
void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "A" << std::endl;
	}
	else if (dynamic_cast<B*>(p)) {
		std::cout << "B" << std::endl;
	}
	else if (dynamic_cast<C*>(p)) {
		std::cout << "C" << std::endl;
	}
}

/**
 * @brief Identify the class with the reference
 * 
 * @param p reference to the class
 */
void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}

    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}

    try {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}

    std::cout << "Unknown" << std::endl;
}

/**
 * @brief Main function
 * 
 * We test that the identify function works with both pointers and references
 */
int main() {
	
	Base* base = generate();
	E* e = new E;
	identify(base);
	identify(*base);
	delete base;
	identify(*e);
	delete e;
	return 0;
}