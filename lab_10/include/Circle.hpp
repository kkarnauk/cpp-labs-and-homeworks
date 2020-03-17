#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int center_x, int center_y, int radius, const char* label);
    ~Circle() override;

    void print() const override;
    bool is_inside(int point_x, int point_y) const override;
    void zoom(int factor) override;

protected:
    int radius;
    char* label;
};
