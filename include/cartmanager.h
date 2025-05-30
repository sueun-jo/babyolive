#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include "manager.h"
#include "cart.h"
#include "csvhandler.h"
#include <iostream>

class CartManager : public Manager<Cart> {
private:
    string currentUserId;

public:
    CartManager() : currentUserId("") {}
    
    void setCurrentUser(const string& userId) { currentUserId = userId; }
    
    void addToCart(const string& productInfo) {
        for (auto& cart : items) {
            if (cart.matchUserId(currentUserId)) {
                cart.addProduct(productInfo);
                saveToFile();
                return;
            }
        }
        
        // 사용자의 장바구니가 없으면 새로 생성
        Cart newCart(currentUserId);
        newCart.addProduct(productInfo);
        items.push_back(newCart);
        saveToFile();
    }
    
    void remove() {
        for (auto& cart : items) {
            if (cart.matchUserId(currentUserId)) {
                cout << "\n삭제할 상품 번호를 입력하세요: ";
                size_t index;
                cin >> index;
                cin.ignore();
                
                if (index > 0 && index <= cart.getProductCount()) {
                    cart.removeProduct(index - 1);
                    saveToFile();
                    cout << "상품이 삭제되었습니다." << endl;
                } else {
                    cout << "잘못된 상품 번호입니다." << endl;
                }
                return;
            }
        }
    }
    
    void clearCart() {
        for (auto& cart : items) {
            if (cart.matchUserId(currentUserId)) {
                cart.clear();
                saveToFile();
                cout << "장바구니가 비워졌습니다." << endl;
                return;
            }
        }
    }
    
    void listAll() const override {
        bool found = false;
        for (const auto& cart : items) {
            if (cart.matchUserId(currentUserId)) {
                found = true;
                const auto& products = cart.getProducts();
                if (products.empty()) {
                    cout << "\n장바구니가 비어있습니다." << endl;
                } else {
                    cout << "\n현재 장바구니 내용:" << endl;
                    for (size_t i = 0; i < products.size(); ++i) {
                        cout << i + 1 << ". " << products[i] << endl;
                    }
                }
                break;
            }
        }
        
        if (!found) {
            cout << "\n장바구니가 비어있습니다." << endl;
        }
    }
    
    void loadFromFile() override {
        items = csvHandler<Cart>::loadAll("carts.csv");
    }
    
    void saveToFile() const override {
        csvHandler<Cart>::saveAll(items, "carts.csv");
    }
};

#endif // CARTMANAGER_H 