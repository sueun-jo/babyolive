#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "manager.h"
#include <vector>
#include <string>

using namespace std;

class UserManager : public Manager<User> {
public:
    UserManager();
    
    // 사용자 관리 책임 및 manager추상클래스 virtual func override
    void add() override;              // 새 사용자 추가
    void remove() override;           // 사용자 삭제
    void update() override;           // 사용자 정보 수정
    void listAll() override;          // 모든 사용자 목록 표시
    User* find() override;            // 일반 검색
    
    // 인증 책임
    User* authenticate(const string& id, const string& password);  // 로그인 인증
    
    // 데이터 관리 책임
    void saveAll();          // 변경사항 저장
};

#endif // USERMANAGER_H
