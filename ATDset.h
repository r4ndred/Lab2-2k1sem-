#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template <typename T>
class List {
private:
    // Вложенная структура для узлов списка
    struct Node {
        T data;        // Хранит значение узла.
        Node* next;    // Указатель на следующий узел.
 
        Node(T val) : data(val), next(nullptr) {} // Конструктор инициализирует значение узла и устанавливает указатель на nullptr.
    };
 
    Node* head; // Указатель на первый узел списка.
    int size;   // Хранит количество элементов в списке.
 
    // Дружественный шаблонный класс MySet, чтобы дать ему доступ к приватным членам List.
    template <typename U>
    friend class MySet;
 
public:
    List() : head(nullptr), size(0) {} // Конструктор инициализирует пустой список.
 
    // Добавление элемента в конец списка
    void add(T element) {
        Node* newNode = new Node(element); // Создаем новый узел.
        if (!head) { // Если список пуст:
            head = newNode; // Новый узел становится головой списка.
        } else { // Если список не пуст:
            Node* current = head; // Начинаем с головы списка.
            while (current->next) { // Проходим до последнего узла.
                current = current->next;
            }
            current->next = newNode; // Присоединяем новый узел в конец списка.
        }
        size++; // Увеличиваем размер списка.
    }
 
    // Удаление элемента из списка
    void remove(T element) {
        if (!head) return; // Если список пуст, ничего не делаем.
 
        if (head->data == element) { // Если элемент находится в голове списка:
            Node* temp = head;       // Временный указатель на голову.
            head = head->next;       // Перемещаем голову на следующий узел.
            delete temp;             // Удаляем старую голову.
            size--;                  // Уменьшаем размер списка.
            return;
        }
 
        Node* current = head; // Указатель на текущий узел.
        while (current->next && current->next->data != element) {
            current = current->next; // Проходим по списку, пока не найдем элемент или не дойдем до конца.
        }
 
        if (current->next) { // Если элемент найден:
            Node* temp = current->next;        // Временный указатель на найденный узел.
            current->next = current->next->next; // Убираем узел из цепочки.
            delete temp;                          // Удаляем узел.
            size--;                               // Уменьшаем размер списка.
        }
    }
 
    // Проверка наличия элемента в списке
    bool contains(T element) const {
        Node* current = head; // Начинаем с головы списка.
        while (current) { // Перебираем узлы, пока не дойдем до конца списка.
            if (current->data == element) { // Если нашли элемент:
                return true;
            }
            current = current->next; // Переходим к следующему узлу.
        }
        return false; // Если элемент не найден, возвращаем false.
    }
 
    // Получение размера списка
    int getSize() const {
        return size; // Возвращаем количество элементов в списке.
    }
 
    // Очистка списка
    void clear() {
        while (head) { // Пока список не пуст:
            Node* temp = head; // Временный указатель на текущий узел.
            head = head->next; // Перемещаем голову на следующий узел.
            delete temp;       // Удаляем текущий узел.
        }
        size = 0; // Сбрасываем размер списка.
    }
 
    // Печать списка (для отладки)
    void print() const {
        Node* current = head; // Начинаем с головы списка.
        while (current) { // Перебираем узлы списка.
            std::cout << current->data << " "; // Выводим значение узла.
            current = current->next; // Переходим к следующему узлу.
        }
        std::cout << std::endl; // Завершаем вывод.
    }
 
    // Получение элемента по индексу
    T get(int index) const {
        if (index < 0 || index >= size) { // Проверяем, находится ли индекс в допустимом диапазоне.
            throw std::out_of_range("Индекс вне диапазона"); // Если нет, выбрасываем исключение.
        }
        Node* current = head; // Начинаем с головы списка.
        for (int i = 0; i < index; i++) { // Переходим к нужному узлу.
            current = current->next;
        }
        return current->data; // Возвращаем значение узла.
    }
 
    Node* getHead() const {
        return head; // Возвращаем указатель на голову списка.
    }
 
    // Функция поиска элемента на заданной позиции
    bool find(int index, T value) const {
        if (index < 0 || index >= size) { // Проверяем, находится ли индекс в допустимом диапазоне.
            return false; // Если нет, возвращаем false.
        }
 
        Node* current = head; // Начинаем с головы списка.
        int currentIndex = 0;
 
        while (current) { // Перебираем узлы списка.
            if (currentIndex == index) { // Если индекс совпадает:
                return current->data == value; // Проверяем, совпадает ли значение.
            }
            current = current->next; // Переходим к следующему узлу.
            currentIndex++;
        }
 
        return false; // Если элемент не найден, возвращаем false.
    }
 
    // Деструктор для очистки памяти
    ~List() {
        clear(); // Очищаем список, чтобы освободить память.
    }
};
 
template <typename T>
class MySet {
private:
    List<T> list; // Используем List для хранения уникальных элементов.
 
public:
    // Добавление элемента
    void SETADD(T element) {
        if (!list.contains(element)) { // Добавляем только если элемент отсутствует.
            list.add(element);
        }
    }
 
    // Удаление элемента
    void SETDEL(T element) {
        if (list.contains(element)) { // Удаляем только если элемент существует.
            list.remove(element);
        } else {
            std::cout << "Элемент " << element << " не найден в множестве." << std::endl;
        }
    }
 
    // Проверка наличия элемента
    bool SET_AT(T element) const {
        return list.contains(element); // Проверяем, содержится ли элемент в множестве.
    }
 
    // Получение элемента по индексу
    T SETGET(int index) const {
        return list.get(index); // Получаем элемент списка по индексу.
    }
 
    // Оператор сравнения
    bool operator==(const MySet<T>& other) const {
        if (list.getSize() != other.list.getSize()) { // Если размеры множеств различны, они не равны.
            return false;
        }
 
        for (int i = 0; i < list.getSize(); ++i) { // Проверяем, содержатся ли все элементы одного множества в другом.
            if (!other.SET_AT(list.get(i))) {
                return false;
            }
        }
 
        return true; // Множества равны, если все элементы совпадают.
    }
 
    // Загрузка множества из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream infile(filename); // Открываем файл для чтения.
        if (!infile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения");
        }
 
        T element;
        while (infile >> element) { // Читаем элементы из файла.
            SETADD(element); // Добавляем каждый элемент в множество.
        }
 
        infile.close(); // Закрываем файл.
    }
 
    // Выгрузка множества в файл
    void saveToFile(const std::string& filename) const {
        std::ofstream outfile(filename); // Открываем файл для записи.
        if (!outfile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи");
        }
 
        typename List<T>::Node* current = list.head; // Начинаем с головы списка.
        while (current) { // Перебираем узлы списка.
            outfile << current->data << std::endl; // Записываем значение узла в файл.
            current = current->next; // Переходим к следующему узлу.
        }
 
        outfile.close(); // Закрываем файл.
    }
 
    // Печать множества
    void print() const {
        std::cout << "Множество: ";
        list.print(); // Выводим элементы списка.
    }
 
    // Получение размера множества
    int getSize() const {
        return list.getSize(); // Возвращаем количество элементов множества.
    }
 
    // Очистка множества
    void clear() {
        list.clear(); // Очищаем список.
    }
};