#include <stdexcept>
#include <assert.h>
#include "Board.h"

Board::Board() : 
    move_number{0} {

    for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
        for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
            field[x][y] = Board::CellContent::EMPTY;
        }
    }
}

bool Board::can_move(Board::Position pos) const {
    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= static_cast<int>(Board::FIELD_SIZE) ||
        pos.y >= static_cast<int>(Board::FIELD_SIZE) ||
        field[pos.x][pos.y] != Board::CellContent::EMPTY) {
        
        return false;
    }
    return true;
}

void Board::move(Board::Position pos) {
    assert(can_move(pos));
    std::optional<Board::Player> player = get_current_player();
    assert(player.has_value());
    if (player.value() == Board::Player::X) {
        field[pos.x][pos.y] = Board::CellContent::X;
    } else {
        field[pos.x][pos.y] = Board::CellContent::O;
    }
    move_number++;
}

std::optional<Board::Player> Board::get_current_player() const {
    if (move_number == Board::FIELD_SIZE * Board::FIELD_SIZE) {
        return std::nullopt;
    }
    else if (move_number % 2 == 0) {
        return Board::Player::O;
    } else {
        return Board::Player::X;
    }
}

Board::CellContent Board::get_cell_content(Board::Position pos) const {
    assert(pos.x >= 0 && pos.y >= 0);
    assert(pos.x < static_cast<int>(Board::FIELD_SIZE) && pos.y < static_cast<int>(Board::FIELD_SIZE));
    return field[pos.x][pos.y];
}

std::optional<Board::Player> Board::check_number_to_win_in_line(Board::Position pos, int dx, int dy) const {
    int cur_x = pos.x;
    int cur_y = pos.y;
    if (field[cur_x][cur_y] == Board::CellContent::EMPTY) {
        return std::nullopt;
    }
    for (size_t i = 0; i < Board::AIM_NUMBER; i++) {
        if (cur_x < 0 || cur_y < 0 ||
            cur_x >= static_cast<int>(Board::FIELD_SIZE) ||
            cur_y >= static_cast<int>(Board::FIELD_SIZE) ||
            field[cur_x][cur_y] == Board::CellContent::EMPTY ||
            field[cur_x][cur_y] != field[pos.x][pos.y]) {
            
            return std::nullopt;
        }
        cur_x += dx;
        cur_y += dy;
    }
    if (field[pos.x][pos.y] == Board::CellContent::X) {
        return Board::Player::X;
    } else {
        return Board::Player::O;
    }
}

Board::State Board::get_state() const {
    for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
        for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    std::optional<Board::Player> checked = check_number_to_win_in_line({static_cast<int>(x), static_cast<int>(y)}, dx, dy);
                    if (checked.has_value()) {
                        if (checked.value() == Board::Player::X) {
                            return Board::State::XWIN;
                        } else {
                            return Board::State::OWIN;
                        }
                    }
                }
            }
        }
    }
    if (move_number == Board::FIELD_SIZE * Board::FIELD_SIZE) {
        return Board::State::DRAW;
    }
    return Board::State::GAME;
}