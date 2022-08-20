#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

struct Move {
    sf::Vector2i pos;

    enum class MoveType {
        MOVE,
        ATTACK,
        SPECIAL
    };

    MoveType move_type;
};
class Board;

class Piece {
public:
    Piece(sf::Vector2i const& initial_pos, bool side)
        : m_pos(initial_pos)
        , m_side(side) { }

    virtual const std::vector<Move> get_moves(const Board* pieces) const = 0;
    virtual void load_texture() = 0;

    void move(sf::Vector2i const& new_pos);
    void draw(sf::RenderWindow& window, sf::FloatRect const& rect) const;

    sf::Vector2i pos() const { return m_pos; }
    bool side() const { return m_side; }
    bool first_move() const { return m_first_move; }

    virtual ~Piece() { }

protected:
    void set_texture(const sf::Texture& texture) { m_texture = texture; }
    sf::Sprite get_sprite(sf::FloatRect const& rect) const;

private:
    sf::Vector2i m_pos;
    sf::Texture m_texture;
    bool m_first_move = true;
    const bool m_side;
};
