// Polynomial_hw08.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Polynomial_hw08.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;





class Polynomial;

struct intCo { //inCo struct acts as node
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






int Polynomial::returnDegree() const { return highestDeg; }

intCo* Polynomial::getLList() const { return PolyCo; }

bool Polynomial::isEmpty() const { return PolyCo == nullptr; }



void Polynomial::clear() {
	while (PolyCo != nullptr) {
		intCo* temp = PolyCo;
		PolyCo = PolyCo->next;
		delete temp;

	}
	highestDeg = -1; //-1 to represent an empty LList becuase highestDegree will eventually be used for comparison
}



Polynomial::~Polynomial() { clear(); }


ostream&  operator<<(ostream& os, const Polynomial& p) {
	intCo* temp = p.PolyCo;


	while (temp != nullptr) {
		if (temp->deg > 1 && temp->next != nullptr) { //to prevent "x^1" from being printed out
			os << temp->coefficient << "x^" << temp->deg << "  +  ";
		}
		
		else if (temp->deg == 0) { //same as for when deg=1, makes the output appear more like how it's normally represented
			if (temp->next == nullptr)
				os << temp->coefficient;
			else //prevents '+' from being printed at the end
				os << temp->coefficient << " + ";
		}

		else if (temp->deg == 1) {
			if (temp->next == nullptr)
				os << temp->coefficient << 'x';
			else
				os << temp->coefficient << 'x' << " + ";
		}
		else if (temp->next == nullptr)
			os << temp->coefficient << "x^" << temp->deg;
		
		
		temp = temp->next;
	}
	
	


	cout << endl;

	return os;
}



void Polynomial::vecToLList(vector<int> vec) {

	for (int data = vec.size()-1; data >= 0; --data) { //loops through vector backwards to properly create the LList
		PolyCo = new intCo(vec[data], PolyCo);
		PolyCo->deg = vec.size() - 1 - data; //each coefficient node will store its own exponent
	}

}


void display(const Polynomial& p) { //used for testing, no other purpose. Please ignore
	Polynomial temp(p);

	while (temp.PolyCo != nullptr) {
		cout << temp.PolyCo->coefficient;
		//cout << temp.PolyCo->coefficient << "x^" << temp.PolyCo->deg << "  +  ";
		temp.PolyCo = temp.PolyCo->next;
	}

	temp.clear();

}


Polynomial::Polynomial(const Polynomial& rhs) { 
	if (rhs.PolyCo == nullptr) { PolyCo = nullptr; } //if rhs is empty

	intCo* temp = rhs.PolyCo;
	highestDeg = rhs.highestDeg; //change lhs highestDegree
	vector<int> coVec; //basically the method used for initialization, create the vector, convert it, clear vector
	while (temp != nullptr) {
		coVec.push_back(temp->coefficient);
		temp = temp->next;
	}

	vecToLList(coVec);
	//coVec.clear()

}





Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this == &rhs) //self-assignment
		return *this;

	clear();

	if (rhs.isEmpty()) { PolyCo = nullptr; } //is rhs empty?


	intCo* temp = rhs.PolyCo; 
	highestDeg = rhs.highestDeg;
	vector<int> coVec;

	

	while (temp != nullptr) {
		coVec.push_back(temp->coefficient);
		temp = temp->next;
	}

	vecToLList(coVec);


	return *this;

}
 
int power(int base, int exp) { //for exponentiation
	if (exp == 0) { return 1; }
	else if (exp > 0)
		return base*power(base, exp - 1);
	else
		return 1 / power(base, -exp);
}

int Polynomial::evaluate(int var) {
	intCo* temp = PolyCo;
	int theSum = 0;
	if (isEmpty()) { return 0; }
	while (temp != nullptr) { //calculates value of polynomial with x value passed through
		theSum += temp->coefficient*power(var, temp->deg);
		temp = temp->next;
	}
	return theSum;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	intCo* temp = PolyCo;
	intCo* rhsTemp = rhs.PolyCo;
	
	
	vector<int>  coVec;



	int dif = highestDeg - rhs.highestDeg; //difference in powers, used to make sure terms of the same power are added

	if (dif > 0) { //if lhs is a higher power than rhs
		int skip = 0; //skip x terms in lhs
		while (skip < dif) {
			coVec.push_back(temp->coefficient); //append them directly to the vector (and subsequently the LList)
			skip+=1;
			temp = temp->next;
		}
		while (rhsTemp != nullptr) { //now, there should be an equal amount of terms left in both
			coVec.push_back(temp->coefficient + rhsTemp->coefficient); //push_back the sum of each pair of terms
			temp = temp->next; //incrementations
			rhsTemp = rhsTemp->next;
		}	
	}

	else if (dif < 0) { //if rhs has a higher power
		int skip = 0;
		while (skip < (-dif)) { //repeat previous if block, make dif positive
		
			coVec.push_back(rhsTemp->coefficient);
			skip+=1;
			rhsTemp = temp->next;
		}
		while (temp != nullptr) {
			coVec.push_back(temp->coefficient + rhsTemp->coefficient);
			temp = temp->next;
			rhsTemp = temp->next;
		}
	}

	else if (dif == 0){ //if both polynomials have an equal quantity of terms
		while (temp != nullptr && rhsTemp!=nullptr) {
			coVec.push_back(temp->coefficient + rhsTemp->coefficient);
			temp = temp->next;
			rhsTemp = temp->next;
		}
	}


	clear(); //clears this 

	vecToLList(coVec); //converts this

	coVec.clear(); //clears created vector
	return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	cout << "SUM" << endl;
	Polynomial sum(lhs);
	sum += rhs;
	
	return sum;

}

bool Polynomial::operator==(const Polynomial& rhs) const {
	if (this->highestDeg != rhs.highestDeg) { return false; } //can't be same if highest degrees differ
	Polynomial temp(*this);
	Polynomial rhsTemp(rhs);
	bool theSame = true; //boolean switch
	while (theSame == true && temp.PolyCo != nullptr) { //
		if (temp.PolyCo->coefficient != rhsTemp.PolyCo->coefficient) {
			theSame = false; //once false, the loop ends 
		}
		temp.PolyCo = temp.PolyCo->next;
		rhsTemp.PolyCo = rhsTemp.PolyCo->next;
	}
	temp.clear();
	rhsTemp.clear(); //clear it all
	return theSame; //return true or false
}

bool Polynomial::operator!=(const Polynomial& rhs) const {
	return !(*this == rhs); //just the opposite of ==
}