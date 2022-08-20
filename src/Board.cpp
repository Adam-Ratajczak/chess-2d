#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

std::string Board::theme = "";

Board::Board(std::string const& new_theme) {
    theme = new_theme;

    m_board_texture.loadFromFile("../assets/chess" + Board::theme + "/board.png");
}

void Board::init() {
    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(0, 0), false));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(1, 0), false));
    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(2, 0), false));
    m_pieces.push_back(std::make_shared<Queen>(sf::Vector2i(3, 0), false));
    m_pieces.push_back(std::make_shared<King>(sf::Vector2i(4, 0), false));
    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(5, 0), false));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(6, 0), false));
    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(7, 0), false));

    for (size_t i = 0; i < 8; i++) {
        m_pieces.push_back(std::make_shared<Pawn>(sf::Vector2i(i, 1), false));
    }

    for (size_t i = 0; i < 8; i++) {
        m_pieces.push_back(std::make_shared<Pawn>(sf::Vector2i(i, 6), true));
    }

    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(0, 7), true));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(1, 7), true));
    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(2, 7), true));
    m_pieces.push_back(std::make_shared<Queen>(sf::Vector2i(3, 7), true));
    m_pieces.push_back(std::make_shared<King>(sf::Vector2i(4, 7), true));
    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(5, 7), true));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(6, 7), true));
    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(7, 7), true));

    for (auto& piece : m_pieces) {
        piece->load_texture();
    }
}

void Board::draw(sf::RenderWindow& window) const {
    sf::Sprite board;
    board.setTexture(m_board_texture);

    int size = std::min(window.getSize().x, window.getSize().y) - 200;
    float scale = (float)size / m_board_texture.getSize().x;
    board.setPosition((float)window.getSize().x / 2,
        (float)window.getSize().y / 2);
    board
        .setOrigin((float)m_board_texture.getSize().x / 2,
            (float)m_board_texture.getSize().y / 2);
    board.setScale(scale, scale);
    window.draw(board);

    for (const auto& piece : m_pieces) {
        piece->draw(window, board.getPosition(), size, scale);
    }
}
