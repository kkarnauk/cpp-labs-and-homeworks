#include "BoardView.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"

class GameController final {
public:
    enum class Mode {
        DEFAULT = 0,
        SILENT = 1,
        NCURSES = 2
    };

    explicit GameController(Mode);
    ~GameController() = default;
    GameController(const GameController &) = delete;
    GameController &operator=(const GameController &) = delete;
    
    void play_game();

private:
    Mode mode;
};