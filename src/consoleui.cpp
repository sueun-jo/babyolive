#include "../include/consoleui.h"
#include "../include/util.h"
#include "../include/usermanager.h"
#include <iostream>
#include <string>
#include <regex>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::regex_match;

consoleUI::consoleUI() {
    // 파일에서 데이터 로드
    um.loadFromFile();
    pm.loadFromFile();
    cm.loadFromFile();
} //기본 생성자


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
        case 0: exit(0); break;
        default : pauseForUser(); break;
        }
    }
}


/*로그인 화면*/
void consoleUI::showLoginUI(){
    while (true){
        clearScreen();
        string inputid, inputpw;
        cout << "=====================================\n";
        cout << "              [Log in]               \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "-------------------------------------\n";
        cout << "  ID: "; cin >> inputid;
        
        if (inputid[0] == '0') exit(0);
        else if (inputid[0] == '1') return;

        cout << "  PW: "; cin >> inputpw;
        cout << "-------------------------------------\n";

        // authenticate 메서드로 한 번에 ID와 비밀번호 검증
        User* user = um.authenticate(inputid, inputpw);
        if (user) {
            cout << "\n=== 로그인한 사용자 정보 ===\n";
            user->showUserInfo();
            cout << "계속하려면 enter를 입력하세요.";
            cin.get();
            
            // 장바구니 매니저에 현재 사용자 ID 설정
            cm.setCurrentUser(inputid);
            
            if (user->isAdminUser()) {
                showAdminUI();
            } else {
                showMemberUI(); 
            }
        } else {
            cout << "로그인 실패!" << endl;
            cout << "계속하려면 enter를 입력하세요.\n";
            cin.ignore(); cin.get();
        }
    }
}

/*회원가입 화면*/
void consoleUI::showSignupUI(){
    while(true){
    clearScreen();
        
        cout << "=====================================\n";
        cout << "             [Sign Up]               \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "  2. 회원가입\n";
        cout << "-------------------------------------\n";

        int choice;
        cout << "선택: "; cin >> choice;

        switch (choice){
            case 0: exit(0); break;
            case 1: return; break;
            case 2: um.add(); break;
            default: pauseForUser(); break;
        }
    }
}

/*멤버 ui -> 쇼핑몰 이용할 수 있음*/
void consoleUI::showMemberUI(){
    while (true) {
        clearScreen();
        
        cout << "=====================================\n";
        cout << "         [Member Shopping]           \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "  2. 상품 전체 보기\n";
        cout << "  3. 상품 찾기\n";
        cout << "  4. 장바구니 보기\n";
        cout << "-------------------------------------\n";
        cout << "  선택: ";

        int choice;
        cin >> choice; cin.ignore();

        switch (choice) {
            case 0: exit(0); break;
            case 1: return; break;
            case 2: showAllProductsWithCart(); break;
            case 3: findProductWithCart(); break;
            case 4: showCurrentCart(); break;
            default: pauseForUser(); break;
        }
    }
}

void consoleUI::showAllProductsWithCart() {
    pm.listAll();
    askToAddToCart(nullptr);  // nullptr means we'll ask for product ID
}

void consoleUI::findProductWithCart() {
    Product* product = pm.find();
    if (product) {
        product->showProductInfo();
        askToAddToCart(product);
    }
}

void consoleUI::askToAddToCart(Product* product) {
    cout << "\n장바구니에 추가하시겠습니까? (Y/N): ";
    string response;
    getline(cin, response);

    if (response == "Y" || response == "y") {
        if (!product) {
            // 상품 ID로 찾기
            cout << "추가할 상품의 ID를 입력하세요: ";
            string productId;
            getline(cin, productId);
            
            for (const auto& p : pm.getItems()) {
                if (p.matches(1, productId)) {
                    product = const_cast<Product*>(&p);
                    break;
                }
            }
            
            if (!product) {
                cout << "해당 ID의 상품을 찾을 수 없습니다." << endl;
                cout << "계속하려면 enter를 입력하세요."; cin.get();
                return;
            }
        }
        
        cm.addToCart(product->toCartString());
        cout << "장바구니에 추가되었습니다." << endl;
        cout << "계속하려면 enter를 입력하세요."; cin.get();
    }
}

void consoleUI::showCurrentCart() {
    cm.listAll();
    cout << "\n1. 상품 삭제\n";
    cout << "2. 장바구니 비우기\n";
    cout << "3. 돌아가기\n";
    cout << "선택: ";

    int choice;
    cin >> choice; cin.ignore();

    switch (choice) {
        case 1:
            cm.remove();
            break;
        case 2:
            cm.clearCart();
            break;
        case 3:
            return;
    }
    
    cout << "계속하려면 enter를 입력하세요."; cin.get();
}

/*관리자 ui -> 상품 등록, 유저 등록 관리*/
void consoleUI::showAdminUI(){
    while(true){

        clearScreen();

        cout << "=====================================\n";
        cout << "            [Admin UI]               \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "  2. 상품 관리\n";
        cout << "  3. 고객 관리\n";
        cout << "-------------------------------------\n";
        cout << "  선택: ";

        int choice; cin >> choice; cin.ignore();
        switch (choice){
        case 0 : exit(0); break;
        case 1 : return; break;
        case 2: showAdminProductManageUI(); break;
        case 3: showAdminUserManageUI(); break;
        default : pauseForUser(); break;
        }
    }
} 

void consoleUI::showAdminProductManageUI(){

    while (true){
        clearScreen();

        cout << "=====================================\n";
        cout << "         [Admin UI : 상품관리]         \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "  2. 상품 전체 보기\n";
        cout << "  3. 신규 상품 등록하기\n";
        cout << "  4. 기존 상품 수정하기\n";
        cout << "  5. 상품 삭제 하기\n";
        cout << "-------------------------------------\n";
        cout << "  선택: ";

        int choice;
        cin >> choice; cin.ignore();

        switch (choice){
        case 0: exit(0); break;

        case 1: return; break;

        case 2: pm.listAll();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;

        case 3: pm.add();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;

        case 4: pm.update();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;

        case 5: pm.remove();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;

        default: pauseForUser(); break;
        }

    }

}

/*관리자 : 유저 관리*/
void consoleUI::showAdminUserManageUI(){
    while (true){ 
        clearScreen();
        
        cout << "=====================================\n";
        cout << "         [Admin UI : 유저관리]         \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "  2. 유저 전체 보기\n";
        cout << "  3. 신규 유저 등록하기\n";
        cout << "  4. 기존 유저 수정하기\n";
        cout << "  5. 유저 삭제 하기\n";
        cout << "-------------------------------------\n";
        cout << "  선택: ";

        int choice; cin >> choice; cin.ignore();
        switch(choice){
            case 0: exit(0); break;
            case 1: return; break;
            case 2: um.listAll();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;
            case 3: um.add();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;
            case 4: um.update();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;
            case 5: um.remove();
            cout << "계속하려면 enter를 입력하세요."; cin.get();
            break;
            default: pauseForUser(); break;
        }
    }
}
