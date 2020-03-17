#include <cstring>
#include <stdio.h>

#include "Circle.hpp"

Circle::Circle(int id, int center_x, int center_y, int radius, const char* label_):
        Figure(id, center_x, center_y), radius(radius) {
    label = new char[strlen(label_) + 1];
    strcpy(label, label_);
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, center_x, center_y, radius, label);
}

bool Circle::is_inside(int point_x, int point_y) const {
    long long dx = center_x - point_x;
    long long dy = center_y - point_y;
    return dx * dx + dy * dy <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}