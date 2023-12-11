#include <ncurses/ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Fungsi untuk menggambar bola pada posisi tertentu
void drawBall(int x, int y) {
    mvprintw(y, x, "0");
}

// Fungsi untuk menggambar persegi panjang pada posisi tertentu
void drawRectangle(int x, int y, int length) {
    for (int i = 0; i < length; ++i) {
        mvprintw(y, x + i, "=");
    }
}

// Fungsi untuk menampilkan menu start
void showCreativeStartMenu() {
    mvprintw(5, 10, "*****************************");
    mvprintw(6, 10, "*     WELCOME TO Get My Ball    *");
    mvprintw(7, 10, "*                           *");
    mvprintw(8, 10, "*        PRESS '1' TO       *");
    mvprintw(9, 10, "*        START THE GAME     *");
    mvprintw(10, 10, "*                           *");
    mvprintw(11, 10, "*        PRESS '2' TO       *");
    mvprintw(12, 10, "*           EXIT            *");
    mvprintw(13, 10, "*                           *");
    mvprintw(14, 10, "*****************************");
    refresh();
}

int main() {
    // Inisialisasi ncurses
    initscr();
    // Menyembunyikan kursor
    curs_set(0);
    // Mendisable buffering agar karakter langsung tercetak
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    // Mendisable buffering karakter agar langsung tercetak
    timeout(0);

    // Inisialisasi variabel
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    srand(time(0));

    int rectX = maxX / 2; // Posisi awal persegi panjang
    int rectY = maxY - 3; // Posisi awal lebih ke atas 2 baris
    int rectLength = 10;  // Panjang awal persegi panjang
    int rectSpeed = 5;    // Kecepatan pergerakan persegi panjang
    int rectSpeedX = 0;   // Kecepatan pergerakan horizontal
    int rectSpeedY = 0;   // Kecepatan pergerakan vertikal

    int ballX = rand() % maxX; // Posisi awal bola
    int ballY = 0;

    int ch;
    int speed = 150; // Kecepatan jatuh bola, semakin kecil semakin cepat

    int score = 0; // Skor awal

    bool game_over = false;
    bool start_menu = true;

    while (start_menu) {
        showCreativeStartMenu();
        ch = getch();
        switch (ch) {
            case '1':
                start_menu = false;
                break;
            case '2':
                endwin(); // Menutup ncurses sebelum keluar
                return 0;
            default:
                break;
        }
    }

    while (!game_over) {
        clear(); // Membersihkan layar

        // Menggambar bola pada posisi baru
        drawBall(ballX, ballY);
        ballY++;

        // Menggambar persegi panjang pada posisi baru
        drawRectangle(rectX, rectY, rectLength);

        // Jika bola mencapai batas bawah, game over
        if (ballY >= maxY) {
            game_over = true;
        }

        // Jika bola menyentuh persegi panjang, tambahkan skor dan reset bola
        if (ballY == rectY && ballX >= rectX && ballX < rectX + rectLength) {
            score++;
            ballX = rand() % maxX;
            ballY = 0;
        }
