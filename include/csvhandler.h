#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem; 

template<typename T> /*템플릿 클래스로 별도 cpp없이 바로 메소드 정의와 구현 동시에 함*/
class csvHandler {
public:
    static vector<T> loadAll(const string& filename) {
        vector<T> items;
        string filepath = getDataPath(filename);
        
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filepath << endl;
            return items;
        }

        // UTF-8 BOM 제거 메소드
        removeBOM(file);

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            istringstream iss(line);
            T item;
            
            // CSV 파싱 로직은 각 클래스에서 구현
            items.push_back(item);
        }
        
        file.close();
        return items;
    }

    static bool saveAll(const vector<T>& items, const string& filename) {
        string filepath = getDataPath(filename);
        
        ofstream file(filepath);
        if (!file.is_open()) {
            cerr << "Failed to open file for writing: " << filepath << endl;
            return false;
        }

        for (const auto& item : items) {
            file << item.toCSVRow() << "\n";
        }

        file.close();
        return true;
    }

private: // fs = std::filesystem
    static string getDataPath(const string& filename) {
        #ifdef DATA_DIR
            fs::path dataDir = DATA_DIR;
        #else
            fs::path dataDir = fs::current_path() / "data";
        #endif
        
        // 데이터 디렉토리가 없으면 생성
        if (!fs::exists(dataDir)) {
            fs::create_directory(dataDir);
        }
        
        return (dataDir / filename).string();
    }
    
    static void removeBOM(ifstream& file) {
        char bom[3];
        file.read(bom, 3);
        
        // BOM이 없으면 파일 포인터를 다시 처음으로
        if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) {
            file.seekg(0);
        }
    }
};

#endif // CSVHANDLER_H
