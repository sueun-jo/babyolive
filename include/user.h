#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string id;
    std::string password;
    std::string name;
    std::string address;
    bool isAdmin;

public:
    User();
    User(std::string id, std::string password, std::string name, std::string address, bool isAdmin = false);
    ~User();

    // 유저 정보 관련 메소드
    void showUserInfo() const;  // 사용자 정보 표시
    std::string toCSVRow() const;    // CSV 저장을 위한 문자열 변환
    bool matches(int choice, std::string keyword) const;  // 검색 조건과 일치하는지 확인
    void updateField();         // 사용자 정보 수정
    bool authenticate(const std::string& inputid, const std::string& inputPassword) const;  // 비밀번호 인증
    bool isAdminUser() const; // 관리자 여부 확인
    
    const std::string& getId() const;
    // update에서 사용할 method
    void setName(const std::string& newName);
    void setAddress(const std::string& newAddress);
    void setPassword(const std::string& newPassword);

};

#endif // USER_H 