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

void CartManager::add() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    string productInfo;
    cout << "장바구니에 추가할 상품 정보를 입력하세요: ";
    getline(cin >> ws, productInfo);
    
    addToCart(productInfo);
}

void CartManager::update() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = find();
    if (!cart) {
        cout << "장바구니를 찾을 수 없습니다." << endl;
        return;
    }

    listAll();
    
    int index;
    cout << "수정할 상품 번호를 선택하세요: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > cart->products.size()) {
        cout << "잘못된 상품 번호입니다." << endl;
        return;
    }

    string newProductInfo;
    cout << "새로운 상품 정보를 입력하세요: ";
    getline(cin, newProductInfo);

    cart->removeProduct(index - 1);
    cart->addProduct(newProductInfo);
    saveAll();
}

void CartManager::remove() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = find();
    if (!cart) {
        cout << "장바구니를 찾을 수 없습니다." << endl;
        return;
    }

    listAll();
    
    int index;
    cout << "삭제할 상품 번호를 선택하세요: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > cart->products.size()) {
        cout << "잘못된 상품 번호입니다." << endl;
        return;
    }

    cart->removeProduct(index - 1);
    saveAll();
}

Cart* CartManager::find() {
    return findCartByUserId(currentUserId);
}

void CartManager::listAll() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = find();
    if (cart) {
        cart->showCart();
    } else {
        cout << "장바구니를 찾을 수 없습니다." << endl;
    }
}

void CartManager::addToCart(const string& productInfo) {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = findCartByUserId(currentUserId);
    if (!cart) {
        items.push_back(Cart(currentUserId));
        cart = &items.back();
    }
    cart->addProduct(productInfo);
    saveAll();
}

void CartManager::clearCart() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = find();
    if (cart) {
        cart->clearCart();
        saveAll();
    }
}

Cart* CartManager::findCartByUserId(const string& userId) {
    for (auto& cart : items) {
        if (cart.userId == userId) {
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