#pragma once

#ifndef NOBLE_H
#define NOBLE_H
#include <string>
#include <vector>
#include <iostream>
#include "Warrior.h"



namespace WarriorCraft {
	class Noble{
		std::string name;
		std::vector<Warrior*> army;
	public:
		Noble(std::string newName) : name(newName) {}
		
		std::string getName() const;
		std::vector<Warrior*> getArmy() const { return army; };

		friend std::ostream& operator<<(std::ostream& os, const Noble& n);

		void battleDamage(std::string result, int strengthRatio);
		void battle(Noble enemy);
		int armyStrength();
		void fire(Warrior firedWarrior, bool isRunaway = false);
		void hire(Warrior newWarrior);
	};
}






#endif