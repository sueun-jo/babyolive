#ifndef CART_H
#define CART_H

#include <string>
#include <vector>

using namespace std;

class Cart {
private:
    string userId;              // 장바구니 소유자 ID
    vector<string> products;    // 담은 상품 목록

public:
    Cart(const string& id) : userId(id) {}

    // 장바구니 기본 기능
    void addProduct(const string& product) { products.push_back(product); }
    void removeProduct(size_t index) {
        if (index < products.size()) {
            products.erase(products.begin() + index);
        }
    }
    void clear() { products.clear(); }
    void showCart() const;                        // 장바구니 내용 표시
    
    // 필수 기능
    bool matchUserId(const string& id) const { return userId == id; }  // 사용자 ID 일치 확인
    size_t getProductCount() const { return products.size(); }         // 상품 개수 확인
    const vector<string>& getProducts() const { return products; }
    
    // CSV 변환
    string toCSVRow() const {
        string result = userId;
        if (!products.empty()) {
            result += ",";
            for (size_t i = 0; i < products.size(); ++i) {
                result += products[i];
                if (i < products.size() - 1) result += "|";
            }
        }
        return result;
    }
};

#endif // CART_H 