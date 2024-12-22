#include "Arr.h"

int main() {
    Array arr;
    initArray(arr, 4); // Инициализируем массив с емкостью 4

    int n;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string element;
        cout << "Элемент " << (i + 1) << ": ";
        cin >> element;
        addElement(arr, element); // Добавляем элементы в массив
    }

    cout << "Исходный массив: ";
    printArray(arr);

    printAllSubsets(arr); // Выводим все подмножества

    freeArray(arr); // Освобождаем память
    return 0;
}