// hw05.cpp : Defines the entry point for the console application.
//Purpose of program is to allocate information to the heap and modify the program to recognize and handle errors

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class Warrior { //create warrior class
	string name;
	int strength;
	//bool employed; unused procedure for identifying fired/unemployed warriors 

public:
	Warrior(string newName, int newStrength = 0) : name(newName), strength(newStrength) {} //employed(false) {}
	string getName() const { return name; } //accessors
	int getStrength() const { return strength; }
	void setStrength(int newStrength) { strength = newStrength; } //sets new strength for individual warrior
	//void setEmployment(bool truthValue) { employed = truthValue; }
	//bool getEmployment() const { return employed; }
	
};

class Noble {
	string name;
	vector<Warrior*> warrior_vec; //vector of warrior pointers

public:
	Noble(string newName) :name(newName) {}
	string getName() const { return name; }
	void display() const; //displays noble information, such as name and army statistics
	void hire(Warrior* warriorPtr); //hires a new warrior for the army
	void fire(Warrior* firedWarrior); //fires a warrior from the army
	bool hasArmy() { return (warrior_vec.size() != 0); } //checks if the noble has any fighters
	int armyStrength(); //returns total army strength
	void battleDamage(string result, int strengthRatio); //adjusts each warrior's strength based on the result and ratio of losing strength to winning strength
	void battle(Noble* enemy); //battle method
};

void Noble::display() const {
	cout << name << " has an army of " << warrior_vec.size() << endl;
	for (Warrior* x : warrior_vec) {
		cout << '\t' << x->getName() << ": " << x->getStrength() << endl;
	}
}
void Noble::hire(Warrior* warriorPtr) {
	//Warrior* warriorPtr = &newWarrior; //stores location of warrior into warrior pointer
	warrior_vec.push_back(warriorPtr); //pushes back warrior pointer to the vector of warrior pointers
	//warriorPtr->setEmployment(true);

}
void Noble::fire(Warrior* firedWarrior) {
	string firedWarriorName = firedWarrior->getName();
	if (hasArmy() == true) {
		for (int warrIdx = 0; warrIdx < warrior_vec.size(); ++warrIdx) { //the index of the fired warrior is found within the vector of warrior pointers
			if (warrior_vec[warrIdx]->getName() == firedWarriorName) {
				if (warrior_vec.size() > 1) {
					cout << "You don't work for me anymore " << warrior_vec[warrIdx]->getName() << "-- " << name << endl; //output seen in example main()
					//warrior_vec[warrIdx]->setEmployment(false);
					warrior_vec[warrIdx] = nullptr; //sets warrior pointer to null
					warrior_vec[warrIdx] = warrior_vec[warrior_vec.size() - 1]; //replaces fired warrior with a copy of the last warrior in the vector, as order doesn't matter in ectors
					warrior_vec.pop_back(); //gets rid of the final element to avoid duplicates
					break;
				}
				else {
					cout << "You don't work for me anymore " << warrior_vec[warrIdx]->getName() << "-- " << name << endl; //if the noble's warrior pointer vector only has 1 warrior pointer, the warrior is simply removed
					//warrior_vec[warrIdx]->setEmployment(false);
					warrior_vec[warrIdx] = nullptr; //set the pointer to null, first
					warrior_vec.pop_back();

				}
			}
		}
	}
}

int Noble::armyStrength() {
	int totalStrength = 0;
	for (Warrior* x : warrior_vec) {
		totalStrength = totalStrength + x->getStrength(); //adds the strengths of all warriors in a noble's army
	}
	return totalStrength;
}

void Noble::battleDamage(string result, int strengthRatio) {
	if (result == "win") {
		for (Warrior* hiredWarrior : warrior_vec) {
			int newStrength = (hiredWarrior->getStrength() - (strengthRatio*hiredWarrior->getStrength()));
			//if (newStrength > 0) { hiredWarrior->setStrength(newStrength); } note necessary
			//else { hiredWarrior->setStrength(0); }
		}
	}
	else if (result == "lose") {
		for (Warrior* hiredWarrior : warrior_vec) {
			hiredWarrior->setStrength(0);
		}
	}
}
void Noble::battle(Noble* enemy) {
	int nobleOneStrength = armyStrength();
	int nobleTwoStrength = enemy->armyStrength();

	cout << name << " battles " << enemy->getName() << endl;

	if (nobleOneStrength == 0 && nobleTwoStrength == 0) {
		cout << "Oh NO! They're both dead! Yuck!" << endl;

	}
	else if (nobleOneStrength == 0) {
		cout << "He's dead, " << enemy->getName() << endl;
	}
	else if (nobleTwoStrength == 0) {
		cout << "He's dead, " << getName() << endl;
	}
	else if (nobleOneStrength > nobleTwoStrength) {
		battleDamage("win", nobleTwoStrength / nobleOneStrength);
		enemy->battleDamage("lose", nobleTwoStrength / nobleOneStrength);
		cout << name << " defeats " << enemy->getName() << endl;

	}
	else if (nobleTwoStrength > nobleOneStrength) {
		enemy->battleDamage("win", nobleOneStrength / nobleTwoStrength);
		battleDamage("lose", nobleOneStrength / nobleTwoStrength);
		cout << enemy->getName() << " defeats " << name << endl;
	}
	else {
		cout << "Mutual Annihilation: " << name << " and " << enemy->getName() << " die at each other's hands" << endl;
		battleDamage("lose", 1 / 1);
		enemy->battleDamage("lose", 1 / 1);
	}
}


void openFile(ifstream& inFile) {
	string filename = "nobleWarriors.txt";  //string filename;
	inFile.open(filename);

	while (!inFile) {
		cout << "Wrong file name!" << endl << "Please enter the correct one: ";
		cin >> filename;
		inFile.clear();
		inFile.open(filename);
	}
}

Noble* nobleSearch(string nobleName, vector<Noble*>& nobleVec){ //returns Noble pointer from vector  
	for (Noble* noble : nobleVec) {
		if (nobleName == noble->getName()) { return noble; }
	}
}

Warrior* warriorSearch(string warriorName, vector<Warrior*>& warriorVec) { //returns Warrior pointer from vector
	for (Warrior* warrior : warriorVec) {
		if (warriorName == warrior->getName()) { return warrior; }
	}
}

int main()
{
	ifstream inFile;
	openFile(inFile);
	
	string command, first_name, second_name; //temporarily stores names and warrior strengths when reading from file
	int strength;
	vector<Noble*> nobleVec; //initialize vector of Noble pointers
	vector<Warrior*> warriorVec; //initialize vector of warrior pointers
	vector<Warrior*> firedWarriors; //initialize vector for fired warrior pointers

	while (inFile >> command) {
		if (command == "Noble") {
			inFile >> first_name;
			int nobleCount = 0;
			for (Noble* noble : nobleVec) { //checks to see if Noble with the same name already exists in the vector currently
				if (first_name == noble->getName()) { ++nobleCount; }
			}
			if (nobleCount == 0) { //if not taken, proceed
				Noble* noblePtr = new Noble(first_name);
				nobleVec.push_back(noblePtr);
			}
			else { cout << "Noble name taken<<" << endl; } //if taken, this message appears
		}
		else if (command == "Warrior") {
			inFile >> first_name >> strength;
			int warriorCount = 0;
			for (Warrior* warrior : warriorVec) {
				if (first_name == warrior->getName()) { ++warriorCount; } //same as with Noble error checking, proceeds if warrior with proposed new name doesn't already exist
			}
			if (warriorCount == 0) {
				Warrior* warriorPtr = new Warrior(first_name, strength);
				warriorVec.push_back(warriorPtr);
			}
			else { cout << "Warrior name taken" << endl; }
		}
		else if (command == "Hire") {
			inFile >> first_name >> second_name;
			nobleSearch(first_name, nobleVec)->hire(warriorSearch(second_name, warriorVec));
			for (size_t idx = 0; idx < firedWarriors.size();++idx) {
				if (second_name == firedWarriors[idx]->getName()) {
					firedWarriors[idx] = firedWarriors[firedWarriors.size() - 1];
					firedWarriors.pop_back();
					break;
				}
			}
		}
		else if (command == "Fire") {
			inFile >> first_name >> second_name;
			nobleSearch(first_name, nobleVec)->fire(warriorSearch(second_name, warriorVec));
			firedWarriors.push_back(warriorSearch(second_name, warriorVec)); //pushes it back to the firedWarriors vector
			for (Warrior* warrior : warriorVec) {
				if (second_name == warrior->getName()) { warrior = nullptr; } 
			}
		}
		else if (command == "Status") {
			cout << endl << "Status\n" << endl << "====" << endl;
			if (nobleVec.size() > 0) {
				cout << "Nobles:\n";
				for (Noble* noble : nobleVec) { noble->display(); }


				//cout << warrior->getName() << endl;
			}
			else { cout << "Nobles: " << endl << "NONE" << endl; }

			//cout << "Unemployed Warriors: " << endl;

			/*int unemployedCount = 0;
			for (Warrior* warrior : warriorVec) {
				if (warrior->getEmployment() == true) {
					cout << warrior->getEmployment() << endl;
					unemployedCount += 1;
					cout << warrior->getName() << ": " << warrior->getStrength() << endl;
				}
				if (unemployedCount == 0){ cout << "Unemployed Warriors\n" << "NONE\n" << endl; }
			}*/
			if (firedWarriors.size() > 0) {
				cout << "Unemployed Warriors: " << endl;
				for (Warrior* warrior : firedWarriors) {
					cout << warrior->getName() << ": " << warrior->getStrength() << endl; 
				}
			}
			else { cout << "Unemployed Warriors\n" << "NONE\n" << endl; }

		}
		else if (command == "Battle") {
			inFile >> first_name >> second_name;
			int firstNobleCount = 0;
			int secondNobleCount = 0;
			
			for (Noble* noble : nobleVec) {
				if (first_name == noble->getName()) { ++firstNobleCount; }
			}
			for (Noble* noble : nobleVec) {
				if (second_name == noble->getName()) { ++secondNobleCount; }
			}
			if (firstNobleCount == 1 && secondNobleCount == 1) {
				nobleSearch(first_name, nobleVec)->battle(nobleSearch(second_name, nobleVec));
			}
			else {cout << "One or both nobles do not exist!" << endl;} //at this point, there is either one instance of the noble, or none at all
		}
		else if (command == "Clear") {
			for (Noble* noble : nobleVec) { delete noble; }
			for (Warrior* warrior : warriorVec) { delete warrior; }
			//for (Warrior* warrior : firedWarriors) { delete warrior; } //crashes program
			nobleVec.clear();
			warriorVec.clear();
			firedWarriors.clear();
			
		}
	}
		 
		
	
	
	


	 
}

