#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Функция для проверки изоморфности строк
bool areIsomorphic(string a, string b) {
    // Если строки разной длины, они не могут быть изоморфными
    if (a.length() != b.length()) {
        return false;
    }

    // Создаем два словаря для сопоставления символов
    unordered_map<char, char> map_a_to_b;  // Для сопоставления символов из строки a в строку b
    unordered_map<char, char> map_b_to_a;  // Для сопоставления символов из строки b в строку a

    // Проходим по символам обеих строк
    for (int i = 0; i < a.length(); ++i) {
        // Выводим проверку символов
        cout << "Проверяем символы: a[" << i << "] = " << a[i] << " и b[" << i << "] = " << b[i] << endl;

        // Если символ из строки a уже сопоставлен с другим символом в строке b
        if (map_a_to_b.find(a[i]) != map_a_to_b.end()) {
            // Проверяем, соответствует ли текущий символ в строке b уже сопоставленному
            if (map_a_to_b[a[i]] != b[i]) {
                return false; // Если не соответствует, строки не изоморфны
            }
        } else {
            // Если символ из строки a еще не сопоставлен, то добавляем пару в словарь
            map_a_to_b[a[i]] = b[i];
            cout << "Добавлено сопоставление: " << a[i] << " -> " << b[i] << endl;
        }

        // Повторяем аналогичную проверку для второго направления (с b в a)
        if (map_b_to_a.find(b[i]) != map_b_to_a.end()) {
            if (map_b_to_a[b[i]] != a[i]) {
                return false; // Если не соответствует, строки не изоморфны
            }
        } else {
            map_b_to_a[b[i]] = a[i];
            cout << "Добавлено сопоставление: " << b[i] << " -> " << a[i] << endl;
        }
    }

    // Если все символы сопоставлены корректно, строки изоморфны
    return true;
}

int main() {
    // Пример 1
    string str1 = "fall";
    string str2 = "redd";

    // Выводим пример и результат для первой пары строк
    cout << "Пример: \"" << str1 << "\" и \"" << str2 << "\"" << endl;
    cout << "Проверка:" << endl;
    if (areIsomorphic(str1, str2)) {
        cout << "Результат: строки изоморфны" << endl;
    } else {
        cout << "Результат: строки не изоморфны" << endl;
    }

    // Пример 2
    string str3 = "hype";
    string str4 = "ilya";

    // Выводим пример и результат для второй пары строк
    cout << "\nПример: \"" << str3 << "\" и \"" << str4 << "\"" << endl;
    cout << "Проверка:" << endl;
    if (areIsomorphic(str3, str4)) {
        cout << "Результат: строки изоморфны" << endl;
    } else {
        cout << "Результат: строки не изоморфны" << endl;
    }

    return 0;
}
