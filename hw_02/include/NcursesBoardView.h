#include "BoardView.h"

class NcursesBoardView final : public BoardView {
public:
    explicit NcursesBoardView();
    ~NcursesBoardView();
    NcursesBoardView(const NcursesBoardView &) = delete;
    NcursesBoardView &operator=(const NcursesBoardView &) = delete;

    std::optional<Board::Position> retrieve_next_position(const Board &) override;
    void move(const Board &, Board::Position) override;
    void print_board(const Board &) const override;
    void end_game(const Board &) const override;
private:
    Board::Position cur_pos;
    mutable bool is_field_drawn;
};