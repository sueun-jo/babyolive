#ifndef CARTMANAGER_H
#define CARTMANAGER_H

#include "cart.h"
#include "manager.h"
#include <vector>
#include <string>

using namespace std;

class CartManager : public Manager<Cart> {
private:
    string currentUserId;  // 현재 로그인한 사용자 ID

public:
    CartManager();
    ~CartManager();

    // Manager 추상 클래스의 순수 가상 함수 구현
    void add() override;             // 현재 사용자의 장바구니에 상품 추가
    void update() override;          // 현재 사용자의 장바구니 상품 수정
    void remove() override;          // 현재 사용자의 장바구니에서 상품 제거
    Cart* find() override;           // 현재 사용자의 장바구니 찾기
    void listAll() override;         // 현재 사용자의 장바구니 내용 표시

    // 추가 기능
    void setCurrentUser(const string& userId) { currentUserId = userId; }
    void addToCart(const string& productInfo);  // 현재 사용자의 장바구니에 상품 추가
    void clearCart();                           // 현재 사용자의 장바구니 비우기
    Cart* findCartByUserId(const string& userId);  // 특정 사용자의 장바구니 찾기
    
    // 데이터 관리
    bool saveAll() const;  // CSV 파일로 저장
    bool loadAll();        // CSV 파일에서 로드
};

#endif // CARTMANAGER_H 