#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	explicit Button(float x, float y, float width, float height,
					unsigned int charSize, float textOffsetX, float textOffsetY,
					const std::string& label, const sf::Font& font);
	void draw(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos) const noexcept;
	const std::string& getLabel() const noexcept { return text.getString(); }

private:
	sf::RectangleShape shape;
	sf::Text text;
};