#pragma once

#include "Board.h"
#include "BoardView.h"

class StdioBoardView final : public BoardView {
public:
    explicit StdioBoardView() = default;
    ~StdioBoardView() = default;
    StdioBoardView(const StdioBoardView &) = delete;
    StdioBoardView &operator=(const StdioBoardView &) = delete;

    std::optional<Board::Position> retrieve_next_position(const Board &) override;
    void move(const Board &, Board::Position) override;
    void print_board(const Board &) const override;
    void end_game(const Board &) const override;
    void process_incorrect_move() const;
};