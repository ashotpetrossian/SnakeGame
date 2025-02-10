#include "Snake.h"


Snake::Snake(float w, float h, float size, float step) :
	windowWidth{w},
	windowHeight{h},
	cellSize{size},
	stepSize{step},
	fruit{ sf::Vector2f{ cellSize, cellSize }, cellSize, windowWidth, windowHeight },
	gen{ rd() },
	xDistribution{ 0, static_cast<int>(windowWidth / cellSize) - 1 },
	yDistribution{ 0, static_cast<int>(windowHeight / cellSize) - 1 }
{
	setInitPos();
}

void Snake::setInitPos()
{
	sf::RectangleShape head{ {cellSize, cellSize} };
	head.setFillColor(sf::Color::Red);

	int randX{ xDistribution(gen) };
	int randY{ yDistribution(gen) };

	head.setPosition({ randX * cellSize, randY * cellSize });

	snakeBody.push_back(head);
	setNextFruitInfo();
}

void Snake::setNextFruitInfo()
{
	while (fruitOverlapsWithSnake(fruit.generateNewFruit())) { }
}

bool Snake::fruitOverlapsWithSnake(sf::Vector2f fruitPos)
{
	for (sf::RectangleShape& rect : snakeBody) {
		if (rect.getGlobalBounds().contains(fruitPos)) {
			return true;
		}
	}

	return false;
}

bool Snake::hasCollidedWithWall() const
{
	sf::Vector2f headPos{ snakeBody.front().getPosition()};
	return headPos.x < 0.f || headPos.y < 0.f || headPos.x >= windowWidth || headPos.y >= windowHeight;
}

bool Snake::hasCollidedItself() const
{
	sf::Vector2f headPos{ snakeBody.front().getPosition() };
	
	for (int i{ 2 }; i < snakeBody.size(); ++i) {
		if (snakeBody[i].getPosition() == headPos) {
			return true;
		}
	}

	return false;
}

bool Snake::hasEatenFruit() const
{
	return snakeBody.front().getPosition() == fruit.getFruit().getPosition();
}

void Snake::grow()
{
	snakeBody.push_back(snakeBody.back());
}

void Snake::move(Direction dir)
{
	for (int i = snakeBody.size() - 1; i > 0; --i) {
		snakeBody[i].setPosition(snakeBody[i - 1].getPosition());
	}

	auto& head{ snakeBody.front() };
	sf::Vector2f lastPos{ head.getPosition() };
	float x{lastPos.x}, y{lastPos.y};

	if (dir == Direction::Up) {
		y -= cellSize;
	}
	else if (dir == Direction::Down) {
		y += cellSize;
	}
	else if (dir == Direction::Left) {
		x -= cellSize;
	}
	else {
		x += cellSize;
	}

	head.setPosition({x, y});
}