#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
#include "StdioBoardView.h"

void StdioBoardView::process_incorrect_move() const {
    std::cout << "Bad move!" << std::endl;
}

bool is_number(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    if (!isdigit(str[0]) && str[0] != '-') {
        return false;
    }
    if (str[0] == '-' && str.size() == 1) {
        return false;
    }
    for (size_t i = 1; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> split(std::string str, const std::string &delimiter) {
    std::vector<std::string> splitted;
    std::stringstream stream;
    stream << str;
    std::string token;
    while (stream >> token) {
        splitted.push_back(token);
    }
    return splitted;
} 

std::optional<Board::Position> StdioBoardView::retrieve_next_position(const Board &board) {
    while (true) {
        std::optional<Board::Player> player = board.get_current_player();
        assert(player.has_value());
        std::cout << static_cast<char>(player.value()) << " move: ";

        std::string input;
        std::getline(std::cin, input);
        std::vector<std::string> numbers = split(input, " ");
        if (numbers.size() != 2 ||
            !is_number(numbers[0]) ||
            !is_number(numbers[1])) {
            
            process_incorrect_move();
            continue;
        }
        Board::Position pos = {std::stoi(numbers[0]), std::stoi(numbers[1])};
        if (pos.x == -1 && pos.y == -1) {
            return std::nullopt;
        }
        if (board.can_move(pos)) {
            return pos;
        }
        process_incorrect_move();
    }
}

void StdioBoardView::move(const Board &, Board::Position) {}

void StdioBoardView::print_board(const Board &board) const {
    std::cout << std::endl;
    for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
        for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
            std::cout << static_cast<char>(board.get_cell_content({static_cast<int>(x), static_cast<int>(y)}));
        }
        std::cout << std::endl;
    }
}

void StdioBoardView::end_game(const Board &board) const {
    Board::State state = board.get_state();
    if (state == Board::State::OWIN) {
        std::cout << "O wins!" << std::endl;
    } else if (state == Board::State::XWIN) {
        std::cout << "X wins!" << std::endl;
    } else {
        std::cout << "Draw." << std::endl;
    }
}