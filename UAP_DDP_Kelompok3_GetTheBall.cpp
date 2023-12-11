#include <ncurses/ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Fungsi untuk menggambar bola dan warna
void drawBall(int x, int y) {
    attron(COLOR_PAIR(1) | A_BOLD); // atribut warna dengan pair 1 dan tebal
    mvprintw(y, x, "O");
}
// Fungsi untuk menggambar persegi panjang dan warna biru muda dan tebal
void drawRectangle(int x, int y, int length) {
    attron(COLOR_PAIR(1) | A_BOLD); // atribut warna dengan pair 1 dan tebal
    for (int i = 0; i < length; ++i) {
        mvprintw(y, x + i, "=");
    }
    attroff(COLOR_PAIR(1) | A_BOLD); // Menonaktifkan atribut warna dan tebal
}

// Fungsi untuk menampilkan menu start
void showStartMenu() {
    mvprintw(8, 35, "*************************************************");
    mvprintw(9, 35, "*                                               *");
    mvprintw(10, 35, "*             WELCOME TO GET MY BALL            *");
    mvprintw(11, 35, "*                                               *");
    mvprintw(12, 35, "*                  PRESS '1' TO                 *");
    mvprintw(13, 35, "*                 START THE GAME                *");
    mvprintw(14, 35, "*                                               *");
    mvprintw(15, 35, "*                 PRESS '2' TO                  *");
    mvprintw(16, 35, "*                     EXIT                      *");
    mvprintw(17, 35, "*                                               *");
    mvprintw(18, 35, "*************************************************");
    refresh();
}

int main() {
    // Inisialisasi ncurses
    initscr();
    start_color(); // Mengaktifkan mode warna
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
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
    int rectLength = 8;   // Panjang awal persegi panjang
    int rectSpeed = 6;    // Kecepatan pergerakan persegi panjang
    int rectSpeedX = 0;   // Kecepatan pergerakan horizontal
    int rectSpeedY = 0;   // Kecepatan pergerakan vertikal

    int ballX1 = rand() % maxX; // Posisi awal bola 1/random(acak)
    int ballY1 = 0;

    int ballX2 = rand() % maxX; // Posisi awal bola 2/random(acak)
    int ballY2 = -15; // Memberikan jarak supaya bola kedua tidak jatuh bersamaan dengan bola pertama

    int ch;
    int speed = 180; // Kecepatan jatuh bola

    int score = 0; // Skor awal
    long elapsedTime = 0; // Waktu yang diperlukan

    int minutes, seconds; // variabel waktu

    bool game_over = false;
    bool start_menu = true;

    time_t startTime = time(nullptr); // Inisialisasi waktu awal

    while (start_menu) {
        showStartMenu();
        ch = getch();
        switch (ch) {
            case '1':
                start_menu = false;
                break;
            case '2':
                endwin();
                return 0;
            default:
                break;
        }
    }

    while (!game_over) {
        clear(); // Membersihkan layar

        // Menggambar bola 1 pada posisi baru dengan warna biru muda dan tebal
        drawBall(ballX1, ballY1);
        ballY1++;

        // Menggambar bola 2 pada posisi baru dengan warna biru muda dan tebal
        drawBall(ballX2, ballY2);
        ballY2++;

        // Menggambar persegi panjang pada posisi baru dengan warna biru muda dan tebal
        drawRectangle(rectX, rectY, rectLength);

        // Jika bola 1 mencapai batas bawah maka game over
        if (ballY1 >= maxY) {
            game_over = true;
        }

        // Jika bola 1 menyentuh persegi panjang maka mendapat skor dan reset bola
        if (ballY1 == rectY && ballX1 >= rectX && ballX1 < rectX + rectLength) {
            score++;
            ballX1 = rand() % maxX;
            ballY1 = 0;
        }

        // Jika bola 2 mencapai batas bawah maka game over
        if (ballY2 >= maxY) {
            game_over = true;
        }

        // Jika bola 2 menyentuh persegi panjang maka mendapat skor dan reset bola
        if (ballY2 == rectY && ballX2 >= rectX && ballX2 < rectX + rectLength) {
            score++;
            ballX2 = rand() % maxX;
            ballY2 = 0;
        }

        // Menampilkan skor real-time di pojok kiri atas
        mvprintw(0, 0, "Skor: %d", score);

        // Menampilkan waktu di bawah skor
        time_t currentTime = time(nullptr);
        elapsedTime = difftime(currentTime, startTime);

        // Handle overflow
        if (elapsedTime < 0) {
            elapsedTime = 0;
        }

        minutes = elapsedTime / 60;
        seconds = elapsedTime % 60;
        mvprintw(1, 0, "Waktu: %02d:%02d", minutes, seconds);

        // Memperbarui tampilan
        refresh();

        // Mengatur kecepatan jatuh bola
        napms(speed);

        // Kontroller untuk menggerakkan persegi panjang
        int input = getch();
        switch (input) {
            case KEY_LEFT:
                rectSpeedX = -rectSpeed;
                rectSpeedY = 0;
                break;
            case KEY_RIGHT:
                rectSpeedX = rectSpeed;
                rectSpeedY = 0;
                break;
            case 'l': // Menambah panjang persegi panjang
                rectLength++;
                break;
            default:
                rectSpeedX = 0;
                rectSpeedY = 0;
                break;
        }

        // Memperbarui posisi persegi panjang
        rectX = (rectX + rectSpeedX + maxX) % maxX;
        rectY = (rectY + rectSpeedY + maxY) % maxY;
    }

    // Membersihkan layar
    clear();
    // Menampilkan skor akhir dan waktu 
    mvprintw(8, 35, "*************************************************");
    mvprintw(9, 35, "*                                               *");
    mvprintw(10, 35, "*                   GAME OVER                   *");
    mvprintw(11, 35, "*                YOUR SCORE: %d                  *", score);
    mvprintw(12, 35, "*                YOUR TIME: %02d:%02d               *", minutes, seconds);
    mvprintw(13, 35, "*                                               *");
    mvprintw(14, 35, "*               PRESS 'ESC' TO EXIT             *");
    mvprintw(15, 35, "*                                               *");
    mvprintw(16, 35, "*************************************************");
    refresh();

    // Menunggu sampai pengguna menekan tombol ESC
    while (getch() != 27);
    endwin();
    return 0;
}
