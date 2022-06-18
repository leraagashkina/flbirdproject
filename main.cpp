#include "flappybird.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    setcursor(0, 0);
    srand((unsigned) time(nullptr));
    do {
        system("cls");
        gotoxy(10, 5);
        cout << " ------------------------- ";
        gotoxy(10, 6);
        cout << " |      Flappy Bird      | ";
        gotoxy(10, 7);
        cout << " ------------------------- ";
        gotoxy(10, 9);
        cout << "1. Start Game";
        gotoxy(10, 10);
        cout << "2. Instructions";
        gotoxy(10, 11);
        cout << "3. Quit";
        gotoxy(10, 12);
        cout << "Select option: ";
        char op = getchar();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}
