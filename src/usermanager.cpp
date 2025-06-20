#include "../include/usermanager.h"
#include "../include/csvhandler.h"
#include "../include/util.h"
#include "../include/manager.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include "user.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

UserManager::UserManager() {
    cout << "Current working directory: " << fs::current_path().string() << endl;
    cout << "Attempting to load users from users.csv..." << endl;
    
    this->items = CsvHandler<User>::loadAll("users.csv");
    cout << "UserManager 생성자 생성 -> call CsvHandler<User>::loadAll" << endl;
    cout << "등록된 사용자 수 : " << items.size() << endl;
    
    // Debug: 사용자 정보 출력
    cout << "\n=== Registered Users ===\n";
    for (const auto& user : items) {
        user.showUserInfo();
    }
    cout << "=====================\n";
}

UserManager::~UserManager() {
    saveToFile();
}

void UserManager::loadFromFile() {
    items = CsvHandler<User>::loadAll("users.csv");
}

void UserManager::saveToFile() const {
    if (!CsvHandler<User>::saveAll(items, "users.csv")) {
        cerr << "사용자 정보 저장에 실패했습니다." << endl;
    }
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
    for(const auto& user : items) {
        if(user.matches(1, id)) {
            cout << "이미 존재하는 ID입니다." << endl;
            return;
        }
    }

    cout << "비밀번호: "; getline(cin >> ws, password);
    cout << "이름: "; getline(cin >> ws, name);
    cout << "주소: "; getline(cin >> ws, address);
    
    User newUser(id, password, name, address);
    items.push_back(newUser);
    
    saveToFile();
}

void UserManager::remove() {
    User* target = find();
    
    if (!target) {
        cout << "해당 사용자를 찾을 수 없습니다." << endl;
        return;
    }

    auto it = remove_if(items.begin(), items.end(),
                       [&](const User& u) { return &u == target; });
    
    if(it != items.end()) {
        items.erase(it, items.end());
        cout << "사용자를 삭제했습니다." << endl;
        saveToFile();
    }
}

void UserManager::update() {
    User* target = find();
    if (!target) {
        cout << "수정할 사용자를 찾을 수 없습니다." << endl;
        cout << "계속하려면 enter 키를 입력하세요."; cin.get();
        return;
    }

    target->showUserInfo();
    target->updateField();
    target->showUserInfo();
    saveToFile();
}

void UserManager::listAll() {
    clearScreen();
    
    cout << "=====================================\n";
    cout << " [Admin : 사용자관리 : 사용자 전체 보기]\n";
    cout << "=====================================\n";
    
    for (const auto& user : items)
        user.showUserInfo();
}

User* UserManager::find() {
    cout << "어떤 검색 기준을 사용할건가요? (숫자로 입력해주세요)" << endl;
    cout << "[1]ID [2]이름 " << endl;
    
    int choice;
    cin >> choice; cin.ignore();
    
    cout << "찾을 키워드를 입력해주세요." << endl;
    string keyword;
    getline(cin >> ws, keyword);
    
    for (auto& user : items) {
        if (user.matches(choice, keyword))
            return &user;
    }
    
    return nullptr;
}

User* UserManager::authenticate(const std::string& inputid, const std::string& inputpassword) {
    for (auto& user : items) {
        if (user.authenticate(inputid, inputpassword)) {
            cout << "로그인 성공" << endl;
            cout << "계속하려면 enter 키를 입력하세요.";
            cin.ignore(); cin.get();
            return &user;
        }
    }
    return nullptr;
}
