#include "Fruit.h"
#include <random>

Fruit::Fruit(sf::Vector2f fruitSize, float cSize, float width, float height) :
	fruit{ fruitSize },
	cellSize{ cSize },
	windowWidth{ width },
	windowHeight{ height },
	gen{ rd() },
	xDistribution{ 0, static_cast<int>(windowWidth / cellSize) - 1 },
	yDistribution{ 0, static_cast<int>(windowHeight / cellSize) - 1 }
{
	fruit.setFillColor(sf::Color::Green);
}

sf::Vector2f Fruit::generateNewFruit()
{
	int randX{ xDistribution(gen) };
	int randY{ yDistribution(gen) };

	fruit.setPosition({ randX * cellSize, randY * cellSize });
	return { randX * cellSize, randY * cellSize };
}