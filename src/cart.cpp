#include "../include/cart.h"
#include <iostream>
#include <sstream>

using namespace std;


Cart::Cart(const std::string& id) : userId(id) {}


void Cart::addProduct(const std::string& product) {
    cartProducts.push_back(product);
}

void Cart::removeProduct(size_t index) {
    if (index < cartProducts.size()) {
        cartProducts.erase(cartProducts.begin() + index);
    }
}

void Cart::clear() {
    cartProducts.clear();
}

void Cart::showCart() const {
    std::cout << "\n장바구니 내용:\n";
    std::cout << "-------------------------------------\n";
    if (cartProducts.empty()) {
        std::cout << "장바구니가 비어있습니다.\n";
        return;
    }
    
    for (size_t i = 0; i < cartProducts.size(); ++i) {
        std::cout << i + 1 << ". " << cartProducts[i] << "\n";
    }
    std::cout << "-------------------------------------\n";
}

bool Cart::matchUserId(const std::string& id) const {
    return userId == id;
}

size_t Cart::getProductCount() const {
    return cartProducts.size();
}

const std::vector<std::string>& Cart::getProducts() const {
    return cartProducts;
}

std::string Cart::toCSVRow() const {
    std::ostringstream oss;
    oss << userId;
    
    if (!cartProducts.empty()) {
        oss << ",";
        for (size_t i = 0; i < cartProducts.size(); ++i) {
            if (i > 0) oss << "|";
            oss << cartProducts[i];
        }
    }
    
    return oss.str();
} 