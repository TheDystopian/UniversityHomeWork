#include <iostream>

using namespace std;
void spin_1() {
    int a, b, c, res = 0;
    cout << "Сколько стоит основа: ";
    cin >> a;

    cout << "Сколько стоит лопасть: ";
    cin >> b;

    cout << "Сколько пользователь может максимум заплатить за продукт: ";
    cin >> c;

    c -= a;

    if (c < b) {
        cout << "Ему хватит только на основу или вообще не хватит"; return;
    }

    cout << c / b;
}

void spin_2() {
    int a,spin_f=0;

    cout << "Сколько у вас лопастей: ";
    if (!(cin >> a)) return;

    while (a % 3 > 0 && a > 3) {
        a -= 4;
        spin_f += 1;
    }

    cout << a / 3 << "\n" << spin_f;
}

void not_spin() {
    int n, m, res = 0;

    cout << "Ширина и высота?\n";
    cin >> n >> m;

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            res += m > 1 ? i + 1 : 0;
        }
        res += n > 1 ? j + 1 : 0; // Вперед тернарники, освободите от лишнего кода
    }

    cout << res;
}

void НУ_НЕ_НАДО() {
    bool coupe[] = { true,true,true,true,true,true,true,true,true };
    int place = -1, count = 0, max = 0, temp_place;


    while (cin >> temp_place) {
        if (temp_place == place) { cout << 0; return; }
        if (temp_place > 54 || temp_place < 1) break;
        place = temp_place;
        coupe[place < 36 ? place / 4 : 8 - ((place + 1) / 2 - 19)] = false;
    }

    for (auto a : coupe) {
        count += a == 1 ? 1 : -count; // C++ думал, что я его не переигаю? Что я его не уничтожу? Я его переиграл вот так (Тернарники не прнимали булеву логику)
        if (count > max) max = count;
    }
    cout << max;
}

void ААААА_ХВАТИТ() {
    int n, q, max;

    cout << "Количество мест: ";
    if (!(cin >> n)) { cout << "ЭТО НАУЧНО НЕВОЗМОЖНО"; return; }

    cout << "Количество школьников: ";
    if (!(cin >> q) || q > n) { cout << "Боюсь, что они не поместятся"; return; }

    max = n/q + (n % q > 0 ? 1 : 0); // Внезапно я додумался до более элегантного решения

    cout << (max - 1) / 2 << "\n" << max / 2;
}


int main() {
    setlocale(0, "");

    short int choice;
    cout << "Выберите программу\n1. Спиннеры\n2. Снова спиннеры\n3. Не про спиннеры\n4. Плацкартный вагон\n5. Кинотеатр\n";
    cin >> choice;

    switch (choice) {
    case 1: {spin_1(); break; }
    case 2: {spin_2(); break; }
    case 3: {not_spin(); break; }
    case 4: {НУ_НЕ_НАДО(); break; }
    case 5: {ААААА_ХВАТИТ(); break; }
    default: cout << "Сейчас к вам приклеют спиннер, который вы всегда будете крутить";
    }
}

