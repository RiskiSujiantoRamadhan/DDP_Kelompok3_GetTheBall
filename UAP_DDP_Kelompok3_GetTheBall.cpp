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
