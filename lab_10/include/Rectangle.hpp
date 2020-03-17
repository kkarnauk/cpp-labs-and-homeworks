#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int center_x, int center_y, int width, int height);
    ~Rectangle() = default;

    void print() const override;
    bool is_inside(int point_x, int point_y) const override;
    void zoom(int factor) override;
    
protected:
    int width;
    int height;
};
