#include "Button.h"

Button::Button(float x, float y,
			   float width, float height,
			   unsigned int charSize,
			   float textOffsetX, float textOffsetY,
			   const std::string& label, const sf::Font& font)
	: text{ font }
{
	shape.setPosition({ x, y });
	shape.setSize({ width, height });
	shape.setFillColor(sf::Color::Blue);

	text.setString(label);
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::White);
	text.setPosition({ x + textOffsetX, y + textOffsetY });
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

bool Button::isClicked(sf::Vector2f mousePos) const noexcept
{
	return shape.getGlobalBounds().contains(mousePos);
}

