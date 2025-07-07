#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
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
void resetHighScore();

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

// high score storage
int highScore = 0;

void loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        if (file.fail()) highScore = 0;
        file.close();
    } else {
        highScore = 0;
        ofstream outfile("highscore.txt");
        outfile << "0";
        outfile.close();
    }
}

void saveHighScore(int newScore) {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << newScore;
        file.close();
    }
}

void resetHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << "0";
        file.close();
        highScore = 0;
    }
    gotoxy(25, 13); cout << "High score has been reset!";
    gotoxy(25, 15); cout << "Press any key to return to menu...";
    _getch();
    displayMenu();
}

// help
void showHelp() {
    system("cls");
    drawBorder();
    gotoxy(10, 5); cout << "PING PONG GAME HELP";
    gotoxy(10, 7); cout << "Left Paddle: W(up), S(down)";
    gotoxy(10, 8); cout << "Right Paddle: Arrow up/down";
    gotoxy(10, 9); cout << "Press Esc to quit during gameplay.";
    gotoxy(10, 10); cout << "Press R in menu to reset high score.";
    gotoxy(10, 12); cout << "Press any key to return to menu...";
    _getch();
    displayMenu();
}

// menu
void displayMenu() {
    system("cls");
    drawBorder();
    gotoxy(30, 5); cout << "PING PONG GAME";
    gotoxy(30, 7); cout << "High Score: " << highScore;
    gotoxy(30, 9); cout << "1. Play Game";
    gotoxy(30, 11); cout << "2. How to Play";
    gotoxy(30, 13); cout << "3. Exit";
    gotoxy(30, 15); cout << "Press R to reset high score";
    gotoxy(30, 17); cout << "Enter choice: ";
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
    else if (choice == 'r' || choice == 'R') {
        resetHighScore();
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
    bool beatenHighScore = false;

    while (gameRunning) {
        // erase paddles
        for (int i = 2; i <= 24; i++) {
            gotoxy(3, i); cout << " ";
            gotoxy(78, i); cout << " ";
        }

        // erase ball from previous position
        gotoxy(ballX, ballY); cout << " ";

        // update ball coordinates
        ballX += ballDirX;
        ballY += ballDirY;

        // draw paddles
        for (int i = 0; i < paddleHeight; i++) {
            gotoxy(3, leftPaddleY + i); cout << "|";
            gotoxy(78, rightPaddleY + i); cout << "|";
        }

        // draw ball in new position
        gotoxy(ballX, ballY); cout << "O";

        // draw score and high score
        gotoxy(20, 1); cout << "Score: " << score << "  |  High Score: " << highScore << "      ";

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
                if (score > highScore) {
                    highScore = score;
                    saveHighScore(highScore);
                    beatenHighScore = true;
                }
            }
            else {
                gotoxy(30, 13); cout << "GAME OVER! Your Score: " << score;
                gotoxy(30, 14); cout << "High Score: " << highScore;
                if (beatenHighScore) {
                    gotoxy(28, 16); cout << "CONGRATULATIONS! NEW HIGH SCORE!";
                }
                gotoxy(30, 18); cout << "Press any key to return to menu...";
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
                ballDirX = -1;  // reflect off the right wall even if missed
            }
        }

        // user input (continuous)
        if (GetAsyncKeyState('W') & 0x8000) {
            if (leftPaddleY > 2) leftPaddleY--;
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            if (leftPaddleY + paddleHeight < 24) leftPaddleY++;
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (rightPaddleY > 2) rightPaddleY--;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (rightPaddleY + paddleHeight < 24) rightPaddleY++;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            displayMenu();
            return;
        }

        Sleep(50); // game speed
    }
}

// main
int main() {
    setCursor(0, 0);    // hide console cursor
    srand(time(0));     // seed random
    loadHighScore();
    displayMenu();
}
