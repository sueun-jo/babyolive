#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>

using namespace std;

/*추상클래스 Manager*/
template <typename T>
class Manager
{

protected:
    vector <T> items;
public:
    Manager(); // default constructor
    virtual void add() = 0;
    virtual void updatePriceOrStock() = 0;
    virtual void remove() = 0;
    virtual T* findByID(string id) = 0;
    virtual void listAll() = 0;
};

#endif // MANAGER_H
