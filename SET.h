#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node { 
    int value;       // Значение узла списка.
    Node* next;      // Указатель на следующий узел.
};
 
// Структура для хранения множества
struct Set {
    Node* head;  // Указатель на начало односвязного списка.
    int size;    // Количество элементов в множестве.
 
    // Конструктор множества
    Set() : head(nullptr), size(0) {} // Инициализируем пустое множество.
 
    // Добавление элемента в множество
    void add(int value) {
        if (contains(value)) { // Проверяем, существует ли уже элемент в множестве.
            throw runtime_error("Ошибка: элемент " + to_string(value) + " уже существует в множестве.");
        }
        Node* newNode = new Node{value, head}; // Создаем новый узел и связываем его с текущим началом списка.
        head = newNode; // Перемещаем указатель на начало списка к новому узлу.
        size++; // Увеличиваем размер множества.
    }
 
    // Проверка, находится ли элемент в множестве
    bool contains(int value) {
        Node* current = head; // Начинаем с головы списка.
        while (current != nullptr) { // Перебираем все узлы списка.
            if (current->value == value) { // Если находим совпадение по значению:
                return true; // Возвращаем true, элемент найден.
            }
            current = current->next; // Переходим к следующему узлу.
        }
        return false; // Если дошли до конца списка, элемент не найден.
    }
 
    // Удаление элемента из множества
    void remove(int value) {
        Node* current = head; // Начинаем с головы списка.
        Node* previous = nullptr; // Указатель на предыдущий узел (изначально nullptr).
 
        while (current != nullptr) { // Перебираем узлы списка.
            if (current->value == value) { // Если нашли нужный узел:
                if (previous == nullptr) { // Если это голова списка:
                    head = current->next; // Перемещаем голову на следующий узел.
                } else { // Если это не голова:
                    previous->next = current->next; // Пропускаем текущий узел.
                }
                delete current; // Удаляем найденный узел.
                size--; // Уменьшаем размер множества.
                return;
            }
            previous = current; // Сохраняем текущий узел как предыдущий.
            current = current->next; // Переходим к следующему узлу.
        }
        throw runtime_error("Ошибка: элемент " + to_string(value) + " не найден в множестве."); // Элемент не найден.
    }
 
    // Вывод всех элементов множества
    void print() {
        Node* current = head; // Начинаем с головы списка.
        cout << "{ ";
        while (current != nullptr) { // Перебираем узлы списка.
            cout << current->value << " "; // Выводим значение текущего узла.
            current = current->next; // Переходим к следующему узлу.
        }
        cout << "}" << endl; // Завершаем вывод множества.
    }
 
    // Функция для очистки множества
    void clear() {
        while (head != nullptr) { // Пока список не пуст:
            Node* temp = head; // Сохраняем текущую голову.
            head = head->next; // Перемещаем голову на следующий узел.
            delete temp; // Удаляем предыдущую голову.
        }
        size = 0; // Обнуляем размер множества.
    }
 
    // Функция для вычисления суммы всех элементов в множестве
    int sum() {
        int total = 0; // Инициализируем сумму.
        Node* current = head; // Начинаем с головы списка.
        while (current != nullptr) { // Перебираем узлы списка.
            total += current->value; // Добавляем значение текущего узла к сумме.
            current = current->next; // Переходим к следующему узлу.
        }
        return total; // Возвращаем сумму.
    }
};
 
// Рекурсивная функция для поиска подмножества с заданной суммой
bool findSubset(Set& set, Set& subset, int targetSum, Node* startNode) {
    if (targetSum == 0) { // Если целевая сумма достигнута:
        return true; // Возвращаем true.
    }
    if (startNode == nullptr || targetSum < 0) { // Если узлы закончились или сумма стала отрицательной:
        return false; // Возвращаем false.
    }
    Node* current = startNode; // Начинаем с текущего узла.
    while (current != nullptr) { // Перебираем узлы списка.
        int value = current->value; // Берем значение текущего узла.
        subset.add(value);            // Добавляем значение во временное подмножество.
        set.remove(value);            // Убираем его из исходного множества.
        if (findSubset(set, subset, targetSum - value, set.head)) { // Рекурсивно ищем остаток суммы.
            return true; // Если нашли подходящее подмножество, возвращаем true.
        }
        subset.remove(value);         // Если не нашли, убираем значение из временного подмножества.
        set.add(value);               // Возвращаем значение обратно в множество.
        current = current->next;      // Переходим к следующему узлу.
    }
    return false; // Если не удалось найти подходящее подмножество, возвращаем false.
}
 
// Основная функция для разбиения множества на подмножества с заданной суммой
void splitSet(Set& set, int targetSum) {
    int totalSum = set.sum(); // Вычисляем сумму всех элементов множества.
    if (totalSum % targetSum != 0) { // Если сумма элементов не делится нацело на целевую сумму:
        throw runtime_error("Ошибка: множество не может быть разбито на подмножества с суммой " + to_string(targetSum) + ".");
    }
 
    int numSubsets = totalSum / targetSum;  // Вычисляем количество подмножеств, которые нужно найти.
    for (int i = 0; i < numSubsets; ++i) { // Итерируемся по количеству подмножеств.
        Set subset;  // Создаем временное подмножество.
        if (findSubset(set, subset, targetSum, set.head)) { // Ищем подмножество с целевой суммой.
            cout << "Подмножество " << (i + 1) << ": "; // Выводим номер подмножества.
            subset.print(); // Выводим найденное подмножество.
        } else { // Если не удалось найти подмножество:
            throw runtime_error("Ошибка: не удалось найти подмножество с суммой " + to_string(targetSum) + ".");
        }
    }
}