// Эта версия имеет эксперементальное решение 4 пункта, которое меньше и кажись более элегантное, чем было

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void monthly_pay() {
    double S, n, p;

    cout << "Сколько займ? ";
    if (!(cin >> S) || (S < 0)) return;
    cout << "На сколько лет? ";
    if (!(cin >> n) || (n < 0)) return;
    cout << "Какой процент? ";
    if (!(cin >> p) || (p < 0)) return;

    p /= 100;
    double percyear = pow(1 + p, n);
    cout << "Месячная выплата: " << (S * p * percyear) / (12 * (percyear - 1)) << endl;
}

void perc() {
    double m,S,n,r = -0.001;

    cout << "Сколько займ? ";
    if (!(cin >> S) || (S < 0)) return;
    cout << "Сколько лет выплачивать? ";
    if (!(cin >> n) || (n < 0)) return;
    cout << "Какая месячная выплата? ";
    if (!(cin >> m) || (m < 0)) return;
    
    if ((S * r * pow(1 + r, n)) / (12 * (pow(1 + r, n) - 1)) > m) cout << "Ты это не выплатишь!\n"; 
    else {
        r += 0.002;
        while ((S * r * pow(1 + r, n)) / (12 * (pow(1 + r, n) - 1)) < m) r += 0.001;
        cout << "Процент: " << r * 100 << "%" << endl;
    }
}


// 3
#include <iostream>

void file_create_and_write() {
    string a, b;

    cout << "Запись в текстовый файл. напишите то, что нужно туда написать\n";
    getline(cin,a);
    getline(cin, a);
    ofstream fout("111.txt");
    fout << a;
    fout.close();

    ifstream fin("111.txt");
    getline(fin, b);
    fin.close();

    cout << "В тектовом файле записано\n" << b << endl;
}


void only_num_out() {
    string a, b;
    
    cout << "Эта программа выведет только числа, окруженные пробелами. Вводить можно что угодно\n"; getchar();

    inputgoto1:getline(cin,a);
    if (a.length() == 0) { cout << "Введи что нибудь!\n"; goto inputgoto1; }
    ofstream out1("abc.txt");
    out1 << a;
    ifstream in1("abc.txt");
    in1 >> a;
    ofstream out2("123.txt");

    stringstream ss(a);
    while (getline(ss, b, ' ')) {
        int dot_1 = b.find('.'), dot_2 = b.substr(dot_1 + 1).find('.');
        if (b.length() != 0 && b.substr(1).find('-') == -1 && (b[0] != '-' || b.length() > 1) && (dot_1 == -1 || (dot_1 > 0 && b[0] != '-') || dot_1 > 1) && dot_2 == -1) {
            for (int i = 0; i < b.length(); i++) {
                if (!(isdigit(b[i]) || b[i] == '-' || b[i] == '.')) { b.clear(); break; }
            }
            if (b.length() != 0) { out2 << b << " "; cout << b << " "; }
        }
    }
    cout << endl;
}

// Quicksort
// 
// Работает так: 
// Берем меньшую и большую точки массива
// Потом отсекаем из любой точки разделитель (тут от самой большей точки массива)
// Далее сканируется массив с начала до конца. Все, что меньше разделителя идет в начало
// Потом функция возвращает место той точки, относительно которой все сортировалось
// Далее контроллирующая функция вызывается рекурсивно (волноваться не нужно, ибо тут самая большая точка для сортировки уходит в начало)
// Когда дойдет до начала, функция пойдет в сторону конца, и проделает то же самое
// Таким образом выйдет сортированный массив

int partitioner(string &b, int lowestpos, int highestpos) {
    int pivot = highestpos;
    int lowpos1 = lowestpos;
    for (int i = lowestpos; i < highestpos; i++) {
        if (tolower(b[i]) < tolower(b[pivot])) {
            swap(b[i], b[lowpos1]);
            lowpos1++;
        }
    }
    swap(b[lowpos1], b[pivot]);
     return lowpos1;
}

void quicksortctl (string &b,int lowestpos, int highestpos) {
     if (lowestpos < highestpos) {
        int partindex = partitioner(b,lowestpos,highestpos);

        quicksortctl(b, lowestpos, partindex - 1);
        quicksortctl(b, partindex + 1, highestpos);
    }
}

string upperinsert (string upper, string lower) {
    for (int i = 0; i < lower.length(); i++) {
        if (upper[0] + 32 == lower[i]) {
            lower[i] = upper[0];
            upper.erase(upper.begin());
        }
        if (upper.length() == 0) break;
    }
    return lower;
}

void sorter() {
    string a, b, bupper;

    cout << "Что вам надо отсортировать?\n";

    getline(cin, a);
    inputgoto1:getline(cin, a);
    if (a.length() == 0) { cout << "Введи что нибудь!\n"; goto inputgoto1; }
    ofstream fout1("111.txt");
    fout1 << a;
    fout1.close();

    ifstream fin1("111.txt");
    getline(fin1, b);
    fin1.close();

    quicksortctl(b, 0, b.length() - 1);
    for (int i = 0; i < b.length(); i++) if (isupper(b[i])) { bupper.push_back(b[i]); b[i] = tolower(b[i]); }
    b = upperinsert(bupper, b);

    ofstream fout2("111.txt");
    fout2 << b;
    fout2.close();

    ifstream fin2("111.txt");
    getline(fin2, a);
    fin2.close();

    cout << "Отсортировано!\n" << a << endl;
}

int main() {
    setlocale(0, "");
    short int x;
    cout << "Выберите программу\n1. Вычисление месячной выплаты\n2. Ссуда\n3. Копирование файла\n4. Фильтр чисел\n5. Сортировка строки\n";
    cin >> x;
    switch (x) {
    case 1: {monthly_pay(); break; }
    case 2: {perc(); break;}
    case 3: {file_create_and_write(); break; }
    case 4: {only_num_out(); break; }
    case 5: {sorter(); break; }
    default: cout << "Неправильный ввод!\n";
    }
    system("pause");
}
