#include "Warrior.h"
#include "Noble.h"


std::string WarriorCraft::Noble::getName() const { return name; }
//std::vector<WarriorCraft::Warrior*> WarriorCraft::Noble::getArmy() const { return army; }



void WarriorCraft::Noble::hire(WarriorCraft::Warrior newWarrior) { //hires warrior
	if (newWarrior.getLeader() != nullptr) {
		army.push_back(&newWarrior);
		newWarrior.setLeader(*this);
	}
}

void WarriorCraft::Noble::fire(WarriorCraft::Warrior firedWarrior, bool isRunaway) {  //fire method, has a default value of "false" passed through, as it is mainly used with one input. Alternatively, it's included in the runaway method
	if (isRunaway == false) { std::cout << "You don't work for me anymore," << firedWarrior.getName() << '!' << std::endl; }
	for (size_t i = 0; i < army.size(); i++) {
		if (firedWarrior.getName() == army[i]->getName()) {
			army[i]->setLeader(nullptr);
			army[i] = army[army.size() - 1];
			army.pop_back();
			
		}
	}
}


WarriorCraft::Noble operator<<(std::ostream& os, const WarriorCraft::Noble& n) {
	os << n.getName() << " has an army of " << n.getArmy().size() << '\n';
	for (WarriorCraft::Warrior* warrior : n.getArmy()) {
		std::cout << warrior->getName() << ": " << warrior->getStrength << '\n';
	}

}

int WarriorCraft::Noble::armyStrength() {
	int totalStrength = 0;
	for (Warrior* hiredWarrior : army) {
		totalStrength += hiredWarrior->getStrength();
	}
	return totalStrength;
}

void WarriorCraft::Noble::battleDamage(std::string result, int strengthRatio) {
	if (result == "win") {
		for (WarriorCraft::Warrior* hiredWarrior : army) {
			int newStrength = (hiredWarrior->getStrength() - (strengthRatio*hiredWarrior->getStrength()));
			//if (newStrength > 0) { hiredWarrior->setStrength(newStrength); } not necessary
			//else { hiredWarrior->setStrength(0); }
		}
	}
	else if (result == "lose") {
		for (WarriorCraft::Warrior* hiredWarrior : army) {
			hiredWarrior->setStrength(0);
		}
	}
}

void WarriorCraft::Noble::battle(Noble enemy) {
	int nobleOneStrength = armyStrength();
	int nobleTwoStrength = enemy.armyStrength();

	std::cout << name << " battles " << enemy.getName() << std::endl;

	if (nobleOneStrength == 0 && nobleTwoStrength == 0) {
		std::cout << "Oh NO! They're both dead! Yuck!" << std::endl;

	}
	else if (nobleOneStrength == 0) {
		std::cout << "He's dead, " << enemy.getName() << std::endl;
	}
	else if (nobleTwoStrength == 0) {
		std::cout << "He's dead, " << getName() << std::endl;
	}
	else if (nobleOneStrength > nobleTwoStrength) {
		battleDamage("win", nobleTwoStrength / nobleOneStrength);
		enemy.battleDamage("lose", nobleTwoStrength / nobleOneStrength);
		std::cout << name << " defeats " << enemy.getName() << std::endl;

	}
	else if (nobleTwoStrength > nobleOneStrength) {
		enemy.battleDamage("win", nobleOneStrength / nobleTwoStrength);
		battleDamage("lose", nobleOneStrength / nobleTwoStrength);
		std::cout << enemy.getName() << " defeats " << name << std::endl;
	}
	else {
		std::cout << "Mutual Annihilation: " << name << " and " << enemy.getName() << " die at each other's hands" << std::endl;
		battleDamage("lose", 1 / 1);
		enemy.battleDamage("lose", 1 / 1);
	}
}


