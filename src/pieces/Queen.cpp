#include "Queen.hpp"
#include "../Board.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

const std::vector<Move> Queen::get_moves(bool) const {
    std::vector<Move> result;

    if (side()) {
        result.push_back(Move { .pos = sf::Vector2i(pos().x - 1, pos().y - 1),
            .move_type = Move::MoveType::ATTACK });
        result.push_back(Move { .pos = sf::Vector2i(pos().x, pos().y - 1),
            .move_type = Move::MoveType::MOVE });
        result.push_back(Move { .pos = sf::Vector2i(pos().x + 1, pos().y - 1),
            .move_type = Move::MoveType::ATTACK });

        if (first_move())
            result.push_back(Move { .pos = sf::Vector2i(pos().x, pos().y - 2),
                .move_type = Move::MoveType::SPECIAL });
    }
    else {
        result.push_back(Move { .pos = sf::Vector2i(pos().x - 1, pos().y + 1),
            .move_type = Move::MoveType::ATTACK });
        result.push_back(Move { .pos = sf::Vector2i(pos().x, pos().y + 1),
            .move_type = Move::MoveType::MOVE });
        result.push_back(Move { .pos = sf::Vector2i(pos().x + 1, pos().y + 1),
            .move_type = Move::MoveType::ATTACK });

        if (first_move())
            result.push_back(Move { .pos = sf::Vector2i(pos().x, pos().y + 2),
                .move_type = Move::MoveType::SPECIAL });
    }

    auto val = std::remove_if(
        result.begin(), result.end(),
        [](const Move& lhs) -> bool { return lhs.pos.x < 0 || lhs.pos.y < 0; });

    return result;
}

void Queen::load_texture() {
    sf::Texture texture;
    texture.loadFromFile("../assets/chess" + Board::theme + "/" + (side() ? "white" : "black") + "_queen.png");

    set_texture(texture);
}
