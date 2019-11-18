// hw04.cpp : Defines the entry point for the console application.
//In this assignment, the Noble class is added to the game of warriors. Now, nobles may command a group of warriors to do battle and damage is calculated a bit differently than in the previous iterations of the game.

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class Warrior { //create warrior class
	string name;
	int strength;

public:
	Warrior(string newName, int newStrength = 0) : name(newName), strength(newStrength) {} 
	string getName() const { return name; } //accessors
	int getStrength() const { return strength; }
	void setStrength(int newStrength) { strength = newStrength; } //sets new strength for individual warrior
};

class Noble {
	string name; 
	vector<Warrior*> warrior_vec; //vector of warrior pointers

public:
	Noble(string newName) :name(newName) {}
	string getName() const { return name; }
	void display() const; //displays noble information, such as name and army statistics
	void hire(Warrior& newWarrior); //hires a new warrior for the army
	void fire(Warrior& firedWarrior); //fires a warrior from the army
	bool hasArmy() { return (warrior_vec.size() != 0); } //checks if the noble has any fighters
	int armyStrength(); //returns total army strength
	void battleDamage(string result, int strengthRatio); //adjusts each warrior's strength based on the result and ratio of losing strength to winning strength
	void battle(Noble enemy); //battle method
};

void Noble::display() const {
	cout << name << " has an army of " << warrior_vec.size() << endl;
	for (Warrior* x : warrior_vec) {
		cout <<'\t' << x->getName() << ": " << x->getStrength() << endl;
	}
}
void Noble::hire(Warrior& newWarrior) {
	Warrior* warriorPtr = &newWarrior; //stores location of warrior into warrior pointer
	warrior_vec.push_back(warriorPtr); //pushes back warrior pointer to the vector of warrior pointers
}
void Noble::fire(Warrior& firedWarrior) {
	string firedWarriorName = firedWarrior.getName();
	if (hasArmy() == true) { 
		for (int warrIdx = 0; warrIdx < warrior_vec.size(); ++warrIdx) { //the index of the fired warrior is found within the vector of warrior pointers
			if (warrior_vec[warrIdx]->getName() == firedWarriorName) {
				if (warrior_vec.size() > 1) {
					cout << warrior_vec[warrIdx]->getName() << ", you're fired! -- " << name << endl; //output seen in example main()
					warrior_vec[warrIdx] = nullptr; //sets warrior pointer to null
					warrior_vec[warrIdx] = warrior_vec[warrior_vec.size() - 1]; //replaces fired warrior with a copy of the last warrior in the vector, as order doesn't matter in ectors
					warrior_vec.pop_back(); //gets rid of the final element to avoid duplicates
			}
				else { 
					cout << warrior_vec[warrIdx]->getName() << ", you're fired! -- " << name << endl; //if the noble's warrior pointer vector only has 1 warrior pointer, the warrior is simply removed
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
void Noble::battle(Noble enemy) {
	int nobleOneStrength = armyStrength();
	int nobleTwoStrength = enemy.armyStrength();

	cout << name << " battles " << enemy.getName() << endl;

	if (nobleOneStrength == 0 && nobleTwoStrength == 0) {
		cout << "Oh NO! They're both dead! Yuck!" << endl;
		
	}
	else if (nobleOneStrength == 0) {
		cout << "He's dead, " << enemy.getName() << endl;
	}
	else if (nobleTwoStrength == 0) {
		cout << "He's dead, " << getName() << endl;
	}
	else if (nobleOneStrength > nobleTwoStrength) {
		battleDamage("win", nobleTwoStrength / nobleOneStrength);
		enemy.battleDamage("lose", nobleTwoStrength / nobleOneStrength);
		cout << name << " defeats " << enemy.getName() << endl;

	}
	else if (nobleTwoStrength > nobleOneStrength) {
		enemy.battleDamage("win", nobleOneStrength / nobleTwoStrength);
		battleDamage("lose", nobleOneStrength / nobleTwoStrength);
		cout << enemy.getName() << " defeats " << name << endl;
	}
	else {
		cout << "Mutual Annihilation: " << name << " and " << enemy.getName() << " die at each other's hands" << endl;
		battleDamage("lose", 1 / 1);
		enemy.battleDamage("lose", 1 / 1);
	}
}
int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}