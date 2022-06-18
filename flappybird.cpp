#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define  SCREEN_WIDTH 90 // ширина экрана
#define SCREEN_HEIGHT 26 // высота экрана
#define WIN_WIDTH 70 // ширина окна с непосредственно игрой
#define GAP_SIZE 7 // размер расстояния между верхней и нижней частью колонны

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[2]; // позиция колонны (максимум в окне - 2 штуки, поэтому массив из двух элементов)
int gapPos[2]; // пробел в колоннах
int pipeFlag[2]; // флаг, показывающий есть ли колонна
char bird[2][6] = {'/', '-', '-', 'o', '\\', ' ',
                   '|', '_', '_', '_', ' ', '>'}; // рисунок птички
int birdPos = 6; // начальная позиция птички
int score = 0;

/*!
	Данная функция помещает курсор текстового экрана в точку с координатами х,у.
 @arg Координаты х и у.
*/
void gotoxy(short int x, short int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

/*!
	Данная функция отрисовывает курсор.
*/
void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

/*!
	Данная функция отрисовывает рамку, в которой идет игра.
*/
void drawBorder() {

    for (short int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0);
        cout << "=";
        gotoxy(i, SCREEN_HEIGHT);
        cout << "=";
    }

    for (short int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i);
        cout << "=";
        gotoxy(SCREEN_WIDTH, i);
        cout << "=";
    }

    for (short int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i);
        cout << "=";
    }
}

/*!
	Данная функция генерирует колонны. Она выдает координату начала пробела между колоннами по оси y.
 @arg Номер колонны.
*/
void genPipe(int ind) {
    gapPos[ind] = 3 + rand() % 14;
}

/*!
	Данная функция отрисовывает колонны.
 @arg Номер колонны.
*/
void drawPipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "***";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "***";
        }
    }
}

/*!
	Данная функция стирает колонну. Используется для перемещения.
@arg Номер колонны.
*/
void erasePipe(int ind) {
    if (pipeFlag[ind] == true) {
        for (int i = 0; i < gapPos[ind]; i++) { // нижняя часть колонн
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "   ";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) { // верхняя часть колонн
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "   ";
        }
    }
}

/*!
	Данная функция отрисовывает птичку на экране.
*/
void drawBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos);
            cout << bird[i][j];
        }
    }
}

/*!
	Данная функция стирает птичку. Используется для создания перемещения.
*/
void eraseBird() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos);
            cout << " ";
        }
    }
}

/*!
	Данная функция возвращает 1, если птичка врезалась в колонну, и 0, если все хорошо.

int collision() {
    if (pipePos[0] >= 61) {
        if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}
*/

/*!
	Данная функция возвращает 1, если птичка врезалась в колонну, и 0, если все хорошо.
    int pP - позиция колонны
    int gP - позиция пробела в колонне
    int bP - позиция птички
*/
int collision(int pP, int gP, int bP) {
    if (pP >= 61) {
        if (bP < gP || bP > gP + GAP_SIZE) {
            return 1;
        }
    }
    return 0;
}
/*!
	Данная функция выводит на экран сообщение о том, что игра закончена и ждет ввода любого символа для перехода к меню.
*/
void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t---------------------------" << endl;
    cout << "\t\t------- GAME  OVER --------" << endl;
    cout << "\t\t--------  Score: " << score << " --------" << endl << endl;
    cout << "\t\tPress any key to go back to menu.";
    getch();
}

/*!
	Данная функция выводит на экран количество пройденных колонн непосредственно во время игры.
*/
void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

/*!
	Данная функция выводит на экран инструкцию по работе с игрой.
*/
void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n-------------------";
    cout << "\n Press spacebar to make bird fly";
    cout << "\n\nPress any key to go back to menu";
    getch();
}

/*!
	Данная функция выводит на экран описание непосредственно во время игры.
*/
void description() {
    gotoxy(WIN_WIDTH + 5, 2);
    cout << "FLAPPY BIRD";
    gotoxy(WIN_WIDTH + 6, 4);
    cout << "-----------";
    gotoxy(WIN_WIDTH + 6, 6);
    cout << "-----------";
    gotoxy(WIN_WIDTH + 7, 12);
    cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13);
    cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14);
    cout << " Spacebar = jump";

    gotoxy(10, 5);
    cout << "Press any key to start";
    getch();
    gotoxy(10, 5);
    cout << "                      ";
}

/*!
	Данная поднимает птичку вверх.
 @arg Начальная позиция птички
 @return Новая позиция птички
*/
int pressSpace(int bP) {
    if (bP > 3)
        bP -= 3;
    return bP;
}
/*!
	Данная функция обрабатывает нажатия на клавиши во время игры.
 @return -1, если esc; новую позицию птички, если space
*/
int reaction() {
    if (kbhit()) { //если происходит любое нажатие на клавиатуру
        char ch = getch();
        if (ch == 32) { // если это пробел, поднимаем птичку
            birdPos = pressSpace(birdPos);
            return birdPos;
        }
        if (ch == 27) { // если это esc, возвращаемся в меню
            return -1;
        }
    }
}

/*!
	Данная спускает птичку вниз.
 @arg Начальная позиция птички
 @return Новая позиция птички
*/
int birdDown(int bP) {
    bP+=1;
    return bP;
}

/*!
	Данная функция собирает игру воедино с помощью всех функций, написанных выше.
*/
void play() {

    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1;
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();
    description();

    while (1) {
        if (reaction() == -1) {
            break;
        }
        // если нажатия не было, продолжаем так:
        drawBird(); // рисуем птичку
        drawPipe(0); // рисуем первую колонну
        drawPipe(1); // рисуем вторую колонну
        if (collision(pipePos[0], gapPos[0], birdPos) == 1) { // если столкновение, заканчиваем игру
            gameover();
            return;
        }
        Sleep(100); // засыпаем
        eraseBird(); // в это время стираем птичку
        erasePipe(0); // и колонны тоже стираем
        erasePipe(1); // обе
        birdPos = birdDown(birdPos); // спускаем птичку, чтоб она падала

        if (birdPos > SCREEN_HEIGHT - 2) { // если птичка коснулась низа, игра окончена
            gameover();
            return;
        }

        if (pipeFlag[0] == 1) // если первая колонна уже есть
            pipePos[0] += 2; // продвигаем ее влево
        if (pipeFlag[1] == 1) // если вторая колонна уже есть
            pipePos[1] += 2; // продвигаем ее влево
        if (pipePos[0] >= 40 && pipePos[0] < 42) { // если для второй колонны уже достаточно места
            pipeFlag[1] = 1; // добавляем ее
            pipePos[1] = 4; // и ставим в начало экрана справа
            genPipe(1); // генерируем ее размеры
        }
        if (pipePos[0] > 68) { // если колонна продвинулась влево дальше птички, значит, эта колонна пройдена
            score++; // можем прибавить себе балл
            updateScore();
            pipeFlag[1] = 0; // на экране остается одна колонна
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}