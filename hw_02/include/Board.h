#pragma once

#include <optional>
#include <stddef.h>

class Board final {
public:
    constexpr static size_t FIELD_SIZE = 10;
    constexpr static size_t AIM_NUMBER = 5;

    enum class Player : char {
        X = 'X',
        O = 'O'
    };

    enum class CellContent : char {
        X = 'X',
        O = 'O',
        EMPTY = '.'
    };

    enum class State : int {
        GAME = -1,
        DRAW = 0,
        XWIN = 1,
        OWIN = 2
    };

    explicit Board();
    ~Board() = default;
    Board(const Board &) = delete;
    Board &operator=(const Board &) = delete;

    struct Position {
        int x;
        int y;
    };

    bool can_move(Position) const;
    void move(Position);

    std::optional<Player> get_current_player() const;
    std::optional<Player> check_number_to_win_in_line(Position, int, int) const;
    State get_state() const;
    CellContent get_cell_content(Position) const;
private:
    size_t move_number;
    CellContent field[FIELD_SIZE][FIELD_SIZE];
};