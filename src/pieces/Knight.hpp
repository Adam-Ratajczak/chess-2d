#pragma once

#include "Piece.hpp"
class Knight : public Piece {
public:
    Knight(sf::Vector2i const& initial_pos, bool side)
        : Piece(initial_pos, side) { }

    virtual const std::vector<Move> get_moves(bool can_castle = false) const override;
    virtual void load_texture() override;
};