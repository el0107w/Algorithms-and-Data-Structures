#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale>

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));

	const int N = 5;
	int matrix[N][N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 201 - 100;
		}
	}
	std::ofstream wstart("strGrid.bin", std::ios::binary);
	if (!wstart.is_open()) {
		std::cerr << "Не удалось открыть файл strGrid.bin" << std::endl;
		return 1;
	}
	wstart.write((char*)matrix, sizeof(matrix));
	wstart.close();

	std::cout << "Матрица до изменения: " << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::ifstream rstart("strGrid.bin", std::ios::binary);
	if (!rstart.is_open()) {
		std::cerr << "Не удалось открыть файл strGrid.bin" << std::endl;
		return 1;
	}
	rstart.read((char*)matrix, sizeof(matrix));
	rstart.close();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] *= 2;
		}
	}
	std::ofstream wresult("strGrid.bin", std::ios::binary);
	if (!wresult.is_open()) {
		std::cerr << "Не удалось открыть файл strGrid.bin" << std::endl;
		return 1;
	}
	wresult.write((char*)matrix, sizeof(matrix));
	wresult.close();

	std::ifstream rresult("strGrid.bin", std::ios::binary);
	if (!rresult.is_open()) {
		std::cerr << "Не удалось открыть файл strGrid.bin" << std::endl;
		return 1;
	}
	rresult.read((char*)matrix, sizeof(matrix));
	rresult.close();

	std::cout << "\nМатрица после изменения: " << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	return 0;
}