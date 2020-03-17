#include <iostream>
#include <algorithm>
#include <string.h>
#include "my_vector.h"
#include "tests.h"

namespace product {

class Product final {
public:
    Product(const char*, int, double);
    Product(const Product&);
    Product(Product&&) noexcept;
    Product& operator=(const Product&);
    Product& operator=(Product&&) noexcept;
    ~Product();

    bool operator==(const Product&);

    friend std::ostream& operator<<(std::ostream& out, const Product&);

private:
    char *name_;
    int quantity_;
    double price_;
};

Product::Product(const char* name, int quantity, double price) :
    quantity_{quantity}, price_{price} {
    
    name_ = new char[strlen(name) + 1];
    strcpy(name_, name);
}

Product::Product(const Product& other) :
    Product{other.name_, other.quantity_, other.price_} {}

Product::Product(Product&& other) noexcept :
    name_{nullptr} {
    
    *this = std::move(other);
}

Product& Product::operator=(const Product& other) {
    if (this == &other) {
        return *this;
    }
    Product other_cpy(other);
    return (*this = std::move(other_cpy));
} 

Product& Product::operator=(Product&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    std::swap(name_, other.name_);
    std::swap(quantity_, other.quantity_);
    std::swap(price_, other.price_);

    return *this;
}

Product::~Product() {
    delete[] name_;
}

bool Product::operator==(const Product& other) {
    return (quantity_ == other.quantity_ && price_ == other.price_ &&
            strcmp(name_, other.name_) == 0);
}

std::ostream& operator<<(std::ostream& out, const Product& prod) {
    return out << prod.name_ << " " << prod.quantity_ << " " << prod.price_;
}

}  // namespace product


int main() {
    my_vector::test::test<int>(5, 10);
    my_vector::test::test<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    my_vector::test_default_consructible::test<int>(10);

    return 0;
}


#include "my_vector_impl.h"