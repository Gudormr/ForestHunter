// test060619.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()
#include "Character.h"
#include <vector>

typedef void(*combatCommand)(Character &x, Character &y);
combatCommand getCombatCommand(Character &x, Character &y);

std::string newName();

// Generate a random number between min and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
															// evenly distribute the random number across our range
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void attack(Character &x, Character &y)
{
	if ((x.getAccuracy() * getRandomNumber(1, 100)) > (y.getLuck() * getRandomNumber(1, 100)))
	{
		std::cout << x.getName() << " has dealt " << (x.getStrength() - (y.getDefense() / 2)) << " damage to " << y.getName() << "\n";
		y.decreaseHealth(x.getStrength() - (y.getDefense() / 2));
	}
	else
		std::cout << x.getName() << "'s attack missed!\n";
}

std::string getCommand()
{
	std::string command;
	std::cin >> command;
	return command;
}

void useItem(Character &x, Character &y)
{
	std::string command;
	while (true)
	{
		std::cout << "You have food and a spear\nWhat item do you want to use?\n";
		command = getCommand();
		if (command == "food")
		{
			std::cin.ignore(32767, '\n');
			x.increaseHealth(10);
			attack(y, x);
			break;
		}
		if (command == "spear")
		{
			std::cin.ignore(32767, '\n');
			std::cout << x.getName() << " has dealt 10 damage to " << y.getName() << "\n";
			y.decreaseHealth(10);
			if (y.getCurrentHealth() > 0)
				attack(y, x);
			break;
		}
		if (command == "back")
		{
			std::cin.ignore(32767, '\n');
			break;
		}
		else
			std::cin.ignore(32767, '\n');
	}
}

void combatPriority(Character &x, Character &y)
{
	if (x.getSpeed() > y.getSpeed())
	{
		attack(x, y);
		if (y.getCurrentHealth() > 0)
			attack(y, x);
	}
	else if (x.getSpeed() < y.getSpeed())
	{
		attack(y, x);
		if (x.getCurrentHealth() > 0)
			attack(x, y);
	}
	else
	{
		if (getRandomNumber(0, 1) == 0)
		{
			attack(x, y);
			if (y.getCurrentHealth() > 0)
				attack(y, x);
		}
		else
		{
			attack(y, x);
			if (x.getCurrentHealth() > 0)
				attack(x, y);
		}
	}
}



combatCommand getCombatCommand(Character &x, Character &y)
{
	std::string command;
	while (true)
	{
		std::cout << "\nYou have " << x.getCurrentHealth() << " health\nType help to get commands\nWhat do you want to do?\n";
		command = getCommand();
		if (command == "attack")
		{
			std::cin.ignore(32767, '\n');
			return combatPriority;
		}
		if (command == "item")
		{
			std::cin.ignore(32767, '\n');
			return useItem;
		}
		if (command == "help")
		{
			std::cin.ignore(32767, '\n');
			std::cout << "Type attack to attack\nType item to use an item\nfood restores 10 health\nspear deals 10 damage and always strikes first\n\n";
		}
		else
			std::cin.ignore(32767, '\n');
	}
}

Character zombeastCreation(Player &player);

bool combat(Player &x, Character &y, std::vector<Character> &enemyArray)
{
	std::cout << "You have encountered a " << y.getName() << "!\n";
	while (x.getCurrentHealth() > 0 && y.getCurrentHealth() > 0)
	{
		combatCommand choice = getCombatCommand(x, y);
		choice(x, y);
	}
	if (y.getCurrentHealth() < 1)
	{
		y.death();
		x.kill(y);
		return true;
	}
	if (x.getCurrentHealth() < 1)
	{
		enemyArray.push_back(zombeastCreation(x));
		x.death();
		return false;
	}
	return true;
}

void playGame()
{
	std::cout << "Monsters have been attacking the village.\nYou must head into the forest and hunt them down.\n";
	Player player(newName());
	int difficulty = 0;
	for (int count = 0; count < 3; count++)
	{
		std::cout << "\nEntering a new area...\n\n";
		std::vector<Character> enemyArray;
		for (int count = 0; count < 5; count++)
			enemyArray.push_back(newEnemy(difficulty));
		while (enemyArray.size() > 0)
		{
			if (combat(player, enemyArray.back(), enemyArray))
				enemyArray.pop_back();
		}
		std::cout << "\nAll the enemies are dead!\n";
		difficulty += 2;
	}
	std::cout << "The village is saved!\n";
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
	getRandomNumber(0, 100);

	playGame();
    return 0;
}

