#ifndef UTIL_H
#define UTIL_H

#include <iostream>
using namespace std;

/*잠시 대기*/
inline void pauseForUser(){
    cout << "잘못된 접근입니다.\n계속하려면 Enter 키를 누르세요.";
    cin.ignore();
    cin.get();
}

/*화면 초기화*/
inline void clearScreen(){
    cout << "\033[2J\033[1;1H";
    return;
}
#endif // UTIL_H
