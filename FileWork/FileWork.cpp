#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

struct Fraction {
    int chisl;
    int znam;
};


int nod(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


void printFractionToFile(FILE* file, Fraction f1, char op, Fraction f2, Fraction result) {
    fprintf(file, "%d     %d\n", f1.chisl, f2.chisl);
    fprintf(file, "-  %c  -  =  %d/%d\n", op, result.chisl, result.znam);
    fprintf(file, "%d     %d\n\n", f1.znam, f2.znam);
}

int main() {
    setlocale(LC_ALL, "RU");
    Fraction f1, f2, sum, diff;
    FILE* file;

    cout << "Введите первую дробь (числитель и знаменатель через пробел): ";
    cin >> f1.chisl >> f1.znam;
    cout << "Введите вторую дробь (числитель и знаменатель через пробел): ";
    cin >> f2.chisl >> f2.znam;

    // Проверка на нулевой знаменатель
    if (f1.znam == 0 || f2.znam == 0) {
        cout << "Ошибка: знаменатель не может быть равен нулю!" << endl;
        return 1;
    }


    sum.chisl = f1.chisl * f2.znam + f2.chisl * f1.znam;
    sum.znam = f1.znam * f2.znam;
    int delitel = nod(sum.chisl, sum.znam);
    sum.chisl /= delitel;
    sum.znam /= delitel;


    diff.chisl = f1.chisl * f2.znam - f2.chisl * f1.znam;
    diff.znam = f1.znam * f2.znam;
    delitel = nod(diff.chisl, diff.znam);
    diff.chisl /= delitel;
    diff.znam /= delitel;


    fopen_s(&file, "result.txt", "w");
    if (file == NULL) {
        cout << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    printFractionToFile(file, f1, '+', f2, sum);
    printFractionToFile(file, f1, '-', f2, diff);

    fclose(file);
    cout << "Результаты записаны в файл result.txt" << endl;
    return 0;
}
