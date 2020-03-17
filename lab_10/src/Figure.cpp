#include "Figure.hpp"

Figure::Figure(int id, int center_x, int center_y) :
    id(id), center_x(center_x), center_y(center_y) {}

void Figure::move(int new_x, int new_y) {
    center_x = new_x;
    center_y = new_y;
}

int Figure::get_id() const {
    return id;
}