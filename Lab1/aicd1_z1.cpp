#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <cstdlib>
#include <ctime>

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;

void createFiles() {
    std::ofstream f1("file1.txt");
    if (!f1.is_open()) {
        std::cerr << "Не удалось открыть файл file1.txt" << std::endl;
        return;
    }
    std::cout << "Файл file1.txt успешно создан и открыт" << std::endl;

    int k = 1, m = 2, n = 3;
    f1 << k << " " << m << " " << n << std::endl;
    for (int qty = 0; qty < k; qty++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                f1 << rand() % 201 - 100 << " ";
            }
            f1 << std::endl;
        }
    }
    f1.close();

    std::ofstream f2("file2.txt");
    if (!f2.is_open()) {
        std::cerr << "Не удалось открыть файл file2.txt " << std::endl;
        return;
    }
    std::cout << "Файл file2.txt успешно создан и открыт" << std::endl;

    f2 << k << " " << n << std::endl;
    for (int qty = 0; qty < k; qty++) {
        for (int j = 0; j < n; j++) {
            f2 << rand() % 201 - 100 << std::endl;
        }
    }
    f2.close();
}

Matrix readFile1(int& k, int& m, int& n) {
    std::ifstream ff1("file1.txt");
    if (!ff1.is_open()) {
        std::cerr << "Не удалось открыть файл file1.txt" << std::endl;
        return{};
    }

    ff1 >> k >> m >> n;
    Matrix ma(m, std::vector<int>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ff1 >> ma[i][j];
        }
    }
    ff1.close();
    return ma;
}

Vector readFile2(int& k, int& n) {
    std::ifstream ff2("file2.txt");
    if (!ff2.is_open()) {
        std::cerr << "Не удалось открыть файл file2.txt" << std::endl;
        return{};
    }

    ff2 >> k >> n;
    Vector ve(n);
    for (int i = 0; i < n; i++) {
        ff2 >> ve[i];
    }
    ff2.close();
    return ve;
}

void outputMatrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void outputVector(const Vector& ve) {
    for (int i = 0; i < ve.size(); i++) {
        std::cout << ve[i] << std::endl;
    }
}

Vector prod(const Matrix& ma, const Vector& ve) {
    int m = ma.size();
    int n = ma[0].size();
    Vector result(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += ma[i][j] * ve[j];
        }
    }
    return result;
}

struct MatrixIO {
    Matrix ma;
    Vector ve;
    Vector result;
};

void saveProd(const MatrixIO& strm, int k, int m, int n) {
    std::ofstream f3("file3.txt");
    if (!f3.is_open()) {
        std::cerr << "Не удалось открыть файл file3.txt" << std::endl;
        return;
    }
    f3 << k << " " << m << " " << n << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            f3 << strm.ma[i][j] << " ";
        }
        f3 << std::endl;
    }
    for (int i = 0; i < n; i++) {
        f3 << strm.ve[i] << std::endl;
    }
    for (int i = 0; i < m; i++) {
        f3 << strm.result[i] << std::endl;
    }
    f3.close();
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));
    createFiles();

    int k, m, n;
    Matrix ma = readFile1(k, m, n);
    std::cout << "\nМатрица из file1: k = " << k << " m = " << m << " n = " << n << std::endl;
    outputMatrix(ma);

    int k2, n2;
    Vector ve = readFile2(k2, n2);
    std::cout << "\nВектор из file2: k = " << k2 << " n = " << n2 << std::endl;
    outputVector(ve);

    Vector re = prod(ma, ve);
    std::cout << "\nРезультат произведений соответствующих матриц из file1 и file2: " << std::endl;
    outputVector(re);

    MatrixIO str{ ma,ve,re };
    saveProd(str, k, m, n);
    std::cout << "\nРезультат произведений записан в file3.txt" << std::endl;

    return 0;
}