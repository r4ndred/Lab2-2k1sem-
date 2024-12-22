#include "Stack.h"

// Узел стека
struct StackNode {
    int value;
    StackNode* next;
};

// Функция для добавления элемента в стек
void push(StackNode*& top, int value) {
    StackNode* newNode = new StackNode{value, top};  // Создаем новый узел и связываем его с текущим вершиной стека.
    top = newNode;                                   // Обновляем вершину стека, чтобы указывать на новый узел.
}

// Функция для удаления элемента из стека и возврата его значения
int pop(StackNode*& top) {
    if (top == nullptr) {                            // Проверяем, что стек не пуст.
        throw runtime_error("Ошибка: стек пуст (Stack underflow)"); // Выбрасываем исключение, если стек пуст.
    }
    int value = top->value;                          // Сохраняем значение вершины стека.
    StackNode* temp = top;                           // Сохраняем указатель на текущую вершину.
    top = top->next;                                 // Перемещаем вершину стека на следующий элемент.
    delete temp;                                     // Удаляем старую вершину.
    return value;                                    // Возвращаем значение удаленной вершины.
}

// Функция для получения значения верхнего элемента стека без его удаления
int peek(StackNode* top) {
    if (top == nullptr) {                            // Проверяем, что стек не пуст.
        throw runtime_error("Stack is empty");       // Бросаем исключение, если стек пуст.
    }
    return top->value;                               // Возвращаем значение верхнего элемента.
}

// Функция для проверки, пуст ли стек
bool isEmpty(StackNode* top) {
    return top == nullptr;                           // Возвращаем true, если top равен nullptr, иначе false.
}

// Функция для определения приоритета операций
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;            // Операторы сложения и вычитания имеют низкий приоритет.
    if (op == '*' || op == '/') return 2;            // Операторы умножения и деления имеют более высокий приоритет.
    return 0;                                        // Все остальные символы имеют приоритет 0.
}

// Функция для выполнения арифметической операции
int applyOperation(int a, int b, char op) {
    switch (op) {                                    // Выбор операции в зависимости от оператора.
        case '+': return a + b;                      // Сложение.
        case '-': return a - b;                      // Вычитание.
        case '*': return a * b;                      // Умножение.
        case '/': 
            if (b == 0) throw runtime_error("Ошибка: деление на ноль"); // Проверяем, делится ли на ноль.
            return a / b;                            // Деление.
        default: throw runtime_error("Ошибка: неизвестный оператор");  // Исключение для недопустимого оператора.
    }
}

// Преобразование инфиксного выражения в постфиксное
string infixToPostfix(const string& expression) {
    StackNode* operators = nullptr;                  // Инициализируем пустой стек для операторов.
    string postfix;                                  // Переменная для хранения постфиксной нотации.
    bool lastWasOperator = true;                     // Флаг для отслеживания, если предыдущий символ был оператором.
 
    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];                     // Текущий символ выражения.
 
        if (isspace(ch)) continue;                   // Пропускаем пробелы.
 
        if (isdigit(ch) || (ch == '-' && lastWasOperator)) { // Если символ — цифра или отрицательное число.
            if (ch == '-') {                         // Если символ — унарный минус.
                postfix += ch;                       // Добавляем унарный минус в постфиксную строку.
                ++i;                                 // Переходим к следующему символу.
            }
            while (i < expression.length() && isdigit(expression[i])) {  // Считываем все цифры числа.
                postfix += expression[i++];          // Добавляем цифры в постфиксную строку.
            }
            postfix += ' ';                          // Разделяем числа пробелом.
            --i;                                     // Корректируем индекс, чтобы избежать пропуска символов.
            lastWasOperator = false;                // Устанавливаем флаг, что последний символ — не оператор.
        } else if (ch == '(') {                      // Если символ — открывающая скобка.
            push(operators, ch);                     // Добавляем её в стек операторов.
            lastWasOperator = true;                 // Открывающая скобка считается оператором.
        } else if (ch == ')') {                      // Если символ — закрывающая скобка.
            while (!isEmpty(operators) && peek(operators) != '(') { // Пока не найдем открывающую скобку.
                postfix += static_cast<char>(pop(operators));  // Добавляем оператор из стека в постфиксную строку.
                postfix += ' ';                     // Разделяем пробелом.
            }
            if (!isEmpty(operators)) pop(operators); // Удаляем открывающую скобку из стека.
            lastWasOperator = false;                // Закрывающая скобка завершает число/оператор.
        } else {                                    // Если символ — оператор (+, -, *, /).
            while (!isEmpty(operators) && getPrecedence(peek(operators)) >= getPrecedence(ch)) {
                postfix += static_cast<char>(pop(operators));  // Переносим операторы с большим/равным приоритетом.
                postfix += ' ';
            }
            push(operators, ch);                    // Добавляем текущий оператор в стек.
            lastWasOperator = true;                 // Флаг показывает, что последний символ — оператор.
        }
    }
 
    while (!isEmpty(operators)) {                   // Переносим оставшиеся операторы из стека.
        postfix += static_cast<char>(pop(operators));
        postfix += ' ';
    }
 
    return postfix;                                 // Возвращаем постфиксное выражение.
}

// Вычисление значения постфиксного выражения
int evaluatePostfix(const string& postfix) {
    StackNode* values = nullptr;                    // Инициализируем стек для операндов.
 
    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];                       // Текущий символ из постфиксного выражения.
 
        if (isspace(ch)) continue;                  // Пропускаем пробелы.
 
        if (isdigit(ch) || (ch == '-' && i + 1 < postfix.length() && isdigit(postfix[i + 1]))) {
            int num = 0;
            int sign = 1;
 
            if (ch == '-') {                        // Обрабатываем отрицательное число.
                sign = -1;
                ++i;
            }
 
            while (i < postfix.length() && isdigit(postfix[i])) { // Читаем число из постфиксного выражения.
                num = num * 10 + (postfix[i] - '0'); // Строим число из цифр.
                ++i;
            }
            push(values, sign * num);               // Добавляем число (с учетом знака) в стек.
            --i;                                    // Возвращаемся на один символ назад для корректной итерации.
        } else {                                    // Если символ — оператор.
            int b = pop(values);                    // Извлекаем правый операнд.
            int a = pop(values);                    // Извлекаем левый операнд.
            int result = applyOperation(a, b, ch);  // Выполняем операцию.
            push(values, result);                   // Добавляем результат в стек.
        }
    }
 
    return pop(values);                             // Возвращаем итоговый результат из стека.
}