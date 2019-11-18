#include "Noble.h"
#include "Warrior.h"

WarriorCraft::Noble* WarriorCraft::Warrior::getLeader() { return leader; } //returns Noble pointer

void WarriorCraft::Warrior::setLeader(WarriorCraft::Noble* newLeader) { leader = newLeader; } //leader is assigned to the address of the noble;

std::string WarriorCraft::Warrior::getName() const { return name; } //returns name

int WarriorCraft::Warrior::getStrength() const { return strength; } //returns strength value

void WarriorCraft::Warrior::setStrength(int newStrength) { strength = newStrength; } //modifies strength of warrior

void WarriorCraft::Warrior::runaway() { //when a warrior runs away from battle
	if (leader != nullptr) {
		std::cout << name << " flees in terror, abandoning his lord, " << this->getLeader().getName() << std::endl;
		leader->fire(*this, true); //fire() has a value of "true" passed in, meaning the message for a firing won't display
		leader = nullptr;
	}
}