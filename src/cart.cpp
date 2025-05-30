#include "../include/cart.h"
#include <iostream>
#include <sstream>

using namespace std;

Cart::Cart() {}

Cart::Cart(const string& userId) : userId(userId) {}

Cart::~Cart() {}

void Cart::addProduct(const string& productInfo) {
    products.push_back(productInfo);
    cout << "장바구니에 상품이 추가되었습니다." << endl;
}

void Cart::removeProduct(int index) {
    if (index >= 0 && index < products.size()) {
        products.erase(products.begin() + index);
        cout << "상품이 장바구니에서 제거되었습니다." << endl;
    }
}

void Cart::clearCart() {
    products.clear();
    cout << "장바구니가 비워졌습니다." << endl;
}

void Cart::showCart() const {
    cout << "\n=== " << userId << "님의 장바구니 ===\n";
    if (products.empty()) {
        cout << "장바구니가 비어있습니다." << endl;
        return;
    }

    for (size_t i = 0; i < products.size(); ++i) {
        cout << (i + 1) << ". " << products[i] << endl;
    }
    cout << "========================\n";
}

string Cart::toCSVRow() const {
    ostringstream oss;
    oss << userId;
    
    if (!products.empty()) {
        oss << ",";
        for (size_t i = 0; i < products.size(); ++i) {
            if (i > 0) oss << "|";
            oss << products[i];
        }
    }
    
    return oss.str();
} 