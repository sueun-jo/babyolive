#ifndef CART_H
#define CART_H

#include <string>
#include <vector>

using namespace std;

class Cart {
private:
    string userId;              // 장바구니 소유자 ID
    vector<string> products;    // 담은 상품 목록

    friend class CartManager;   // CartManager가 private 멤버에 접근할 수 있도록 함

public:
    Cart();
    Cart(const string& userId);
    ~Cart();

    // 장바구니 기본 기능
    void addProduct(const string& productInfo);    // 상품 추가
    void removeProduct(int index);                 // 상품 제거
    void clearCart();                             // 장바구니 비우기
    void showCart() const;                        // 장바구니 내용 표시
    
    // CSV 변환
    string toCSVRow() const;    // CSV 저장용 문자열 변환
};

#endif // CART_H 