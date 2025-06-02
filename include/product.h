#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private: // 상품id, 분류, 브랜드명, 상품명, 가격, 재고, 용량(숫자), 용량(단위), 제조사명
    std::string id;
    std::string category;
    std::string brand;
    std::string name;
    int price;
    int stock;

public:
    Product();

    Product(std::string id, std::string category, std::string brand, std::string name,
            int price, int stock);

    ~Product();

    void showProductInfo() const;  // 상품 정보 표시
    std::string toCSVRow() const;       // CSV 저장용 문자열 변환
    std::string toCartString() const;   // 장바구니용 상품 정보 문자열 반환
    bool matches(int choice, std::string keyword) const;  // 검색 조건과 일치하는지 확인
    void updateField();

    /* 상품 정보 update에 필요한 setter method*/
    void setCategory(const std::string& newCategory);
    void setBrand(const std::string& newBrand);
    void setName(const std::string& newName);
    void setPrice(const int p);
    void setStock(const int s);
};

#endif // PRODUCT_H
