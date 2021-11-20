#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// Создать файл, записать в него 10 чисел, закрыть, потом вновь открыть файл и найти сумму чисел
void summ_10_ints() {
    int b,summ = 0;

    ofstream numwrite("numbers.txt");
    for (int i = 0; i < 10; i++) {
        cin >> b;
        numwrite << b << " ";
    }
    numwrite.close();

    ifstream numget("numbers.txt");
    for (int i = 0; i < 10; i++) {
        numget >> b;
        summ += b;
    }
    numget.close();

    cout << summ;
}

// Определить знак введенного с клавиатуры числа
int sign(double n) {
    if (n > 0) return 1;
    else if (n < 0) return -1;
    else return 0;
}

// Здесь находится Pi
const double pi = 3.1415926535;

// Площадь прямоугольника
double CountRect() {
    double a, b;
    cout << "Введите большую и меньшую стороны (В любом порядке)\n";
    if (!(cin >> a >> b)) return -1;
    return a * b;
}

// Площадь треугольника
double CountTriangleHeron() {
    double a, b, c;
    cout << "Введите все стороны\n";
    if (!(cin >> a >> b >> c)) return -1;
    double halfp = (a + b + c) / 2;
    return sqrt(halfp * (halfp - a) * (halfp - b) * (halfp - c) );
}

// Площадь круга
double CountCircle() {
    double r;
    cout << "Введите радиус\n";
    if (!(cin >> r)) return -1;
    return pi * r * r;
}

void count_area() {
    short int choice;
    double out;
    cout << "Какую площадь посчитать?\n1. Прямоугольника/Квадрата\n2. Треугольника\n3. Круга\n";
    cin >> choice;
    switch (choice) {
    case 1: out = CountRect(); break;
    case 2: out = CountTriangleHeron(); break;
    case 3: out = CountCircle(); break;
    default: {cout << "Некорректный ввод!\n"; return; }
    }
    if (out > 0) {cout << out << endl; system("pause"); }
    else { cout << "Некорректный треугольник!\n"; system("pause"); }
}

///////////////////////////
// Декодер римских чисел //
///////////////////////////

void roman() {
    // Переменные
    map <char, int> dict = {{'I', 1},{'V', 5},{'X', 10},{'L', 50}, {'C', 100}, {'D', 500} , {'M', 1000}};
    string a;
    int result = 0;

    // Ввод
    cout << "Введите римское число\n";
    cin >> a;

    int buff = dict[a[a.length() - 1]];

    for (int i = a.length() - 1; i >= 0; i--) {
        // Проверка
        if (dict[a[i]] == 0) { cout << "Неправильно введено число!"; return; }

        // Подсчет
        if (dict[a[i]] < buff) result -= dict[a[i]];
        else { result += dict[a[i]]; buff = dict[a[i]]; }
    }
    cout << result;
}

/////////////////
// Былая слава //
/////////////////

// Получение данных об окне консоли
HDC device_context = GetDC(GetConsoleWindow());

void flag_background(HBRUSH brush, const int heightline, int &height) {
    // Рисование линий длиной в height
    // Сдвиг для начальной линии еще имеет "--" перед height чтобы не было расстояния между линиями и чтобы "-" не воспринимался как "---"
    SelectObject(device_context, brush);
    Rectangle(device_context, 0, --height - heightline, 1100, height);
    height += heightline;
}

void hide_cursor() {
    // ЬЕЬ-нуть курсор для ввода
    HANDLE conHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(conHndlr, &info);
}

void flag_glory() {
    hide_cursor();
    
    // Высота
    // heightline - высота 1 линии
    // height - высота глобальная
    const int heightline = 525 / 13;
    int height = heightline;

    // Кисти
    HBRUSH red_brush = CreateSolidBrush(RGB(255,0,0));
    HBRUSH white_brush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH blue_brush = CreateSolidBrush(RGB(0, 0, 255));
    // Линии
    while (height < 525 - heightline) {
        flag_background(red_brush, heightline, height);
        flag_background(white_brush, heightline, height);
    }
    flag_background(red_brush, heightline, height);

    // синий прямоугольник
    SelectObject(device_context, blue_brush);
    Rectangle(device_context, 0, 0, 1050 / 3 , height * 6 / 14);

    // Назначение позиции точек
    // вычисляется по формуле
    // ширина или высота синего прямоугольника / (Кол-во точек + 1)
    // Все сокращено
    double dotlocwidth = 1050 / 27;
    double dotlocheight = height * 6 / 98;

    // Размещение точек размером 20 сеткой 8x6
    SelectObject(device_context, white_brush);
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 8; j++)
            Ellipse(device_context, dotlocwidth * j-10, dotlocheight * i-10, dotlocwidth * j +10, dotlocheight * i+10);
    }
    // Эта строчка просто существовала
    // ReleaseDC(console_handle, device_context);
    
    // И немного deadmau5 для вечного сна )))
    while (1 < 2) Sleep(1);
}
///////////

///////////////
// Синусоида //
///////////////

// рисование линии
void line(double fromX, double fromY, double toX, double toY, HPEN pen) {
    // сменить ручку
    SelectObject(device_context, pen);

    // нарисовать точку из a в b
    MoveToEx(device_context, fromX, fromY, 0);
    LineTo(device_context, toX, toY);

    // чтобы не утонуть в ручках
    DeleteObject(pen);
}

void draw_sinus() {
    hide_cursor();

    // Начальная и конечная точки графика
    double begin_graph = 0;
    double end_graph = 13 * pi;

    // Точность. Чем больше тем точнее график. Рекомендуется минимум 10 на каждый pi
    //int precision = 10; // Ручной режим
    int precision = (abs(begin_graph) + abs(end_graph)) / pi * 10; // автоматический режим

    // Масштаб ширины графика, чем больше, тем меньше отображаемый график
    double graph_width_scale = 4;

    // Смещение от верхнего левого угла 
    int graph_offset_width = 20;
    int graph_offset_height = 20;

    // Высота графика
    int graph_height = 100;

    // Ширина графика вычисляется автоматически по данным формулам
    double graph_width_left = abs(begin_graph) * graph_height / graph_width_scale;
    double graph_width_right = abs(end_graph) * graph_height / graph_width_scale;


    // Ручки
    HPEN white_pen = CreatePen(BS_SOLID, 2,RGB(255, 255, 255));

    // Защита от дурака
    // Начальная точка графика будет всегда меньше конечной 
    if (begin_graph > end_graph) { 
        std::swap(begin_graph, end_graph);
        std::swap(graph_width_left, graph_width_right);
    }

    // чтобы не было лишних сдвигов
    if (begin_graph > 0) graph_width_left = 0;
    else if (end_graph < 0) graph_width_right = 0;

    // Рисование направляющих графика
    // Сначала ось y
    // Потом ось x
    // Если начало координат больше 0, то ось y рисуется в 0
    line(graph_offset_width + graph_width_left, graph_offset_height, graph_offset_width + graph_width_left, graph_height + graph_offset_height, white_pen);
    line(graph_offset_width, graph_height / 2 + graph_offset_height, graph_width_left + graph_width_right + graph_offset_height, graph_height / 2 + graph_offset_height, white_pen);


    // Начальная точка
    double i_prev = begin_graph;
    // Цикл с шагом (начальная точка) + (|начало графика| |конец графика|) / точность
    // от начальной точки до конечной
    for (double i = begin_graph + ((abs(begin_graph) + abs(end_graph)) / precision); i <= end_graph; i += (abs(begin_graph) + abs(end_graph)) / precision) {
        // RGB ручка ))
        HPEN rgb_pen = CreatePen(BS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
        // Формулы
        // Ось x - смещение от левого края окна программы + длина графика с левого края слева + позиция цикла * высота графика / масштаб графика
        // Ось y - (синус позиции цикла - 1) * -высота графика / 2 + смещение от верхнего края программы
        double xprev = graph_offset_width + graph_width_left + i_prev * graph_height / graph_width_scale;
        double yprev = (sin(i_prev) - 1) * -graph_height / 2 + graph_offset_height;
        double xcurr = graph_offset_width + graph_width_left + i * graph_height / graph_width_scale;
        double ycurr = (sin(i) - 1) * -graph_height / 2 + graph_offset_height;
        // рисование от предыдущей точки до текущей и обновление предыдущей точки
        line(xprev, yprev, xcurr, ycurr, rgb_pen);
        i_prev = i;
        // Эффект красивого появления синусоиды
        Sleep(16);
    }

    // И немного альбома от deadmau5 для вечного сна )))
    while (1 < 2) Sleep(1);
}

//////////////////////////////////////
// Генератор псевдо-случайных чисел //
//////////////////////////////////////

void PseudoRandom() {
    // Начальные значения
    int m = 25173;
    int itarget = 13849;
    int c = 65537;
    vector <int> s = {0};

    // Подсчет псевдослучайной переменной
    for (int i = 0; i < itarget; i++) {
        // Генерация
        s.push_back((m * s[0] + i) % c);
        // Это сильно уменьшает потребление памяти
        if (s.size() > 1) s.erase(s.begin());
        // Генерация в настоящем времени
        // cout << "S" << i << " = " << s[0] << "\n";
    }
    // Готовый результат
    cout << "S" << itarget << " = " << s[0] << "\n";
}

float summ_vect(vector <float> price_total) {
    float summ = 0;
    for (int i = 0; i < price_total.size(); i++)
        summ += price_total[i];
    return summ;
}

tuple <int,int,float,float,float> min_max(vector <float> price_total) {
    float min_pos = 0, max_pos = 0;
    for(int i = 0; i < price_total.size(); i++) {
        if (price_total[i] < price_total[min_pos]) min_pos = i;
        if (price_total[i] > price_total[max_pos]) max_pos = i;
    }
    return { min_pos, max_pos, price_total[min_pos], price_total[max_pos], summ_vect(price_total) };
}

tuple <int, int, float, float, float> count_matrix(int matrix[][4], float multiplier[]) {
    vector <float> totals;
    for (int i = 0; i < 3; i++) {
        float total_summ = 0;
        for (int j = 0; j < 4; j++)
            total_summ += matrix[i][j] * multiplier[j];
        totals.push_back(total_summ);
    }
    return min_max(totals);
}


void multi_matrix() {
    // [продавец][товар]
    int main_matrix[3][4] = { {5,2,0,10}, {3,5,2,5}, {20,0,0,0} };
    // цена и коммисионные
    float price[4] = { 1.2,2.8,5.0,2.0 };
    float commisional[4] = { 0.5,0.4,1,1.5 };

    int seller_min, seller_max;
    float mini, maxi, summ_sell, summ_comm;
    tie(seller_min, seller_max, mini, maxi, summ_sell) = count_matrix(main_matrix, price);
    cout << "Больше всего получил с продаж продавец № " << seller_max + 1 << "\nОн получил " << maxi << "\nМеньше всего получил с продаж продавец № " << seller_min + 1 << "\nОн получил " << mini << "\nВсего получено с продаж " << summ_sell << endl;
    tie(seller_min, seller_max, mini, maxi, summ_comm) = count_matrix(main_matrix, commisional);
    cout << "Больше всего коммисионных получил продавец № " << seller_max + 1 << "\nОн получил " << maxi << "\nМеньше всего коммисионных получил продавец № " << seller_min + 1 << "\nОн получил " << mini << "\nВсего получено комиссионных " << summ_comm << endl;
    cout << "Всего прошло денег через продавцов " << summ_sell + summ_comm;
}

//////////////////////////////////////////
// Конвертер в другую систему счисления //
//////////////////////////////////////////

void Convertxtoy () {

    int src_num_sys, new_num_sys;
    string src_num;

    cout << "Введите число, которое надо преобразовать\n";
    cin >> src_num;
    for (int i = 0; i < src_num.length(); i++) 
        src_num[i] = toupper(src_num[i]);

    cout << "В какой оно системе счисления\n";
    if (!(cin >> src_num_sys)) return;

    // Перевод в десятичную (чтобы представить как число)
    int dec_num = 0;
    for (int i = 0; i < src_num.length(); i++)
        if (isdigit(src_num[i]) && src_num[i] - '0' < src_num_sys)
            dec_num += (src_num[i] - '0') * pow(src_num_sys, src_num.length() - i - 1);
        else if (src_num[i] < src_num_sys + 'A' - 10 && isalpha(src_num[i]))
            dec_num += (src_num[i] + 10 - 'A') * pow(src_num_sys, src_num.length() - i - 1);
        else return;

    cout << "Какова целевая система счисления\n"; 
    if (!(cin >> new_num_sys)) return;
    cout << "Результат: ";
    
    // Перевод в другую систему счисления
    if (new_num_sys != src_num_sys) {
        string ready_num;
        for (int i = 0; dec_num > 0; i++) {
            if (dec_num % new_num_sys > 9)
                ready_num += char('A' - 10 + dec_num % new_num_sys);
            else
                ready_num += char(dec_num % new_num_sys + '0');
            dec_num /= new_num_sys;
        }
        reverse(ready_num.begin(), ready_num.end());
        cout << ready_num;
    }
    else cout << src_num;

}


int main() {
    short int choice_main;
    setlocale(0, "");
    cout << "Выберите программу\n1. Запись 10 чисел в файл и нахождение их суммы\n2. Нахождение знака числа\n3. Вычисление площади прямоугольника, треугольника, круга\n4. Флаг Былая слава\n5. Синусоида\n6. Декодирование римских чисел\n7. Генератор псевдослучайных чисел\n8. Умножение матриц\n9. Преобразование из одной системы счисления в другую\n";
    cin >> choice_main;
    switch (choice_main) {
    case 1: {summ_10_ints(); break; }
    case 2: {
        double n;
        if (cin >> n) cout << sign(n);
        else cout << "Неправильный ввод";
    }
    case 3: {count_area();  break; }
    case 4: {system("cls"); flag_glory();  break; }
    case 5: {system("cls"); draw_sinus();  break; }
    case 6: {roman(); break; }
    case 7: {PseudoRandom(); break; }
    case 8: {multi_matrix(); break; }
    case 9: {Convertxtoy(); break; }
    default: cout << "Неправильный ввод";
    }
}
