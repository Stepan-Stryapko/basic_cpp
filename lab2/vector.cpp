#include <iostream>

template<typename T>
class subvector {
    T *mas;
    unsigned int top;
    unsigned int capacity;
     
public:
    // Конструктор по умолчанию
    subvector() : mas(nullptr), top(0), capacity(0) {}

    // Конструктор с параметром
    explicit subvector(unsigned int n) : capacity(n), top(0) {
        mas = new T[n];
    }

    // Деструктор
    ~subvector(){
        delete[] mas;
    }

    // Конструктор копирования
    subvector(const subvector& other) : mas(nullptr), top(0), capacity(0) {
        if (other.capacity > 0) {
            mas = new T[other.capacity];
            capacity = other.capacity;
            top = other.top;
            for (unsigned int i = 0; i < top; i++) {
                mas[i] = other.mas[i];
            }
        }
    }

    // Оператор присваивания
    subvector& operator=(const subvector& other){
        if(this == &other) return *this;
        delete[] mas;
        capacity = other.capacity;
        top = other.top;
        mas = new T[capacity];
        for(unsigned int i = 0; i < top; i++){
            mas[i] = other.mas[i];
        }
        return *this;
    }

    // Конструктор перемещения
    subvector(subvector&& other) : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    // Оператор присваивания перемещением
    subvector& operator=(subvector&& other) {
        if (this != &other) {
            delete[] mas;
            
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // push_back 
    bool push_back(const T& d){
        if(top >= capacity){
            if(!resize(capacity == 0 ? 1 : capacity * 2)) return false;
        }
        mas[top] = d;
        top++;
        return true;
    }

    // pop_back 
    T pop_back() {
        if (top == 0) return T{};
        top--;
        return mas[top];
    }

    // resize
    bool resize(unsigned int new_capacity) {
        if (new_capacity == capacity) return true;
        T* new_mas = new T[new_capacity];
        unsigned int copy_size = (top < new_capacity) ? top : new_capacity;
        for (unsigned int i = 0; i < copy_size; ++i) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        top = copy_size;
        return true;
    }

    // shrink_to_fit 
    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }

    // clear 
    void clear() {
        top = 0;
    }

    // Операторы доступа
    T& operator[](unsigned int index){
        return mas[index];
    }

    const T& operator[](unsigned int index) const {
        return mas[index];
    }

    // Методы размера
    unsigned int size() const {
        return top;
    }

    unsigned int get_capacity() const {
        return capacity;
    }
};