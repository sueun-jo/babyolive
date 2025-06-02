#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "manager.h"
#include <string>

class UserManager : public Manager<User> {
public:
    UserManager();
    ~UserManager();
    
    // Manager 추상 클래스의 순수 가상 함수 구현
    void add() override;              // 새 사용자 추가
    void remove() override;           // 사용자 삭제
    void update() override;           // 사용자 정보 수정
    void listAll() override;          // 모든 사용자 목록 표시
    User* find() override;            // 일반 검색
    
    // 파일 입출력 구현
    void loadFromFile() override;
    void saveToFile() const override;
    
    // 인증 책임
    User* authenticate(const std::string& id, const std::string& password);  // 로그인 인증
};

#endif // USERMANAGER_H
