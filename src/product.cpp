#include "product.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

/* class product의 메소드 구현부*/
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

// 문자열 앞뒤의 공백을 제거하는 함수
static string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

/*keyword랑 일치하는지 확인함*/
bool Product::matches(int choice, string keyword) const {
    // 입력된 키워드와 저장된 값 모두 trim
    keyword = trim(keyword);
    string trimmed_id = trim(id);
    string trimmed_name = trim(name);
    string trimmed_brand = trim(brand);
    string trimmed_category = trim(category);

    switch(choice) {
    case 1: return (trimmed_id == keyword);
    case 2: return (trimmed_name == keyword);
    case 3: return (trimmed_brand == keyword);
    case 4: return (trimmed_category == keyword);
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


