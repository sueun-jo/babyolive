#include "product.h"
#include "csvHandler.h"
#include <iostream>

int main(void){

    Product *lipmonster = new Product("001", "립몬스터", "4.5g", "메이크업", 18000, 10);
    lipmonster->showProductInfo();

    return 0;
}
