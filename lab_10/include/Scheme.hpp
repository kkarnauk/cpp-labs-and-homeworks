#pragma once

#include "Figure.hpp"

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures() const;
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int point_x, int point_y) const; // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

private:
    Figure** figures_; // размер массива задается в конструкторе и больше не растет
    int last_;
    int capacity_;

    Figure* find_by_id(int id);
};
