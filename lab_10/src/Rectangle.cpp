#include <stdio.h>
#include <cmath>

#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int center_x, int center_y, int width, int height) :
    Figure(id, center_x, center_y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, center_x, center_y, width, height);
} 

bool Rectangle::is_inside(int point_x, int point_y) const {
    return abs(point_x - center_x) <= width / 2 && abs(point_y - center_y) <= height / 2;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}