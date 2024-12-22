#include "ATDset.h"

int main(int argc, char* argv[]) {
    MySet<int> mySet; // Создание множества
    string command;
    int element;

    while (true) {
        cout << "Введите команду (add, delete, contains, size, load, save, back): ";
        cin >> command;

        if (command == "add") {
            cout << "Введите элемент для добавления: ";
            cin >> element;
            mySet.SETADD(element);
            cout << "Элемент " << element << " добавлен." << endl;

        } else if (command == "delete") {
            cout << "Введите элемент для удаления: ";
            cin >> element;
            mySet.SETDEL(element);

        } else if (command == "contains") {
            cout << "Введите элемент для проверки: ";
            cin >> element;
            if (mySet.SET_AT(element)) {
                cout << "Элемент " << element << " присутствует в множестве." << endl;
            } else {
                cout << "Элемент " << element << " отсутствует в множестве." << endl;
            }

        } else if (command == "size") {
            cout << "Размер множества: " << mySet.getSize() << endl;

        } else if (command == "load") {
            string filename;
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            try {
                mySet.loadFromFile(filename);
                cout << "Множество загружено из файла " << filename << "." << endl;
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }

        } else if (command == "save") {
            string filename;
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            try {
                mySet.saveToFile(filename);
                cout << "Множество сохранено в файл " << filename << "." << endl;
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }

        } else if (command == "back") {
            cout << "Выход из программы." << endl;
            break;

        } else {
            cout << "Неизвестная команда. Попробуйте снова." << endl;
        }

        // Опционально: вывод текущего состояния множества
        mySet.print();
    }

    return 0;
}