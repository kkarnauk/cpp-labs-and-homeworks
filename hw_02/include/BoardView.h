#pragma once

#include "Board.h"

class BoardView {
public:
    explicit BoardView() = default;
    virtual ~BoardView() = default;
    BoardView(const BoardView &) = delete;
    BoardView &operator=(const BoardView &) = delete; 

    virtual std::optional<Board::Position> retrieve_next_position(const Board &) = 0;
    virtual void move(const Board &, Board::Position) = 0;
    virtual void print_board(const Board &) const = 0;
    virtual void end_game(const Board &) const = 0;
};