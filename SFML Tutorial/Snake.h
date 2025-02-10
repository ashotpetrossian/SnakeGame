#pragma once

#include <SFML/Graphics.hpp>
#include "Fruit.h"

#include <random>

class Snake
{
public:
	enum class Direction { Up, Down, Left, Right };

	Snake(float w, float h, float size, float step);

	void setInitPos();
	void setNextFruitInfo();

	bool hasCollidedWithWall() const;
	bool hasCollidedItself() const;
	bool hasEatenFruit() const;

	bool fruitOverlapsWithSnake(sf::Vector2f fruitPos);

	void grow();
	void move(Direction dir);
	const std::vector<sf::RectangleShape>& getBody() const noexcept { return snakeBody; }

	const sf::RectangleShape& getFruit() const noexcept { return fruit.getFruit(); }

private:
	const float windowWidth{};
	const float windowHeight{};
	const float cellSize{};
	const float stepSize{};

	std::vector<sf::RectangleShape> snakeBody;
	Fruit fruit;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> xDistribution;
	std::uniform_int_distribution<> yDistribution;
};