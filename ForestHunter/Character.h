#pragma once
#include <string>

int getRandomNumber(int min, int max);

class Character
{
protected:
	std::string m_name;
	int m_level;
	int m_maxHealth;
	int m_currentHealth;
	int m_strength;
	int m_speed;
	int m_defense;
	int m_accuracy;
	int m_luck;

public:
	Character();
	Character(std::string name);
	Character(std::string name, int level, int health, int strength, int speed, int defense, int accuracy, int luck);

	std::string getName() { return m_name; }
	int getLevel() { return m_level; }
	int getMaxHealth() { return m_maxHealth; }
	int getCurrentHealth() { return m_currentHealth; }
	int getStrength() { return m_strength; }
	int getSpeed() { return m_speed; }
	int getDefense() { return m_defense; }
	int getAccuracy() { return m_accuracy; }
	int getLuck() { return m_luck; }

	void decreaseHealth(int damage);
	void increaseHealth(int healing);
	void levelUp(int difficulty);
	void death();
	void printSkills();
};

class Player : public Character
	{
		private:
			int m_maxExperience;
			int m_currentExperience;
			
		public:
			Player() {}
			Player(std::string name) : Character(name) 
			{
				m_maxExperience = 30;
				m_currentExperience = 0;
				printSkills();
			};
			int getMaxExperience() { return m_maxExperience; }
			int getCurrentExperience() { return m_currentExperience; }

			void newCharacter(std::string name);
			void decreaseHealth(int damage);
			void increaseExperience(int experience);
			void printSkills();
			void levelUp();
			void death();
			void kill(Character x);
	};

class Enemy : public Character
{
private:
	std::string m_rank;
public:

	Enemy(int rankMin = 1, int rankMax = 4, int nameMin = 1, int nameMax = 6)
	{
		m_name = (randomRank(rankMin, rankMax) + randomName(nameMin, nameMax));
	}

	Enemy(std::string name, int level, int health, int strength, int speed, int defense, int accuracy, int luck, int rankMin = 1, int rankMax = 4) : Character(name, level, health, strength, speed, defense, accuracy, luck)
	{
		m_rank = randomRank(rankMin, rankMax);
		m_name = m_rank + m_name;
	}

	std::string randomRank(int min, int max);
	std::string randomName(int min, int max);
	friend Character newEnemy(int difficulty);
};