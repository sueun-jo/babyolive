#ifndef CsvHandler_H
#define CsvHandler_H

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "util.h"
#include "user.h"
#include "product.h"
#include "cart.h"

using namespace std;
namespace fs = std::filesystem; 

template<typename T>
class CsvHandler {
private:
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

public:
    /*vector데이터를 csv로 저장하는 saveAll 메소드*/
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

    /*csv를 vector로 불러오는 loadAll 메소드*/
    static vector<T> loadAll(const string& filename);
};

// Vector<User> 특수화
template<>
inline vector<User> CsvHandler<User>::loadAll(const string& filename) {
    vector<User> users;
    string filepath = getDataPath(filename);
    
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filepath << endl;
        return users;
    }

    // UTF-8 BOM 제거
    removeBOM(file);

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        //istringstream은 문자열을 파싱하여 변수 형식에 맞게 변환한다
        istringstream iss(line);
        string id, password, name, address, isAdminStr;
        
        getline(iss, id, ',');
        getline(iss, password, ',');
        getline(iss, name, ',');
        getline(iss, address, ',');
        getline(iss, isAdminStr, ',');
        
        bool isAdmin = (isAdminStr == "1");
        User user(id, password, name, address, isAdmin);
        users.push_back(user);
    }
    
    file.close();
    return users;
}

// vector<Product> 특수화
template<>
inline vector<Product> CsvHandler<Product>::loadAll(const string& filename) {
    vector<Product> products;
    string filepath = getDataPath(filename);
    
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filepath << endl;
        return products;
    }

    // UTF-8 BOM 제거
    removeBOM(file);

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string id, category, brand, name, priceStr, stockStr;
        
        getline(iss, id, ',');
        getline(iss, category, ',');
        getline(iss, brand, ',');
        getline(iss, name, ',');
        getline(iss, priceStr, ',');
        getline(iss, stockStr);
        
        int price = stoi(priceStr);
        int stock = stoi(stockStr);
        Product item(id, category, brand, name, price, stock);
        products.push_back(item);
       
    }
    
    file.close();
    return products;
}

// Vector<Cart> 특수화
template<>
inline vector<Cart> CsvHandler<Cart>::loadAll(const string& filename) {
    vector<Cart> carts;
    string filepath = getDataPath(filename);
    
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filepath << endl;
        return carts;
    }

    // UTF-8 BOM 제거
    removeBOM(file);

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string userId, products;
        
        getline(iss, userId, ',');
        Cart cart(userId);
        
        if (getline(iss, products)) {
            istringstream productStream(products);
            string product;
            while (getline(productStream, product, '|')) {
                cart.addProduct(product);
            }
        }
        
        carts.push_back(cart);
    }
    
    file.close();
    return carts;
}

#endif // CsvHandler_H
