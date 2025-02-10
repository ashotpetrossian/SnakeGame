#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Fruit
{
public:
	Fruit(sf::Vector2f size, float cellSize, float width, float height);
	// randomly chooses the next fruitType and position
	sf::Vector2f generateNewFruit();

	const sf::RectangleShape& getFruit() const noexcept { return fruit; }
private:
	sf::RectangleShape fruit;
	const float cellSize;
	const float windowWidth;
	const float windowHeight;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> xDistribution;
	std::uniform_int_distribution<> yDistribution;
};
