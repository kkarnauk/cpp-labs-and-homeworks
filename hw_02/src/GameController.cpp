#include <ncurses.h>
#include <memory>
#include "GameController.h"

GameController::GameController(Mode _mode) :
    mode{_mode} {}

void GameController::play_game() {
    Board board;
    std::unique_ptr<BoardView> board_view;
    if (mode != GameController::Mode::NCURSES) {
        board_view = std::make_unique<StdioBoardView>();
    } else {
        board_view = std::make_unique<NcursesBoardView>();
    }

    if (mode != GameController::Mode::SILENT) {
        board_view->print_board(board);
    }

    while (true) {
        std::optional<Board::Position> pos = board_view->retrieve_next_position(board);
        if (!pos.has_value()) {
            break;
        }
        board_view->move(board, pos.value());
        board.move(pos.value());
        if (board.get_state() == Board::State::GAME) {
            if (mode != GameController::Mode::SILENT) {
                board_view->print_board(board);
            }
            continue;
        } 
        board_view->print_board(board);
        board_view->end_game(board);
        break;
    }
}