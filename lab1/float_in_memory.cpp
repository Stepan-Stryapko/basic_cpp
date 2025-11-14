#include<iostream>


using std::cout;
using std::cin;
using std::endl;

//float in memory (like int, but float)
void bin_float(float *n) {
    cout << endl << "представление флотов в памяти" << endl << endl;
    int *i = (int*) n;
    cout << "Your float in memory: "<< endl;
    for(int j = 31; j >= 0; --j){
        cout << ((*i >> j) & 1);
        if (j == 31 || j == 23)
            cout << " ";
    }

    cout << endl << endl;
}

//difference between numberx
void sensetivity() {
    cout << endl << "разность номеров" << endl << endl;
    float x = 1.0f;
    while (x != (x+1.0f))
        x *= 2;
    cout << "y: для любого x > y -> x == x+1: " << static_cast<int>(x) << endl;

    cout << "Числа, между которыми ошибка составляет 1: " << endl
    << "(1 + 0)*2^23 = " << (2<<23) << " и (1 + 2^-23)*2^23) = "<< ((2<<23)+1) << endl << endl;
}

//ROW
//если бы ряд расходился, цикл был бы бесконечным
void row() {
    cout << endl << "ирсследование ряда" << endl << endl;
    float sum = 0.0f;
    int k = 1;
    do{
        sum += 1.0f/k;
        ++k;
    }while(sum+(1.0f/k) != sum);
    cout << "Сумма: " << sum << endl;
    cout << "Искомое число:  " << 1.0f/k << " | С номером: " << k <<  endl << endl;

    sum = 0.0f;
    for (int i = 1; i <= k + 100; ++i) {
        sum += 1.0f / i;
    }
    cout << "Новая сумма (к+100) is " << sum << endl;

    sum = 0.0f;
    for (int i = k + 100; i >= 1; --i) {
        sum += 1.0f / i;
    }
    cout << "Реверснутая сумма is " << sum << endl;
}

int main()
{
    float num;
    cin >> num;

    bin_float(&num);

    sensetivity();

    
    cout << endl << "Ассоциативность" << endl << endl;
    cout << static_cast<bool>(0.1f + (0.1f+0.5f) == (0.1f + 0.1f)+0.5f) << endl;
    

    row();

   


    cout << endl << "end" << endl << endl;
    return 0;
}