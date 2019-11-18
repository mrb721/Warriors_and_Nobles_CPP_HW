#pragma once
#ifndef POLYNOMIAL_HW_08
#define POLYNOMIAL_HW08_H

#include <iostream>
#include <vector>
#include <string>






class Polynomial;

struct intCo { //intCo struct acts as node
	int coefficient;
	intCo* next;
	int deg;
	intCo(int newCo = 0, intCo* newnext = nullptr) : coefficient(newCo), next(newnext), deg(0) {}
};


class Polynomial { //Polynomial acts as LList class
	intCo* PolyCo;
	int highestDeg;
	int getDegree(std::vector<int> vec) const; //can be used for polynomiials with leading coefficient of 0
	void vecToLList(std::vector<int> vec); //converts vector of coefficients to a singly linked list

public:
	Polynomial(std::vector<int> vec = {}) :highestDeg(vec.size() - 1), PolyCo(nullptr) { vecToLList(vec); } //for polynomials with leadind zeroes, initialize highestDeg to getDegree(vec);
	bool isEmpty() const; //checks if there are no nodes in the LList
	void clear(); //clears LList, sets highest degree to 0
	virtual ~Polynomial();//destructor, makes use of clear()
	Polynomial(const Polynomial& rhs); //copy constructor
	Polynomial& operator=(const Polynomial& rhs); //overloaded assignment operator
	intCo* getLList() const; //gets the node
	int returnDegree() const; //returns highestDegree
	int evaluate(int var); //x value passed in to solve the polynomial
	Polynomial& operator+=(const Polynomial& rhs); //overloaded +=
	bool operator==(const Polynomial& rhs) const;
	bool operator!=(const Polynomial & rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
	friend void display(const Polynomial& p); //does the job of the overloaded output operator, except in method form. Not used in this assignment, only used for testing before overloading "<<"

};





#endif // !POLYNOMIAL_HW_08
