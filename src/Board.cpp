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
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <memory>

std::string Board::theme = "";

Board::Board(std::string const& new_theme) {
    theme = new_theme;

    m_board_texture.loadFromFile("../assets/chess" + Board::theme + "/board.png");
    m_numbers_texture.loadFromFile("../assets/chess" + Board::theme + "/numbers.png");
    m_letters_texture.loadFromFile("../assets/chess" + Board::theme + "/text.png");

    m_bg_color = m_board_texture.copyToImage().getPixel(0, 0);
}

void Board::init() {
    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(0, 0), false));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(1, 0), false));
    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(2, 0), false));
    m_pieces.push_back(std::make_shared<Queen>(sf::Vector2i(3, 0), false));

    m_pieces.push_back(std::make_shared<King>(sf::Vector2i(4, 0), false));
    m_black_king = m_pieces.back().get();

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
    m_black_king = m_pieces.back().get();

    m_pieces.push_back(std::make_shared<Bishop>(sf::Vector2i(5, 7), true));
    m_pieces.push_back(std::make_shared<Knight>(sf::Vector2i(6, 7), true));
    m_pieces.push_back(std::make_shared<Rook>(sf::Vector2i(7, 7), true));

    for (auto& piece : m_pieces) {
        piece->load_texture();
    }
}

void Board::draw(sf::RenderWindow& window) const {
    window.clear(m_bg_color);

    sf::Sprite board;
    board.setTexture(m_board_texture);

    int size = std::min(window.getSize().x, window.getSize().y) - 200;
    float scale = (float)size / m_board_texture.getSize().x;
    board.setOrigin((float)m_board_texture.getSize().x / 2, (float)m_board_texture.getSize().y / 2);
    board.setPosition((float)window.getSize().x / 2, (float)window.getSize().y / 2);
    board.setScale(scale, scale);
    window.draw(board);

    sf::Color inverted(-m_bg_color.r, -m_bg_color.g, -m_bg_color.b);

    sf::Sprite numbers;
    numbers.setTexture(m_numbers_texture);
    numbers.setScale((float)size / m_numbers_texture.getSize().y, (float)size / m_numbers_texture.getSize().y);
    numbers.setPosition(board.getGlobalBounds().left - 20 - numbers.getGlobalBounds().width, board.getGlobalBounds().top);
    numbers.setColor(inverted);
    window.draw(numbers);

    sf::Sprite letters;
    letters.setTexture(m_letters_texture);
    letters.setScale((float)size / m_letters_texture.getSize().x, (float)size / m_letters_texture.getSize().x);
    letters.setPosition(board.getGlobalBounds().left, board.getGlobalBounds().top - 20 - letters.getGlobalBounds().height);
    letters.setColor(inverted);
    window.draw(letters);

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

void Board::handle_events(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Sprite board;
        board.setTexture(m_board_texture);

        int size = std::min(window.getSize().x, window.getSize().y) - 200;
        float scale = (float)size / m_board_texture.getSize().x;
        board.setOrigin((float)m_board_texture.getSize().x / 2, (float)m_board_texture.getSize().y / 2);
        board.setPosition((float)window.getSize().x / 2, (float)window.getSize().y / 2);
        board.setScale(scale, scale);

        auto create_rect = [&](sf::Vector2i pos) -> sf::IntRect {
            sf::IntRect result;
            float tile_size = board.getGlobalBounds().width / 8;

            result.left = board.getGlobalBounds().left + pos.x * tile_size;
            result.top = board.getGlobalBounds().top + (pos.y + .5) * tile_size;
            result.width = tile_size;
            result.height = tile_size;

            return result;
        };

        sf::Vector2i mouse_pos = sf::Mouse::getPosition();

        for (const auto& move : m_moves) {
            auto rect = create_rect(move.pos);

            if (rect.contains(mouse_pos)) {
                if (move.move_type == Move::MoveType::ATTACK) {
                    auto deleted_piece = query_piece(move.pos);
                    deleted_piece->delete_piece();
                    
                    if(deleted_piece->side()){
                        deleted_piece->move(sf::Vector2i(9 + m_deleted_white_pieces / 8, m_deleted_white_pieces % 8));
                        m_deleted_white_pieces++;
                    }else{
                        deleted_piece->move(sf::Vector2i(-2 - m_deleted_black_pieces / 8, m_deleted_black_pieces % 8));
                        m_deleted_black_pieces++;
                    }

                    m_selected->move(move.pos);
                }
                else {
                    if (m_selected == m_white_king || m_selected == m_black_king) {
                        if (move.move_type == Move::MoveType::SPECIAL) {
                            auto rook = query_piece(sf::Vector2i(move.pos.x == 2 ? 0 : 7, move.pos.y));
                            rook->move(sf::Vector2i(move.pos.x == 2 ? 3 : 5, move.pos.y));
                        }
                    }
                    m_selected->move(move.pos);
                }

                m_turn = !m_turn;
                m_moves.clear();
                m_selected = nullptr;
                return;
            }
        }

        for (const auto& piece : m_pieces) {
            if (piece->deleted() || piece->side() != m_turn)
                continue;

            auto rect = create_rect(piece->pos());

            if (rect.contains(mouse_pos)) {
                m_selected = piece.get();
                m_moves = m_selected->get_moves(this);

                return;
            }
        }

        m_moves.clear();
        m_selected = nullptr;
    }
}
