#include "HashTable.h"

int main() {
    HashTable table;
    initHashTable(table);  // Инициализация хэш-таблицы

    // Ввод пар (сотрудник, менеджер) от пользователя
    string employee, manager;
    cout << "Введите пары (сотрудник, менеджер) через пробел. Введите 'END' для завершения ввода:" << endl;
    while (true) {
        cout << "Пара (сотрудник менеджер): ";
        cin >> employee;
        if (employee == "END") {
            break;  // Завершаем ввод при вводе 'END'
        }
        cin >> manager;
        insert(table, employee, manager);  // Вставляем пару в хэш-таблицу
    }

    // Подсчитываем количество подчиненных и выводим результат
    countSubordinates(table);

    // Освобождение памяти
    freeMemory(table);

    return 0;
}