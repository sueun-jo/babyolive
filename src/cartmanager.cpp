#include "../include/cartmanager.h"
#include "../include/csvhandler.h"
#include <iostream>

using namespace std;

CartManager::CartManager() {
    loadAll();
}

CartManager::~CartManager() {
    saveAll();
}

void CartManager::addToCart(const string& userId, const string& productInfo) {
    Cart* cart = findCartByUserId(userId);
    if (!cart) {
        // 사용자의 장바구니가 없으면 새로 생성
        items.push_back(Cart(userId));
        cart = &items.back();
    }
    cart->addProduct(productInfo);
    saveAll();
}

void CartManager::removeFromCart(const string& userId, int index) {
    Cart* cart = findCartByUserId(userId);
    if (cart) {
        cart->removeProduct(index);
        saveAll();
    }
}

void CartManager::clearCart(const string& userId) {
    Cart* cart = findCartByUserId(userId);
    if (cart) {
        cart->clearCart();
        saveAll();
    }
}

void CartManager::showUserCart(const string& userId) const {
    for (const auto& cart : items) {
        if (cart.getUserId() == userId) {
            cart.showCart();
            return;
        }
    }
    cout << "장바구니를 찾을 수 없습니다." << endl;
}

Cart* CartManager::findCartByUserId(const string& userId) {
    for (auto& cart : items) {
        if (cart.getUserId() == userId) {
            return &cart;
        }
    }
    return nullptr;
}

bool CartManager::saveAll() const {
    return csvHandler<Cart>::saveAll(items, "carts.csv");
}

bool CartManager::loadAll() {
    items = csvHandler<Cart>::loadAll("carts.csv");
    return true;
} 