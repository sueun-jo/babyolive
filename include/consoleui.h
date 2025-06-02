#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include "productmanager.h"
#include "usermanager.h"
#include "cartmanager.h"

class ConsoleUI
{
public:
    ConsoleUI();

    void run(); //제일 첫 화면

    void showLoginUI(); //로그인 화면

    void showSignupUI(); // 회원가입 화면

    void showMemberUI(); // 회원 화면 -> 쇼핑몰로 연결

    void showAdminUI(); // 관리자 화면 -> 상품 등록, 상품 화면

    void showAdminProductManageUI(); // 상품관리 창

    void showAdminUserManageUI(); // 유저 관리 창

private:
    UserManager um;
    ProductManager pm;
    CartManager cm;
    void showAllProductsWithCart();
    void findProductWithCart();
    void askToAddToCart(Product* product);
    void showCurrentCart();
};

#endif // CONSOLEUI_H
