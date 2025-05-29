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
    double price;
    int stock;


public:
    Product();

    Product(string id, string category, string brand, string name,
            int price, int stock);

    ~Product();

    void showProductInfo () const;
    string toCSVRow() const; //csv로 저장하기 위해 csv 포맷으로 product 객체 변환
    bool matches(int choice, string keyword) const;
    void updateField();

    void setCategory(const string& newCategory);
    void setBrand(const string& newBrand);
    void setName(const string& newName);
    void setPrice (const int p);
    void setStock(const int s);
};

#endif // PRODUCT_H
