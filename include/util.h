#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <cstdlib> //system("cls") 사용
using namespace std;

/*유틸 함수를 모아둔 헤더파일*/


/*잘못된 접근일 경우*/
inline void pauseForUser(){
    cout << "잘못된 접근입니다.\n계속하려면 Enter 키를 누르세요.";
    cin.ignore();
    cin.get();
}

/*화면 초기화*/
inline void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}

/*UTF-8 BOM 제거*/
inline void removeBOM(ifstream& file) {
    char bom[3];
    file.read(bom, 3);
    
    // BOM이 없으면 파일 포인터를 다시 처음으로
    if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) {
        file.seekg(0); //파일 포인터를 처음으로 이동시킴
    }
}

#endif // UTIL_H
