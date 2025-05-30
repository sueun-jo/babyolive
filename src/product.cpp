#include "../include/product.h"
#include "../include/util.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

/* class product의 메소드 구현부*/
Product::Product() : price(0), stock(0) {} // 기본 생성자 추가

Product::Product(string id, string category, string brand, string name,
                 int price, int stock) {

    this->id = id;
    this->category = category;
    this->brand = brand;
    this->name = name;
    this->price = price;
    this->stock = stock;
} //constructor

Product::~Product(){

} //Product::destructor

/* product 객체의 정보를 보여준다 */
void Product::showProductInfo() const{

    cout << "\n";
    cout << "Product Info | " << "ID: " << id << "\n";
    cout << "Category: " << category << "\n";
    cout << "Brand: " << brand << "\n";
    cout << "Name: " << name << "\n";
    cout << "Price: " << price << "\n";
    cout << "Stock: " << stock << "\n\n";
    cout << "-------------------------------------\n";

} //Product::showProductInfo


/*csv파일로 만들기 위한 메소드*/
string Product::toCSVRow() const {

    ostringstream oss;

    oss << id << "," << category << "," << brand << "," << name << ","
        << price << "," << stock;

    return oss.str();
}

/*keyword랑 일치하는지 확인함*/
bool Product::matches(int choice, string keyword) const{
    switch(choice){
    case 1: return id == keyword;
    case 2: return name == keyword;
    case 3: return brand == keyword;
    case 4: return category == keyword;
    default: return false;
    }
}

void Product::updateField(){

    cout << "\n수정할 항목을 선택하세요.\n";
    cout << "[1] 카테고리 [2]브랜드 [3]상품명 [4]가격 [5] 재고수량\n";
    cout << "선택: ";

    int choice;
    cin >> choice; cin.ignore();


    switch (choice) {
    case 1: {
        string newCategory;
        cout << "새 카테고리: ";
        getline(cin >> ws, newCategory);
        setCategory(newCategory);
        break;
    }
    case 2: {
        string newBrand;
        cout << "새 브랜드: ";
        getline(cin >> ws, newBrand);
        setBrand(newBrand);
        break;
    }
    case 3: {
        string newName;
        cout << "새 상품명: ";
        getline(cin >> ws, newName);
        setName(newName);
        break;
    }
    case 4: {
        int newPrice;
        cout << "새 가격: ";
        cin >> newPrice; cin.ignore();
        setPrice(newPrice);
        break;
    }
    case 5: {
        int newStock;
        cout << "새 재고 수량: ";
        cin >> newStock; cin.ignore();
        setStock(newStock);
        break;
    }
    default:
        cout << "잘못된 선택입니다.\n";
        return;
    }

}

void Product::setCategory(const string& newCategory){
    category = newCategory;
}

void Product::setBrand(const string& newBrand){
    brand = newBrand;
}

void Product::setName(const string& newName){
    name = newName;
}

void Product::setPrice (const int p){
    price = p;
}

void Product::setStock(const int s){
    stock = s;
}

string Product::toCartString() const {
    ostringstream oss;
    oss << "[" << id << "] " << brand << " " << name << " - " << price << "원";
    return oss.str();
}


