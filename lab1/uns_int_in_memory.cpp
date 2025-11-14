#include <iostream>

int main() {
    unsigned int number;
    
    // Ввод числа от пользователя
    std::cout << "Введите число типа unsigned int: ";
    std::cin >> number;
    
    // Определяем размер unsigned int в битах
    int bits = sizeof(unsigned int) * 8;
    
    // Выводим побитовое представление
    std::cout << "Побитовое представление: ";
    
    for (int i = bits - 1; i >= 0; i--) {
        unsigned int bit = (number >> i) & 1;
        std::cout << bit;
    }
    std::cout << std::endl;
    
    return 0;
}