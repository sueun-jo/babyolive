#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class User {
private:
    string id;
    string password;
    string name;
    string address;
    vector<string> orders;  // 주문 내역을 저장할 벡터
    bool isAdmin;

public:
    User();
    User(string id, string password, string name, string address, bool isAdmin = false);
    ~User();

    // 유저 정보 관련 메소드
    void showUserInfo() const;  // 사용자 정보 표시
    string toCSVRow() const;    // CSV 저장을 위한 문자열 변환
    bool matches(int choice, string keyword) const;  // 검색 조건과 일치하는지 확인
    void updateField();         // 사용자 정보 수정
    bool authenticate(const string& inputid, const string& inputPassword) const;  // 비밀번호 인증
    bool isAdminUser() const; // 관리자 여부 확인
    
    // 주문 관련 메소드
    void addOrder(const string& orderInfo);  // 주문 추가
    void showOrders() const;    // 주문 내역 표시
    const vector<string>& getOrders() const { return orders; }  // 주문 내역 반환

    // Setter methods
    void setName(const string& newName);
    void setAddress(const string& newAddress);
    void setPassword(const string& newPassword);
};

#endif // USER_H 