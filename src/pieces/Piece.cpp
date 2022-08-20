#include "Piece.hpp"

void Piece::draw(sf::RenderWindow& window, sf::Vector2f board_pos, float size,
    float scale) const {
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setPosition(board_pos.x + 2 * scale + m_pos.x * size / 8,
        board_pos.y + 2 * scale + m_pos.y * size / 8);
    // sprite.setScale((scale / 8 - 4) / m_texture.getSize().x, (scale / 8 - 4) /
    // m_texture.getSize().y);

    window.draw(sprite);
}

void Piece::move(const sf::Vector2i& new_pos) {
    m_pos = new_pos;

    m_first_move = 0;
}
