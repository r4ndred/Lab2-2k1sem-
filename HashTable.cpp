#include "HashTable.h"

// Инициализация хэш-таблицы
void initHashTable(HashTable& hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable.table[i] = nullptr; // Инициализация каждой ячейки как пустой
    }
}
 
// Простая хеш-функция для строки
int hashFunction(const string& key) {
    int hash = 0; // Инициализация переменной hash значением 0
    for (char ch : key) { // Проход по каждому символу строки (ключа)
        hash += ch; // Добавление ASCII-кода символа к переменной hash
    }
    return hash % TABLE_SIZE; // Возвращаем хеш по модулю TABLE_SIZE (размер таблицы)
}
 
// Метод для вставки элемента в хэш-таблицу
void insert(HashTable& hashTable, const string& key, const string& value) {
    int index = hashFunction(key); // Получаем индекс для вставки
    Node* newNode = new Node(key, value); // Создаем новый узел с ключом и значением
 
    // Вставляем элемент в начало цепочки (метод цепочек для обработки коллизий)
    newNode->next = hashTable.table[index];
    hashTable.table[index] = newNode;
}

// Метод для проверки, существует ли запись для менеджера, если нет, то добавляем с 0
void ensureManagerExists(HashTable& countTable, const string& manager) {
    int index = hashFunction(manager);
    Node* current = countTable.table[index];
    while (current != nullptr) {
        if (current->key == manager) {
            return; // Менеджер уже существует, ничего не делаем
        }
        current = current->next;
    }
    // Если менеджер не найден, добавляем его с количеством 0
    insert(countTable, manager, "0");
}
 
// Метод для проверки существования ключа в хэш-таблице
bool existsInTable(HashTable& hashTable, const string& key) {
    int index = hashFunction(key);
    Node* current = hashTable.table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true; // Ключ найден
        }
        current = current->next;
    }
    return false; // Ключ не найден
}
 
// Метод для добавления ключа в массив посещенных
void addToVisited(string visited[], int& size, const string& key) {
    visited[size] = key;
    ++size;
}
 
// Метод для проверки, был ли ключ уже посещен
bool isVisited(string visited[], int size, const string& key) {
    for (int i = 0; i < size; ++i) {
        if (visited[i] == key) {
            return true;
        }
    }
    return false;
}
 
// Метод для получения всех подчиненных (рекурсивно)
int getSubordinateCount(HashTable& hashTable, const string& manager, string visited[], int& visitedSize) {
    // Проверяем, если менеджер уже посещен, чтобы избежать бесконечной рекурсии
    if (isVisited(visited, visitedSize, manager)) {
        return 0;
    }
    addToVisited(visited, visitedSize, manager); // Добавляем менеджера в посещенные
 
    int count = 0; // Счетчик подчиненных
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = hashTable.table[i];
        while (current != nullptr) {
            // Проверяем, если текущая пара представляет цикл (менеджер указывает на самого себя)
            if (current->value == manager && current->key == manager) {
                current = current->next;
                continue; // Игнорируем эту пару
            }
 
            if (current->value == manager) { // Если текущий узел указывает на менеджера
                count += 1; // Считаем непосредственного подчиненного
                count += getSubordinateCount(hashTable, current->key, visited, visitedSize); // Рекурсивный подсчет подчиненных текущего подчиненного
            }
            current = current->next;
        }
    }
    return count;
}

// Метод для вывода количества подчиненных
void printCounts(const HashTable& countTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = countTable.table[i];
        while (current != nullptr) {
            cout << current->key << " - " << current->value << endl; // Печатаем ключ и количество подчиненных
            current = current->next; // Переходим к следующему узлу
        }
    }
}
 
// Метод для освобождения памяти
void freeMemory(HashTable& hashTable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = hashTable.table[i];
        while (current != nullptr) {
            Node* temp = current; // Сохраняем текущий узел во временную переменную
            current = current->next; // Переходим к следующему узлу
            delete temp; // Удаляем текущий узел
        }
        hashTable.table[i] = nullptr; // Обнуляем указатель на начало цепочки
    }
}
 
// Метод для подсчета количества сотрудников, подчиненных каждому менеджеру
void countSubordinates(HashTable& hashTable) {
    HashTable countTable;
    initHashTable(countTable); // Инициализация таблицы для подсчета подчиненных
 
    // Сначала добавляем всех уникальных менеджеров в таблицу для подсчета с начальными значениями
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = hashTable.table[i];
        while (current != nullptr) {
            ensureManagerExists(countTable, current->value); // Убеждаемся, что запись для менеджера есть
            current = current->next;
        }
    }
 
    // Подсчитываем подчиненных для каждого менеджера
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = hashTable.table[i];
        while (current != nullptr) {
            string visited[TABLE_SIZE]; // Массив для отслеживания посещенных узлов
            int visitedSize = 0; // Размер массива посещенных
            int count = getSubordinateCount(hashTable, current->key, visited, visitedSize);
            insert(countTable, current->key, to_string(count));
            current = current->next;
        }
    }
 
    // Выводим результат
    printCounts(countTable);
    freeMemory(countTable); // Освобождаем память, выделенную для countTable
}
 
