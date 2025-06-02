#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "manager.h"
#include "product.h"

class ProductManager : public Manager<Product>
{
public:
    ProductManager();
    ~ProductManager();

    // Manager 추상 클래스의 순수 가상 함수 구현
    void add() override;
    void remove() override;
    void update() override;
    Product* find() override;
    void listAll() override;

    // 파일 입출력 구현
    void loadFromFile() override;
    void saveToFile() const override;

    // 추가 기능
    Product* findByID();
};

#endif // PRODUCTMANAGER_H
