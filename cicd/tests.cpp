#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

int run_test(string name, string input, string expected);
string run_program(string input);

int main() {
    int failed = 0;

    cout << "=== Запуск тестов для проверки латинского квадрата ===" << endl;

    // Тест 1: Правильный латинский квадрат 3x3
    failed += run_test(
        "Тест 1: Латинский квадрат 3x3 (корректный)",
        "3\n1 2 3\n2 3 1\n3 1 2\n",
        "Матрица M (3x3):\n   1    2    3 \n   2    3    1 \n   3    1    2 \n\nРезультат: Матрица M ЯВЛЯЕТСЯ латинским квадратом!\n"
        );

    // Тест 2: Неправильный квадрат (повтор в строке)
    failed += run_test(
        "Тест 2: Латинский квадрат 3x3 (повтор в строке)",
        "3\n1 2 3\n2 2 1\n3 1 2\n",
        "НЕ ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 3: Неправильный квадрат (число вне диапазона)
    failed += run_test(
        "Тест 3: Латинский квадрат 3x3 (число 4 вне диапазона)",
        "3\n1 2 3\n2 4 1\n3 1 2\n",
        "НЕ ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 4: Правильный латинский квадрат 4x4
    failed += run_test(
        "Тест 4: Латинский квадрат 4x4 (корректный)",
        "4\n1 2 3 4\n2 1 4 3\n3 4 1 2\n4 3 2 1\n",
        "Матрица M (4x4):\n   1    2    3    4 \n   2    1    4    3 \n   3    4    1    2 \n   4    3    2    1 \n\nРезультат: Матрица M ЯВЛЯЕТСЯ латинским квадратом!\n"
        );

    cout << "\n=== Результаты тестов ===" << endl;

    if (failed == 0) {
        cout << "✅ Все тесты пройдены успешно!" << endl;
        return 0;
    } else {
        cout << "❌ Провалено тестов: " << failed << endl;
        return 1;
    }
}

string run_program(string input) {
    // Путь к вашей программе
    string command = "echo \"" + input + "\" | ../usr/bin/trrispo";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw runtime_error("popen failed");
    }

    char buffer[4096];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    return result;
}

int run_test(string name, string input, string expected) {
    string output = run_program(input);

    // Проверяем, содержится ли ожидаемый текст в выводе
    if (output.find(expected) != string::npos) {
        cout << "✅ " << name << " - ПРОЙДЕН" << endl;
        return 0;
    } else {
        cout << "❌ " << name << " - ПРОВАЛЕН" << endl;
        cout << "   Ожидалось: \"" << expected << "\"" << endl;
        cout << "   Получено: \"" << output.substr(0, 100) << "...\"" << endl;
        return 1;
    }
}
