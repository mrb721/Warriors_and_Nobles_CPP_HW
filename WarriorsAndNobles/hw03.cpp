// hw03.cpp : Defines the entry point for the console application.
//Minhazur Bhuiyan (N18429515) CS1124
//Purpose of program is to include weapons in the "game" program started in hw02. Also, hw02 must be re-coded to work with classes instead of structs. 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;






class Weapon { //create weapon class with weapon name and strength
	string weapon_name;
	int weapon_strength;

public: //make public methods to obtain information without modifying it 
	Weapon(string name, int strength) { weapon_name = name; weapon_strength = strength; }
	//accessors
	string getWeapon() const { return weapon_name; }
	int getStrength() const { return weapon_strength; }

	//setter
	void setStrength(int newStrength)   {
		weapon_strength = newStrength;
	}
	
};




class Warrior { //create warrior class with warrior name and weapon class
	string warrior_name;
	Weapon weapon;
	 

public:
	Warrior(string name, string weapon_name, int strength) :weapon(weapon_name, strength) { warrior_name = name; } //constructor allows for input of warrior and weapon class information

	string getWarrior() const { return warrior_name; } //methods for obtaining information
	
	//accessors that take information from the weapon class
	void displayStatus()const;
	void print(ostream& disp = cout)const;
	string getWeapon() const { return weapon.getWeapon(); }
	int getStrength() const { return weapon.getStrength(); }
	//setter
	void setStrength(int newStrength) {
		weapon.setStrength(newStrength);
	}
	
};



 



void openFile(ifstream& inFile); //opens file
int findWarriorIdx(string warrior, vector<Warrior>& Warrior_Vec); //finds index of warrior within vector
void checkStatus(vector<Warrior>& warrior_vec); //checks status of warriors in vector using .displayStatus() method
void BattleOn(int first_idx, int second_idx, vector<Warrior>& Warrior_Vec); //battle sequence function


int main()
{
	ifstream inFile;
	openFile(inFile);

	//initialize variables to store what is read from file
	string info;
	string warrior_name;
	string first_warrior;
	string second_warrior;
	string weapon_name;
	int weapon_strength;
	vector<Warrior> Warrior_Vec; //initializes vector of warriors


	while (inFile >> info) { //loop to save warriors and information into the vector
		if (info == "Warrior") {
			inFile >> warrior_name >> weapon_name >> weapon_strength;
			Warrior MyWarrior(warrior_name, weapon_name, weapon_strength);
			Warrior_Vec.push_back(MyWarrior);

		}
	}
	
	inFile.clear(); //reread file from beginning, as "Status" includes a count of warriors, which isn't known until all the warriors have been pushed back to the vector
	inFile.seekg(0);
	
	
	
	while(inFile >> info){
		if (info == "Battle"){
			inFile >> first_warrior >> second_warrior;
			int idx_fw = findWarriorIdx(first_warrior, Warrior_Vec);
			int idx_sw = findWarriorIdx(second_warrior, Warrior_Vec);
			BattleOn(idx_fw, idx_sw, Warrior_Vec); //battle sequence
		
		}

		else if (info == "Status"){
			checkStatus(Warrior_Vec);
			
		
		
		}

	}


    
}

void openFile(ifstream& inFile) {
	string filename = "warriors (1).txt";
	inFile.open(filename);

	while (!inFile) {
		cout << "Bad file name!\n" << "Please enter correct file name: \n";
		cin >> filename;

		inFile.clear();
		inFile.open(filename);

	}
}

void Warrior::print(ostream& disp)const {
	char space = ' ';
	string comma = ", ";
		 
	cout << "Warrior: " << getWarrior() << comma;
	cout << "weapon: " << weapon.getWeapon() << comma;
	cout << weapon.getStrength() << endl;
}

void Warrior::displayStatus()const {
	print(cout);
}

int findWarriorIdx(string warrior, vector<Warrior>& Warrior_Vec) {
	for (size_t idx = 0; idx < Warrior_Vec.size(); ++idx) {
		if (Warrior_Vec[idx].getWarrior() == warrior)
			return idx;
	}
}



void BattleOn(int first_warrior_idx, int second_warrior_idx, vector<Warrior>& warrior_vec) {


	int first_warrior_strength = warrior_vec[first_warrior_idx].getStrength(); //finds strength
	int second_warrior_strength = warrior_vec[second_warrior_idx].getStrength();

	string first_warrior_name = warrior_vec[first_warrior_idx].getWarrior();
	string second_warrior_name = warrior_vec[second_warrior_idx].getWarrior();

	if (first_warrior_strength == 0 && second_warrior_strength == 0) { //they're both dead
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		cout << "Oh NO! They're both dead! Yuck!" << endl;
	}
	else if (first_warrior_strength == 0) { //if only one warrior is dead
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		cout << "He's dead, " << second_warrior_name << endl;
	}//no subtraction, as the stronger warrior wouldn't experience a change in strength and the dead warrior isn't allowed to have negative strength

	else if (second_warrior_strength == 0) {
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		cout << "He's dead, " << first_warrior_name << endl;

	}

	else if (first_warrior_strength > second_warrior_strength) { //if warrior 1 beats warrior 2
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		warrior_vec[first_warrior_idx].setStrength(first_warrior_strength - second_warrior_strength);
		warrior_vec[second_warrior_idx].setStrength(0);
		cout << first_warrior_name << " defeats " << second_warrior_name << endl;


	}

	else if (first_warrior_strength < second_warrior_strength) { //if warrior 2 beats warrior 1
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		warrior_vec[second_warrior_idx].setStrength(second_warrior_strength - first_warrior_strength);
		warrior_vec[first_warrior_idx].setStrength(0);

		cout << second_warrior_name << " defeats " << first_warrior_name << endl;


	}

	else { //if both warriors have equal strength
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		warrior_vec[first_warrior_idx].setStrength (0);
		warrior_vec[second_warrior_idx].setStrength(0);
		cout << "Mutual annhilation: " << first_warrior_name << " and " << second_warrior_name << " die at each other's hands" << endl;
	}
}

void checkStatus(vector<Warrior>& warrior_vec) {
	cout << "There are: " << warrior_vec.size() << " warriors" << endl;

	for (int warrior_idx = 0; warrior_idx < warrior_vec.size(); ++warrior_idx) {
		warrior_vec[warrior_idx].displayStatus();
	
	}
}