#include "Pawn.hpp"
#include "../Board.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>

const std::vector<Move> Pawn::get_moves(const Board* pieces) const {
    std::vector<Move> result;

    auto fits_on_board = [](sf::Vector2i const& to_test) -> bool {
        return to_test.x >= 0 && to_test.x <= 7 && to_test.y >= 0 && to_test.y <= 7;
    };

    auto search_slot = [&](int fx, int fy, Move::MoveType type) {
        sf::Vector2i it(pos().x + fx, pos().y + fy);

        if (fits_on_board(it)) {
            auto piece = pieces->query_piece(it);
            if (type == Move::MoveType::ATTACK) {
                if (piece && piece->side() != side())
                    result.push_back(Move { .pos = it, .move_type = type });
                else
                    result.push_back(Move { .pos = it, .move_type = Move::MoveType::PROTECT });
            }
            else {
                if(!piece){
                    result.push_back(Move { .pos = it, .move_type = type });
                }
            }
        }
    };

    if(side()){
        search_slot(-1, -1, Move::MoveType::ATTACK);
        search_slot(0, -1, Move::MoveType::MOVE);
        search_slot(1, -1, Move::MoveType::ATTACK);

        if(first_move())
            search_slot(0, -2, Move::MoveType::SPECIAL);
    }else{
        search_slot(-1, 1, Move::MoveType::ATTACK);
        search_slot(0, 1, Move::MoveType::MOVE);
        search_slot(1, 1, Move::MoveType::ATTACK);
        if(first_move())
            search_slot(0, 2, Move::MoveType::SPECIAL);
    }

    return result;
}

void Pawn::load_texture() {
    sf::Texture texture;
    texture.loadFromFile("../assets/chess" + Board::theme + "/" + (side() ? "white" : "black") + "_pawn.png");

    set_texture(texture);
}
