#include "Bishop.hpp"
#include "../Board.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

const std::vector<Move> Bishop::get_moves(const Board* pieces) const {
    std::vector<Move> result;

    auto fits_on_board = [](sf::Vector2i const& to_test) -> bool {
        return to_test.x >= 0 && to_test.x <= 7 && to_test.y >= 0 && to_test.y <= 7;
    };

    auto search_ray = [&](int fx, int fy){
        sf::Vector2i it(pos().x + fx, pos().y + fy);

        while (fits_on_board(it)) {
            auto piece = pieces->query_piece(it);
            if(piece){
                if (piece->side() != side()) 
                    result.push_back(Move{.pos = it, .move_type = Move::MoveType::ATTACK});
                return;
            }else{
                result.push_back(Move{.pos = it, .move_type = Move::MoveType::MOVE});
            }

            it.x += fx;
            it.y += fy;
        }
    };

    search_ray(-1, -1);
    search_ray(1, -1);
    search_ray(1, 1);
    search_ray(-1, 1);

    return result;
}

void Bishop::load_texture() {
    sf::Texture texture;
    texture.loadFromFile("../assets/chess" + Board::theme + "/" + (side() ? "white" : "black") + "_bishop.png");

    set_texture(texture);
}
