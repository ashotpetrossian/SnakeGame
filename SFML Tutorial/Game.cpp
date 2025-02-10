#include "Game.h"
#include "SnakeException.h"
#include "Button.h"

#include <iostream>

void Game::run()
{
    try
    {
        welcome();
    }
    catch (const SnakeException& ex)
    {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
        return;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Unexpected exception: " << ex.what() << std::endl;
    }

    switch (difficulty) {
        case Difficulty::EASY: moveDelay = 0.2f; break;
        case Difficulty::MEDIUM: moveDelay = 0.1f; break;
        case Difficulty::HARD: moveDelay = 0.05f; break;
    }

    bool inGame{ true };
    while (inGame) {
        try
        {
            play();
        }
        catch (const SnakeException& ex)
        {
            restart(inGame);
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Unexpected exception: " << ex.what() << std::endl;
        }
    }
    
}

void Game::welcome()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode{ { welcomeWindow } }, "Snake game wellcome!");

    std::string fontPath{ "Prototype.ttf" };
    if (!font.openFromFile(fontPath)) {
        throw PathFindException(fontPath);
    }

    sf::Text text(font, "Choose the difficulty", 40);
    text.setFillColor(sf::Color::Magenta);
    text.move({ 100.f, 100.f });

    /*
        float x, float y, float width, float height,
        unsigned int charSize, float xDiff, float yDiff,
        const std::string& label, const sf::Font& font
    */
    Button easy{ 50.f, 300.f, 150.f, 75.f, 35, 20.f, 10.f, "Easy", font };
    Button medium{ 250.f, 300.f, 150.f, 75.f, 35, 20.f, 10.f, "Medium", font };
    Button hard{ 450.f, 300.f, 150.f, 75.f, 35, 20.f, 10.f, "Hard", font };

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                throw WindowCloseException{ "" };
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const sf::Event::MouseButtonPressed* p_mouseButtonEvent{ event->getIf<sf::Event::MouseButtonPressed>() };

                if (p_mouseButtonEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2i pos = p_mouseButtonEvent->position;
                    if (easy.isClicked({ pos.x * 1.f, pos.y * 1.f })) {
                        difficulty = Difficulty::EASY;
                        return;
                    }
                    else if (medium.isClicked({ pos.x * 1.f, pos.y * 1.f })) {
                        difficulty = Difficulty::MEDIUM;
                        return;
                    }
                    else if (hard.isClicked({ pos.x * 1.f, pos.y * 1.f })) {
                        difficulty = Difficulty::HARD;
                        return;
                    }
                }
            }
        }

        window.clear();

        window.draw(text);
        easy.draw(window);
        medium.draw(window);
        hard.draw(window);

        window.display();
    }
}

void Game::play()
{
    sf::RenderWindow window(sf::VideoMode{ { mainWindow } }, "Snake Game!");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Snake snake{ 1200.f, 1200.f, 40.f, 40.f };
    Snake::Direction dir{ Snake::Direction::Right };
    score = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                throw WindowCloseException{ "" };
            }
            
            if (event->is<sf::Event::KeyReleased>()) {
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Up && dir != Snake::Direction::Down) {
                    dir = Snake::Direction::Up;
                }
                else if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Down && dir != Snake::Direction::Up) {
                    dir = Snake::Direction::Down;
                }
                else if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Left && dir != Snake::Direction::Right) {
                    dir = Snake::Direction::Left;
                }
                else if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Right && dir != Snake::Direction::Left) {
                    dir = Snake::Direction::Right;
                }
            }
        }

        if (snake.hasEatenFruit()) {
            ++score;
            snake.setNextFruitInfo();
            snake.grow();
        }
            

        if (clock.getElapsedTime().asSeconds() > moveDelay) {
            snake.move(dir);
            clock.restart();
        }

        if (snake.hasCollidedWithWall() || snake.hasCollidedItself()) {
            throw CollisionException{ "" };
        }

        window.clear();

        drawTheSnake(window, snake);
        window.draw(snake.getFruit());

        window.display();
    }
}

void Game::restart(bool& inGame)
{
    sf::RenderWindow window({ sf::VideoMode{welcomeWindow} }, "Wanna play again?");

    sf::Text scoreText(font, "Your score is: " + std::to_string(score), 40);
    scoreText.setFillColor(sf::Color::Magenta);
    scoreText.move({ 100.f, 100.f });

    Button playAgainButton{ 250.f, 300.f, 350.f, 100.f, 60, 32.f, 12.f, "Play again", font };

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                inGame = false;
                return;
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const sf::Event::MouseButtonPressed* p_mouseButtonEvent{ event->getIf<sf::Event::MouseButtonPressed>() };

                if (p_mouseButtonEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2i pos = p_mouseButtonEvent->position;
                    if (playAgainButton.isClicked({ static_cast<float>(pos.x), static_cast<float>(pos.y) })) {
                        // keep inGame true
                        return;
                    }
                }
            }
            if (event->is<sf::Event::KeyReleased>()) {
                if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Enter) {
                    return;
                }
            }
        }

        window.clear();

        playAgainButton.draw(window);
        window.draw(scoreText);

        window.display();
    }

}

void Game::drawTheSnake(sf::RenderWindow& window, const Snake& snake)
{
    for (const auto& part : snake.getBody()) {
        window.draw(part);
    }
}