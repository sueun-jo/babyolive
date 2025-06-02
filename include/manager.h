#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>

/*추상클래스 Manager*/
template <typename T>
class Manager
{
protected:
    std::vector<T> items;

public:
    Manager() = default;
    virtual ~Manager() = default;

    // 기본 CRUD 작업
    virtual void add() = 0;
    virtual void update() = 0;
    virtual void remove() = 0;
    virtual T* find() = 0;
    virtual void listAll() = 0;

    // 파일 입출력 작업
    virtual void loadFromFile() = 0;
    virtual void saveToFile() const = 0;

    // items getter
    const std::vector<T>& getItems() const { return items; }
};

#endif // MANAGER_H
