#include "product.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

/* class product의 메소드 구현부*/
Product::Product(string id, string category, string brand, string name,
                 double price, int stock, double capacity, string unit, string manufacturer) {

    this->id = id;
    this->category = category;
    this->brand = brand;
    this->name = name;
    this->price = price;
    this->stock = stock;
    this->capacity = capacity;
    this->unit = unit;
    this->manufacturer = manufacturer;

} //constructor

Product::~Product(){

} //Product::destructor

/* product 객체의 정보를 보여준다 */
void Product::showProductInfo() const{
    cout << "Product ID: " << id << endl;
    cout << "Product Category: " << category << endl;
    cout << "Brand: " << brand << endl;
    cout << "Product Name: " << name << endl;
    cout << "Product Price: " << price << endl;
    cout << "Product Stock: " << stock << endl;
    cout << "Capacity: " << capacity << unit << endl;
    cout << "Manufacturer: " << manufacturer << endl << endl;
} //Product::showProductInfo


/*csv파일로 만들기 위한 메소드*/
string Product::toCSVRow() const {

    ostringstream oss;
    oss << fixed << setprecision(2); /*소수점 둘째자리까지 저장 (price, capacity)*/

    oss << id << "," << category << "," << brand << "," << name << ","
        << price << "," << stock << ","
        << capacity << "," << unit << "," << manufacturer;

    return oss.str();
}


bool Product::matches(int choice, string keyword) const{
    switch(choice){
    case 1: return name == keyword; break;
    case 2: return category == keyword; break;
    case 3: return brand == keyword; break;
    case 4: return manufacturer == keyword; break;
    case 5: return id == keyword; break;
    default: return false;
    }
}

void Product::increaseStock(){

}

void Product::decreaseStock(){

}


