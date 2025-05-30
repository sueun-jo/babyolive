#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
private: // 상품id, 분류, 브랜드명, 상품명, 가격, 재고, 용량(숫자), 용량(단위), 제조사명
    string id;
    string category;
    string brand;
    string name;
    int price;
    int stock;


public:
    Product();

    Product(string id, string category, string brand, string name,
            int price, int stock);

    ~Product();

    void showProductInfo() const;  // 상품 정보 표시
    string toCSVRow() const;       // CSV 저장용 문자열 변환
    string toCartString() const;   // 장바구니용 상품 정보 문자열 반환
    bool matches(int choice, string keyword) const;  // 검색 조건과 일치하는지 확인
    void updateField();

    void setCategory(const string& newCategory);
    void setBrand(const string& newBrand);
    void setName(const string& newName);
    void setPrice (const int p);
    void setStock(const int s);
};

#endif // PRODUCT_H
