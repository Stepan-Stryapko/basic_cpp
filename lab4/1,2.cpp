#include <iostream>
#include <deque>
#include <string>

template <typename T, typename Container = std::deque<T>>
class Stack {
private:
    Container storage;

public:
    bool empty() const {
        return storage.empty();
    }

    std::size_t length() const {
        return storage.size();
    }

    const T& top() const {
        return storage.back();
    }

    T& top() {
        return storage.back();
    }

    void push(const T& val) {
        storage.push_back(val);
    }

    void pop() {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }
};

template <>
class Stack<char, std::string> {
private:
    std::string storage;

public:
    bool empty() const {
        return storage.empty();
    }

    std::size_t length() const {
        return storage.size();
    }

    const char& top() const {
        return storage.back();
    }

    char& top() {
        return storage.back();
    }

    void push(char ch) {
        storage.push_back(ch);
    }

    void pop() {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }
};

int main() {
    Stack<int> numbers{};
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);

    std::cout << "int top: " << numbers.top() << '\n';
    numbers.pop();
    std::cout << "int length: " << numbers.length() << '\n';
    std::cout << "int empty: " << (numbers.empty() ? "yes" : "no") << '\n';

    Stack<char, std::string> letters{};
    letters.push('a');
    letters.push('b');
    letters.push('c');

    std::cout << "char top: " << letters.top() << '\n';
    letters.pop();
    std::cout << "char length: " << letters.length() << '\n';
    std::cout << "char empty: " << (letters.empty() ? "yes" : "no") << '\n';

    return 0;
}
