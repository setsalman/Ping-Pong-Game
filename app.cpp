#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

// console handle
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// global paddle size
const int paddleHeight = 4;

// function prototypes
void displayMenu();
void gameplay();
void showHelp();
void drawBorder();

// gotoxy
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// hide cursor
void setCursor(bool visible, DWORD size = 20) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(console, &cursorInfo);
}

// border drawing
void drawBorder() {
    for (int i = 1; i <= 80; i++) {
        gotoxy(i, 1); cout << "-";
        gotoxy(i, 25); cout << "-";
    }
    for (int i = 1; i <= 25; i++) {
        gotoxy(1, i); cout << "|";
        gotoxy(80, i); cout << "|";
    }
}

// help
void showHelp() {
    system("cls");
    drawBorder();
    gotoxy(10, 5); cout << "PING PONG GAME HELP";
    gotoxy(10, 7); cout << "Left Paddle: W(up), S(down)";
    gotoxy(10, 8); cout << "Right Paddle: Arrow up/down";
    gotoxy(10, 9); cout << "Press Esc to quit during gameplay.";
    gotoxy(10, 12); cout << "Press any key to return to menu...";
    _getch();
    displayMenu();
}

// menu
void displayMenu() {
    system("cls");
    drawBorder();
    gotoxy(30, 5); cout << "PING PONG GAME";
    gotoxy(30, 8); cout << "1. Play Game";
    gotoxy(30, 10); cout << "2. How to Play";
    gotoxy(30, 12); cout << "3. Exit";
    gotoxy(30, 15); cout << "Enter choice: ";
    char choice = _getch();
    if (choice == '1') {
        gameplay();
    }
    else if (choice == '2') {
        showHelp();
    }
    else if (choice == '3') {
        exit(0);
    }
    else {
        displayMenu();
    }
}

// gameplay
void gameplay() {
    system("cls");
    drawBorder();

    int leftPaddleY = 12;    // left paddle
    int rightPaddleY = 12;   // right paddle
    int ballX = 40;          // ball
    int ballY = 12;
    int ballDirX = -1;       // moving left first
    int ballDirY = -1;       // moving up first
    int score = 0;

    bool gameRunning = true;

    while (gameRunning) {
        // erase paddles
        for (int i = 2; i <= 24; i++) {
            gotoxy(3, i); cout << " ";
            gotoxy(78, i); cout << " ";
        }
        // erase ball
        gotoxy(ballX, ballY); cout << " ";

        // draw paddles
        for (int i = 0; i < paddleHeight; i++) {
            gotoxy(3, leftPaddleY + i); cout << "|";
            gotoxy(78, rightPaddleY + i); cout << "|";
        }

        // draw ball
        gotoxy(ballX, ballY); cout << "O";

        // draw score
        gotoxy(35, 1); cout << "Score: " << score;

        // update ball
        ballX += ballDirX;
        ballY += ballDirY;

        // top/bottom bounce
        if (ballY <= 2) {
            ballDirY = 1;
        }
        if (ballY >= 24) {
            ballDirY = -1;
        }

        // left paddle collision
        if (ballX == 4) {
            if (ballY >= leftPaddleY && ballY <= leftPaddleY + paddleHeight - 1) {
                ballDirX = 1;
                score++;
            }
            else {
                gotoxy(30, 13); cout << "GAME OVER! Your Score: " << score;
                gotoxy(30, 15); cout << "Press any key to return to menu...";
                _getch();
                displayMenu();
                return;
            }
        }

        // right paddle collision
        if (ballX == 77) {
            if (ballY >= rightPaddleY && ballY <= rightPaddleY + paddleHeight - 1) {
                ballDirX = -1;
            }
            else {
                ballDirX = -1;  // reflect off the right wall even if missed (no game over on right)
            }
        }

        // user input
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w' || key == 'W') {
                if (leftPaddleY > 2) leftPaddleY--;
            }
            else if (key == 's' || key == 'S') {
                if (leftPaddleY + paddleHeight < 24) leftPaddleY++;
            }
            else if (key == 72) { // up arrow
                if (rightPaddleY > 2) rightPaddleY--;
            }
            else if (key == 80) { // down arrow
                if (rightPaddleY + paddleHeight < 24) rightPaddleY++;
            }
            else if (key == 27) { // ESC
                displayMenu();
                return;
            }
        }

        Sleep(50); // game speed
    }
}

// main
int main() {
    setCursor(0, 0);    // hide console cursor
    srand(time(0));     // seed random
    displayMenu();
}
