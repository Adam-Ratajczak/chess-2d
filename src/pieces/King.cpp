#include "King.hpp"
#include "../Board.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <vector>

const std::vector<Move> King::get_moves(const Board* pieces) const {
    std::vector<Move> result;

    auto fits_on_board = [](sf::Vector2i const& to_test) -> bool {
        return to_test.x >= 0 && to_test.x <= 7 && to_test.y >= 0 && to_test.y <= 7;
    };

    auto search_slot = [&](int fx, int fy) {
        sf::Vector2i it(pos().x + fx, pos().y + fy);

        if (fits_on_board(it)) {
            auto piece = pieces->query_piece(it);
            if (piece) {
                if (piece->side() != side())
                    result.push_back(Move { .pos = it, .move_type = Move::MoveType::ATTACK });
            }
            else {
                result.push_back(Move { .pos = it, .move_type = Move::MoveType::MOVE });
            }
        }
    };

    search_slot(-1, -1);
    search_slot(0, -1);
    search_slot(1, -1);
    search_slot(-1, 0);
    search_slot(1, 0);
    search_slot(-1, 1);
    search_slot(0, 1);
    search_slot(1, 1);
    
    auto check_if_castle = [&](int y){
        if(!first_move())
            return;

        std::vector<Piece*> piece_row;

        for(size_t i = 0; i < 8; i++){
            piece_row.push_back(pieces->query_piece(sf::Vector2i(i, y)));
        }

        if(piece_row[0] && piece_row[0]->first_move()){
            if(!piece_row[1] && !piece_row[2] && !piece_row[3]){
                result.push_back(Move{.pos = sf::Vector2i(2, y), .move_type = Move::MoveType::SPECIAL});
            }
        }

        if(piece_row[7] && piece_row[7]->first_move()){
            if(!piece_row[6] && !piece_row[5]){
                result.push_back(Move{.pos = sf::Vector2i(6, y), .move_type = Move::MoveType::SPECIAL});
            }
        }
    };

    if(side()){
        check_if_castle(7);
    }else{
        check_if_castle(0);
    }

    return result;
}

void King::load_texture() {
    sf::Texture texture;
    texture.loadFromFile("../assets/chess" + Board::theme + "/" + (side() ? "white" : "black") + "_king.png");

    set_texture(texture);
}
