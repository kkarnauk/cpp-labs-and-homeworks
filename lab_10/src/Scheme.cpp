#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <cassert>

#include "Scheme.hpp"

Scheme::Scheme(int capacity) :
        last_(0), capacity_(capacity) {
    figures_ = new Figure*[capacity]();
}

Scheme::~Scheme() {
    for (int i = 0; i < capacity_; i++) {
        delete figures_[i];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    figures_[last_] = fg;
    last_++;
}

Figure* Scheme::find_by_id(int id) {
    for (int i = 0; i < last_; i++) {
            if (figures_[i]->get_id() == id) {
                return figures_[i];
            }
    }
    return nullptr;
}

void Scheme::remove_figure(int id) {
    for (int i = 0; i < last_ - 1; i++) {
        if (figures_[i]->get_id() == id) {
            std::swap(figures_[i], figures_[i + 1]);
        }
    }
    if (figures_[last_ - 1]->get_id() == id) {
        delete figures_[last_ - 1];
        figures_[last_ - 1] = nullptr;
        last_--;
    }
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < last_; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    Figure* fig = find_by_id(id);
    if (fig != nullptr) {
        fig->zoom(factor);
    }
}

Figure* Scheme::is_inside_figure(int point_x, int point_y) const {
    for (int i = 0; i < last_; i++) {
        if (figures_[i]->is_inside(point_x, point_y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    Figure* fig = find_by_id(id);
    if (fig != nullptr) {
        fig->move(new_x, new_y);
    }
}