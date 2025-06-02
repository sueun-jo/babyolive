#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include "manager.h"
#include "cart.h"
#include <string>

class CartManager : public Manager<Cart> {
private:
    std::string currentUserId;

public:
    CartManager();
    ~CartManager();
    
    // Manager 추상 클래스의 순수 가상 함수 구현
    void add() override;        // 장바구니에 상품 추가 (addToCart 기능)
    void update() override;     // 장바구니 상품 정보 수정
    void remove() override;     // 장바구니에서 상품 제거
    Cart* find() override;      // 현재 사용자의 장바구니 찾기
    void listAll() override;    // 장바구니 내용 표시

    // 파일 입출력 구현
    void loadFromFile() override;
    void saveToFile() const override;
    
    // 사용자 관련
    void setCurrentUser(const std::string& userId);
    Cart* findCartByUserId(const std::string& userId);
    
    // 장바구니 관련 추가 기능
    void clearCart();           // 장바구니 비우기
    void addToCart(const std::string& productInfo);  // add()의 실제 구현에서 사용
};

#endif // CARTMANAGER_H 