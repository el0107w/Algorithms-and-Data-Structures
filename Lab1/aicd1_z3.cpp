#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

struct Client {
	char fio[100];
	double monthPay;
	int pMonth;
	int fMonth;
};

int main() {
	setlocale(LC_ALL, "");
	
	const int N = 3;
	Client person[N]{
		{"Попова  В.Р.", 550, 12, 3},
		{"Калмазова С.В.", 740, 9, 2},
		{"Утов А.А.", 1020, 6, 5}
	};
	std::ofstream w("cData.bin", std::ios::binary);
	if (!w.is_open()) {
		std::cerr << "Не удалось открыть файл cData.bin" << std::endl;
		return 1;
	}
	w.write((char*)person, sizeof(person));
	w.close();

	std::fstream rw("cData.bin", std::ios::in | std::ios::out | std::ios::binary);
	if (!rw.is_open()) {
		std::cerr << "Не удалось открыть файл cData.bin" << std::endl;
		return 1;
	}
	
	Client st;
	while (rw.read((char*)&st, sizeof(st))) {
		if (st.fMonth == 3) {
			st.monthPay *= 0.93;

			rw.seekp(-(std::streamoff)sizeof(Client), std::ios::cur);
			rw.write((char*)&st, sizeof(st));
			rw.seekg(rw.tellp());
		}
	}
	rw.close();

	std::ifstream r("cData.bin", std::ios::binary);
	if (!r.is_open()) {
		std::cerr << "Не удалось открыть файл cData.bin" << std::endl;
		return 1;
	}
	r.read((char*)person, sizeof(person));
	r.close();

	std::cout << "Содержимое бинарного файла после переписания:\n" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << "Фамилия и инициалы клиентов: " << person[i].fio << std::endl;
		std::cout << "Стоимость оплаты услуг за месяц: " << person[i].monthPay << std::endl;
		std::cout << "Количество месяцев оплаты за услуги: " << person[i].pMonth << std::endl;
		std::cout << "Количество месяцев оплаты вперёд за услуги: " << person[i].fMonth << std::endl;
		std::cout << std::endl;
	}

	return 0;
}