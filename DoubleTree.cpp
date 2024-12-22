#include <iostream>
using namespace std;

// Структура узла бинарного дерева поиска
struct TreeNode {
    int value;                  // Значение узла
    TreeNode* left;             // Указатель на левое поддерево
    TreeNode* right;            // Указатель на правое поддерево

    // Конструктор для создания нового узла
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для поиска минимального значения в правом поддереве
TreeNode* findMin(TreeNode* root) {
    // Идем в самое левое поддерево, пока не достигнем минимального узла
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Функция для удаления узла из дерева
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        // Если дерево пустое, просто возвращаем nullptr
        return root;
    }

    if (key < root->value) {
        // Если ключ меньше текущего значения, удаляем из левого поддерева
        root->left = deleteNode(root->left, key);
    } else if (key > root->value) {
        // Если ключ больше текущего значения, удаляем из правого поддерева
        root->right = deleteNode(root->right, key);
    } else {
        // Найден узел, который нужно удалить
        if (root->left == nullptr && root->right == nullptr) {
            // Если у узла нет потомков, просто удаляем его
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            // Если у узла нет левого потомка, заменяем его правым
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            // Если у узла нет правого потомка, заменяем его левым
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            // Если у узла есть оба потомка
            // Находим минимальный узел в правом поддереве
            TreeNode* temp = findMin(root->right);
            // Копируем его значение в текущий узел
            root->value = temp->value;
            // Удаляем минимальный узел из правого поддерева
            root->right = deleteNode(root->right, temp->value);
        }
    }
    return root;
}

// Функция для добавления узла в дерево
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Функция для вывода дерева (прямой обход)
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->value << " ";
    inorderTraversal(root->right);
}

int main() {
    TreeNode* root = nullptr; // Изначально дерево пустое
    int choice;

    do {
        cout << "\nМеню: \n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Показать дерево\n";
        cout << "4. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Введите значение для добавления: ";
                cin >> value;
                root = insert(root, value);
                break;
            }
            case 2: {
                int value;
                cout << "Введите значение для удаления: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            }
            case 3: {
                cout << "Текущее дерево: ";
                inorderTraversal(root);
                cout << endl;
                break;
            }
            case 4: {
                cout << "Выход из программы." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
