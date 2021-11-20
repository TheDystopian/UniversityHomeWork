#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <csignal>

using namespace std;
//////////////////////
// Алгоритм Евклида //
//////////////////////

void Euclid() {
	// Ввод значений
	int a, b;
	cout << "Введите делитель\n";
	if (!(cin >> a)) return;
	cout << "Введите делимое\n";
	if (!(cin >> b)) return;

	// Сам алгоритм Евклида
	while (a != 0 && b != 0) {
		if (a > b) a %= b;
		else b %= a;
	}

	cout << "НОД: " << a + b;
}
//////////////////

void eratosphen() {
	int n;
	cout << "Введите число, до которого надо искать простые числа (Больше 2)\n";
	if (!(cin >> n) || n <= 2) return;
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;

	for (int i = 2; i * i <= n; ++i)
		if (isPrime[i])
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = false;

	cout << "Простые числа\n";
	for (int i = 2; i < n; i++)
		if (isPrime[i]) cout << i << " ";


}

void TextFile() {
	string* filelines = new string;
	cout << "Запись в abc.txt\nЧтобы закончить ввод, не вводите ничего в строке\n"; cin.ignore();

	ofstream out1("abc.txt");

	do {
		getline(cin, *filelines);
		out1 << *filelines << '\n';
	} while (*filelines != "");

	out1.close(); filelines->clear();
	
	vector <string> file;
	fstream in1("abc.txt", ios::in);
	while (getline(in1, *filelines)) file.push_back(*filelines);

	delete filelines;
	cout << "В файле \"abc.txt\" записано:\n";
	for (auto out : file) cout << out << '\n';

	short int choice;
	cout << "\nВыберите действие\n1. Замена пробелов на символы\n2. Поиск фразы минимальной\\максимальной длины\n";
	cin >> choice;
	switch (choice) {
	case 1: {
		cout << "На какой символ заменить пробелы" << endl; cin.ignore();
		char change = cin.get();

		for (int i = 0; i < file.size(); i++) {
			while (file[i].find(' ') != -1) file[i][file[i].find(' ')] = change;
		}
		cout << "Содержимое файла \"abc.txt\" теперь выглядит вот так\n";
		fstream in1("abc.txt", ios::out);
		for (auto out : file) {
			cout << out << '\n';
			in1 << out << '/n';
		}
		break;
	}
	case 2: {
		string min, max, curr;
		for (int i = 0; i < file.size(); i++) {
			stringstream space_split(file[i]); // Деление на пробелы
			while (getline(space_split, curr, ' ')) {
				if (min.length() == 0 || curr.length() < min.length()) min = curr;
				if (max.length() == 0 || curr.length() > max.length()) max = curr;

			}
		
		}
		cout << "Максимальная длина у слова: " << max << ". Его длина равна: " << max.length() << endl;
		cout << "Минимальная длина у слова: " << min << ". Его длина равна: " << min.length() << endl;
	}
	default: {in1.close(); return; }
	}
}

void recursive_math() {
	int n;
	cout << "Введите n: ";
	if (!(cin >> n)) return;

	short int choice;
	cout << "Выберите действие\n1.Вычислить 1/sin(1)+...+n/(sin(1)+...+sin(n))\n1.Вычислить 1!/sin(2)+...+n!/(sin(2)+...+sin(2*n))\n";
	cin >> choice;
	switch (choice) {
	case 1: {
		double sinus_sum = 0, res = 0;
		for (int i = 1; i <= n; i++) {
			sinus_sum += sin(i); // Сумма синусов в знаминателе
			res += i / sinus_sum; // Сам результат
		}
		cout << res;
		break;
	}
	case 2: {
		double factor = 1, sin_sum = 0, res = 0;
		for (int i = 1; i <= n; i++) {
			factor *= i;
			sin_sum += sin(2 * i);
			res += factor / sin_sum;
		}
		cout << res;
		break;
	}
	default: return;
	}
}

void csv_read(vector<vector<int>> &mas, string doc) {
	ifstream *a = new ifstream(doc);
	string *temp = new string, *tmpNum = new string;

	while (*a >> *temp) {
		vector <int>* tempArr = new vector <int>; // Временный массив
		stringstream ss(*temp); // Это позволяет искать 
		while (getline(ss, *tmpNum, ',')) tempArr->push_back(stoi(*tmpNum)); // Чтение строки и последующи переход на следующую
		mas.push_back(*tempArr);
		delete tempArr, tmpNum, temp; // Чтобы не захламлять память
	}
	a->close(); delete a;
}
void csv_write(vector<vector<int>> &mas, string doc) {
	ofstream *a = new ofstream(doc);
	// Запись в столбец
	for (auto z : mas) {
		// Запись в строку
		if (z.size() != 0) {
			for (auto y : z) *a << y << ',';
			*a << endl;
		}
	}
	a->close(); delete a; mas.clear();
}

void File() {
	vector <vector<int>> matrix;

	cout << "Введите матрицу\nЧтобы закончиты ввод введите любое не число.\n";
	for (int i = 0; i < 10; i++) {
		matrix.push_back(*new vector<int>);
		int *tempint = new int;
		for (int j = 0; j < 10; j++) {
			if (!(cin >> *tempint)) break;
			matrix[i].push_back(*tempint);
		}
		delete tempint;
		if (matrix[i].size() < 10) break;
	}
	csv_write(matrix, "1.csv");
	csv_read(matrix, "1.csv");

	for (int j = 0; j < matrix.size(); j++) {
		vector <int> min = { 0 }, max = { 0 };
		for (int i = 1; i < matrix[j].size(); i++) {
			if (matrix[j][i] >= matrix[j][max[0]]) {
				if (matrix[j][i] > matrix[j][max[0]]) max.clear();
				max.push_back(i);
			}
			if (matrix[j][i] <= matrix[j][min[0]]) {
				if (matrix[j][i] < matrix[j][min[0]]) min.clear();
				min.push_back(i);
			}
		}
		for (auto Min : min) matrix[j][Min] = 0;
		for (auto Max : max) matrix[j][Max] = 0;
	}
	csv_write(matrix, "2.csv");
	csv_read(matrix, "2.csv");

	while (matrix.size() < 10) matrix.push_back(*new vector<int>);

	for (int i = 0; i < 10; i++) {
		if (matrix[i].size() < 10) {
			for (int j = 0; j < 10; j++) {
				if (j >= matrix[i].size()) matrix[i].push_back(rand() % 100);
			}
		}
	}
	csv_write(matrix, "3.csv");
	cout << "Все матрицы в csv файлах\n";
}

void struct_num() {
	int k, fibo[3] = { 0, 1, 1 };

	cout << "Введите номер числа Фибоначчи";
	if (!(cin >> k) || k < 0) return;

	if (k < 3) {cout << fibo[k]; return;}
	else {
		for (int i = 3; i <= k; i++) {
			fibo[0] = fibo[1];
			fibo[1] = fibo[2];
			fibo[2] = fibo[0] + fibo[1];
		}
		cout << fibo[2];
	}
}

int main() {
	setlocale(0, "");
	cout << "Выберите задание\n1. Алгоритм Евклида\n2. Решето Эратосфена\n3. Обработка текстовых файлов (1, 3, 5, 12, 13)\n4. Ряды (1 и 3)\n5. Файлы (3)\n6. Структурные числа (Фибоначчи)\n";
	short int choice;
	cin >> choice;
	switch (choice) {
	case 1: {Euclid(); break; }
	case 2: {eratosphen(); break; }
	case 3: {TextFile(); break; }
	case 4: {recursive_math(); break; }
	case 5: {File(); break; }
	case 6: {struct_num(); break; }
	default: cout << "Неправильный ввод";
	}
}
