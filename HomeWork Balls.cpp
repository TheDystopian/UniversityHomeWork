#include <iostream>
#include <vector>

using namespace std;

int factor(int f) {
    int factor = 1;
    for (int i = 2; i <= f; i++) factor *= i;
    return factor;
}

int perestanovka(vector<bool> balls,int n, int m = 1) {
    int counter = 0;
    for (int i = 0; i < n && m <= n; i++) {
        if (balls[i]) continue;
        if (i == m) counter += factor(n - m);
        else {
            balls[i] = true;
            counter += perestanovka(balls, n, m + 1);
            balls[i] = false;
        }
    }
    return counter;
}

int main() {
    setlocale(0, "");

    int n;
    cout << "I've got balls of steel\n- Duke Nukem\nА если серьезно, каково количество шариков: ";
    if (!(cin >> n) || n < 1) { cout << "Ну че теперь, пиши заявление в полицию о краже шаров и после возврата перезапусти\n"; return 1; }

    cout << "Количество перестановок: " << perestanovka(*new vector <bool>(n, false), n) << '\n';
}