#include "Character.h"
#include <string>
#include <iostream>

int getRandomNumber(int min, int max);

std::string newName()
{
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;
	std::cin.ignore(32767, '\n');
	return name;

}

Character::Character()
{
	m_level = 1;
	m_maxHealth = getRandomNumber(15, 25);
	m_currentHealth = m_maxHealth;
	m_strength = getRandomNumber(10, 15);
	m_speed = getRandomNumber(10, 15);
	m_defense = getRandomNumber(10, 15);
	m_accuracy = getRandomNumber(10, 15);
	m_luck = getRandomNumber(1, 5);
}

Character::Character(std::string name)
{
	m_name = name;
	m_level = 1;
	m_maxHealth = getRandomNumber(20, 25);
	m_currentHealth = m_maxHealth;
	m_strength = getRandomNumber(15, 20);
	m_speed = getRandomNumber(15, 20);
	m_defense = getRandomNumber(15, 20);
	m_accuracy = getRandomNumber(15, 20);
	m_luck = getRandomNumber(3, 5);
}

Character::Character(std::string name, int level, int health, int strength, int speed, int defense, int accuracy, int luck)
{
	m_name = name;
	m_level = level;
	m_maxHealth = health;
	m_currentHealth = m_maxHealth;
	m_strength = strength;
	m_speed = speed;
	m_defense = defense;
	m_accuracy = accuracy;
	m_luck = luck;
}

void Character::printSkills()
{
	std::cout << "Your name is " << m_name << "\n";
	std::cout << "Your level is " << m_level << "\n";
	std::cout << "Your health is " << m_currentHealth << "/" << m_maxHealth << "\n";
	std::cout << "Your strength is " << m_strength << "\n";
	std::cout << "Your speed is " << m_speed << "\n";
	std::cout << "Your defense is " << m_defense << "\n";
	std::cout << "Your accuracy is " << m_accuracy << "\n";
	std::cout << "Your luck is " << m_luck << "\n\n";
}

void Player::printSkills()
{
	//std::cout << "Your name is " << m_name << "\n";
	std::cout << "You are level " << m_level << "\n";
	std::cout << "You have " << m_currentExperience << "/" << m_maxExperience << " experience\n";
	std::cout << "You have " << m_currentHealth << "/" << m_maxHealth << " health\n";
	std::cout << "You have " << m_strength << " strength\n";
	std::cout << "You have " << m_speed << " speed\n";
	std::cout << "You have " << m_defense << " defense\n";
	std::cout << "You have " << m_accuracy << " accuracy\n";
	std::cout << "You have " << m_luck << " luck\n\n";
}

void Player::levelUp()
{
	m_level += 1;
	m_maxExperience += 10;
	m_maxHealth += getRandomNumber(0, 3);
	m_strength += getRandomNumber(0, 3);
	m_speed += getRandomNumber(0, 3);
	m_defense += getRandomNumber(0, 3);
	m_accuracy += getRandomNumber(0, 3);
	m_luck += getRandomNumber(0, 2);
	std::cout << "\nYou leveled up!\n";
	printSkills();
}

void Character::levelUp(int difficulty)
{
	m_level += difficulty;
	m_maxHealth += (getRandomNumber(1, 3) * difficulty);
	m_currentHealth = m_maxHealth;
	m_strength += (getRandomNumber(1, 3) * difficulty);
	m_speed += (getRandomNumber(1, 3) * difficulty);
	m_defense += (getRandomNumber(1, 3) * difficulty);
	m_accuracy += (getRandomNumber(1, 3) * difficulty);
	m_luck += (getRandomNumber(1, 2) * difficulty);
}

void Player::increaseExperience(int experience)
{
	m_currentExperience += experience;
	while (m_currentExperience >= m_maxExperience)
	{
		m_currentExperience -= m_maxExperience;
		levelUp();
	}
}

void Character::increaseHealth(int healing)
{
	m_currentHealth += healing;
	if (m_currentHealth > m_maxHealth)
	{
		std::cout << "Your health increased by " << (healing - (m_currentHealth - m_maxHealth)) << "\n";
		m_currentHealth = m_maxHealth;
	}
	else
		std::cout << "Your health increased by " << healing << "\n";
}

void Character::decreaseHealth(int damage)
{
	if (damage < 0)
		damage = 0;
	m_currentHealth -= damage;
}

void Player::decreaseHealth(int damage)
{
	if (damage < 0)
		damage = 0;
	m_currentHealth -= damage;
}

void Character::death()
{
	std::cout << m_name << " has died!\n";

}

void Player::death()
{
	std::cout << m_name << " has died!\n\nMeanwhile, another hunter prepares to head into the forest...\n";
	newCharacter(newName());
}

void Player::newCharacter(std::string name)
{
	m_name = name;
	m_level = 1;
	m_maxExperience = 30;
	m_currentExperience = 0;
	m_maxHealth = getRandomNumber(20, 25);
	m_currentHealth = m_maxHealth;
	m_strength = getRandomNumber(15, 20);
	m_speed = getRandomNumber(15, 20);
	m_defense = getRandomNumber(15, 20);
	m_accuracy = getRandomNumber(15, 20);
	m_luck = getRandomNumber(3, 5);
	printSkills();
}

void Player::kill(Character x)
{
	std::cout << "You earned " << ((x.getStrength() + x.getSpeed() + x.getDefense() + x.getAccuracy()) / 4) << " experience!\n\n";
	increaseExperience(((x.getStrength() + x.getSpeed() + x.getDefense() + x.getAccuracy()) / 4));
}

std::string Enemy::randomRank(int min = 1, int max = 5)
{
	int rank;
	rank = getRandomNumber(min, max);
	switch (rank)
	{
	case(0):
		return "";
	case(1):
		return "Young ";
	case(2):
		return "Large ";
	case(3):
		return "Crazed ";
	case(4):
		return "Possessed ";
	case(5):
		return "Demon ";
	}

}

std::string Enemy::randomName(int min = 1, int max = 5)
{
	int name;
	name = getRandomNumber(min, max);
	switch (name)
	{
	case(1):
		return "Wolf";
	case(2):
		return "Bear";
	case(3):
		return "Gorilla";
	case(4):
		return "Goblin";
	case(5):
		return "Troll";
	}
}

Character newEnemy(int difficulty)
{
	Enemy enemy(0, 5, 1, 5);
	enemy.levelUp(difficulty);
	return enemy;
}

Character zombeastCreation(Player &player)
{
	Enemy zombeast("Zombeast", player.getLevel(), player.getMaxHealth() * 0.8, player.getStrength() * 0.8, player.getSpeed() * 0.8, player.getDefense() * 0.8, player.getAccuracy() * 0.8, player.getLuck(), 0, 0);
	return zombeast;
}