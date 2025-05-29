#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include <iostream>
#include <fstream> // 파일 입출력 lib
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename T> //csvHandler는 템플릿 클래스이기 때문에 .h에 메소드까지 구현한다
class csvHandler
{
public:
    csvHandler(); //constructor
    ~csvHandler(); //descructor

    /*load all - 기존 csv파일 불러오는 메소드*/
    static vector<T> loadAll(const string& filename){
        vector<T> result;

        ifstream file(filename, ios::in | ios::binary);

        if(!file.is_open()){
            cerr << "fail to open - file name : " << filename << endl;
            return result;
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string id, category, brand, name, priceStr, stockStr;

            getline(ss, id, ',');
            getline(ss, category, ',');
            getline(ss, brand, ',');
            getline(ss, name, ',');
            getline(ss, priceStr, ',');
            getline(ss, stockStr);

            try {
                int price = stod(priceStr);
                int stock = stoi(stockStr);

                T item(id, category, brand, name, price, stock);
                result.push_back(item);
            } catch (const std::exception& e) {
                cerr << "CSV 파싱 중 예외 발생: " << e.what() << endl;
                cerr << "문제 줄: " << line << endl;
                continue;
            }
        }

        file.close();
        return result;
    }

    /* vector내 자료들 저장하는 saveAll 메소드 구현부*/
    static bool saveAll(const vector<T>& items, const string& filename){
        ofstream file(filename);

        if (!file.is_open()){
            cerr << "fail to open : "  << filename << endl;
            return false;
        }

        for (const auto& item : items) // vector<T> items에 담긴 항목 하나씩 접근한다
        {
            file << item.toCSVRow() << endl;
        }
        file.close();
        return true;
    }


};

#endif // CSVHANDLER_H
