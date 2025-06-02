#include "user.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::cin;
using std::ws;
using std::string;
using std::ostringstream;

User::User() : isAdmin(false) {} //기본생성자의 관리자 권한은 0

User::User(string id, string password, string name, string address, bool isAdmin)
    : id(id), password(password), name(name), address(address), isAdmin(isAdmin) {}

User::~User() {}

void User::showUserInfo() const {
    cout << "\n";
    cout << "User Info | \n";
    cout << "ID: " << id << "\n";
    cout << "Password: " << password << "\n";
    cout << "Name: " << name << "\n";
    cout << "Address: " << address << "\n";
    cout << "Role: " << (isAdmin ? "Admin" : "Member") << "\n";
    cout << "-------------------------------------\n";
}

/*csv로 내보내기 전에 vector에서 string형으로 바꿔서 csv로 내보냄*/
string User::toCSVRow() const {
    ostringstream oss;
    oss << id << "," << password << "," << name << "," << address << "," << (isAdmin ? "1" : "0");
    
    return oss.str();
}

bool User::matches(int choice, string keyword) const {
    switch(choice) {
    case 1: return id == keyword;
    case 2: return name == keyword;
    default: return false;
    }
}

const string& User::getId() const {
    return id;
}

void User::setName(const string& newName) {
    name = newName;
}

void User::setAddress(const string& newAddress) {
    address = newAddress;
}

void User::setPassword(const string& newPassword) {
    password = newPassword;
}

void User::updateField() {
    cout << "\n수정할 항목을 선택하세요.\n";
    cout << "[1]이름 [2]주소 [3]비밀번호\n";
    cout << "선택: ";

    int choice;
    cin >> choice; cin.ignore();

    switch (choice) {
    case 1: {
        string newName;
        cout << "새 이름: ";
        getline(cin >> ws, newName);
        setName(newName);
        break;
    }
    case 2: {
        string newAddress;
        cout << "새 주소: ";
        getline(cin >> ws, newAddress);
        setAddress(newAddress);
        break;
    }
    case 3: {
        string newPassword;
        cout << "새 비밀번호: ";
        getline(cin >> ws, newPassword);
        setPassword(newPassword);
        break;
    }
    default:
        cout << "잘못된 선택입니다.\n";
        return;
    }
}

/* 로그인 인증 authenticate */
bool User::authenticate(const string& inputid, const string& inputPassword) const {
    return (id == inputid && password == inputPassword);
}

bool User::isAdminUser() const { return isAdmin; }


