#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Chess 2d");

    Board board("");
    board.init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Green);

        board.draw(window);

        window.display();
    }
}
