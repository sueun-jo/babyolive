#include "productmanager.h"
#include "csvhandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* ProductManager pm만들 때 메모리 상에 product 정보 읽어서 vector<Product> items에 올려둠*/
ProductManager::ProductManager() {
    items = csvHandler<Product>::loadAll("product.csv");
    cout << "ProductManager 생성자 생성 -> call csvHandler<Product>::loadAll" << endl;
    cout << "불러온 상품 수 : " << items.size() << endl;
}

/*상품 추가 등록*/
void ProductManager::add(){

    string id, category, brand, name, unit, manufacturer;
    double price, capacity;
    int stock;

    string capacityInput; //capacity(숫자)+unit(단위) 합쳐서 입력 받음

    /*사용자로부터 product info를 입력 받습니다*/
    cout << "상품 정보 입력을 시작합니다." << endl;
    cout << "상품ID : "; getline (cin, id);
    cout << "카테고리 : "; getline (cin, category);
    cout << "브랜드(책임판매업자) : "; getline (cin, brand);
    cout << "상품명 : "; getline (cin, name);
    cout << "가격 : "; cin >> price;
    cout << "재고수량 : "; cin >> stock;
    cout << "용량 (ex) 50ml, 3.5g : "; getline( cin>>ws, capacityInput); //앞에서 cin사용했으니까 개행 지워줘야됨

    /* 용량을 숫자와 문자를 함께 입력 받고
     해당 내용을 double capacity와 unit으로 나눠서 입력하는 로직*/
    string numberStr = "", unitStr = "";
    for (char ch : capacityInput) {
        if (isdigit(ch) || ch == '.') numberStr += ch;
        else unitStr += ch;
    }

    capacity = stod(numberStr); //string to double
    unit = unitStr;

    cout << "제조사명 : "; getline( cin >> ws, manufacturer);

    /*입력한 정보를 기반으로 prdouct 객체 생성*/
    Product p(id, category, brand, name, price, stock, capacity, unit, manufacturer);
    items.push_back(p);

    saveAll(); // vector에 새로운 상품 정보 등록하면 saveAll();

}


void ProductManager::remove(){}

Product* ProductManager::find(){}

void ProductManager::update(){}

void ProductManager::listAll(){

    cout << "---전체 상품 보기---" << endl;
    for (const auto& p : items)
        p.showProductInfo();

}

void ProductManager::saveAll(){
    if (csvHandler<Product>::saveAll(items, "product.csv")) /* false값 true 받으면 저장 성공*/
        cout << "success to save " << endl;
    else
        cerr << "fail to save" << endl;
}

