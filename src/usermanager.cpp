#include "usermanager.h"
#include "csvhandler.h"
#include "util.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

UserManager::UserManager() {
    users = csvHandler<User>::loadAll("users.csv");
    cout << "UserManager 생성자 생성 -> call csvHandler<User>::loadAll" << endl;
    cout << "등록된 사용자 수 : " << users.size() << endl;
}

void UserManager::add() {
    string id, password, name, address;

    cout << "사용자 정보 입력을 시작합니다." << endl;
    
    // ID 입력 및 검증
    while(true) {
        cout << "ID (영문만 가능): "; 
        getline(cin >> ws, id);
        regex idRegex("^[A-Za-z]+$");
        if(regex_match(id, idRegex)) break;
        cout << "ID는 영문자만 사용 가능합니다." << endl;
    }

    // 중복 ID 체크
    for(const auto& user : users) {
        if(user.matches(1, id)) {
            cout << "이미 존재하는 ID입니다." << endl;
            return;
        }
    }

    cout << "비밀번호: "; getline(cin >> ws, password);
    cout << "이름: "; getline(cin >> ws, name);
    cout << "주소: "; getline(cin >> ws, address);
    
    User newUser(id, password, name, address);
    users.push_back(newUser);
    
    saveAll();
}

void UserManager::remove() {
    User* target = findByID();
    
    if (!target) {
        cout << "해당 사용자를 찾을 수 없습니다." << endl;
        return;
    }

    auto it = remove_if(users.begin(), users.end(),
                       [&](const User& u) { return &u == target; });
    
    if(it != users.end()) {
        users.erase(it, users.end());
        cout << "사용자를 삭제했습니다." << endl;
        saveAll();
    }
}

void UserManager::update() {
    User* target = findByID();
    if (!target) {
        cout << "수정할 사용자를 찾을 수 없습니다." << endl;
        cout << "계속하려면 enter 키를 입력하세요."; cin.get();
        return;
    }

    target->showUserInfo();
    target->updateField();
    target->showUserInfo();
    saveAll();
}

void UserManager::listAll() {
    clearScreen();
    
    cout << "=====================================\n";
    cout << " [Admin : 사용자관리 : 사용자 전체 보기]\n";
    cout << "=====================================\n";
    
    for (const auto& user : users)
        user.showUserInfo();
}

User* UserManager::find() {
    cout << "어떤 검색 기준을 사용할건가요? (숫자로 입력해주세요)" << endl;
    cout << "[1]ID [2]이름 [3]이메일" << endl;
    
    int choice;
    cin >> choice; cin.ignore();
    
    cout << "찾을 키워드를 입력해주세요." << endl;
    string keyword;
    getline(cin >> ws, keyword);
    
    for (auto& user : users) {
        if (user.matches(choice, keyword))
            return &user;
    }
    
    return nullptr;
}

User* UserManager::findByID() {
    string id;
    cout << "찾을 사용자 ID를 입력해주세요: ";
    getline(cin >> ws, id);
    
    for (auto& user : users) {
        if (user.matches(1, id))
            return &user;
    }
    
    cout << "해당 사용자를 찾을 수 없습니다." << endl;
    return nullptr;
}

User* UserManager::authenticate(const string& id, const string& password) {
    for (auto& user : users) {
        if (user.matches(1, id) && user.authenticate(password))
            return &user;
    }
    return nullptr;
}

void UserManager::saveAll() {
    if (csvHandler<User>::saveAll(users, "users.csv"))
        cout << "변경사항을 저장했습니다." << endl;
    else
        cerr << "저장에 실패했습니다." << endl;
}
