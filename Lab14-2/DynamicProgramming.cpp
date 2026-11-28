#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// ЧАСТЬ 1: РЮКЗАК С НЕСКОЛЬКИМИ ОГРАНИЧЕНИЯМИ (Вес + Объем)
void solveKnapsack() {
    cout << "\nЗАДАЧА О РЮКЗАКЕ (Вес + Объем)" << endl;
    int N, W_max, V_max;
    cout << "Введите количество предметов: "; cin >> N;
    cout << "Введите максимальный вес рюкзака: "; cin >> W_max;
    cout << "Введите максимальный объем рюкзака: "; cin >> V_max;

    vector<int> weight(N), volume(N), value(N);
    for (int i = 0; i < N; i++) {
        cout << "Предмет " << i + 1 << ": вес, объем, ценность: ";
        cin >> weight[i] >> volume[i] >> value[i];
    }

    // 3D таблица: dp[предмет][вес][объем]
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(W_max + 1, vector<int>(V_max + 1, 0)));

    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= W_max; w++) {
            for (int v = 0; v <= V_max; v++) {
                if (weight[i - 1] <= w && volume[i - 1] <= v) {
                    // Максимум из: не брать предмет ИЛИ взять предмет
                    dp[i][w][v] = max(dp[i - 1][w][v],
                        dp[i - 1][w - weight[i - 1]][v - volume[i - 1]] + value[i - 1]);
                }
                else {
                    dp[i][w][v] = dp[i - 1][w][v];
                }
            }
        }
    }

    // Восстановление предметов
    vector<int> selected;
    int w = W_max, v = V_max;
    for (int i = N; i > 0; i--) {
        if (dp[i][w][v] != dp[i - 1][w][v]) {
            selected.push_back(i - 1);
            w -= weight[i - 1];
            v -= volume[i - 1];
        }
    }

    cout << "\nМаксимальная ценность: " << dp[N][W_max][V_max] << endl;
    cout << "Выбранные предметы (индексы с 1): ";
    for (int i = selected.size() - 1; i >= 0; i--) cout << selected[i] + 1 << " ";
    cout << endl;

    // Вывод таблицы ДП (срез для последнего предмета при максимальном весе)
    cout << "\nТаблица ДП (dp[N][вес][объем] для объема = " << V_max << "):" << endl;
    cout << "Вес:  ";
    for (int ww = 0; ww <= W_max; ww++) cout << setw(4) << ww;
    cout << endl;
    for (int i = 0; i <= N; i++) {
        cout << "i=" << i << ": ";
        for (int ww = 0; ww <= W_max; ww++) {
            cout << setw(4) << dp[i][ww][V_max];
        }
        cout << endl;
    }
}

// ЧАСТЬ 2: LCS С ШТРАФАМИ ЗА ПРОПУСКИ (Gap Penalty)
void solveLCS() {
    cout << "\nLCS C ШТРАФАМИ ЗА ПРОПУСКИ (Gap Penalty)" << endl;
    string X, Y;
    cout << "Введите первую строку: "; cin >> X;
    cout << "Введите вторую строку: "; cin >> Y;

    int m = X.length();
    int n = Y.length();

    // Штрафы: совпадение +2, несовпадение -1, пропуск (гэп) -2
    int match = 2, mismatch = -1, gap = -2;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Инициализация первой строки и столбца (штрафы за пропуски)
    for (int i = 1; i <= m; i++) dp[i][0] = i * gap;
    for (int j = 1; j <= n; j++) dp[0][j] = j * gap;

    // Заполнение таблицы
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int diag = dp[i - 1][j - 1] + (X[i - 1] == Y[j - 1] ? match : mismatch);
            int up = dp[i - 1][j] + gap;
            int left = dp[i][j - 1] + gap;
            dp[i][j] = max({ diag, up, left });
        }
    }

    // Восстановление выравнивания
    string alignX = "", alignY = "";
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + (X[i - 1] == Y[j - 1] ? match : mismatch)) {
            alignX = X[i - 1] + alignX;
            alignY = Y[j - 1] + alignY;
            i--; j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + gap) {
            alignX = X[i - 1] + alignX;
            alignY = "-" + alignY;
            i--;
        }
        else {
            alignX = "-" + alignX;
            alignY = Y[j - 1] + alignY;
            j--;
        }
    }

    cout << "\nМаксимальный балл выравнивания: " << dp[m][n] << endl;
    cout << "Выравнивание X: " << alignX << endl;
    cout << "Выравнивание Y: " << alignY << endl;

    // Вывод таблицы ДП
    cout << "\nТаблица ДП:" << endl;
    cout << "    ";
    for (int j = 0; j <= n; j++) cout << setw(4) << (j == 0 ? '-' : Y[j - 1]);
    cout << endl;
    for (int i = 0; i <= m; i++) {
        cout << (i == 0 ? '-' : X[i - 1]) << ":  ";
        for (int j = 0; j <= n; j++) {
            cout << setw(4) << dp[i][j];
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    cout << "ПРИМЕНЕНИЕ ДИНАМИЧЕСКОГО ПРОГРАММИРОВАНИЯ" << endl;

    solveKnapsack();
    solveLCS();

    return 0;
}