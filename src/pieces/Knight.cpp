#include "Knight.hpp"
#include "../Board.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

const std::vector<Move> Knight::get_moves(bool) const {
    std::vector<Move> result;
    result.push_back(Move { .pos = sf::Vector2i(pos().x - 1, pos().y - 2),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x + 1, pos().y - 2),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x + 2, pos().y - 1),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x + 2, pos().y + 1),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x + 1, pos().y + 2),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x - 1, pos().y + 2),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x - 2, pos().y + 1),
        .move_type = Move::MoveType::BOTH });
    result.push_back(Move { .pos = sf::Vector2i(pos().x - 2, pos().y - 1),
        .move_type = Move::MoveType::BOTH });

    auto val = std::remove_if(
        result.begin(), result.end(),
        [](const Move& lhs) -> bool { return lhs.pos.x < 0 || lhs.pos.y < 0; });

    return result;
}

void Knight::load_texture() {
    sf::Texture texture;
    texture.loadFromFile("../assets/chess" + Board::theme + "/" + (side() ? "white" : "black") + "_knight.png");

    set_texture(texture);
}
