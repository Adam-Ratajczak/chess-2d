#pragma once

#include "pieces/Piece.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <vector>

class Board {
public:
    explicit Board(std::string const& theme);
    static std::string theme;

    void init();

    void draw(sf::RenderWindow& window) const;

private:
    std::vector<std::shared_ptr<Piece>> m_pieces;
    sf::Texture m_board_texture;
};
