#pragma once

#include "Snake.h"

class Game
{
public:
	void run();
	void welcome();
	void play();
	void restart(bool& inGame);

	void drawTheSnake(sf::RenderWindow& window, const Snake& snake);

	enum class Difficulty { EASY, MEDIUM, HARD };

private:
	Difficulty difficulty{ Difficulty::MEDIUM };
	float moveDelay{ 0.1f };	
	sf::Font font;
	size_t score{};
	
	static constexpr sf::Vector2u mainWindow{ 1200, 1200 };
	static constexpr sf::Vector2u welcomeWindow{ 800, 800 };
};