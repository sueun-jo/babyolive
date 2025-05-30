#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include "cart.h"
#include <vector>
#include <string>

using namespace std;

class CartManager {
private:
    vector<Cart> items;

public:
    CartManager();
    ~CartManager();

    // 장바구니 관리 기능
    void addToCart(const string& userId, const string& productInfo);  // 장바구니에 상품 추가
    void removeFromCart(const string& userId, int index);            // 장바구니에서 상품 제거
    void clearCart(const string& userId);                           // 장바구니 비우기
    
    // 장바구니 조회
    void showUserCart(const string& userId) const;                  // 특정 사용자의 장바구니 표시
    Cart* findCartByUserId(const string& userId);                  // 사용자 ID로 장바구니 찾기
    
    // 데이터 관리
    bool saveAll() const;  // CSV 파일로 저장
    bool loadAll();        // CSV 파일에서 로드
};

#endif // CARTMANAGER_H 