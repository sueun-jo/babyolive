#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include <iostream>
#include <fstream> // 파일 입출력 lib
#include <string>
#include <vector>

using namespace std;

template <typename T> //csvHandler는 템플릿 클래스이기 때문에 .h에 메소드까지 구현한다
class csvHandler
{
public:
    csvHandler(); //constructor

    void saveToCSV(const vector<T> &items, const string& filename){
        ofstream file(filename);
        if (!file.is_open()){
            cerr << "fail to open file" << endl;
            return;
        }
    }

    vector<T> loadFromCSV(const string &filename){

    }
};

#endif // CSVHANDLER_H
