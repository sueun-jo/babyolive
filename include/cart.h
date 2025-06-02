#ifndef CART_H
#define CART_H

#include <string>
#include <vector>
#include <sstream>

class Cart {
private:
    std::string userId;              // 장바구니 소유자 ID
    std::vector<std::string> cartProducts;    // 담은 상품 목록

public:
    Cart() = default;  // 기본 생성자
    explicit Cart(const std::string& id);
    ~Cart() = default;  // 소멸자

    // 장바구니 기본 기능
    void addProduct(const std::string& product);
    void removeProduct(size_t index);
    void clear();
    void showCart() const;

    // Getters
    bool matchUserId(const std::string& id) const;
    size_t getProductCount() const;
    const std::vector<std::string>& getProducts() const;
    std::string toCSVRow() const;
};

#endif // CART_H 