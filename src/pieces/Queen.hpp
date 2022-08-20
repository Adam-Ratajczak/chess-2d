#pragma once

#include "Piece.hpp"
class Queen : public Piece {
public:
    Queen(sf::Vector2i const& initial_pos, bool side)
        : Piece(initial_pos, side) { }

    virtual const std::vector<Move> get_moves(const Board* pieces) const override;
    virtual void load_texture() override;
};
