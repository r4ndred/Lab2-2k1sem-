#include "Stack.h"

int main() {
    try {
        string expression;
        cout << "Введите арифметическое выражение: ";
        getline(cin, expression);
 
        string postfix = infixToPostfix(expression); // Преобразуем в постфиксную нотацию.
        cout << "Постфиксное выражение: " << postfix << endl;
 
        int result = evaluatePostfix(postfix);       // Вычисляем результат.
        cout << "Результат: " << result << endl;
    } catch (const exception& ex) {
        cerr << ex.what() << endl;                   // Выводим сообщение об ошибке.
    }
    return 0;
}