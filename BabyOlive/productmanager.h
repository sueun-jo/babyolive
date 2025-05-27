#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "manager.h"
#include "product.h"
#include "csvhandler.h"

using namespace std;
class ProductManager : public Manager<Product> /*추상클래스 Manager 상속받음*/
{
public:
    ProductManager();

    void add () override;
    void remove() override;
    void update() override;
    Product* findByID(string id) override;
    void listAll() override;
};

#endif // PRODUCTMANAGER_H
