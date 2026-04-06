#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Функция для ввода числа с проверкой диапазона от 1 до 100
int inputNumber(const string& prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число от 1 до 100." << endl;
        }
        else if (number < 1 || number > 100) {
            cout << "Ошибка! Число должно быть от 1 до 100." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}

// Функция для ввода матрицы с клавиатуры
void inputMatrix(int** matrix, int size, const string& name) {
    cout << "\nВведите элементы матрицы " << name << " (" << size << "x" << size << "):" << endl;
    cout << "Числа должны быть целыми от 1 до " << size << " (для латинского квадрата)." << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            string prompt = "Элемент [" + to_string(i + 1) + "][" + to_string(j + 1) + "]: ";
            matrix[i][j] = inputNumber(prompt);
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int size, const string& name) {
    cout << "\nМатрица " << name << " (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для проверки, является ли матрица латинским квадратом
bool isLatinSquare(int** matrix, int size) {
    // Проверка строк
    for (int i = 0; i < size; i++) {
        bool* seen = new bool[size + 1](); // +1 для индексации от 1 до size

        for (int j = 0; j < size; j++) {
            int val = matrix[i][j];
            // Проверка, что число в диапазоне от 1 до size
            if (val < 1 || val > size) {
                delete[] seen;
                return false;
            }
            // Проверка на повторение в строке
            if (seen[val]) {
                delete[] seen;
                return false;
            }
            seen[val] = true;
        }
        delete[] seen;
    }

    // Проверка столбцов
    for (int j = 0; j < size; j++) {
        bool* seen = new bool[size + 1]();

        for (int i = 0; i < size; i++) {
            int val = matrix[i][j];
            // Проверка, что число в диапазоне от 1 до size
            if (val < 1 || val > size) {
                delete[] seen;
                return false;
            }
            // Проверка на повторение в столбце
            if (seen[val]) {
                delete[] seen;
                return false;
            }
            seen[val] = true;
        }
        delete[] seen;
    }

    return true;
}

// Функция для проверки и вывода результата
void checkLatinSquare(int** matrix, int size, const string& name) {
    cout << "\n=== Проверка матрицы " << name << " ===" << endl;
    printMatrix(matrix, size, name);

    if (isLatinSquare(matrix, size)) {
        cout << "\nРезультат: Матрица " << name << " ЯВЛЯЕТСЯ латинским квадратом!" << endl;
        cout << "Каждая строка и каждый столбец содержат все числа от 1 до " << size << "." << endl;
    } else {
        cout << "\nРезультат: Матрица " << name << " НЕ ЯВЛЯЕТСЯ латинским квадратом." << endl;
        cout << "Условие нарушено (число вне диапазона 1.." << size
             << " или есть повторения в строке/столбце)." << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "=== Программа проверки латинского квадрата ===" << endl;
    cout << "Латинский квадрат порядка n — это матрица n x n," << endl;
    cout << "в которой каждая строка и каждый столбец содержат все числа от 1 до n." << endl;

    // Запрос размера матрицы
    int size;
    cout << "\nВведите порядок матрицы n (от 1 до 100): ";
    size = inputNumber("n = ");

    // Создание матрицы
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    // Ввод матрицы
    inputMatrix(matrix, size, "M");

    // Проверка
    checkLatinSquare(matrix, size, "M");

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
