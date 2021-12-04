#include <iostream>

using namespace std;
void spin_1() {
    int a, b, c;

    cout << "Сколько стоит основа: ";
    if (!(cin >> a) || a < 0) return;

    cout << "Сколько стоит лопасть: ";
    if (!(cin >> b) || b < 0) return;

    cout << "Сколько покупатель может максимум заплатить за продукт: ";
    if (!(cin >> c) || c < 0) return;

    c -= a; // Сразу вычту основу - почему бы и нет

    if (c < b) {
        cout << "Ему хватит только на основу или вообще не хватит"; return;
    }

    cout << c / b;
}

void spin_2() {
    int a, spin_f = 0;

    cout << "Сколько у вас лопастей: ";
    if (!(cin >> a)) return;

    while (a % 3 > 0 && a > 3) {
        a -= 4;
        spin_f++;
    }

    cout << a / 3 << "\n" << spin_f;
}

void not_spin() {
    int n, m, res = 0;

    cout << "Ширина и высота?\n";
    if (!(cin >> n >> m) || n < 1 || m < 1) return;

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            res += m > 1 ? i + 1 : 0;
        }
        res += n > 1 ? j + 1 : 0; // Вперед тернарники, освободите от лишнего кода
    }

    cout << res;
}

void train() {
    bool coupe[] = { true,true,true,true,true,true,true,true,true }; // True - свободное купе, false - нет
    int place = -1, count = 0, max = 0, temp_place;


    cout << "Введите занятые места в поезде\nЧтобы прекратить ввод, введите букву или число, меньшее, чем 1 или большее, чем 54\n";
    while (cin >> temp_place) {
        if (temp_place == place) { cout << 0; return; }
        if (temp_place > 54 || temp_place < 1) break; // Обход неумения анализа значений while
        place = --temp_place;
        coupe[place < 35 ? place / 4 : 8 - ((place + 1) / 2 - 19)] = false;
    }

    for (auto a : coupe) {
        count += a == 1 ? 1 : -count; // C++ думал, что я его не переигаю? Что я его не уничтожу? Я его переиграл вот так (Тернарники не прнимали булеву логику)
        if (count > max) max = count;
    }
    cout << max;
}

bool musicPlay = false;

constexpr auto NOTE_A4 = 440, NOTE_B4 = 494, NOTE_CS5 = 554, NOTE_D5 = 587, NOTE_E5 = 659, NOTE_FS5 = 740, NOTE_G5 = 784, NOTE_A5 = 880, REST = -1;

#include <windows.h>
#include <future>

void RR() {

    // Взял это здесь https://github.com/robsoncouto/arduino-songs/tree/master/nevergonnagiveyouup

    int melody[] = {

        // Never Gonna Give You Up - Rick Astley
        // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
        // Arranged by Chlorondria
      NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4,

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,

  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8,
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,

  REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4,
  NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,

   NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45

  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,

  NOTE_E5,4, NOTE_D5,2
    };

    int notes = sizeof(melody) / sizeof(melody[0]), tempo = 100, wholenote = (60000 * 4) / tempo, divider, noteDuration;

    cout << "Музыка включена\n";

    for (int thisNote = 0; thisNote < notes && musicPlay; thisNote += 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) noteDuration = wholenote / divider;
        else noteDuration = (wholenote / abs(divider)) * 1.5;
        Beep(melody[thisNote], noteDuration);
    }
}

void cinema() {
    int n, q, max;

    cout << "Количество мест: ";
    if (!(cin >> n) || n < 1) { cout << "ЭТО НАУЧНО НЕВОЗМОЖНО"; return; }

    cout << "Количество школьников: ";
    if (!(cin >> q) || q > n) { cout << "Боюсь, что они не поместятся"; return; }

    max = n / q + (n % q > 0 ? 1 : 0); // Внезапно я додумался до более элегантного решения

    cout << (max - 1) / 2 << "\n" << max / 2;
}

#undef max

void _choice() {
    short int choice;

    do {
        if (!cin) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "Выберите программу\n1. Спиннеры\n2. Снова спиннеры\n3. Не про спиннеры\n4. Плацкартный вагон\n5. Кинотеатр\n" << (musicPlay == 0 ? "0. Включить музыку (Ее громкость зависит от системной громкости)\n" : "0. Выключить музыку\n");
        cin >> choice;
    } while (!cin);

    switch (choice) {
    case 1: {spin_1(); break; }
    case 2: {spin_2(); break; }
    case 3: {not_spin(); break; }
    case 4: {train(); break; }
    case 5: {cinema(); break; }
    case 0: {
        musicPlay = !musicPlay;
        auto Z = async(RR);
        _choice();
        break;
    }
    default: cout << "Не-а";
    }
    musicPlay = !musicPlay;
}

int main() {
    setlocale(0, "");

    _choice();
}

