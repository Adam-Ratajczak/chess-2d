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

    void draw(sf::RenderWindow& window) const;
    void handle_events(sf::RenderWindow& window, sf::Event& event);

private:
    std::vector<std::shared_ptr<Piece>> m_pieces;
    std::vector<Move> m_moves;

    Piece* m_selected = nullptr;
    Piece* m_black_king = nullptr;
    Piece* m_white_king = nullptr;

    sf::Texture m_board_texture, m_numbers_texture, m_letters_texture;

    sf::Color m_bg_color;

    bool m_turn = true;
};
