#pragma once

class Figure {
public:
    Figure(int id, int center_x, int center_y);
    virtual ~Figure() = default;

    virtual void print() const = 0;
    virtual bool is_inside(int point_x, int point_y) const = 0;
    virtual void zoom(int factor) = 0;
    void move(int new_x, int new_y);
    int get_id() const;

protected:
    int id;
    int center_x;
    int center_y;
};
