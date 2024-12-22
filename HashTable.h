#pragma once
#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

// Структура для узла связного списка
struct Node {
    string key;       // Ключ (имя сотрудника)
    string value;     // Значение (имя менеджера)
    Node* next;       // Указатель на следующий узел

    Node(string k, string v) : key(k), value(v), next(nullptr) {}  // Конструктор для создания нового узла
};

struct HashTable {
    Node* table[TABLE_SIZE]; 

    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
};

void initHashTable(HashTable& hashTable);           // Инициализация хэш-таблицы
int hashFunction(const string& key);  // Хэш-функция для получения индекса
void insert(HashTable& hashTable, const string& key, const string& value); // Вставка элемента в хэш-таблицу
void ensureManagerExists(HashTable& countTable, const string& manager);
bool existsInTable(HashTable& hashTable, const string& key);
void addToVisited(string visited[], int& size, const string& key);
bool isVisited(string visited[], int size, const string& key);
int getSubordinateCount(HashTable& hashTable, const string& manager, string visited[], int& visitedSize);
void printCounts(const HashTable& countTable);
void freeMemory(HashTable& hashTable);
void countSubordinates(HashTable& hashTable);
