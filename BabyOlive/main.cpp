#include "product.h"
#include "csvHandler.h"
#include "productmanager.h"
#include <iostream>

using namespace std;

int main(void){

    ProductManager pm; //pm객체 생성하면서 csvHandler::loadAll()불러와서 vector<Product> items엔 내용 담겨야됨
    // pm.add();
    pm.listAll();

    return 0;
}
