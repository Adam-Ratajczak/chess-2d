#include "Piece.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

sf::Sprite Piece::get_sprite(sf::FloatRect const& rect) const {
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setOrigin((float)m_texture.getSize().x / 2, (float)m_texture.getSize().y / 2);
    sprite.setPosition(rect.left + (m_pos.x + .5) * rect.width / 8, rect.top + (m_pos.y + .5) * rect.height / 8);
    sprite.setScale((rect.width / 8 - 20) / m_texture.getSize().x, (rect.height / 8 - 20) / m_texture.getSize().y);

    return sprite;
}

void Piece::draw(sf::RenderWindow& window, sf::FloatRect const& rect) const {
    window.draw(get_sprite(rect));
}

void Piece::move(const sf::Vector2i& new_pos) {
    m_pos = new_pos;

    m_first_move = 0;
}
