#pragma once

#include "pieces/Piece.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <string>
#include <vector>

class Board {
public:
    explicit Board(std::string const& theme);
    static std::string theme;

    void init();

    Piece* query_piece(sf::Vector2i const& slot) const;
    std::vector<std::shared_ptr<Piece>> const& pieces() const { return m_pieces; }

    void draw(sf::RenderWindow& window) const;
    void handle_events(sf::RenderWindow& window, sf::Event& event);

    void is_check();

    bool turn() const { return m_turn; }

private:
    std::vector<std::shared_ptr<Piece>> m_pieces;
    std::vector<Move> m_moves;
    std::vector<std::vector<Move>> m_allowed_moves;

    Piece* m_selected = nullptr;
    Piece* m_black_king = nullptr;
    Piece* m_white_king = nullptr;

    sf::Texture m_board_texture, m_numbers_texture, m_letters_texture;

    sf::Color m_bg_color;

    bool m_turn = true, m_check = false;

    size_t m_deleted_black_pieces = 0, m_deleted_white_pieces = 0;
};
