#include "Test.h"
#include "Board.h"

class BoardTest final : public Test {
public:
    explicit BoardTest() = default;
    ~BoardTest() = default;
    BoardTest(const BoardTest &) = delete;
    BoardTest &operator=(const BoardTest &) = delete;

    void run_all_tests() override;
private:
    void test_incorrect_move_outside_field_up();
    void test_incorrect_move_outside_field_right();
    void test_incorrect_move_outside_field_down();
    void test_incorrect_move_outside_field_left();
    void test_incorrect_move_the_same_point();
    void test_correct_move();
    void test_check_with_deltas_x_result();
    void test_check_with_deltas_o_result();
    void test_check_with_deltas_game_result();
    void test_x_wins_result();
    void test_o_wins_result();
    void test_win_in_row();
    void test_win_in_column();
    void test_win_in_diagonal();
    void test_draw_result();
    void test_game_result();
    void test_get_current_player_end_of_game();
    void test_get_current_player_x();
    void test_get_current_player_o();
    void test_get_current_player_immediately();
    void test_get_cell_content_o();
    void test_get_cell_content_x();
    void test_get_cell_content_empty();
};