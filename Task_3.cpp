#include "SET.h"
#include <limits>

int main() {
    Set mySet;
    int numElements;

    cout << "Введите количество элементов в множестве: ";
    while (true) {
        cin >> numElements;
        if (cin.fail() || numElements <= 0) {  // Проверка на некорректный ввод
            cin.clear();  // Сбросить состояние ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистить входной буфер
            cerr << "Ошибка: введите корректное целое число больше нуля." << endl;
            cout << "Введите количество элементов в множестве: ";
        } else {
            break;
        }
    }

    cout << "Введите элементы множества:\n";
    for (int i = 0; i < numElements; ++i) {
        int element;
        cout << "Элемент " << (i + 1) << ": ";
        
        // Проверка на корректный ввод каждого элемента
        while (true) {
            cin >> element;
            if (cin.fail()) {  // Проверка на некорректный ввод
                cin.clear();  // Сбросить состояние ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистить входной буфер
                cerr << "Ошибка: введите корректное целое число." << endl;
                cout << "Элемент " << (i + 1) << ": ";
            } else {
                try {
                    mySet.add(element);
                    break;  // Выход из цикла ввода текущего элемента
                } catch (const runtime_error& e) {
                    cerr << e.what() << endl;  // Сообщение об ошибке, если элемент уже существует
                    cout << "Элемент " << (i + 1) << ": ";
                }
            }
        }
    }

    int targetSum;
    cout << "Введите целевую сумму для подмножеств: ";
    while (true) {
        cin >> targetSum;
        if (cin.fail() || targetSum <= 0) {  // Проверка на некорректный ввод
            cin.clear();  // Сбросить состояние ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очистить входной буфер
            cerr << "Ошибка: введите корректное целое число больше нуля." << endl;
            cout << "Введите целевую сумму для подмножеств: ";
        } else {
            break;
        }
    }

    cout << "Исходное множество: ";
    mySet.print();

    try {
        // Разделяем множество на подмножества с заданной суммой
        splitSet(mySet, targetSum);
    } catch (const runtime_error& e) {
        // Обработка исключений и вывод сообщения об ошибке
        cerr << e.what() << endl;
    }

    return 0;
}