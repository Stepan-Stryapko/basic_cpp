#include <iostream>

template<typename T>
class subforwardlist {
    struct Node {
        T data;
        Node* next;
    };

    Node* begin;

public:
    // Конструктор по умолчанию
    subforwardlist(){
        begin = nullptr;
    }

    // Деструктор 
    ~subforwardlist() {
        clear();
    }

    // Конструктор копирования
    subforwardlist(const subforwardlist& other){
        begin = nullptr;
        if(!other.begin) return;
        Node* other_current = other.begin;
        begin = new Node{other_current->data, nullptr};
        Node* current = begin;
        other_current = other_current->next;
        while(other_current){
            current->next = new Node{other_current->data, nullptr};
            current = current->next;
            other_current = other_current->next;
        }
    }

    // Оператор присваивания
    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            clear();
            
            if (other.begin) {
                Node* other_current = other.begin;
                Node** current_ptr = &begin;
                
                while (other_current) {
                    *current_ptr = new Node{other_current->data, nullptr};
                    current_ptr = &((*current_ptr)->next);
                    other_current = other_current->next;
                }
            }
        }
        return *this;
    }

    // Конструктор перемещения
    subforwardlist(subforwardlist&& other) : begin(other.begin) {
        other.begin = nullptr;
    }

    // Оператор присваивания перемещением
    subforwardlist& operator=(subforwardlist&& other)  {
        if(this == &other) return *this;
        while(begin){
            Node* temp = begin;
            begin = begin->next;
            delete temp;
        }
        begin = other.begin;
        other.begin = nullptr;
        return *this;
    }

    // push_back 
    void push_back(const T& data) {
        Node* new_node = new Node{data, nullptr};
        
        if (!begin) {
            begin = new_node;
            return;
        }
        
        Node* current = begin;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }

    // pop_back
    T pop_back(){
        if(!begin) return T{};
        if(!begin->next){
            T value = begin->data;
            delete begin;
            begin = nullptr;
            return value;
        }
        Node* current = begin;
        while(current->next->next){
            current = current->next;
        }
        T value = current->next->data;
        delete current->next;
        current->next = nullptr;
        return value;
    }

    // push_forward 
    void push_forward(const T& data){
        Node* new_node = new Node{data, begin};
        begin = new_node;
    }

    // pop_forward 
    T pop_forward() {
        if (!begin) return T{};
        
        T data = begin->data;
        Node* temp = begin;
        begin = begin->next;
        delete temp;
        return data;
    }

    // push_where 
    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i < where - 1 && current; i++) {
            current = current->next;
        }
        
        if (!current) {
            push_back(data);
            return;
        }
        
        Node* new_node = new Node{data, nullptr};
        new_node->next = current->next;
        current->next = new_node;
    }

    // erase_where
    T erase_where(unsigned int where){
        if(!begin) return T{};
        if(where == 0){
            return pop_forward();
        }
        Node* current = begin;
        for(unsigned int i = 0; i < where - 1 && current->next; i++){
            current = current->next;
        }
        if(!current || !current->next) return T{};
        Node* to_delete = current->next;
        T value = to_delete->data;
        current->next = to_delete->next;
        delete to_delete;
        return value;
    }

    // size 
    unsigned int size() {
        unsigned int count = 0;
        Node* current = begin;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

private:
    // clear
    void clear() {
        while (begin) {
            Node* temp = begin;
            begin = begin->next;
            delete temp;
        }
    }
};