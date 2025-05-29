#include "product.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


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

/*keyword랑 일치하는지 확인함*/
bool Product::matches(int choice, string keyword) const{
    switch(choice){
    case 1: return id== keyword; break;
    case 2: return name == keyword; break;
    case 3: return brand == keyword; break;
    case 4: return category == keyword; break;
    default: return false;
    }
}

void Product::increaseStock(){

}

void Product::decreaseStock(){

}


