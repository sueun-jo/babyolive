#include "product.h"
#include <iostream>
using namespace std;

/* class product의 메소드 구현부*/
Product::Product(string id, string name, string capacity, string category, double price, int stock) {
    this->id = id;
    this->name = name;
    this->capacity = capacity ;
    this->category = category;
    this->price = price;
    this->stock = stock;
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
