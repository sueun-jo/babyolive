#include "../include/productmanager.h"
#include "../include/csvhandler.h"
#include "../include/util.h"
#include "../include/product.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

/* ProductManager pm만들 때 메모리 상에 product 정보 읽어서 vector<Product> items에 올려둠*/
ProductManager::ProductManager() {
    loadFromFile();
}

ProductManager::~ProductManager() {
    saveToFile();
}

void ProductManager::loadFromFile() {
    items = csvHandler<Product>::loadAll("product.csv");
}

void ProductManager::saveToFile() const {
    if (!csvHandler<Product>::saveAll(items, "product.csv")) {
        cerr << "상품 정보 저장에 실패했습니다." << endl;
    }
}

/*상품 추가 등록*/
void ProductManager::add() {
    string id, category, brand, name;
    int price, stock;

    /*사용자로부터 product info를 입력 받습니다*/
    cout << "상품 정보 입력을 시작합니다." << endl;
    cout << "상품ID : "; getline(cin >> ws, id);
    cout << "카테고리 : "; getline(cin >> ws, category);
    cout << "브랜드(책임판매업자) : "; getline(cin >> ws, brand);
    cout << "상품명 : "; getline(cin >> ws, name);
    cout << "가격 : "; cin >> price;
    cout << "재고수량 : "; cin >> stock; cin.ignore();

    /*입력한 정보를 기반으로 prdouct 객체 생성*/
    Product newProduct(id, category, brand, name, price, stock);
    items.push_back(newProduct);

    saveToFile();
}

/*vector<Product> items에서 상품을 찾는다 : 이건 사용자용임*/
Product* ProductManager::find() {
    /*검색 기준을 사용자에게 물어봄*/
    int choice; //검색기준 인자
    cout << "어떤 검색 기준을 사용할건가요? (숫자로 입력해주세요)" << endl;
    cout << "[1]상품ID [2]상품명 [3]브랜드 [4]카테고리" << endl;
    cin >> choice; cin.ignore();

    cout << "찾을 키워드를 입력해주세요." << endl;
    string keyword; //검색할 키워드
    getline(cin >> ws, keyword); //키워드 받기

    for (auto& p : items)
    {
        if (p.matches(choice, keyword))
            return &p; // 해당하는 객체 p의 주소연산자&
    }

    return nullptr; //못찾으면 return nullptr
}

/*관리자용 find메소드는 id기반으로 찾음*/
Product* ProductManager::findByID() {
    string id;
    cout << "찾을 상품 ID를 입력해주세요: ";
    getline(cin >> ws, id);

    for (auto& p : items)
    {
        if (p.matches(1, id)) {
            return &p;
        }
    }
    cout << "해당 상품을 찾을 수 없습니다." << endl;
    return nullptr;
}

/* 상품을 찾아 삭제한다 */
void ProductManager::remove() {
    Product* target = findByID();

    if (!target) {
        cout << "해당 조건의 상품을 찾을 수 없습니다." << endl;
        return;
    }

    /* target(match되는 객체p의 주소값)과 매칭되는 객체p를 뒤로 밀어줌*/
    auto it = remove_if(items.begin(), items.end(),
                        [&](const Product& p) { return &p == target; });

    /*그리고 진짜 지움*/
    if(it != items.end()){
        items.erase(it, items.end());
        cout << "요청하신 상품을 삭제했습니다." << endl;
        saveToFile();
    }
}

void ProductManager::update() {
    Product* target = find();
    if (!target) {
        cout << "수정할 상품을 찾을 수 없습니다." << endl;
        cout << "계속하려면 enter 키를 입력하세요."; cin.get();
        return;
    }
    cout << "수정 전의 상품 정보" << endl;
    target->showProductInfo(); //수정 전 정보 보여줌
    target->updateField(); //Product의 updateField에 접근해서 내부에서 처리함
    cout << "수정이 완료되었습니다. 상품 정보는 하기와 같습니다." << endl;
    target->showProductInfo(); //수정 후 정보 보여줌
    
    saveToFile(); //저장함
}

void ProductManager::listAll() {
    clearScreen();

    cout << "=====================================\n";
    cout << " [Admin : 상품관리 : 상품 전체 보기]   \n";
    cout << "=====================================\n";

    for (const auto& p : items)
        p.showProductInfo();
}

