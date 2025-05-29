#include "user.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

User::User() : isAdmin(false) {}

User::User(string id, string password, string name, string address, bool isAdmin)
    : id(id), password(password), name(name), address(address), isAdmin(isAdmin) {}

User::~User() {}

void User::showUserInfo() const {
    cout << "\n";
    cout << "User Info | " << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Address: " << address << "\n";
    cout << "Role: " << (isAdmin ? "Admin" : "Member") << "\n";
    cout << "Orders: " << orders.size() << " orders\n\n";
    cout << "-------------------------------------\n";
}

string User::toCSVRow() const {
    ostringstream oss;
    oss << id << "," << password << "," << name << "," << address << "," << (isAdmin ? "1" : "0");
    
    // 주문 내역을 |로 구분하여 저장
    oss << ",";
    for(size_t i = 0; i < orders.size(); ++i) {
        if(i > 0) oss << "|";
        oss << orders[i];
    }
    
    return oss.str();
}

bool User::matches(int choice, string keyword) const {
    switch(choice) {
    case 1: return (id == keyword);
    case 2: return (name == keyword);
    case 3: return (address == keyword);
    default: return false;
    }
}

void User::updateField() {
    cout << "\n수정할 항목을 선택하세요.\n";
    cout << "[1]이름 [2]주소 [3]비밀번호\n";
    cout << "선택: ";

    int choice;
    cin >> choice; cin.ignore();

    switch (choice) {
    case 1: {
        cout << "새 이름: ";
        getline(cin >> ws, name);
        break;
    }
    case 2: {
        cout << "새 주소: ";
        getline(cin >> ws, address);
        break;
    }
    case 3: {
        cout << "새 비밀번호: ";
        getline(cin >> ws, password);
        break;
    }
    default:
        cout << "잘못된 선택입니다.\n";
        return;
    }
}

bool User::authenticate(const string& inputPassword) const {
    return password == inputPassword;
}

void User::addOrder(const string& orderInfo) {
    orders.push_back(orderInfo);
}

void User::showOrders() const {
    cout << "\n주문 내역:\n";
    cout << "-------------------------------------\n";
    if(orders.empty()) {
        cout << "주문 내역이 없습니다.\n";
        return;
    }
    
    for(size_t i = 0; i < orders.size(); ++i) {
        cout << (i+1) << ". " << orders[i] << "\n";
    }
    cout << "-------------------------------------\n";
} 