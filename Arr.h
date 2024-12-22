#pragma once

#include <iostream>
#include <string>

using namespace std;

// Структура для динамического массива
struct Array {
    string* data;  // Указатель на массив строк
    int capacity;  // Емкость массива
    int size;      // Количество элементов в массиве
};

// Функция для инициализации динамического массива
void initArray(Array& arr, int initialCapacity) {
    arr.data = new string[initialCapacity];
    arr.capacity = initialCapacity;
    arr.size = 0;
}

// Функция для добавления элемента в массив
void addElement(Array& arr, const string& value) {
    if (arr.size == arr.capacity) {
        arr.capacity *= 2;  // Увеличиваем емкость массива в 2 раза
        string* newData = new string[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;  // Удаляем старый массив
        arr.data = newData; // Устанавливаем новый массив
    }
    arr.data[arr.size++] = value; // Добавляем элемент и увеличиваем размер массива
}

// Функция для освобождения памяти массива
void freeArray(Array& arr) {
    delete[] arr.data;  // Освобождаем память, выделенную под массив
    arr.data = nullptr;
    arr.capacity = 0;
    arr.size = 0;
}

// Функция для печати массива
void printArray(const Array& arr) {
    cout << "{ ";
    for (int i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << " ";
    }
    cout << "}" << endl;
}

// Функция для вывода всех подмножеств массива
void printAllSubsets(const Array& arr) {
    cout << "Все подмножества:" << endl;

    // Общее количество подмножеств равно 2^n
    int totalSubsets = 1 << arr.size;

    // Временный массив для формирования подмножеств
    Array subset;
    initArray(subset, arr.size);

    for (int subsetMask = 0; subsetMask < totalSubsets; ++subsetMask) {
        subset.size = 0; // Очищаем временное подмножество перед каждым использованием

        for (int i = 0; i < arr.size; ++i) {
            if (subsetMask & (1 << i)) { // Если i-й элемент включен в текущее подмножество
                addElement(subset, arr.data[i]); // Добавляем элемент в подмножество
            }
        }

        printArray(subset); // Выводим текущее подмножество
    }

    freeArray(subset); // Освобождаем память временного массива
}
