#include "productmanager.h"
#include <string>
#include <vector>

using namespace std;

ProductManager::ProductManager() {}

void ProductManager::add(){
    string id, category, brand, name, unit, manufacturer;
    double price, capacity;
    int stock;

    string capacityInput; //capacity(숫자)+unit(단위) 합쳐서 입력 받음

    /*사용자로부터 product info를 입력 받습니다*/
    cout << "상품ID : "; cin >> id;
    cout << "카테고리 : "; cin >> category;
    cout << "브랜드(책임판매업자) : "; cin >> brand;
    cout << "상품명 : "; cin >> name;
    cout << "가격 : "; cin >> price;
    cout << "재고수량 : "; cin >> stock;
    cout << "용량 (ex) 50ml, 3.5g : "; cin >> capacityInput;

    /* 용량을 숫자와 문자를 함께 입력 받고
     해당 내용을 double capacity와 unit으로 나눠서 입력하는 로직*/
    string numberStr = "", unitStr = "";
    for (char ch : capacityInput) {
        if (isdigit(ch) || ch == '.') numberStr += ch;
        else unitStr += ch;
    }

    capacity = stod(numberStr); //string to double
    unit = unitStr;

    cout << "제조사명 : "; cin >> manufacturer;

    Product p(id, category, brand, name, price, stock, capacity, unit, manufacturer);
    items.push_back(p);

}


void ProductManager::remove(){}

Product* ProductManager::findByID(string id){}

void ProductManager::listAll(){}

