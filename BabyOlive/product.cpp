#include "product.h"
#include <iostream>
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

void Product::showProductInfo(){
    cout << "Product ID: " << this->id << endl;
    cout << "Product Name: " << this->name << endl;
    cout << "Product Category: " << this->category << endl;
    cout << "Product Price: " << this->price << endl;
    cout << "Product Stock: " << this->stock << endl;
} //Product::showProductInfo


void Product::increaseStock(){

}

void Product::decreaseStock(){

}
