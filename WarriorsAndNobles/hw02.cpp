// hw02.cpp : Defines the entry point for the console application.
// Minhazur Bhuiyan  N18429515 CS1124
// The purpose of this program is to read game data from a file to produce output in accordance with the given commands ("Battle", "Status") 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;




struct warrior { //creates warrior struct to store name and strength
	string name;
	double strength;

};

 



void openFile(ifstream& inFile); //opens file
double warriorFinder(vector<warrior> warrior_vec, string the_warrior); //originally meant to find warriors within the vector of structs, unused in this program
double WarriorStrength(string warrior_name, vector<warrior>& warrior_vec); //returns warrior strengths
void BattleOn(string first_warrior_name, string second_warrior_name, vector<warrior>& warrior_vec); //uses WarriorStrength() to  subtract/compare strengths and findWarriorIdx() to save any changes to the struct
void checkStatus(vector<warrior> warrior_vec); //checks status of warriors
int findWarriorIdx(string warrior_name, vector<warrior> warrior_vec); //returns index of warriors, helpful for modifying structs within a vector 

int main()
{
	ifstream inFile; //open file
	openFile(inFile);


	string info; //stores warrior,battle,status temporarily
	string name; //stores name during first file loop temporarily
	string first_warrior_name; //stores name of first warrior
	string second_warrior_name; //stores name of second warrior
	double strength; //stores strength temporarily


	
	vector<warrior> Warrior_Vec; //stores each warrior struct



	while (inFile >> info >> name >> strength) {
		if (info == "Warrior") { //only applies to lines with "Warrior" as the first string
			warrior MyWarrior; //creates temporary warrior struct for each iteration
			MyWarrior.name = name; //stores name into struct
			MyWarrior.strength = strength; //stores strength into struct
			Warrior_Vec.push_back(MyWarrior); //stores each struct into the vector
		}

	}

	 
	
	inFile.clear(); //clears variables associated with inFile
	inFile.seekg(0); //goes back to beginning of file
	 

	while (inFile >> info) {    //can be done within the previous while loop, broken up for my own readability
		if (info == "Battle") { //searches for battle lines
			inFile >> first_warrior_name >> second_warrior_name; //saves names after "Battle"
			
			BattleOn(first_warrior_name, second_warrior_name, Warrior_Vec); //Battles rage on whenever the battle lines are read from the file

				 
			}

		else if (info == "Status") {  //displays status whenever a status line is encountered
			checkStatus(Warrior_Vec);
		}
		}
			
	
	
	} 


	
	 



	
void openFile(ifstream& inFile) { //file opening function, option for user input commented out
	string filename = "warriors.txt";
	//cout << "Please input file name: \n";
	//cin >> filename;
	inFile.open(filename);


	while (!inFile) {
		cout << "Bad filename!" << endl << "Please input file name: " << endl;
		cin >> filename;

		inFile.clear();
		inFile.open(filename);
	}
}

//void battleNames(string line_of_warriors) {
//
//	for (char x : line_of_warriors) {
//		if (x == ' ') {
//			cout << x + 1 << endl;
//		}
//	}
//}

double WarriorStrength(string warrior_name, vector<warrior>& warrior_vec) { //returns warrior strengths
	double warrior_strength;

	for (int warrior_idx = 0; warrior_idx < warrior_vec.size(); ++warrior_idx) {
		if (warrior_vec[warrior_idx].name == warrior_name) {
			warrior_strength = warrior_vec[warrior_idx].strength;
			return warrior_strength;
		}
	
	}

	 
}

void BattleOn(string first_warrior_name, string second_warrior_name, vector<warrior>& warrior_vec) {

	double first_warrior_strength = WarriorStrength(first_warrior_name, warrior_vec); //finds strength
	double second_warrior_strength = WarriorStrength(second_warrior_name, warrior_vec);

	int first_warrior_idx = findWarriorIdx(first_warrior_name, warrior_vec); //finds indices
	int second_warrior_idx = findWarriorIdx(second_warrior_name, warrior_vec);

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
		warrior_vec[first_warrior_idx].strength = first_warrior_strength - second_warrior_strength;
		warrior_vec[second_warrior_idx].strength =  0;
		cout << first_warrior_name << " defeats " << second_warrior_name << endl;


	}

	else if (first_warrior_strength < second_warrior_strength) { //if warrior 2 beats warrior 1
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		warrior_vec[second_warrior_idx].strength = second_warrior_strength - first_warrior_strength;
		warrior_vec[first_warrior_idx].strength = 0;

		cout << second_warrior_name << " defeats " << first_warrior_name << endl;


	}

	else { //if both warriors have equal strength
		cout << first_warrior_name << " battles " << second_warrior_name << endl;
		warrior_vec[first_warrior_idx].strength = 0;
		warrior_vec[second_warrior_idx].strength = 0;
		cout << "Mutual annhilation: " << first_warrior_name << " and " << second_warrior_name << " die at each other's hands" << endl;



	}
}

void checkStatus(vector<warrior> warrior_vec) { //displays the status of each warrior
	cout << "There are: " << warrior_vec.size() << " warriors." << endl;
	for (int warrior_idx = 0; warrior_idx < warrior_vec.size(); ++warrior_idx) {
		cout << "Warrior:  " << warrior_vec[warrior_idx].name << "  Strength: " << warrior_vec[warrior_idx].strength << endl;
	}
}
 
int findWarriorIdx(string warrior_name, vector<warrior> warrior_vec) {   //returns the index of the warriors
	for (int warrior_idx = 0; warrior_idx < warrior_vec.size(); ++warrior_idx) {
		if (warrior_name == warrior_vec[warrior_idx].name) {
			return warrior_idx;
		}
		 
		
	}
}