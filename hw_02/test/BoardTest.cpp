#include "BoardTest.h"
#include <string>

void get_draw_board(Board &b) {
    std::string result;
    for (int i = 0; i < 5; i++) {
        result += "XXOOXXOOXXOOXXOOXXOO";
    }
    for (size_t i = 0; i < Board::FIELD_SIZE * Board::FIELD_SIZE; i++) {
        char player = static_cast<char>(b.get_current_player().value());
        for (size_t x = 0; x < Board::FIELD_SIZE; x++) {
            for (size_t y = 0; y < Board::FIELD_SIZE; y++) {
                if (result[x * Board::FIELD_SIZE + y] == player && b.can_move({(int)x, (int)y})) {
                    b.move({(int)x, (int)y});
                    x = Board::FIELD_SIZE;
                    break;
                }
            }
        }
    }
}

void BoardTest::test_incorrect_move_outside_field_up() {
    Board b;
    DO_CHECK(!b.can_move({-1, 0}));
}

void BoardTest::test_incorrect_move_outside_field_right() {
    Board b;  
    DO_CHECK(!b.can_move({0, Board::FIELD_SIZE}));
}

void BoardTest::test_incorrect_move_outside_field_down() {
    Board b;
    DO_CHECK(!b.can_move({Board::FIELD_SIZE, 0}));
}

void BoardTest::test_incorrect_move_outside_field_left() {
    Board b;
    DO_CHECK(!b.can_move({0, -1}));
}

void BoardTest::test_incorrect_move_the_same_point() {
    Board b;
    b.move({0, 0});
    b.move({1, 0});
    DO_CHECK(!b.can_move({0, 0}));
}

void BoardTest::test_correct_move() {
    Board b;
    b.move({9, 9});
    b.move({7, 5});
    b.move({3, 2});
    DO_CHECK(b.can_move({7, 3}));
}

void BoardTest::test_check_with_deltas_x_result() {
    Board b;
    b.move({0, 0});
    for (int i = 0; i < 4; i++) {
        b.move({1, i});
        b.move({2, i});
    }
    b.move({1, 4});
    std::optional<Board::Player> checked = b.check_number_to_win_in_line({1, 0}, 0, 1); 
    DO_CHECK(checked.has_value() && checked.value() == Board::Player::X);
}

void BoardTest::test_check_with_deltas_o_result() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({0, i});
        b.move({1, i});
    }
    b.move({0, 4});
    std::optional<Board::Player> checked = b.check_number_to_win_in_line({0, 0}, 0, 1); 
    DO_CHECK(checked.has_value() && checked.value() == Board::Player::O);
}

void BoardTest::test_check_with_deltas_game_result() {
    Board b;
    for (int i = 0; i < 5; i++) {
        b.move({0, 2 * i});
        b.move({i, i + 1});
    }
    std::optional<Board::Player> checked = b.check_number_to_win_in_line({2, 2}, 1, 1); 
    DO_CHECK(!checked.has_value());
}

void BoardTest::test_x_wins_result() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({0, i});
        b.move({1, i});
    }
    b.move({2, 4});
    b.move({1, 4});
    DO_CHECK(b.get_state() == Board::State::XWIN);
}

void BoardTest::test_o_wins_result() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({0, i});
        b.move({1, i});
    }
    b.move({0, 4});
    DO_CHECK(b.get_state() == Board::State::OWIN);
}

void BoardTest::test_game_result() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({0, i});
        b.move({1, i});
    }
    DO_CHECK(b.get_state() == Board::State::GAME);
}

void BoardTest::test_win_in_row() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({9, i});
        b.move({2, i});
    }
    b.move({9, 4});
    DO_CHECK(b.get_state() == Board::State::OWIN);
}

void BoardTest::test_win_in_column() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({i, 0});
        b.move({i, 1});
    }
    b.move({4, 0});
    DO_CHECK(b.get_state() == Board::State::OWIN);
}

void BoardTest::test_win_in_diagonal() {
    Board b;
    for (int i = 0; i < 4; i++) {
        b.move({i, i});
        b.move({1 + i, i});
    }
    b.move({4, 4});
    DO_CHECK(b.get_state() == Board::State::OWIN);
}

void BoardTest::test_draw_result() {
    Board b;
    get_draw_board(b);
    DO_CHECK(b.get_state() == Board::State::DRAW);
}

void BoardTest::test_get_current_player_end_of_game() {
    Board b;
    get_draw_board(b);
    std::optional<Board::Player> player = b.get_current_player();
    DO_CHECK(!player.has_value());
}

void BoardTest::test_get_current_player_x() {
    Board b;
    b.move({0, 0});
    b.move({1, 0});
    b.move({2, 0});
    std::optional<Board::Player> player = b.get_current_player();
    DO_CHECK(player.has_value() && player.value() == Board::Player::X);
}

void BoardTest::test_get_current_player_o() {
    Board b;
    b.move({0, 0});
    b.move({1, 0});
    std::optional<Board::Player> player = b.get_current_player();
    DO_CHECK(player.has_value() && player.value() == Board::Player::O);
}

void BoardTest::test_get_current_player_immediately() {
    Board b;
    std::optional<Board::Player> player = b.get_current_player();
    DO_CHECK(player.has_value() && player.value() == Board::Player::O);
}

void BoardTest::test_get_cell_content_o() {
    Board b;
    b.move({0, 0});
    b.move({9, 0});
    DO_CHECK(b.get_cell_content({0, 0}) == Board::CellContent::O);
}

void BoardTest::test_get_cell_content_x() {
    Board b;
    b.move({0, 0});
    b.move({9, 0});
    DO_CHECK(b.get_cell_content({9, 0}) == Board::CellContent::X);
}

void BoardTest::test_get_cell_content_empty() {
    Board b;
    b.move({0, 0});
    b.move({9, 0});
    DO_CHECK(b.get_cell_content({3, 8}) == Board::CellContent::EMPTY);
}

void BoardTest::run_all_tests() {
    test_incorrect_move_outside_field_up();
    test_incorrect_move_outside_field_right();
    test_incorrect_move_outside_field_down();
    test_incorrect_move_outside_field_left();
    test_incorrect_move_the_same_point();
    test_correct_move();
    test_check_with_deltas_x_result();
    test_check_with_deltas_o_result();
    test_check_with_deltas_game_result();
    test_x_wins_result();
    test_o_wins_result();
    test_win_in_row();
    test_win_in_column();
    test_win_in_diagonal();
    test_draw_result();
    test_game_result();
    test_get_current_player_end_of_game();
    test_get_current_player_x();
    test_get_current_player_o();
    test_get_current_player_immediately();
    test_get_cell_content_o();
    test_get_cell_content_x();
    test_get_cell_content_empty();
}