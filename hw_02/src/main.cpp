#include <iostream>
#include <memory>
#include <string.h>
#include "GameController.h"

int main(int argc, char *argv[]) {
    try {
        std::cin.exceptions(std::istream::failbit | std::istream::badbit);
        std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);

        std::unique_ptr<GameController> gc;   
        if (argc == 1) {
            gc = std::make_unique<GameController>(GameController::Mode::DEFAULT);
        } else if (strcmp(argv[1], "silent") == 0) {
            gc = std::make_unique<GameController>(GameController::Mode::SILENT);
        } else if (strcmp(argv[1], "curses") == 0) {
            gc = std::make_unique<GameController>(GameController::Mode::NCURSES);
        } else {
            throw std::logic_error(std::string("The argument \"") + argv[1] + "\" is unknown.");
        }
        gc->play_game();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        
        return -1;
    } catch (...) {
        std::cout << "Unknown error occured.";

        return -2;
    }

    return 0;
}