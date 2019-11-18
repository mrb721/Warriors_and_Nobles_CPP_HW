// hw06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//prototype classes
class Protector;
class Warrior;
class Wizard;
class Archer;
class Swordsmen;

class Noble{  //noble class includes name, strength, and whether or not the noble is alive
	string name;
	int strength;
	bool living;
 

public:
	Noble(string newName, int newStrength) :name(newName), strength(newStrength), living(true) {}
	void battle(Noble enemyNoble);  //battle method made similar to one in hw05
	void setStrength(int newStrength) { strength = newStrength; }
	bool isAlive() const { return living; }
	void setLiving(bool doa) {living = doa; }
	virtual int getStrength() const { return strength; }
	string getName()const { return name; }
	void battleDamage(string result, int theStrength); //battleDamage() method similar to hw05 version, except is intentionally overridden in Lord class
};

void Noble::battleDamage(string result, int theStrength) {
	if (result == "win") {
		setStrength(getStrength() - theStrength);
	}
	else if (result == "lose") {
		setStrength(0);
		setLiving(false);

	}
}

void Noble::battle(Noble enemyNoble) {
	Noble* enemyPtr = &enemyNoble;
	int nobleStrength = this->getStrength();
	int enemyStrength = enemyPtr->getStrength();

	if (!this->isAlive() && !enemyPtr->isAlive()) {
		cout << "Oh NO! They're both dead! Yuck!" << endl;
	}
	else if (!this->isAlive()) {
		cout << "He's dead, " << this->getName() << endl;	
	}
	else if (!enemyPtr->isAlive()) {
		cout << "He's dead, " << enemyPtr->getName() << endl;
	}
	else if (nobleStrength > enemyStrength){
		battleDamage("win", enemyStrength / nobleStrength);
		enemyNoble.battleDamage("lose", enemyStrength / nobleStrength);

	}

	else if (enemyStrength > nobleStrength){
		enemyNoble.battleDamage("win", nobleStrength / enemyStrength);
		battleDamage("lose", nobleStrength / enemyStrength);
	}

	else {
		cout << "Mutual Annihilation: " << name << "and " << enemyNoble.getName() << "die at each other's hands" << endl;
		battleDamage("lose", 1 / 1);
		enemyNoble.battleDamage("lose", 1 / 1);
	}
}

class PersonWithStrengthToFight:public Noble{

public:
	PersonWithStrengthToFight(string newName, int newStrength):Noble(newName, newStrength){}
	//int getStrength()const { return Noble::getStrength(); }
};

class Lord:public Noble{
	vector<Protector*> army; //a Lord can command and army; therefore a hire method is needed. The fire method is not specified at the moment.

public:
	Lord(string newName):Noble(newName, getStrength()){}
	void hires(Protector newProtector); //only hires unhired protectors
	int getStrength() const;
	void battleDamage(string result, int strengthRatio); //overrides Noble class method to carry damage over to the protectors in the army vector
	

};

void Lord::battleDamage(string result, int strengthRatio) {
	if (result == "win") {
		for (Protector* fighter : army) {
			fighter->setStrength(fighter->getStrength() - (strengthRatio*fighter->getStrength())); //fighters lose strength just as in hw05

		}
	}
	else if (result == "lose") {
		for (Protector* fighter:army) {
			fighter->setStrength(0);
		}
	}
}


void  Lord::hires(Protector newProtector) {
	Protector* proPtr = &newProtector;
	if (proPtr->hasLeader() == false) {
		army.push_back(proPtr);
	}
}


int Lord::getStrength() const {
	int totalStrength = 0;
	if (army.size() > 0){
		for (Protector* fighter : army) {
			totalStrength = totalStrength + fighter->getStrength();
		}
		return totalStrength;
	}
	else { return totalStrength; }
}


class Protector{
	string name;
	int strength;
	Noble* leader;
public:
	Protector(string newName, int newStrength):name(newName),strength(newStrength){}
	int getStrength() const { return strength; }
	bool hasLeader() const { return (leader != nullptr); }
	void inBattle(Noble enemy);
	Noble* getLeader() const { return leader; }
	string getName() const { return name; }
	void setStrength(int newStrength) { strength = newStrength; }

};


void Protector::inBattle(Noble enemy) { if (strength == 0) cout << "..." << endl; } //"..." is a test, as there seem to be no generic protectors. This will be overriden within each subsequent class in the inheritance chain




class Wizard:public Protector{

public:
	Wizard(string newName, int newStrength):Protector(newName,newStrength){}
	void inBattle(Noble enemy); 
};


void Wizard::inBattle(Noble enemy) {
	if (getStrength() != 0) {
		cout << "POOF" << endl;
	}
}

class Warrior:public Protector{


public:
	Warrior(string newName, int newStrength):Protector(newName,newStrength){}
	void inBattle(Noble enemy);

};

void Warrior::inBattle(Noble enemy) {
	if (getStrength() != 0) {
		cout << getName() << " says: Take that in the name of my lord, " << getLeader()->getName() << '"'; 
	}
}


class Archer:public Warrior{

public:
	Archer(string newName, int newStrength):Warrior(newName,newStrength){}
	bool hasLeader() const {Protector::hasLeader();}
	void inBattle(Noble enemy);
};

void Archer::inBattle(Noble enemy) {
	if (getStrength() != 0) {
		cout << "TWANG!";
		Warrior::inBattle(enemy);
	}
}

class Swordsman:public Warrior{

public:
	Swordsman(string newName, int newStrength) :Warrior(newName, newStrength) {}
	bool hasLeader() const { Protector::hasLeader(); }
	void inBattle(Noble enemy);


};

void Swordsman::inBattle(Noble enemy) {
	if (getStrength() != 0) {
		cout << "CLANG!";
		Warrior::inBattle(enemy);
	}
}


int main()
{
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);
    
}

