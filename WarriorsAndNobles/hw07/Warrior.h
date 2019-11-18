#pragma once

#ifndef WARRIOR_H
#define WARRIOR_H
#include "Noble.h"
#include <string>

namespace WarriorCraft {
	class Warrior {
		std::string name;
		int strength;
		WarriorCraft::Noble* leader; //Noble pointer represents leader
	public:
		Warrior(std::string newName, int newStrength) : name(newName), strength(newStrength), leader(nullptr) {}
		WarriorCraft::Noble* getLeader();
		void setLeader(WarriorCraft::Noble* newLeader);
		std::string getName() const;
		int getStrength() const;
		void setStrength(int newStrength);
		void runaway();

}





#endif