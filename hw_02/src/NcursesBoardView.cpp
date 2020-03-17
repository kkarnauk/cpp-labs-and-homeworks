#include <algorithm>
#include <ncurses.h>
#include <assert.h>
#include "NcursesBoardView.h"

const size_t RESULT_LINE = Board::FIELD_SIZE + 1;
const size_t INFO_LINE = RESULT_LINE + 2;

enum class FColor : int {
    X = 1,
    O = 2,
    NEUTRAL = 3,
    MARKED = 4,
    RESULT = 5,
    BACKGROUND = 6
};

enum class Mark : int {
    PUSH = 0,
    PULL = 1
};

NcursesBoardView::NcursesBoardView() :
    BoardView{}, cur_pos{0, 0}, is_field_drawn{false} {

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    init_pair(static_cast<short>(FColor::X), COLOR_CYAN, COLOR_BLACK);
    init_pair(static_cast<short>(FColor::O), COLOR_YELLOW, COLOR_BLACK);
    init_pair(static_cast<short>(FColor::NEUTRAL), COLOR_WHITE, COLOR_BLACK);
    init_pair(static_cast<short>(FColor::MARKED), COLOR_RED, COLOR_BLACK);
    init_pair(static_cast<short>(FColor::RESULT), COLOR_GREEN, COLOR_BLACK);
    init_pair(static_cast<short>(FColor::BACKGROUND), -1, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(static_cast<int>(FColor::BACKGROUND)));
}

NcursesBoardView::~NcursesBoardView() {
    endwin();
}

void redraw_symbol(Board::Position pos, Mark mark) {
    char symbol = static_cast<char>(mvinch(pos.x, pos.y));
    FColor color;
    if (mark == Mark::PUSH) {
        color = FColor::MARKED;
    } else {
        if (symbol == 'X') {
            color = FColor::X;
        } else if (symbol == 'O') {
            color = FColor::O;
        } else {
            color = FColor::NEUTRAL;
        }
    }
    attron(COLOR_PAIR(static_cast<int>(color)));
    mvwprintw(stdscr, pos.x, pos.y, "%c", symbol);
    refresh();
}

void print_state(const Board &board) {
    Board::State state = board.get_state();
    if (state == Board::State::GAME) {
        std::optional<Board::Player> player = board.get_current_player();
        assert(player.has_value());
        if (player == Board::Player::X) {
            attron(COLOR_PAIR(static_cast<int>(FColor::X)));
        } else {
            attron(COLOR_PAIR(static_cast<int>(FColor::O)));
        }
        mvwprintw(stdscr, RESULT_LINE, 0, "%c move", static_cast<char>(player.value()));
    } else {
        move(RESULT_LINE, 0);
        clrtobot();

        attron(COLOR_PAIR(static_cast<int>(FColor::RESULT)));
        if (state == Board::State::XWIN) {
            mvwprintw(stdscr, RESULT_LINE, 0, "X wins!");
        } else if (state == Board::State::OWIN) {
            mvwprintw(stdscr, RESULT_LINE, 0, "O wins!");
        } else {
            mvwprintw(stdscr, RESULT_LINE, 0, "Draw.");
        }
        attron(COLOR_PAIR(static_cast<int>(FColor::NEUTRAL)));
        printw("\n\nPress any key to exit");
    }
    refresh();
}

std::optional<Board::Position> NcursesBoardView::retrieve_next_position(const Board &board) {
    while (true) {
        int command = getch();
        if (KEY_DOWN <= command && command <= KEY_RIGHT) {
            redraw_symbol(cur_pos, Mark::PULL);

            if (command == KEY_RIGHT) {
                cur_pos.y = std::min<int>(cur_pos.y + 1, Board::FIELD_SIZE - 1);
            } else if (command == KEY_DOWN) {
                cur_pos.x = std::min<int>(cur_pos.x + 1, Board::FIELD_SIZE - 1);
            } else if (command == KEY_LEFT) {
                cur_pos.y = std::max(cur_pos.y - 1, 0);
            } else if (command == KEY_UP) {
                cur_pos.x = std::max(cur_pos.x - 1, 0);
            }

            redraw_symbol(cur_pos, Mark::PUSH);
        }
        else if (command == ' ') {
            if (board.get_cell_content(cur_pos) == Board::CellContent::EMPTY) {
                return cur_pos;
            } 
        } else if (command == 'x') {
            return std::nullopt;
        } 
    }
}

void NcursesBoardView::move(const Board &board, Board::Position pos) {
    std::optional<Board::Player> player = board.get_current_player();
    assert(player.has_value());
    char player_ch = static_cast<char>(player.value());
    mvwprintw(stdscr, pos.x, pos.y, "%c", player_ch);
    redraw_symbol(pos, Mark::PUSH);
}

void NcursesBoardView::print_board(const Board &board) const {
    if (!is_field_drawn) {
        attron(COLOR_PAIR(static_cast<int>(FColor::NEUTRAL)));
        for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
            for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
                printw(".");
            }
            printw("\n");
        }
        redraw_symbol({0, 0}, Mark::PUSH);

        mvinch(INFO_LINE, 0);
        attron(COLOR_PAIR(static_cast<int>(FColor::NEUTRAL)));
        printw("Use <-> to move within the field!");
        printw("\nUse Space to make a move!");
        printw("\nUse \"X\" to exit!\n");
        print_state(board);
        refresh();

        is_field_drawn = true;
    } else {
        print_state(board);
    }
}

void NcursesBoardView::end_game(const Board &board) const {
    Board::State state = board.get_state();
    if (state == Board::State::DRAW) {
        getch();
        return;
    }
    char winner = (state == Board::State::XWIN ? 'X' : 'O');
    for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
        for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    if (board.check_number_to_win_in_line({static_cast<int>(x), static_cast<int>(y)}, dx, dy).has_value()) {
                        attron(COLOR_PAIR(static_cast<int>(FColor::MARKED)));
                        for (size_t i = 0; i < Board::AIM_NUMBER; i++) {
                            mvwprintw(stdscr, x, y, "%c", winner);
                            x += dx;
                            y += dy;
                        }
                        getch();
                        return;
                    }
                }
            }
        }
    }
    assert(false);
}