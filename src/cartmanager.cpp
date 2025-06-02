#include "../include/cartmanager.h"
#include "../include/csvhandler.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

CartManager::CartManager() : currentUserId("") {
    loadFromFile();
}

CartManager::~CartManager() {
    saveToFile();
}

void CartManager::loadFromFile() {
    items = CsvHandler<Cart>::loadAll("carts.csv");
}

void CartManager::saveToFile() const {
    if (!CsvHandler<Cart>::saveAll(items, "carts.csv")) {
        cerr << "장바구니 저장에 실패했습니다." << endl;
    }
}

void CartManager::setCurrentUser(const string& userId) {
    currentUserId = userId;
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
/* 장바구니 update는 수정하지 않음*/
void CartManager::update() {
    // if (currentUserId.empty()) {
    //     cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
    //     return;
    // }

    // Cart* cart = find();
    // if (!cart) {
    //     cout << "장바구니를 찾을 수 없습니다." << endl;
    //     return;
    // }

    // listAll();
    
    // int index;
    // cout << "수정할 상품 번호를 선택하세요: ";
    // cin >> index;
    // cin.ignore();

    // if (index < 1 || index > cart->getProductCount()) {
    //     cout << "잘못된 상품 번호입니다." << endl;
    //     return;
    // }

    // string newProductInfo;
    // cout << "새로운 상품 정보를 입력하세요: ";
    // getline(cin, newProductInfo);

    // cart->removeProduct(index - 1);
    // cart->addProduct(newProductInfo);
    // saveToFile();
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

    if (index < 1 || index > cart->getProductCount()) {
        cout << "잘못된 상품 번호입니다." << endl;
        return;
    }

    cart->removeProduct(index - 1);
    saveToFile();
    cout << "상품이 삭제되었습니다." << endl;
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
    saveToFile();
    cout << "상품이 장바구니에 추가되었습니다." << endl;
}

void CartManager::clearCart() {
    if (currentUserId.empty()) {
        cout << "오류: 현재 사용자가 설정되지 않았습니다." << endl;
        return;
    }

    Cart* cart = find();
    if (cart) {
        cart->clear();
        saveToFile();
        cout << "장바구니가 비워졌습니다." << endl;
    }
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

Cart* CartManager::find() {
    return findCartByUserId(currentUserId);
}

Cart* CartManager::findCartByUserId(const string& userId) {
    for (auto& cart : items) {
        if (cart.matchUserId(userId)) {
            return &cart;
        }
    }
    return nullptr;
} 