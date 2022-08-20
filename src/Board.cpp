#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Piece.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
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
    board.setOrigin((float)m_board_texture.getSize().x / 2, (float)m_board_texture.getSize().y / 2);
    board.setPosition((float)window.getSize().x / 2, (float)window.getSize().y / 2);
    board.setScale(scale, scale);
    window.draw(board);

    for (const auto& move : m_moves) {
        sf::Vector2f center(board.getGlobalBounds().left + (move.pos.x + .5) * board.getGlobalBounds().width / 8, board.getGlobalBounds().top + (move.pos.y + .5) * board.getGlobalBounds().height / 8);
        switch (move.move_type) {
        case Move::MoveType::MOVE: {
            sf::CircleShape circ(board.getGlobalBounds().width / 32);
            circ.setOrigin(circ.getRadius(), circ.getRadius());
            circ.setPosition(center);
            circ.setFillColor(sf::Color(120, 120, 120, 180));
            window.draw(circ);
        } break;
        case Move::MoveType::ATTACK: {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(board.getGlobalBounds().width / 8, board.getGlobalBounds().width / 8));
            rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
            rect.setPosition(center);
            rect.setFillColor(sf::Color(255, 0, 0, 180));
            window.draw(rect);
        } break;
        case Move::MoveType::SPECIAL: {
            sf::CircleShape circ(board.getGlobalBounds().width / 32);
            circ.setOrigin(circ.getRadius(), circ.getRadius());
            circ.setPosition(center);
            circ.setFillColor(sf::Color(120, 120, 255, 180));
            window.draw(circ);
        } break;
        }
    }

    for (const auto& piece : m_pieces) {
        piece->draw(window, board.getGlobalBounds());
    }
}

Piece* Board::query_piece(const sf::Vector2i& slot) const {
    for (const auto& piece : m_pieces) {
        if (piece->pos() == slot) {
            return piece.get();
        }
    }

    return nullptr;
}
