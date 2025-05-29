#include "consoleui.h"
#include <iostream>

using namespace std;

consoleUI::consoleUI() {
    ProductManager pm;
} //기본 생성자

/*화면 초기화*/
void consoleUI::clearScreen(){
    cout << "\033[2J\033[1;1H";
    return;
}

/*ui첫 시작점 진입*/
void consoleUI::run(){

    while(true){

        clearScreen();

        cout << "=====================================\n";
        cout << "          [Baby Olive Mall]          \n";
        cout << "=====================================\n";
        cout << "  1. 로그인\n";
        cout << "  2. 회원가입\n";
        cout << "  0. 종료하기\n";
        cout << "-------------------------------------\n";
        cout << "  선택: ";

        int choice;
        cin >> choice; //어디로 들어갈건지 보여줌

        switch (choice){
        case 1: showLoginUI(); break;
        case 2: showSignupUI(); break;
        case 0: return; break;
        default : cout << "잘못된 접근입니다. 올바른 번호를 선택해주세요." << endl;
        }
    }

}


/*로그인 화면*/
void consoleUI::showLoginUI(){

}

/*회원가입 화면*/
void showSignupUI(){
    cout << "sigup ui" << endl;
}

/*멤버 ui -> 쇼핑몰 이용할 수 있음*/
void showMemberUI(); // 회원 화면 -> 쇼핑몰로 연결

/*관리자 ui -> 상품 등록, 유저 등록 관리*/
void showAdminUI(); // 관리자 화면 -> 상품 등록, 상품 화면
