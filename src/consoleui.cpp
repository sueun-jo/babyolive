#include "../include/consoleui.h"
#include "../include/util.h"
#include "../include/usermanager.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;


consoleUI::consoleUI() {} //기본 생성자


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
        string id, pw;
        cout << "=====================================\n";
        cout << "              [Log in]               \n";
        cout << "=====================================\n";
        cout << "  0. 종료하기\n";
        cout << "  1. 전 화면으로 돌아가기\n";
        cout << "-------------------------------------\n";
        cout << "  ID: "; cin >> id; //id 입력 받음
               /*0이거나 1인지 보고 종료하거나 전화면으로 돌아감 */

        regex idRegex("^[A-Za-z]+$"); //id로는 AtoZ, atoz만 허용하겠다
        if (regex_match(id, idRegex)){ //regex조건과 id가 알맞으면
            cout << "  PW: "; cin >> pw;
            cout << "-------------------------------------\n";
        }
        else if (id[0] == '0') exit(0);
        else if (id[0] == '1') return;
        else {pauseForUser(); continue;}


        if (id=="sueun" && pw=="1201") { //일단 관리자라고 가정함, 나중에 관리자 권한이 있는 id인지 확인할거임
            showAdminUI();
        }
        else {cout << "로그인 실패!" << endl;
            cout << "계속하려면 enter를 입력하세요.\n";
            cin.ignore(); cin.get();
            }
    }
}

/*회원가입 화면*/
void consoleUI::showSignupUI(){
    cout << "sigup ui" << endl;
}

/*멤버 ui -> 쇼핑몰 이용할 수 있음*/
void consoleUI::showMemberUI(){} // 회원 화면 -> 쇼핑몰로 연결

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

} // 관리자 화면 -> 상품 등록, 상품 화면

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

void consoleUI::showAdminUserManageUI(){
    while (true){ 
        clearScreen();
        
        cout << "=====================================\n";
        cout << "         [Admin UI : 상품관리]         \n";
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
            case 2: um.listAll(); break;
            case 3: um.add(); break;
            case 4: um.update(); break;
            case 5: um.remove(); break;
            default: pauseForUser(); break;
        }
    }
}
