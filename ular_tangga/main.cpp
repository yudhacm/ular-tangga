#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>


int rollDice() {
    return (rand() % 6) + 1;
}

int jumlahlemparan = 1;
int jumlahlemparan2 = 1;

int pemenang = 0;

//Variabel untuk nilai dari player
float bidak_player1_X = 0.4;
float bidak_player1_Y = 0.7;

float bidak_player2_X = 0.4;
float bidak_player2_Y = 0.4;

//Variabel untuk pergantian pemain
bool giliran_player1 = true;

// Variabel untuk menggeser observer
float geser_oberver_X = 0.1;
float geser_oberver_Y = 0.1;

//Variabel untuk batas Observer
const float batas_observer_kiri = -0.05;
const float batas_observer_kanan = 20.65;
const float batas_observer_bawah = -0.25;
const float batas_observer_atas = 3.45;


// Variabel untuk rotasi papan permainan
float sudut_rotasi_X = 0.0f;
float sudut_rotasi_Y = 0.0f;
float sudut_rotasi_Z = 0.0f;

// Variabel untuk pusat rotasi
float pusat_rotasi_X = 10.0f;
float pusat_rotasi_Y = 5.5f;
float pusat_rotasi_Z = 0.0f;

// Variabel untuk menyimpan sudut rotasi terakhir
float sudut_rotasi_terakhir_x = 0.0f;
float sudut_rotasi_terakhir_Y = 0.0f;
float sudut_rotasi_terakhir_Z = 0.0f;


bool isRotated = false;
bool rotasi_awal_dilakukan = false;

// Variabel global untuk mode warna
bool warna_transparan = false;

// gambar 5 koordinat X awal, Y awal, Z awal, kedalaman
void drawTwo(float xAtas, float yBawah, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Bagian depan
    glColor3f(0.8, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.75f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.75f, yBawah + 0.71f, frontZ);
    glVertex3f(xAtas + 0.78f, yBawah + 0.71f, frontZ);
    glVertex3f(xAtas + 0.78f, yBawah + 0.63f, frontZ);
    glVertex3f(xAtas+ 0.75f, yBawah + 0.63f, frontZ);
    glEnd();

    // Bagian belakang (menggunakan depth untuk memberikan kedalaman)
    glColor3f(0.8, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.75f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(xAtas + 0.75f, yBawah + 0.71f, backZ);
    glVertex3f(xAtas + 0.78f, yBawah + 0.71f, backZ);
    glVertex3f(xAtas + 0.78f, yBawah + 0.63f, backZ);
    glVertex3f(xAtas+ 0.75f, yBawah + 0.63f, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glColor3f(0.6, 0.8, 0.0); // Warna lebih gelap untuk sisi
    glBegin(GL_QUADS);

    // Sisi atas (bagian melengkung atas)
    glVertex3f(0.9 + xAtas, 0.9 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.9 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.9 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.9 + yBawah, frontZ);

    // Sisi kanan (bagian vertikal kanan)
    glVertex3f(0.9 + xAtas, 0.9 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.9 + yBawah, backZ);

    // Sisi bawah (bagian horizontal bawah)
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.7 + yBawah, backZ);

    // Sisi kiri (bagian vertikal kiri atas)
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.9 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.9 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.7 + yBawah, backZ);

    // Sisi kiri atas (bagian horizontal kiri atas)
    glVertex3f(0.85 + xAtas, 0.9 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.9 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.9 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.9 + yBawah, backZ);

    // Sisi kiri bawah (bagian horizontal kiri bawah)
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, backZ);

    // Sisi tengah (bagian horizontal tengah)
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);

    // Sisi kiri vertikal (bagian kiri bawah)
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);

    // Sisi kanan vertikal (bagian kanan bawah)
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.65 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.65 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, backZ);

    // Sisi bawah (bagian horizontal paling bawah)
    glVertex3f(0.75 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.6 + yBawah, backZ);

    // Sisi kiri vertikal (bagian kiri paling bawah)
    glVertex3f(0.75 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.65 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.65 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.6 + yBawah, backZ);

    // Sisi tengah vertikal (bagian tengah bawah)
    glVertex3f(0.78 + xAtas, 0.63 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.78 + xAtas, 0.63 + yBawah, backZ);

    // Sisi kiri vertikal (bagian kiri tengah)
    glVertex3f(0.75 + xAtas, 0.63 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.63 + yBawah, backZ);

    glEnd();
}


void drawThree(float x, float y, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Warna dasar kuning untuk angka
    glColor3f(0.8, 1.0, 0.0);

    // =============== BAGIAN DEPAN ===============
    // Batang vertikal kanan
    glBegin(GL_POLYGON);
    glVertex3f(0.9 + x, 0.6 + y, frontZ);
    glVertex3f(0.85 + x, 0.6 + y, frontZ);
    glVertex3f(0.85 + x, 0.90 + y, frontZ);
    glVertex3f(0.9 + x, 0.90 + y, frontZ);
    glEnd();

    // Garis horizontal atas
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glEnd();

    // Garis horizontal tengah
    glBegin(GL_POLYGON);
    glVertex3f(0.75 + x, 0.76 + y, frontZ);
    glVertex3f(0.75 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, frontZ);
    glEnd();

    // Garis horizontal bawah
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.75f, y + 0.65f, frontZ);
    glEnd();

    // =============== BAGIAN BELAKANG ===============
    // Batang vertikal kanan (belakang)
    glBegin(GL_POLYGON);
    glVertex3f(0.9 + x, 0.6 + y, backZ);
    glVertex3f(0.85 + x, 0.6 + y, backZ);
    glVertex3f(0.85 + x, 0.90 + y, backZ);
    glVertex3f(0.9 + x, 0.90 + y, backZ);
    glEnd();

    // Garis horizontal tengah (belakang)
    glBegin(GL_POLYGON);
    glVertex3f(0.75 + x, 0.76 + y, backZ);
    glVertex3f(0.75 + x, 0.71 + y, backZ);
    glVertex3f(0.9 + x, 0.71 + y, backZ);
    glVertex3f(0.9 + x, 0.76 + y, backZ);
    glEnd();

    // Garis horizontal bawah (belakang)
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.75f, y + 0.65f, backZ);
    glEnd();

    // =============== SISI PENGHUBUNG 3D ===============
    // Warna lebih gelap untuk sisi
    glColor3f(0.6, 0.8, 0.0);

    // Sisi kanan (batang vertikal utama)
    glBegin(GL_QUADS);
    glVertex3f(0.9 + x, 0.6 + y, frontZ);
    glVertex3f(0.9 + x, 0.6 + y, backZ);
    glVertex3f(0.9 + x, 0.9 + y, backZ);
    glVertex3f(0.9 + x, 0.9 + y, frontZ);
    glEnd();

    // Sisi kiri (batang vertikal utama)
    glBegin(GL_QUADS);
    glVertex3f(0.85 + x, 0.6 + y, frontZ);
    glVertex3f(0.85 + x, 0.6 + y, backZ);
    glVertex3f(0.85 + x, 0.9 + y, backZ);
    glVertex3f(0.85 + x, 0.9 + y, frontZ);
    glEnd();

    // Sisi atas (garis horizontal atas)
    glBegin(GL_QUADS);
    glVertex3f(0.75 + x, 0.9 + y, frontZ);
    glVertex3f(0.75 + x, 0.9 + y, backZ);
    glVertex3f(0.9 + x, 0.9 + y, backZ);
    glVertex3f(0.9 + x, 0.9 + y, frontZ);
    glEnd();

    // Sisi bawah (garis horizontal bawah)
    glBegin(GL_QUADS);
    glVertex3f(0.75 + x, 0.6 + y, frontZ);
    glVertex3f(0.75 + x, 0.6 + y, backZ);
    glVertex3f(0.9 + x, 0.6 + y, backZ);
    glVertex3f(0.9 + x, 0.6 + y, frontZ);
    glEnd();

    // Sisi depan (garis horizontal tengah)
    glBegin(GL_QUADS);
    glVertex3f(0.75 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.71 + y, backZ);
    glVertex3f(0.75 + x, 0.71 + y, backZ);
    glEnd();

    // Sisi belakang (garis horizontal tengah)
    glBegin(GL_QUADS);
    glVertex3f(0.75 + x, 0.76 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, backZ);
    glVertex3f(0.75 + x, 0.76 + y, backZ);
    glEnd();

    // Sisi kiri (konektor horizontal)
    glBegin(GL_QUADS);
    glVertex3f(0.75 + x, 0.71 + y, frontZ);
    glVertex3f(0.75 + x, 0.76 + y, frontZ);
    glVertex3f(0.75 + x, 0.76 + y, backZ);
    glVertex3f(0.75 + x, 0.71 + y, backZ);
    glEnd();

    // Sisi kanan (konektor horizontal)
    glBegin(GL_QUADS);
    glVertex3f(0.9 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, backZ);
    glVertex3f(0.9 + x, 0.71 + y, backZ);
    glEnd();
}


    // gambar 6 koordinat X awal, Y awal, Z awal, kedalaman
void drawSix(float x, float y, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Bagian depan
    glColor3f(0.8, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glEnd();

    // Bagian belakang
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.8f, y + 0.65f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glBegin(GL_QUADS);
    // Sisi 1
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);

    // Sisi 2
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);

    // Sisi 3
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);

    // Sisi 4
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);

    // Sisi 5
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);

    // Sisi 6
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Sisi 7
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Sisi 8
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);

    // Sisi 9
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);

    // Sisi 10
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);

    // Sisi 11
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);

    // Sisi 12
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);

    // Sisi 13
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);

    // Sisi 14
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);

    // Sisi 15
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);

    glEnd();
}

void drawSeven(float x, float y, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Bagian depan
    glColor3f(0.8, 1.0, 0.0); // Warna kuning kehijauan sama seperti angka 9

    // Bagian horizontal atas
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glEnd();

    // Bagian diagonal
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.87f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.8f, frontZ);
    glEnd();

    // Bagian belakang
    // Bagian horizontal atas
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.87f, backZ);
    glVertex3f(x + 0.75f, y + 0.87f, backZ);
    glEnd();

    // Bagian diagonal
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.87f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.8f, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glBegin(GL_QUADS);
    // Sisi atas
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);

    // Sisi bawah horizontal
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);

    // Sisi kiri
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);

    // Sisi kanan atas
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);

    // Sisi diagonal 1
    glVertex3f(x + 0.9f, y + 0.87f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.87f, backZ);

    // Sisi diagonal 2
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);

    // Sisi diagonal 3
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.8f, frontZ);
    glVertex3f(x + 0.9f, y + 0.8f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Sisi kanan bawah
    glVertex3f(x + 0.9f, y + 0.8f, frontZ);
    glVertex3f(x + 0.9f, y + 0.87f, frontZ);
    glVertex3f(x + 0.9f, y + 0.87f, backZ);
    glVertex3f(x + 0.9f, y + 0.8f, backZ);

    glEnd();
}


void drawNine(float x, float y, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Bagian depan
    glColor3f(0.8, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.71f, frontZ);
    glVertex3f(x + 0.8f, y + 0.71f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.9 + x, 0.6 + y, frontZ);
    glVertex3f(0.85 + x, 0.6 + y, frontZ);
    glVertex3f(0.85 + x, 0.90 + y, frontZ);
    glVertex3f(0.9 + x, 0.90 + y, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.75 + x, 0.76 + y, frontZ);
    glVertex3f(0.75 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.71 + y, frontZ);
    glVertex3f(0.9 + x, 0.76 + y, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.75f, y + 0.65f, frontZ);
    glEnd();

    // Bagian belakang
    glBegin(GL_POLYGON);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.71f, backZ);
    glVertex3f(x + 0.8f, y + 0.71f, backZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.9 + x, 0.6 + y, backZ);
    glVertex3f(0.85 + x, 0.6 + y, backZ);
    glVertex3f(0.85 + x, 0.90 + y, backZ);
    glVertex3f(0.9 + x, 0.90 + y, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.75 + x, 0.76 + y, backZ);
    glVertex3f(0.75 + x, 0.71 + y, backZ);
    glVertex3f(0.9 + x, 0.71 + y, backZ);
    glVertex3f(0.9 + x, 0.76 + y, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.75f, y + 0.65f, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glBegin(GL_QUADS);
    // Sisi 1
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);

    // Sisi 2
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);

    // Sisi 3
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);

    // Sisi 4
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);

    // Sisi 5
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);

    // Sisi 6
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Sisi 7
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Sisi 8
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);

    // Sisi 9
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);

    // Sisi 10
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);

    // Sisi 11
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);

    // Sisi 12
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);

    // Sisi 13
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);

    // Sisi 14
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);

    // Sisi 15
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);

    glEnd();
}

void drawObserver (float x, float y){
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(x + 0.2f ,y + 0.4f, 0.9f);
    glutSolidCone(0.1,0.2,50,50);
    glTranslatef(-(x + 0.2f), -(y + 0.4f), -0.9f);
}

void drawPlayer1 (float x , float y){
    float offsetX = 0.3; // Geser ke kanan 0.2
    glColor3f(1,0,0);
    glTranslatef(x + offsetX, y, 1.0f);
    glutSolidSphere(0.1,50,50);
    glTranslatef(-(x + offsetX), -y, -1.0f);
}

void drawPlayer2(float x, float y){
    float offsetX = 0.3;
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(x + offsetX ,y,1.0f);
    glutSolidCube(0.3);
    glTranslatef(-(x + offsetX),-y,-1.0f);
}

void drawTangga(){
    //MENGGAMBAR TANGGA 1
    glEnable(GL_DEPTH_TEST);           // Aktifkan depth test
    glDepthFunc(GL_LESS);              // Default depth function
    glDepthMask(GL_TRUE);

    glColor3f(1.0f, 0.0f, 0.0f);
    for (float i = 0.6; i < 3.6; i += 0.4) {
        // depan
        glBegin(GL_POLYGON);
        glVertex3f(15.2, i, 1.0);
        glVertex3f(15.8, i, 1.0);
        glVertex3f(15.8, i + 0.1, 1.0);
        glVertex3f(15.2, i + 0.1, 1.0);
        glEnd();
        // belakang
        glBegin(GL_POLYGON);
        glVertex3f(15.2, i, 0.7);
        glVertex3f(15.8, i, 0.7);
        glVertex3f(15.8, i + 0.1, 0.7);
        glVertex3f(15.2, i + 0.1, 0.7);
        glEnd();
        // kiri
        glBegin(GL_POLYGON);
        glVertex3f(15.2, i, 1.0);
        glVertex3f(15.2, i, 0.7);
        glVertex3f(15.2, i + 0.1, 0.7);
        glVertex3f(15.2, i + 0.1, 1.0);
        glEnd();
        // kanan
        glBegin(GL_POLYGON);
        glVertex3f(15.8, i, 1.0);
        glVertex3f(15.8, i, 0.7);
        glVertex3f(15.8, i + 0.1, 0.7);
        glVertex3f(15.8, i + 0.1, 1.0);
        glEnd();
        // atas
        glBegin(GL_POLYGON);
        glVertex3f(15.2, i + 0.1, 1.0);
        glVertex3f(15.8, i + 0.1, 1.0);
        glVertex3f(15.8, i + 0.1, 0.7);
        glVertex3f(15.2, i + 0.1, 0.7);
        glEnd();
        // bawah
        glBegin(GL_POLYGON);
        glVertex3f(15.2, i, 1.0);
        glVertex3f(15.8, i, 1.0);
        glVertex3f(15.8, i, 0.7);
        glVertex3f(15.2, i, 0.7);
        glEnd();
    }
    // gagang kiri
    // depan
    glBegin(GL_POLYGON);
    glVertex3f(15.2, 0.4, 1.0);
    glVertex3f(15.3, 0.4, 1.0);
    glVertex3f(15.3, 3.6, 1.0);
    glVertex3f(15.2, 3.6, 1.0);
    glEnd();
    // belakang
    glBegin(GL_POLYGON);
    glVertex3f(15.2, 0.4, 0.7);
    glVertex3f(15.3, 0.4, 0.7);
    glVertex3f(15.3, 3.6, 0.7);
    glVertex3f(15.2, 3.6, 0.7);
    glEnd();
    // kiri
    glBegin(GL_POLYGON);
    glVertex3f(15.2, 0.4, 1.0);
    glVertex3f(15.2, 0.4, 0.7);
    glVertex3f(15.2, 3.6, 0.7);
    glVertex3f(15.2, 3.6, 1.0);
    glEnd();
    // kanan
    glBegin(GL_POLYGON);
    glVertex3f(15.3, 0.4, 1.0);
    glVertex3f(15.3, 0.4, 0.7);
    glVertex3f(15.3, 3.6, 0.7);
    glVertex3f(15.3, 3.6, 1.0);
    glEnd();
    // atas
    glBegin(GL_POLYGON);
    glVertex3f(15.2, 3.6, 1.0);
    glVertex3f(15.3, 3.6, 1.0);
    glVertex3f(15.3, 3.6, 0.7);
    glVertex3f(15.2, 3.6, 0.7);
    glEnd();
    // bawah
    glBegin(GL_POLYGON);
    glVertex3f(15.2, 0.4, 1.0);
    glVertex3f(15.3, 0.4, 1.0);
    glVertex3f(15.3, 0.4, 0.7);
    glVertex3f(15.2, 0.4, 0.7);
    glEnd();

    // gagang kanan
    // depan
    glBegin(GL_POLYGON);
    glVertex3f(15.7, 0.4, 1.0);
    glVertex3f(15.8, 0.4, 1.0);
    glVertex3f(15.8, 3.6, 1.0);
    glVertex3f(15.7, 3.6, 1.0);
    glEnd();
    // belakang
    glBegin(GL_POLYGON);
    glVertex3f(15.7, 0.4, 0.7);
    glVertex3f(15.8, 0.4, 0.7);
    glVertex3f(15.8, 3.6, 0.7);
    glVertex3f(15.7, 3.6, 0.7);
    glEnd();
    // kiri
    glBegin(GL_POLYGON);
    glVertex3f(15.7, 0.4, 1.0);
    glVertex3f(15.7, 0.4, 0.7);
    glVertex3f(15.7, 3.6, 0.7);
    glVertex3f(15.7, 3.6, 1.0);
    glEnd();
    // kanan
    glBegin(GL_POLYGON);
    glVertex3f(15.8, 0.4, 1.0);
    glVertex3f(15.8, 0.4, 0.7);
    glVertex3f(15.8, 3.6, 0.7);
    glVertex3f(15.8, 3.6, 1.0);
    glEnd();
    // atas
    glBegin(GL_POLYGON);
    glVertex3f(15.7, 3.6, 1.0);
    glVertex3f(15.8, 3.6, 1.0);
    glVertex3f(15.8, 3.6, 0.7);
    glVertex3f(15.7, 3.6, 0.7);
    glEnd();
    // bawah
    glBegin(GL_POLYGON);
    glVertex3f(15.7, 0.4, 1.0);
    glVertex3f(15.8, 0.4, 1.0);
    glVertex3f(15.8, 0.4, 0.7);
    glVertex3f(15.7, 0.4, 0.7);
    glEnd();



    //MENGGAMBAR TANGGA 2



    //MENGGAMBAR TANGGA 3
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    for (float i = 10.4 + 0.3; i < 13.0; i += 0.5) {
        //anak tangga
        //depan
        glBegin(GL_POLYGON);
        glVertex3f(i, 0.7, 1.0);
        glVertex3f(i, 0.7 - 0.4, 1.0);
        glVertex3f(i + 0.1, 0.7 - 0.4, 1.0);
        glVertex3f(i + 0.1, 0.7, 1.0);
        glEnd();
        //belakang
        // Sisi kiri
        glBegin(GL_POLYGON);
        glVertex3f(i, 0.7, 1.0);
        glVertex3f(i, 0.7, 0.7);
        glVertex3f(i, 0.7 - 0.4, 0.7);
        glVertex3f(i, 0.7 - 0.4, 1.0);
        glEnd();
        // Sisi kanan
        glBegin(GL_POLYGON);
        glVertex3f(i + 0.1, 0.7, 1.0);
        glVertex3f(i + 0.1, 0.7, 0.7);
        glVertex3f(i + 0.1, 0.7 - 0.4, 0.7);
        glVertex3f(i + 0.1, 0.7 - 0.4, 1.0);
        glEnd();
        // Sisi atas
        glBegin(GL_POLYGON);
        glVertex3f(i, 0.7, 1.0);
        glVertex3f(i, 0.7, 0.7);
        glVertex3f(i + 0.1, 0.7, 0.7);
        glVertex3f(i + 0.1, 0.7, 1.0);
        glEnd();
        // Sisi bawah
        glBegin(GL_POLYGON);
        glVertex3f(i, 0.7 - 0.4, 1.0);
        glVertex3f(i, 0.7 - 0.4, 0.7);
        glVertex3f(i + 0.1, 0.7 - 0.4, 0.7);
        glVertex3f(i + 0.1, 0.7 - 0.4, 1.0);
        glEnd();
    }
    //gagang kiri
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7, 1.0);
    glVertex3f(13.4, 0.7, 1.0);
    glVertex3f(10.4, 0.7 + 0.1, 1.0);
    glVertex3f(13.4, 0.7 + 0.1, 1.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7, 0.7);
    glVertex3f(13.4, 0.7, 0.7);
    glVertex3f(13.4, 0.7 + 0.1, 0.7);
    glVertex3f(10.4, 0.7 + 0.1, 0.7);
    glEnd();
    // Kiri
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7, 1.0);
    glVertex3f(13.4, 0.7, 0.7);
    glVertex3f(13.4, 0.7 + 0.1, 0.7);
    glVertex3f(10.4, 0.7 + 0.1, 1.0);
    glEnd();
    // Kanan
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7, 1.0);
    glVertex3f(13.4, 0.7, 0.7);
    glVertex3f(13.4, 0.7 + 0.1, 0.7);
    glVertex3f(10.4, 0.7 + 0.1, 1.0);
    glEnd();
    // Atas
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 + 0.1, 1.0);
    glVertex3f(13.4, 0.7 + 0.1, 1.0);
    glVertex3f(13.4, 0.7 + 0.1, 0.7);
    glVertex3f(10.4, 0.7 + 0.1, 0.7);
    glEnd();
    // Bawah
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7, 1.0);
    glVertex3f(13.4, 0.7, 1.0);
    glVertex3f(13.4, 0.7, 0.7);
    glVertex3f(10.4, 0.7, 0.7);
    glEnd();

    //gagang kanan
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.4, 1.0);
    glVertex3f(10.4, 0.7 - 0.4, 1.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.5, 0.7);
    glVertex3f(13.4, 0.7 - 0.5, 0.7);
    glVertex3f(13.4, 0.7 - 0.4, 0.7);
    glVertex3f(10.4, 0.7 - 0.4, 0.7);
    glEnd();
    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.5, 0.7);
    glVertex3f(13.4, 0.7 - 0.4, 0.7);
    glVertex3f(10.4, 0.7 - 0.4, 1.0);
    glEnd();
    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.5, 0.7);
    glVertex3f(13.4, 0.7 - 0.4, 0.7);
    glVertex3f(10.4, 0.7 - 0.4, 1.0);
    glEnd();
    //Atas
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.4, 1.0);
    glVertex3f(13.4, 0.7 - 0.4, 1.0);
    glVertex3f(13.4, 0.7 - 0.4, 0.7);
    glVertex3f(10.4, 0.7 - 0.4, 0.7);
    glEnd();
    //Bawah
    glBegin(GL_POLYGON);
    glVertex3f(10.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.5, 1.0);
    glVertex3f(13.4, 0.7 - 0.5, 0.7);
    glVertex3f(10.4, 0.7 - 0.5, 0.7);
    glEnd();




    //MENGGAMBAR TANGGA 4
// MENGGAMBAR TANGGA 4
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah

    // ANAK TANGGA
    for (float i = 0; i < 3; i += 0.5) {
        // Depan
        glBegin(GL_POLYGON);
        glVertex3f(5.6f + i, 0.9f + i, 1.0);
        glVertex3f(5.5f + i, 0.8f + i, 1.0);
        glVertex3f(5.95f + i, 0.5f + i, 1.0);
        glVertex3f(6.0f + i, 0.6f + i, 1.0);
        glEnd();

        // Belakang
        glBegin(GL_POLYGON);
        glVertex3f(5.6f + i, 0.9f + i, 0.7);
        glVertex3f(5.5f + i, 0.8f + i, 0.7);
        glVertex3f(5.95f + i, 0.5f + i, 0.7);
        glVertex3f(6.0f + i, 0.6f + i, 0.7);
        glEnd();

        // Sisi Penghubung
        glBegin(GL_QUADS);
        // Kiri
        glVertex3f(5.6f + i, 0.9f + i, 1.0);
        glVertex3f(5.6f + i, 0.9f + i, 0.7);
        glVertex3f(5.5f + i, 0.8f + i, 0.7);
        glVertex3f(5.5f + i, 0.8f + i, 1.0);

        // Kanan
        glVertex3f(6.0f + i, 0.6f + i, 1.0);
        glVertex3f(6.0f + i, 0.6f + i, 0.7);
        glVertex3f(5.95f + i, 0.5f + i, 0.7);
        glVertex3f(5.95f + i, 0.5f + i, 1.0);

        // Atas (diperbaiki)
        glVertex3f(5.6f + i, 0.9f + i, 1.0);
        glVertex3f(5.6f + i, 0.9f + i, 0.7);
        glVertex3f(6.0f + i, 0.6f + i, 0.7);
        glVertex3f(6.0f + i, 0.6f + i, 1.0);

        // Bawah (diperbaiki)
        glVertex3f(5.5f + i, 0.8f + i, 1.0);
        glVertex3f(5.5f + i, 0.8f + i, 0.7);
        glVertex3f(5.95f + i, 0.5f + i, 0.7);
        glVertex3f(5.95f + i, 0.5f + i, 1.0);
        glEnd();
    }

    // GAGANG KIRI
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(5.4f, 0.7f, 1.0);
    glVertex3f(5.5f, 0.6f, 1.0);
    glVertex3f(8.4f, 3.7f, 1.0);
    glVertex3f(8.3f, 3.8f, 1.0);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.4f, 0.7f, 0.7);
    glVertex3f(5.5f, 0.6f, 0.7);
    glVertex3f(8.4f, 3.7f, 0.7);
    glVertex3f(8.3f, 3.8f, 0.7);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Kiri
    glVertex3f(5.4f, 0.7f, 1.0);
    glVertex3f(5.4f, 0.7f, 0.7);
    glVertex3f(8.3f, 3.8f, 0.7);
    glVertex3f(8.3f, 3.8f, 1.0);

    // Kanan
    glVertex3f(5.5f, 0.6f, 1.0);
    glVertex3f(5.5f, 0.6f, 0.7);
    glVertex3f(8.4f, 3.7f, 0.7);
    glVertex3f(8.4f, 3.7f, 1.0);

    // Atas
    glVertex3f(8.3f, 3.8f, 1.0);
    glVertex3f(8.3f, 3.8f, 0.7);
    glVertex3f(8.4f, 3.7f, 0.7);
    glVertex3f(8.4f, 3.7f, 1.0);

    // Bawah
    glVertex3f(5.4f, 0.7f, 1.0);
    glVertex3f(5.4f, 0.7f, 0.7);
    glVertex3f(5.5f, 0.6f, 0.7);
    glVertex3f(5.5f, 0.6f, 1.0);
    glEnd();

    // GAGANG KANAN
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(5.7f, 0.3f, 1.0);
    glVertex3f(5.8f, 0.2f, 1.0);
    glVertex3f(8.7f, 3.3f, 1.0);
    glVertex3f(8.6f, 3.4f, 1.0);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.7f, 0.3f, 0.7);
    glVertex3f(5.8f, 0.2f, 0.7);
    glVertex3f(8.7f, 3.3f, 0.7);
    glVertex3f(8.6f, 3.4f, 0.7);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Kiri
    glVertex3f(5.7f, 0.3f, 1.0);
    glVertex3f(5.7f, 0.3f, 0.7);
    glVertex3f(8.6f, 3.4f, 0.7);
    glVertex3f(8.6f, 3.4f, 1.0);

    // Kanan
    glVertex3f(5.8f, 0.2f, 1.0);
    glVertex3f(5.8f, 0.2f, 0.7);
    glVertex3f(8.7f, 3.3f, 0.7);
    glVertex3f(8.7f, 3.3f, 1.0);

    // Atas
    glVertex3f(5.8f, 0.2f, 1.0);
    glVertex3f(5.8f, 0.2f, 0.7);
    glVertex3f(8.7f, 3.3f, 0.7);
    glVertex3f(8.7f, 3.3f, 1.0);

    // Bawah
    glVertex3f(5.7f, 0.3f, 1.0);
    glVertex3f(5.7f, 0.3f, 0.7);
    glVertex3f(8.6f, 3.4f, 0.7);
    glVertex3f(8.6f, 3.4f, 1.0);
    glEnd();

}

void drawUlar(){
    //MENGGAMBAR ULAR 1
    //kepala
    glColor3f(0.36f, 0.25f, 0.20f);
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(13.5, 3.5, 1.0);
    glVertex3f(13.6 + 0.1, 3.5, 1.0);
    glVertex3f(14.2 + 0.1, 2.8, 1.0);
    glVertex3f(14.1, 2.8, 1.0);
    glEnd();
    // belakang
    glBegin(GL_POLYGON);
    glVertex3f(13.5, 3.5, 0.7);
    glVertex3f(13.6, 3.5, 0.7);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(14.1, 2.8, 0.7);
    glEnd();
    // kiri
    glBegin(GL_POLYGON);
    glVertex3f(13.5, 3.5, 1.0);
    glVertex3f(13.5, 3.5, 0.7);
    glVertex3f(14.1, 2.8, 0.7);
    glVertex3f(14.1, 2.8, 1.0);
    glEnd();
    // kanan
    glBegin(GL_POLYGON);
    glVertex3f(13.6, 3.5, 1.0);
    glVertex3f(13.6, 3.5, 0.7);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(14.2, 2.8, 1.0);
    glEnd();
    // atas
    glBegin(GL_POLYGON);
    glVertex3f(13.5, 3.5, 1.0);
    glVertex3f(13.6, 3.5, 1.0);
    glVertex3f(13.6, 3.5, 0.7);
    glVertex3f(13.5, 3.5, 0.7);
    glEnd();
    // bawah
    glBegin(GL_POLYGON);
    glVertex3f(14.1, 2.8, 1.0);
    glVertex3f(14.2, 2.8, 1.0);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(14.1, 2.8, 0.7);
    glEnd();

    //badan
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(14.1, 2.8, 1.0);
    glVertex3f(14.2 + 0.1, 2.8, 1.0);
    glVertex3f(15.5 + 0.1, 2.2, 1.0);
    glVertex3f(15.4, 2.2, 1.0);
    glEnd();
    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(14.1, 2.8, 0.7);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(15.4, 2.2, 0.7);
    glEnd();
    // Kiri
    glBegin(GL_POLYGON);
    glVertex3f(14.1, 2.8, 1.0);
    glVertex3f(14.1, 2.8, 0.7);
    glVertex3f(15.4, 2.2, 0.7);
    glVertex3f(15.4, 2.2, 1.0);
    glEnd();
    // Kanan
    glBegin(GL_POLYGON);
    glVertex3f(14.2, 2.8, 1.0);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(15.5, 2.2, 1.0);
    glEnd();
    // Atas
    glBegin(GL_POLYGON);
    glVertex3f(14.1, 2.8, 1.0);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(14.2, 2.8, 0.7);
    glVertex3f(14.1, 2.8, 1.0);
    glEnd();
    // Bawah
    glBegin(GL_POLYGON);
    glVertex3f(15.4, 2.2, 1.0);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(15.4, 2.2, 1.0);
    glEnd();

    //ekor
    // depan
    glBegin(GL_POLYGON);
    glVertex3f(15.4, 2.2, 1.0);
    glVertex3f(15.5 + 0.1, 2.2, 1.0);
    glVertex3f(16.5 + 0.1, 1.5, 1.0);
    glVertex3f(16.5, 1.5, 1.0);
    glEnd();
    // belakang
    glBegin(GL_POLYGON);
    glVertex3f(15.4, 2.2, 0.7);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(16.5, 1.5, 0.7);
    glVertex3f(16.5, 1.5, 0.7);
    glEnd();
    // kiri
    glBegin(GL_POLYGON);
    glVertex3f(15.4, 2.2, 1.0);
    glVertex3f(15.4, 2.2, 0.7);
    glVertex3f(16.5, 1.5, 0.7);
    glVertex3f(16.5, 1.5, 1.0);
    glEnd();
    // kanan
    glBegin(GL_POLYGON);
    glVertex3f(15.5, 2.2, 1.0);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(16.5, 1.5, 0.7);
    glVertex3f(16.5, 1.5, 1.0);
    glEnd();
    // atas
    glBegin(GL_POLYGON);
    glVertex3f(15.4, 2.2, 1.0);
    glVertex3f(15.5, 2.2, 1.0);
    glVertex3f(15.5, 2.2, 0.7);
    glVertex3f(15.4, 2.2, 0.7);
    glEnd();
    // bawah
    glBegin(GL_POLYGON);
    glVertex3f(16.5, 1.5, 1.0);
    glVertex3f(16.5, 1.5, 0.7);
    glVertex3f(16.5, 1.5, 0.7);
    glVertex3f(16.5, 1.5, 1.0);
    glEnd();




    //MENGGAMBAR ULAR 2
    //kepala
    //depan

    glColor3f(0.36f, 0.25f, 0.20f);

    glBegin(GL_POLYGON);
    glVertex3f(4.5, 3.5, 1.0);
    glVertex3f(4.6 + 0.1, 3.5, 1.0);
    glVertex3f(5.6 + 0.1, 2.8, 1.0);
    glVertex3f(5.5, 2.8, 1.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glVertex3f(4.5, 3.5, 0.7);
    glVertex3f(4.6, 3.5, 0.7);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.5, 2.8, 0.7);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glVertex3f(4.5, 3.5, 1.0);
    glVertex3f(4.5, 3.5, 0.7);
    glVertex3f(5.5, 2.8, 0.7);
    glVertex3f(5.5, 2.8, 1.0);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glVertex3f(4.6, 3.5, 1.0);
    glVertex3f(4.6, 3.5, 0.7);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.6, 2.8, 1.0);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glVertex3f(4.5, 3.5, 1.0);
    glVertex3f(4.6, 3.5, 1.0);
    glVertex3f(4.6, 3.5, 0.7);
    glVertex3f(4.5, 3.5, 0.7);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.8, 1.0);
    glVertex3f(5.6, 2.8, 1.0);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.5, 2.8, 0.7);
    glEnd();

    //badan
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.8, 1.0);
    glVertex3f(5.6 + 0.1, 2.8, 1.0);
    glVertex3f(5.2 + 0.1, 2.5, 1.0);
    glVertex3f(5.1, 2.5, 1.0);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.8, 0.7);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(5.1, 2.5, 0.7);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.8, 1.0);
    glVertex3f(5.5, 2.8, 0.7);
    glVertex3f(5.1, 2.5, 0.7);
    glVertex3f(5.1, 2.5, 1.0);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glVertex3f(5.6, 2.8, 1.0);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(5.2, 2.5, 1.0);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.8, 1.0);
    glVertex3f(5.6, 2.8, 1.0);
    glVertex3f(5.6, 2.8, 0.7);
    glVertex3f(5.5, 2.8, 0.7);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 2.5, 1.0);
    glVertex3f(5.2, 2.5, 1.0);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(5.1, 2.5, 0.7);
    glEnd();

    //ekor
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 2.5, 1.0);
    glVertex3f(5.2 + 0.1, 2.5, 1.0);
    glVertex3f(6.5, 1.5, 1.0);
    glVertex3f(6.5, 1.5, 1.0);
    glEnd();
    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 2.5, 0.7);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(6.5, 1.5, 0.7);
    glVertex3f(6.5, 1.5, 0.7);
    glEnd();
    // Kiri
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 2.5, 1.0);
    glVertex3f(5.1, 2.5, 0.7);
    glVertex3f(6.5, 1.5, 0.7);
    glVertex3f(6.5, 1.5, 1.0);
    glEnd();
    // Kanan
    glBegin(GL_POLYGON);
    glVertex3f(5.2, 2.5, 1.0);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(6.5, 1.5, 0.7);
    glVertex3f(6.5, 1.5, 1.0);
    glEnd();
    // Atas
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 2.5, 1.0);
    glVertex3f(5.2, 2.5, 1.0);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(5.1, 2.5, 0.7);
    glEnd();
    // Bawah
    glBegin(GL_POLYGON);
    glVertex3f(6.5, 1.5, 1.0);
    glVertex3f(6.5, 1.5, 0.7);
    glVertex3f(5.2, 2.5, 0.7);
    glVertex3f(5.2, 2.5, 1.0);
    glEnd();




    //MENGGAMBAR ULAR 3

    glColor3f(0.36f, 0.25f, 0.20f);
    //kepala
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.5, 1.0);
    glVertex3f(5.6 + 0.1, 2.5, 1.0);
    glVertex3f(5.1 + 0.1, 1.8, 1.0);
    glVertex3f(5.0, 1.8, 1.0);
    glEnd();
    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.5, 0.7);
    glVertex3f(5.6, 2.5, 0.7);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(5.0, 1.8, 0.7);
    glEnd();
    // Left side
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.5, 1.0);
    glVertex3f(5.5, 2.5, 0.7);
    glVertex3f(5.0, 1.8, 0.7);
    glVertex3f(5.0, 1.8, 1.0);
    glEnd();
    // Right side
    glBegin(GL_POLYGON);
    glVertex3f(5.6, 2.5, 1.0);
    glVertex3f(5.6, 2.5, 0.7);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(5.1, 1.8, 1.0);
    glEnd();
    // Top side
    glBegin(GL_POLYGON);
    glVertex3f(5.5, 2.5, 1.0);
    glVertex3f(5.6, 2.5, 1.0);
    glVertex3f(5.6, 2.5, 0.7);
    glVertex3f(5.5, 2.5, 0.7);
    glEnd();
    // Bottom side
    glBegin(GL_POLYGON);
    glVertex3f(5.0, 1.8, 1.0);
    glVertex3f(5.1, 1.8, 1.0);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(5.0, 1.8, 0.7);
    glEnd();


    //badan
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(5.0, 1.8, 1.0);
    glVertex3f(5.1 + 0.1, 1.8, 1.0);
    glVertex3f(4.3 + 0.1, 1.3, 1.0);
    glVertex3f(4.2, 1.3, 1.0);
    glEnd();
    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(5.0, 1.8, 0.7);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(4.2, 1.3, 0.7);
    glEnd();
    // Kiri
    glBegin(GL_POLYGON);
    glVertex3f(5.0, 1.8, 1.0);
    glVertex3f(5.0, 1.8, 0.7);
    glVertex3f(4.2, 1.3, 0.7);
    glVertex3f(4.2, 1.3, 1.0);
    glEnd();
    // Kanan
    glBegin(GL_POLYGON);
    glVertex3f(5.1, 1.8, 1.0);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(4.3, 1.3, 1.0);
    glEnd();
    // Atas
    glBegin(GL_POLYGON);
    glVertex3f(5.0, 1.8, 1.0);
    glVertex3f(5.1, 1.8, 1.0);
    glVertex3f(5.1, 1.8, 0.7);
    glVertex3f(5.0, 1.8, 0.7);
    glEnd();
    // Bawah
    glBegin(GL_POLYGON);
    glVertex3f(4.2, 1.3, 1.0);
    glVertex3f(4.3, 1.3, 1.0);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(4.2, 1.3, 0.7);
    glEnd();

    //ekor
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(4.2, 1.3, 1.0);
    glVertex3f(4.3 + 0.1, 1.3, 1.0);
    glVertex3f(2.5 + 0.1, 0.8, 1.0);
    glVertex3f(2.5, 0.8, 1.0);
    glEnd();
    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(4.2, 1.3, 0.7);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(2.5, 0.8, 0.7);
    glVertex3f(2.5, 0.8, 0.7);
    glEnd();
    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(4.2, 1.3, 1.0);
    glVertex3f(4.2, 1.3, 0.7);
    glVertex3f(2.5, 0.8, 0.7);
    glVertex3f(2.5, 0.8, 1.0);
    glEnd();
    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(4.3, 1.3, 1.0);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(2.5, 0.8, 0.7);
    glVertex3f(2.5, 0.8, 1.0);
    glEnd();
    //Atas
    glBegin(GL_POLYGON);
    glVertex3f(4.2, 1.3, 1.0);
    glVertex3f(4.3, 1.3, 1.0);
    glVertex3f(4.3, 1.3, 0.7);
    glVertex3f(4.2, 1.3, 0.7);
    glEnd();
    //Bawah
    glBegin(GL_POLYGON);
    glVertex3f(2.5, 0.8, 1.0);
    glVertex3f(2.5, 0.8, 0.7);
    glVertex3f(2.5, 0.8, 0.7);
    glVertex3f(2.5, 0.8, 1.0);
    glEnd();
}

// beberapa contoh pembuatan kota
void drawKotak(bool warna_transparan) {
    if (warna_transparan) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
    } else {
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
    }

    // Kotak 1 warna
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    // Gambar kotak 1
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(0,0,0.5);
        glVertex3f(1,0,0.5);
        glVertex3f(1,1,0.5);
        glVertex3f(0,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(1,1,0.5);
        glVertex3f(1,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(0,0,0);
        glVertex3f(0,0,0.5);
        glVertex3f(0,1,0.5);
        glVertex3f(0,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,1,0);
        glVertex3f(0,1,0.5);
        glVertex3f(1,1,0.5);
        glVertex3f(1,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi bawah
        glVertex3f(0,0,0);
        glVertex3f(0,0,0.5);
        glVertex3f(1,0,0.5);
        glVertex3f(1,0,0);
    glEnd();

    // Kotak 2 warna
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    // Gambar kotak 2
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(1,0,0.5);
        glVertex3f(2,0,0.5);
        glVertex3f(2,1,0.5);
        glVertex3f(1,1,0.5);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(2,1,0);
        glVertex3f(2,0,0);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(2,0,0);
        glVertex3f(2,1,0);
        glVertex3f(2,1,0.5);
        glVertex3f(2,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(1,0,0);
        glVertex3f(1,0,0.5);
        glVertex3f(1,1,0.5);
        glVertex3f(1,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,1,0);
        glVertex3f(1,1,0.5);
        glVertex3f(2,1,0.5);
        glVertex3f(2,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi bawah
        glVertex3f(1,0,0);
        glVertex3f(1,0,0.5);
        glVertex3f(2,0,0.5);
        glVertex3f(2,0,0);
    glEnd();

    // Fungsi tambahan
    drawTwo(1.0f, -0.1f, 0.7f, 0.1f);

    // Restore OpenGL state setelah semua kotak selesai



    //kotak 3
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(2,0,0.5);
        glVertex3f(3,0,0.5);
        glVertex3f(3,1,0.5);
        glVertex3f(2,1,0.5);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(2,0,0);
        glVertex3f(2,1,0);
        glVertex3f(3,1,0);
        glVertex3f(3,0,0);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(2,0,0);
        glVertex3f(2,1,0);
        glVertex3f(2,1,0.5);
        glVertex3f(2,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(2,0,0);
        glVertex3f(2,0,0.5);
        glVertex3f(2,1,0.5);
        glVertex3f(2,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,1,0);
        glVertex3f(2,1,0.5);
        glVertex3f(3,1,0.5);
        glVertex3f(3,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,0,0);
        glVertex3f(2,0,0.5);
        glVertex3f(3,0,0.5);
        glVertex3f(3,0,0);
    glEnd();
    drawThree(2.0,-0.1,0.7,0.1);


    //kotak 4

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(3,0,0.5);
        glVertex3f(4,0,0.5);
        glVertex3f(4,1,0.5);
        glVertex3f(3,1,0.5);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(3,0,0);
        glVertex3f(3,1,0);
        glVertex3f(4,1,0);
        glVertex3f(4,0,0);
    glEnd();

    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(4,0,0);
        glVertex3f(4,1,0);
        glVertex3f(4,1,0.5);
        glVertex3f(4,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(3,0,0);
        glVertex3f(3,0,0.5);
        glVertex3f(3,1,0.5);
        glVertex3f(3,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,1,0);
        glVertex3f(3,1,0.5);
        glVertex3f(4,1,0.5);
        glVertex3f(4,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,0,0);
        glVertex3f(3,0,0.5);
        glVertex3f(4,0,0.5);
        glVertex3f(4,0,0);
    glEnd();


    //kotak 5

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
        glBegin(GL_POLYGON);
            // Sisi depan
            glVertex3f(4,0,0.5);
            glVertex3f(5,0,0.5);
            glVertex3f(5,1,0.5);
            glVertex3f(4,1,0.5);
        glEnd();

        glBegin(GL_POLYGON);
            // Sisi belakang
            glVertex3f(4,0,0);
            glVertex3f(4,1,0);
            glVertex3f(5,1,0);
            glVertex3f(5,0,0);
        glEnd();

        glBegin(GL_POLYGON);
            // Sisi kanan
            glVertex3f(5,0,0);
            glVertex3f(5,1,0);
            glVertex3f(5,1,0.5);
            glVertex3f(5,0,0.5);
        glEnd();
        glBegin(GL_POLYGON);
            // Sisi kiri
            glVertex3f(4,0,0);
            glVertex3f(4,0,0.5);
            glVertex3f(4,1,0.5);
            glVertex3f(4,1,0);
        glEnd();
         glBegin(GL_POLYGON);
            // Sisi atas
            glVertex3f(4,1,0);
            glVertex3f(4,1,0.5);
            glVertex3f(5,1,0.5);
            glVertex3f(5,1,0);
        glEnd();
         glBegin(GL_POLYGON);
            // Sisi atas
            glVertex3f(4,0,0);
            glVertex3f(4,0,0.5);
            glVertex3f(5,0,0.5);
            glVertex3f(5,0,0);
        glEnd();


    //kotak 6

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(5,0,0.5);
        glVertex3f(6,0,0.5);
        glVertex3f(6,1,0.5);
        glVertex3f(5,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(5,0,0);
        glVertex3f(5,1,0);
        glVertex3f(6,1,0);
        glVertex3f(6,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(6,0,0);
        glVertex3f(6,1,0);
        glVertex3f(6,1,0.5);
        glVertex3f(6,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(5,0,0);
        glVertex3f(5,0,0.5);
        glVertex3f(5,1,0.5);
        glVertex3f(5,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,1,0);
        glVertex3f(5,1,0.5);
        glVertex3f(6,1,0.5);
        glVertex3f(6,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,0,0);
        glVertex3f(5,0,0.5);
        glVertex3f(6,0,0.5);
        glVertex3f(6,0,0);
    glEnd();
    drawSix(5.0,-0.1,0.7,0.1);


    //kotak 7

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(6,0,0.5);
        glVertex3f(7,0,0.5);
        glVertex3f(7,1,0.5);
        glVertex3f(6,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(6,0,0);
        glVertex3f(6,1,0);
        glVertex3f(7,1,0);
        glVertex3f(7,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(7,0,0);
        glVertex3f(7,1,0);
        glVertex3f(7,1,0.5);
        glVertex3f(7,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(6,0,0);
        glVertex3f(6,0,0.5);
        glVertex3f(6,1,0.5);
        glVertex3f(6,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,1,0);
        glVertex3f(6,1,0.5);
        glVertex3f(7,1,0.5);
        glVertex3f(7,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,0,0);
        glVertex3f(6,0,0.5);
        glVertex3f(7,0,0.5);
        glVertex3f(7,0,0);
    glEnd();
    drawSeven(6.0,-0.1,0.7,0.1);

    //kotak 8

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(7,0,0.5);
        glVertex3f(8,0,0.5);
        glVertex3f(8,1,0.5);
        glVertex3f(7,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(7,0,0);
        glVertex3f(7,1,0);
        glVertex3f(8,1,0);
        glVertex3f(8,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(8,0,0);
        glVertex3f(8,1,0);
        glVertex3f(8,1,0.5);
        glVertex3f(8,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(7,0,0);
        glVertex3f(7,0,0.5);
        glVertex3f(7,1,0.5);
        glVertex3f(7,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,1,0);
        glVertex3f(7,1,0.5);
        glVertex3f(8,1,0.5);
        glVertex3f(8,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,0,0);
        glVertex3f(7,0,0.5);
        glVertex3f(8,0,0.5);
        glVertex3f(8,0,0);
    glEnd();


    //kotak 9

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(8,0,0.5);
        glVertex3f(9,0,0.5);
        glVertex3f(9,1,0.5);
        glVertex3f(8,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(8,0,0);
        glVertex3f(8,1,0);
        glVertex3f(9,1,0);
        glVertex3f(9,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(9,0,0);
        glVertex3f(9,1,0);
        glVertex3f(9,1,0.5);
        glVertex3f(9,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(8,0,0);
        glVertex3f(8,0,0.5);
        glVertex3f(8,1,0.5);
        glVertex3f(8,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,1,0);
        glVertex3f(8,1,0.5);
        glVertex3f(9,1,0.5);
        glVertex3f(9,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,0,0);
        glVertex3f(7,0,0.5);
        glVertex3f(8,0,0.5);
        glVertex3f(8,0,0);
    glEnd();
    drawNine(8.0,-0.1,0.7,0.1);

    //kotak 10

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(9,0,0.5);
        glVertex3f(10,0,0.5);
        glVertex3f(10,1,0.5);
        glVertex3f(9,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(9,0,0);
        glVertex3f(9,1,0);
        glVertex3f(10,1,0);
        glVertex3f(10,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(10,0,0);
        glVertex3f(10,1,0);
        glVertex3f(10,1,0.5);
        glVertex3f(10,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(9,0,0);
        glVertex3f(9,0,0.5);
        glVertex3f(9,1,0.5);
        glVertex3f(9,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,1,0);
        glVertex3f(9,1,0.5);
        glVertex3f(10,1,0.5);
        glVertex3f(10,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,0,0);
        glVertex3f(9,0,0.5);
        glVertex3f(10,0,0.5);
        glVertex3f(10,0,0);
    glEnd();


    //kotak 11

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(10,0,0.5);
        glVertex3f(11,0,0.5);
        glVertex3f(11,1,0.5);
        glVertex3f(10,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(10,0,0);
        glVertex3f(10,1,0);
        glVertex3f(11,1,0);
        glVertex3f(11,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(11,0,0);
        glVertex3f(11,1,0);
        glVertex3f(11,1,0.5);
        glVertex3f(11,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(10,0,0);
        glVertex3f(10,0,0.5);
        glVertex3f(10,1,0.5);
        glVertex3f(10,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,1,0);
        glVertex3f(10,1,0.5);
        glVertex3f(11,1,0.5);
        glVertex3f(11,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,0,0);
        glVertex3f(10,0,0.5);
        glVertex3f(11,0,0.5);
        glVertex3f(11,0,0);
    glEnd();


    //kotak 12

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(11,0,0.5);
        glVertex3f(12,0,0.5);
        glVertex3f(12,1,0.5);
        glVertex3f(11,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(11,0,0);
        glVertex3f(11,1,0);
        glVertex3f(12,1,0);
        glVertex3f(12,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(12,0,0);
        glVertex3f(12,1,0);
        glVertex3f(12,1,0.5);
        glVertex3f(12,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(11,0,0);
        glVertex3f(11,0,0.5);
        glVertex3f(11,1,0.5);
        glVertex3f(11,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,1,0);
        glVertex3f(11,1,0.5);
        glVertex3f(12,1,0.5);
        glVertex3f(12,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,0,0);
        glVertex3f(11,0,0.5);
        glVertex3f(12,0,0.5);
        glVertex3f(12,0,0);
    glEnd();

    drawTwo(11.0,-0.1,0.7,0.1);


    //kotak 13

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(12,0,0.5);
        glVertex3f(13,0,0.5);
        glVertex3f(13,1,0.5);
        glVertex3f(12,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(12,0,0);
        glVertex3f(12,1,0);
        glVertex3f(13,1,0);
        glVertex3f(13,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(13,0,0);
        glVertex3f(13,1,0);
        glVertex3f(13,1,0.5);
        glVertex3f(13,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(12,0,0);
        glVertex3f(12,0,0.5);
        glVertex3f(12,1,0.5);
        glVertex3f(12,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,1,0);
        glVertex3f(12,1,0.5);
        glVertex3f(13,1,0.5);
        glVertex3f(13,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,0,0);
        glVertex3f(12,0,0.5);
        glVertex3f(13,0,0.5);
        glVertex3f(13,0,0);
    glEnd();
    drawThree(12.0,-0.1,0.7,0.1);

    //kotak 14
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(13,0,0.5);
        glVertex3f(14,0,0.5);
        glVertex3f(14,1,0.5);
        glVertex3f(13,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(13,0,0);
        glVertex3f(13,1,0);
        glVertex3f(14,1,0);
        glVertex3f(14,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(14,0,0);
        glVertex3f(14,1,0);
        glVertex3f(14,1,0.5);
        glVertex3f(14,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(13,0,0);
        glVertex3f(13,0,0.5);
        glVertex3f(13,1,0.5);
        glVertex3f(13,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,1,0);
        glVertex3f(13,1,0.5);
        glVertex3f(14,1,0.5);
        glVertex3f(14,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,0,0);
        glVertex3f(13,0,0.5);
        glVertex3f(14,0,0.5);
        glVertex3f(14,0,0);
    glEnd();


    //kotak 15
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(14,0,0.5);
        glVertex3f(15,0,0.5);
        glVertex3f(15,1,0.5);
        glVertex3f(14,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(14,0,0);
        glVertex3f(14,1,0);
        glVertex3f(15,1,0);
        glVertex3f(15,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(15,0,0);
        glVertex3f(15,1,0);
        glVertex3f(15,1,0.5);
        glVertex3f(15,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(14,0,0);
        glVertex3f(14,0,0.5);
        glVertex3f(14,1,0.5);
        glVertex3f(14,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,1,0);
        glVertex3f(14,1,0.5);
        glVertex3f(15,1,0.5);
        glVertex3f(15,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,0,0);
        glVertex3f(14,0,0.5);
        glVertex3f(15,0,0.5);
        glVertex3f(15,0,0);
    glEnd();


    //kotak 16
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(15,0,0.5);
        glVertex3f(16,0,0.5);
        glVertex3f(16,1,0.5);
        glVertex3f(15,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(15,0,0);
        glVertex3f(15,1,0);
        glVertex3f(16,1,0);
        glVertex3f(16,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(16,0,0);
        glVertex3f(16,1,0);
        glVertex3f(16,1,0.5);
        glVertex3f(16,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(15,0,0);
        glVertex3f(15,0,0.5);
        glVertex3f(15,1,0.5);
        glVertex3f(15,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,1,0);
        glVertex3f(15,1,0.5);
        glVertex3f(16,1,0.5);
        glVertex3f(16,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,0,0);
        glVertex3f(15,0,0.5);
        glVertex3f(16,0,0.5);
        glVertex3f(16,0,0);
    glEnd();
    drawSix(15.0,-0.1,0.7,0.1);


    //kotak 17
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(16,0,0.5);
        glVertex3f(17,0,0.5);
        glVertex3f(17,1,0.5);
        glVertex3f(16,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(16,0,0);
        glVertex3f(16,1,0);
        glVertex3f(17,1,0);
        glVertex3f(17,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(17,0,0);
        glVertex3f(17,1,0);
        glVertex3f(17,1,0.5);
        glVertex3f(17,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(16,0,0);
        glVertex3f(16,0,0.5);
        glVertex3f(16,1,0.5);
        glVertex3f(16,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,1,0);
        glVertex3f(16,1,0.5);
        glVertex3f(17,1,0.5);
        glVertex3f(17,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,0,0);
        glVertex3f(16,0,0.5);
        glVertex3f(17,0,0.5);
        glVertex3f(17,0,0);
    glEnd();
    drawSeven(16.0,-0.1,0.7,0.1);


    //kotak 18

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(17,0,0.5);
        glVertex3f(18,0,0.5);
        glVertex3f(18,1,0.5);
        glVertex3f(17,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(17,0,0);
        glVertex3f(17,1,0);
        glVertex3f(18,1,0);
        glVertex3f(18,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(18,0,0);
        glVertex3f(18,1,0);
        glVertex3f(18,1,0.5);
        glVertex3f(18,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(17,0,0);
        glVertex3f(17,0,0.5);
        glVertex3f(17,1,0.5);
        glVertex3f(17,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,1,0);
        glVertex3f(17,1,0.5);
        glVertex3f(18,1,0.5);
        glVertex3f(18,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,0,0);
        glVertex3f(17,0,0.5);
        glVertex3f(18,0,0.5);
        glVertex3f(18,0,0);
    glEnd();


    //kotak 19

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(18,0,0.5);
        glVertex3f(19,0,0.5);
        glVertex3f(19,1,0.5);
        glVertex3f(18,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(18,0,0);
        glVertex3f(18,1,0);
        glVertex3f(19,1,0);
        glVertex3f(19,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(19,0,0);
        glVertex3f(19,1,0);
        glVertex3f(19,1,0.5);
        glVertex3f(19,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(18,0,0);
        glVertex3f(18,0,0.5);
        glVertex3f(18,1,0.5);
        glVertex3f(18,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,1,0);
        glVertex3f(18,1,0.5);
        glVertex3f(19,1,0.5);
        glVertex3f(19,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,0,0);
        glVertex3f(18,0,0.5);
        glVertex3f(19,0,0.5);
        glVertex3f(19,0,0);
    glEnd();
    drawNine(18.0,-0.1,0.7,0.1);


    //kotak 20
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(19,0,0.5);
        glVertex3f(20,0,0.5);
        glVertex3f(20,1,0.5);
        glVertex3f(19,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(19,0,0);
        glVertex3f(19,1,0);
        glVertex3f(20,1,0);
        glVertex3f(20,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(20,0,0);
        glVertex3f(20,1,0);
        glVertex3f(20,1,0.5);
        glVertex3f(20,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(19,0,0);
        glVertex3f(19,0,0.5);
        glVertex3f(19,1,0.5);
        glVertex3f(19,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,1,0);
        glVertex3f(19,1,0.5);
        glVertex3f(20,1,0.5);
        glVertex3f(20,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,0,0);
        glVertex3f(19,0,0.5);
        glVertex3f(20,0,0.5);
        glVertex3f(20,0,0);
    glEnd();
    drawTwo(19.0,-0.1,0.7,0.1);

    //kotak 21

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(20,0,0.5);
        glVertex3f(21,0,0.5);
        glVertex3f(21,1,0.5);
        glVertex3f(20,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(20,0,0);
        glVertex3f(20,1,0);
        glVertex3f(21,1,0);
        glVertex3f(21,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(21,0,0);
        glVertex3f(21,1,0);
        glVertex3f(21,1,0.5);
        glVertex3f(21,0,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(20,0,0);
        glVertex3f(20,0,0.5);
        glVertex3f(20,1,0.5);
        glVertex3f(20,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,1,0);
        glVertex3f(20,1,0.5);
        glVertex3f(21,1,0.5);
        glVertex3f(21,1,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,0,0);
        glVertex3f(20,0,0.5);
        glVertex3f(21,0,0.5);
        glVertex3f(21,0,0);
    glEnd();
    drawTwo(19.95,-0.1,0.7,0.1);



    //kotak 22

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(20,1,0.5);
        glVertex3f(21,1,0.5);
        glVertex3f(21,2,0.5);
        glVertex3f(20,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(20,1,0);
        glVertex3f(20,2,0);
        glVertex3f(21,2,0);
        glVertex3f(21,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(21,1,0);
        glVertex3f(21,2,0);
        glVertex3f(21,2,0.5);
        glVertex3f(21,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(20,1,0);
        glVertex3f(20,1,0.5);
        glVertex3f(20,2,0.5);
        glVertex3f(20,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,2,0);
        glVertex3f(20,2,0.5);
        glVertex3f(21,2,0.5);
        glVertex3f(21,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,1,0);
        glVertex3f(20,1,0.5);
        glVertex3f(21,1,0.5);
        glVertex3f(21,1,0);
    glEnd();

    drawTwo(19.95,0.95,0.7,0.1);
    drawTwo(19.65,0.95,0.7,0.1);

    //kotak 23
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(19,1,0.5);
        glVertex3f(20,1,0.5);
        glVertex3f(20,2,0.5);
        glVertex3f(19,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(19,1,0);
        glVertex3f(19,2,0);
        glVertex3f(20,2,0);
        glVertex3f(20,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(20,1,0);
        glVertex3f(20,2,0);
        glVertex3f(20,2,0.5);
        glVertex3f(20,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(19,1,0);
        glVertex3f(19,1,0.5);
        glVertex3f(19,2,0.5);
        glVertex3f(19,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,2,0);
        glVertex3f(19,2,0.5);
        glVertex3f(20,2,0.5);
        glVertex3f(20,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,1,0);
        glVertex3f(19,1,0.5);
        glVertex3f(20,1,0.5);
        glVertex3f(20,1,0);
    glEnd();
    drawThree(18.95,0.95,0.7,0.1);
    drawTwo(18.65,0.95,0.7,0.1);

    //kotak 24

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(18,1,0.5);
        glVertex3f(19,1,0.5);
        glVertex3f(19,2,0.5);
        glVertex3f(18,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(18,1,0);
        glVertex3f(18,2,0);
        glVertex3f(19,2,0);
        glVertex3f(19,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(19,1,0);
        glVertex3f(19,2,0);
        glVertex3f(19,2,0.5);
        glVertex3f(19,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(18,1,0);
        glVertex3f(18,1,0.5);
        glVertex3f(18,2,0.5);
        glVertex3f(18,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,2,0);
        glVertex3f(18,2,0.5);
        glVertex3f(19,2,0.5);
        glVertex3f(19,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,1,0);
        glVertex3f(18,1,0.5);
        glVertex3f(19,1,0.5);
        glVertex3f(19,1,0);
    glEnd();
    drawTwo(18.0,0.95,0.7,0.1);

    //kotak 25

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(17,1,0.5);
        glVertex3f(18,1,0.5);
        glVertex3f(18,2,0.5);
        glVertex3f(17,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(17,1,0);
        glVertex3f(17,2,0);
        glVertex3f(18,2,0);
        glVertex3f(18,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(18,1,0);
        glVertex3f(18,2,0);
        glVertex3f(18,2,0.5);
        glVertex3f(18,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(17,1,0);
        glVertex3f(17,1,0.5);
        glVertex3f(17,2,0.5);
        glVertex3f(17,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,2,0);
        glVertex3f(17,2,0.5);
        glVertex3f(18,2,0.5);
        glVertex3f(18,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,1,0);
        glVertex3f(17,1,0.5);
        glVertex3f(18,1,0.5);
        glVertex3f(18,1,0);
    glEnd();
    drawTwo(17.0,0.95,0.7,0.1);


    //kotak 26

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(16,1,0.5);
        glVertex3f(17,1,0.5);
        glVertex3f(17,2,0.5);
        glVertex3f(16,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(16,1,0);
        glVertex3f(16,2,0);
        glVertex3f(17,2,0);
        glVertex3f(17,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(17,1,0);
        glVertex3f(17,2,0);
        glVertex3f(17,2,0.5);
        glVertex3f(17,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(16,1,0);
        glVertex3f(16,1,0.5);
        glVertex3f(16,2,0.5);
        glVertex3f(16,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,2,0);
        glVertex3f(16,2,0.5);
        glVertex3f(17,2,0.5);
        glVertex3f(17,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,1,0);
        glVertex3f(16,1,0.5);
        glVertex3f(17,1,0.5);
        glVertex3f(17,1,0);
    glEnd();
    drawSix(16.0,0.95,0.7,0.1);
    drawTwo(15.7,0.95,0.7,0.1);




    //kotak 27

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(15,1,0.5);
        glVertex3f(16,1,0.5);
        glVertex3f(16,2,0.5);
        glVertex3f(15,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(15,1,0);
        glVertex3f(15,2,0);
        glVertex3f(16,2,0);
        glVertex3f(16,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(16,1,0);
        glVertex3f(16,2,0);
        glVertex3f(16,2,0.5);
        glVertex3f(16,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(15,1,0);
        glVertex3f(15,1,0.5);
        glVertex3f(15,2,0.5);
        glVertex3f(15,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,2,0);
        glVertex3f(15,2,0.5);
        glVertex3f(16,2,0.5);
        glVertex3f(16,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,1,0);
        glVertex3f(15,1,0.5);
        glVertex3f(16,1,0.5);
        glVertex3f(16,1,0);
    glEnd();
    drawSeven(15.0,0.95,0.7,0.1);
    drawTwo(14.7,0.95,0.7,0.1);


    //kotak 28

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glBegin(GL_POLYGON);
            glVertex3f(14, 1, 0.5);  // Kiri bawah
            glVertex3f(15, 1, 0.5);  // Kanan bawah
            glVertex3f(15, 2, 0.5);  // Kanan atas
            glVertex3f(14, 2, 0.5);  // Kiri atas
        glEnd();
        // sisi belakang
        glBegin(GL_POLYGON);
            glVertex3f(14, 1, 0);    // Kiri bawah
            glVertex3f(14, 2, 0);    // Kanan bawah
            glVertex3f(15, 2, 0);    // Kanan atas
            glVertex3f(15, 1, 0);    // Kiri atas
        glEnd();
        // sisi kanan
        glBegin(GL_POLYGON);
            glVertex3f(15, 1, 0);    // Belakang bawah
            glVertex3f(15, 2, 0.5);  // Depan bawah
            glVertex3f(15, 2, 0.5);  // Depan atas
            glVertex3f(15, 1, 0);    // Belakang atas
        glEnd();
        // sisi kiri
        glBegin(GL_POLYGON);
            glVertex3f(14, 1, 0);    // Belakang bawah
            glVertex3f(14, 1, 0.5);  // Depan bawah
            glVertex3f(14, 2, 0.5);  // Depan atas
            glVertex3f(14, 2, 0);    // Belakang atas
        glEnd();
        // sisi atas
        glBegin(GL_POLYGON);
            glVertex3f(14, 2, 0);    // Kiri belakang
            glVertex3f(14, 2, 0.5);  // Kiri depan
            glVertex3f(15, 2, 0.5);  // Kanan depan
            glVertex3f(15, 2, 0);    // Kanan belakang
        glEnd();
        // sisi atas
        glBegin(GL_POLYGON);
            glVertex3f(14, 1, 0);
            glVertex3f(14, 1, 0.5);
            glVertex3f(15, 1, 0.5);
            glVertex3f(15, 1, 0);
        glEnd();
    drawTwo(14.0,0.95,0.7,0.1);




    //kotak 29

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    // sisi depan
    glBegin(GL_POLYGON);
        glVertex3f(13,1,0);
        glVertex3f(14,1,0);
        glVertex3f(14,2,0);
        glVertex3f(13,2,0);
    glEnd();

    // sisi belakanag
    glBegin(GL_POLYGON);
        glVertex3f(13,1,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(14,2,0.5);
        glVertex3f(14,1,0.5);
    glEnd();

    // sisi kanan
    glBegin(GL_POLYGON);
        glVertex3f(14,1,0);
        glVertex3f(14,2,0.5);
        glVertex3f(14,2,0.5);
        glVertex3f(14,1,0);
    glEnd();

    // sisi kiri
    glBegin(GL_POLYGON);
        glVertex3f(13,1,0);
        glVertex3f(13,1,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(13,2,0);
    glEnd();

    // sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(13,2,0);
        glVertex3f(13,2,0.5);
        glVertex3f(14,2,0.5);
        glVertex3f(14,2,0);
    glEnd();

    // sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(13,1,0);
        glVertex3f(13,1,0.5);
        glVertex3f(14,1,0.5);
        glVertex3f(14,1,0);
    glEnd();

    glDisable(GL_POLYGON);
    drawNine(13.0,0.95,0.7,0.1);
    drawTwo(12.7,0.95,0.7,0.1);


    //kotak 30

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }

    // sisi depan
    glBegin(GL_POLYGON);
        glVertex3f(12,1,0.5);
        glVertex3f(13,1,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(12,2,0.5);
    glEnd();

    // Sisi belakang
    glBegin(GL_POLYGON);
        glVertex3f(12,1,0);
        glVertex3f(12,2,0);
        glVertex3f(13,2,0);
        glVertex3f(13,1,0);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
        glVertex3f(13,1,0);
        glVertex3f(13,2,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(13,1,0);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
        glVertex3f(12,1,0);
        glVertex3f(12,1,0.5);
        glVertex3f(12,2,0.5);
        glVertex3f(12,2,0);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(12,2,0);
        glVertex3f(12,2,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(13,2,0);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
        glVertex3f(12,1,0);
        glVertex3f(12,1,0.5);
        glVertex3f(13,1,0.5);
        glVertex3f(13,1,0);
    glEnd();

    drawThree(12.0,0.95,0.7,0.1);

    //kotak 31

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }

    // Sisi depan
    glBegin(GL_POLYGON);
        glVertex3f(11,1,0.5);
        glVertex3f(12,1,0.5);
        glVertex3f(12,2,0.5);
        glVertex3f(11,2,0.5);
    glEnd();

    // Sisi belakang
    glBegin(GL_POLYGON);
        glVertex3f(11,1,0);
        glVertex3f(11,2,0);
        glVertex3f(12,2,0);
        glVertex3f(12,1,0);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
        glVertex3f(12,1,0);
        glVertex3f(12,2,0);
        glVertex3f(12,2,0.5);
        glVertex3f(12,1,0.5);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
        glVertex3f(11,1,0);
        glVertex3f(11,1,0.5);
        glVertex3f(11,2,0.5);
        glVertex3f(11,2,0);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(11,2,0);
        glVertex3f(11,2,0.5);
        glVertex3f(12,2,0.5);
        glVertex3f(12,2,0);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
        glVertex3f(11,1,0);
        glVertex3f(11,1,0.5);
        glVertex3f(12,1,0.5);
        glVertex3f(12,1,0);
    glEnd();
    drawThree(11.0,0.95,0.7,0.1);


    //kotak 32

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }

    // Sisi depan
    glBegin(GL_POLYGON);
        glVertex3f(10,1,0.5);
        glVertex3f(11,1,0.5);
        glVertex3f(11,2,0.5);
        glVertex3f(10,2,0.5);
    glEnd();

    // Sisi belakang
    glBegin(GL_POLYGON);
        glVertex3f(10,1,0);
        glVertex3f(10,2,0);
        glVertex3f(11,2,0);
        glVertex3f(11,1,0);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
        glVertex3f(11,1,0);
        glVertex3f(11,2,0);
        glVertex3f(11,2,0.5);
        glVertex3f(11,1,0.5);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
        glVertex3f(10,1,0);
        glVertex3f(10,1,0.5);
        glVertex3f(10,2,0.5);
        glVertex3f(10,2,0);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(10,2,0);
        glVertex3f(10,2,0.5);
        glVertex3f(11,2,0.5);
        glVertex3f(11,2,0);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
        glVertex3f(10,1,0);
        glVertex3f(10,1,0.5);
        glVertex3f(11,1,0.5);
        glVertex3f(11,1,0);
    glEnd();
    drawTwo(10.0,0.95,0.7,0.1);
    drawThree(9.7,0.95,0.7,0.1);


    //kotak 33

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }

    // Sisi depan
    glBegin(GL_POLYGON);
        glVertex3f(9,1,0.5);
        glVertex3f(10,1,0.5);
        glVertex3f(10,2,0.5);
        glVertex3f(9,2,0.5);
    glEnd();

    // Sisi belakang
    glBegin(GL_POLYGON);
        glVertex3f(9,1,0);
        glVertex3f(9,2,0);
        glVertex3f(10,2,0);
        glVertex3f(10,1,0);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
        glVertex3f(10,1,0);
        glVertex3f(10,2,0);
        glVertex3f(10,2,0.5);
        glVertex3f(10,1,0.5);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
        glVertex3f(9,1,0);
        glVertex3f(9,1,0.5);
        glVertex3f(9,2,0.5);
        glVertex3f(9,2,0);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
        glVertex3f(9,2,0);
        glVertex3f(9,2,0.5);
        glVertex3f(10,2,0.5);
        glVertex3f(10,2,0);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
        glVertex3f(9,1,0);
        glVertex3f(9,1,0.5);
        glVertex3f(10,1,0.5);
        glVertex3f(10,1,0);
    glEnd();
    drawThree(9.0,0.95,0.7,0.1);
    drawThree(8.7,0.95,0.7,0.1);


    //kotak 34

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(8,1,0.5);
        glVertex3f(9,1,0.5);
        glVertex3f(9,2,0.5);
        glVertex3f(8,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(8,1,0);
        glVertex3f(8,2,0);
        glVertex3f(9,2,0);
        glVertex3f(9,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(9,1,0);
        glVertex3f(9,2,0);
        glVertex3f(9,2,0.5);
        glVertex3f(9,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(8,1,0);
        glVertex3f(8,1,0.5);
        glVertex3f(8,2,0.5);
        glVertex3f(8,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,2,0);
        glVertex3f(8,2,0.5);
        glVertex3f(9,2,0.5);
        glVertex3f(9,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,1,0);
        glVertex3f(8,1,0.5);
        glVertex3f(9,1,0.5);
        glVertex3f(9,1,0);
    glEnd();
    drawThree(8.0,0.95,0.7,0.1);


    //kotak 35

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(7,1,0.5);
        glVertex3f(8,1,0.5);
        glVertex3f(8,2,0.5);
        glVertex3f(7,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(7,1,0);
        glVertex3f(7,2,0);
        glVertex3f(8,2,0);
        glVertex3f(8,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(8,1,0);
        glVertex3f(8,2,0);
        glVertex3f(8,2,0.5);
        glVertex3f(8,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(7,1,0);
        glVertex3f(7,1,0.5);
        glVertex3f(7,2,0.5);
        glVertex3f(7,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,2,0);
        glVertex3f(7,2,0.5);
        glVertex3f(8,2,0.5);
        glVertex3f(8,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,1,0);
        glVertex3f(7,1,0.5);
        glVertex3f(8,1,0.5);
        glVertex3f(8,1,0);
    glEnd();
    drawThree(7.0,0.95,0.7,0.1);


    //kotak 36

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(6,1,0.5);
        glVertex3f(7,1,0.5);
        glVertex3f(7,2,0.5);
        glVertex3f(6,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(6,1,0);
        glVertex3f(6,2,0);
        glVertex3f(7,2,0);
        glVertex3f(7,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(7,1,0);
        glVertex3f(7,2,0);
        glVertex3f(7,2,0.5);
        glVertex3f(7,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(6,1,0);
        glVertex3f(6,1,0.5);
        glVertex3f(6,2,0.5);
        glVertex3f(6,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,2,0);
        glVertex3f(6,2,0.5);
        glVertex3f(7,2,0.5);
        glVertex3f(7,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,1,0);
        glVertex3f(6,1,0.5);
        glVertex3f(7,1,0.5);
        glVertex3f(7,1,0);
    glEnd();
    drawSix(6.0,0.95,0.7,0.1);
    drawThree(5.7,0.95,0.7,0.1);


    //kotak 37

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(5,1,0.5);
        glVertex3f(6,1,0.5);
        glVertex3f(6,2,0.5);
        glVertex3f(5,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(5,1,0);
        glVertex3f(5,2,0);
        glVertex3f(6,2,0);
        glVertex3f(6,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(6,1,0);
        glVertex3f(6,2,0);
        glVertex3f(6,2,0.5);
        glVertex3f(6,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(5,1,0);
        glVertex3f(5,1,0.5);
        glVertex3f(5,2,0.5);
        glVertex3f(5,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,2,0);
        glVertex3f(5,2,0.5);
        glVertex3f(6,2,0.5);
        glVertex3f(6,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,1,0);
        glVertex3f(5,1,0.5);
        glVertex3f(6,1,0.5);
        glVertex3f(6,1,0);
    glEnd();
    drawSeven(5.0,0.95,0.7,0.1);
    drawThree(4.7,0.95,0.7,0.1);


    //kotak 38

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(4,1,0.5);
        glVertex3f(5,1,0.5);
        glVertex3f(5,2,0.5);
        glVertex3f(4,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(4,1,0);
        glVertex3f(4,2,0);
        glVertex3f(5,2,0);
        glVertex3f(5,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(5,1,0);
        glVertex3f(5,2,0);
        glVertex3f(5,2,0.5);
        glVertex3f(5,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(4,1,0);
        glVertex3f(4,1,0.5);
        glVertex3f(4,2,0.5);
        glVertex3f(4,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,2,0);
        glVertex3f(4,2,0.5);
        glVertex3f(5,2,0.5);
        glVertex3f(5,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,1,0);
        glVertex3f(4,1,0.5);
        glVertex3f(5,1,0.5);
        glVertex3f(5,1,0);
    glEnd();
    drawThree(4.0,0.95,0.7,0.1);


    //kotak 39

    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(3,1,0.5);
        glVertex3f(4,1,0.5);
        glVertex3f(4,2,0.5);
        glVertex3f(3,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(3,1,0);
        glVertex3f(3,2,0);
        glVertex3f(4,2,0);
        glVertex3f(4,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(4,1,0);
        glVertex3f(4,2,0);
        glVertex3f(4,2,0.5);
        glVertex3f(4,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(3,1,0);
        glVertex3f(3,1,0.5);
        glVertex3f(3,2,0.5);
        glVertex3f(3,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,2,0);
        glVertex3f(3,2,0.5);
        glVertex3f(4,2,0.5);
        glVertex3f(4,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,1,0);
        glVertex3f(3,1,0.5);
        glVertex3f(4,1,0.5);
        glVertex3f(4,1,0);
    glEnd();
    drawNine(3.0,0.95,0.7,0.1);
    drawThree(2.7,0.95,0.7,0.1);


    //kotak 40

    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(2,1,0.5);
        glVertex3f(3,1,0.5);
        glVertex3f(3,2,0.5);
        glVertex3f(2,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(2,1,0);
        glVertex3f(2,2,0);
        glVertex3f(3,2,0);
        glVertex3f(3,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(3,1,0);
        glVertex3f(3,2,0);
        glVertex3f(3,2,0.5);
        glVertex3f(3,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(2,1,0);
        glVertex3f(2,1,0.5);
        glVertex3f(2,2,0.5);
        glVertex3f(2,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,2,0);
        glVertex3f(2,2,0.5);
        glVertex3f(3,2,0.5);
        glVertex3f(3,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,1,0);
        glVertex3f(2,1,0.5);
        glVertex3f(3,1,0.5);
        glVertex3f(3,1,0);
    glEnd();

    //kotak 41

     if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(1,1,0.5);
        glVertex3f(2,1,0.5);
        glVertex3f(2,2,0.5);
        glVertex3f(1,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(1,1,0);
        glVertex3f(1,2,0);
        glVertex3f(2,2,0);
        glVertex3f(2,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(2,1,0);
        glVertex3f(2,2,0);
        glVertex3f(2,2,0.5);
        glVertex3f(2,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(1,1,0);
        glVertex3f(1,1,0.5);
        glVertex3f(1,2,0.5);
        glVertex3f(1,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,2,0);
        glVertex3f(1,2,0.5);
        glVertex3f(2,2,0.5);
        glVertex3f(2,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,1,0);
        glVertex3f(1,1,0.5);
        glVertex3f(2,1,0.5);
        glVertex3f(2,1,0);
    glEnd();


    //kotak 42
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(0,1,0.5);
        glVertex3f(1,1,0.5);
        glVertex3f(1,2,0.5);
        glVertex3f(0,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(0,1,0);
        glVertex3f(0,2,0);
        glVertex3f(1,2,0);
        glVertex3f(1,1,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(1,1,0);
        glVertex3f(1,2,0);
        glVertex3f(1,2,0.5);
        glVertex3f(1,1,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(0,1,0);
        glVertex3f(0,1,0.5);
        glVertex3f(0,2,0.5);
        glVertex3f(0,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,2,0);
        glVertex3f(0,2,0.5);
        glVertex3f(1,2,0.5);
        glVertex3f(1,2,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,1,0);
        glVertex3f(0,1,0.5);
        glVertex3f(1,1,0.5);
        glVertex3f(1,1,0);
    glEnd();
    drawTwo(0.0,0.95,0.7,0.1);

    //kotak 43
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(0,2,0.5);
        glVertex3f(1,2,0.5);
        glVertex3f(1,3,0.5);
        glVertex3f(0,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(0,2,0);
        glVertex3f(0,3,0);
        glVertex3f(1,3,0);
        glVertex3f(1,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(1,2,0);
        glVertex3f(1,3,0);
        glVertex3f(1,3,0.5);
        glVertex3f(1,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(0,2,0);
        glVertex3f(0,2,0.5);
        glVertex3f(0,3,0.5);
        glVertex3f(0,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,3,0);
        glVertex3f(0,3,0.5);
        glVertex3f(1,3,0.5);
        glVertex3f(1,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,2,0);
        glVertex3f(0,2,0.5);
        glVertex3f(1,2,0.5);
        glVertex3f(1,2,0);
    glEnd();
    drawThree(0.0,1.95,0.7,0.1);

    //kotak 44
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(1,2,0.5);
        glVertex3f(2,2,0.5);
        glVertex3f(2,3,0.5);
        glVertex3f(1,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(1,2,0);
        glVertex3f(1,3,0);
        glVertex3f(2,3,0);
        glVertex3f(2,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(2,2,0);
        glVertex3f(2,3,0);
        glVertex3f(2,3,0.5);
        glVertex3f(2,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(1,2,0);
        glVertex3f(1,2,0.5);
        glVertex3f(1,3,0.5);
        glVertex3f(1,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,3,0);
        glVertex3f(1,3,0.5);
        glVertex3f(2,3,0.5);
        glVertex3f(2,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,2,0);
        glVertex3f(1,2,0.5);
        glVertex3f(2,2,0.5);
        glVertex3f(2,2,0);
    glEnd();

    //kotak 45
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(2,2,0.5);
        glVertex3f(3,2,0.5);
        glVertex3f(3,3,0.5);
        glVertex3f(2,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(2,2,0);
        glVertex3f(2,3,0);
        glVertex3f(3,3,0);
        glVertex3f(3,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(3,2,0);
        glVertex3f(3,3,0);
        glVertex3f(3,3,0.5);
        glVertex3f(3,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(2,2,0);
        glVertex3f(2,2,0.5);
        glVertex3f(2,3,0.5);
        glVertex3f(2,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,3,0);
        glVertex3f(2,3,0.5);
        glVertex3f(3,3,0.5);
        glVertex3f(3,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,2,0);
        glVertex3f(2,2,0.5);
        glVertex3f(3,2,0.5);
        glVertex3f(3,2,0);
    glEnd();

    //kotak 46
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(3,2,0.5);
        glVertex3f(4,2,0.5);
        glVertex3f(4,3,0.5);
        glVertex3f(3,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(3,2,0);
        glVertex3f(3,3,0);
        glVertex3f(4,3,0);
        glVertex3f(4,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(4,2,0);
        glVertex3f(4,3,0);
        glVertex3f(4,3,0.5);
        glVertex3f(4,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(3,2,0);
        glVertex3f(3,2,0.5);
        glVertex3f(3,3,0.5);
        glVertex3f(3,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,3,0);
        glVertex3f(3,3,0.5);
        glVertex3f(4,3,0.5);
        glVertex3f(4,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,2,0);
        glVertex3f(3,2,0.5);
        glVertex3f(4,2,0.5);
        glVertex3f(4,2,0);
    glEnd();
    drawSix(3.0,1.95,0.7,0.1);



    //kotak 47
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(4,2,0.5);
        glVertex3f(5,2,0.5);
        glVertex3f(5,3,0.5);
        glVertex3f(4,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(4,2,0);
        glVertex3f(4,3,0);
        glVertex3f(5,3,0);
        glVertex3f(5,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(5,2,0);
        glVertex3f(5,3,0);
        glVertex3f(5,3,0.5);
        glVertex3f(5,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(4,2,0);
        glVertex3f(4,2,0.5);
        glVertex3f(4,3,0.5);
        glVertex3f(4,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,3,0);
        glVertex3f(4,3,0.5);
        glVertex3f(5,3,0.5);
        glVertex3f(5,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,2,0);
        glVertex3f(4,2,0.5);
        glVertex3f(5,2,0.5);
        glVertex3f(5,2,0);
    glEnd();
    drawSeven(4.0,1.95,0.7,0.1);

    //kotak 48
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(5,2,0.5);
        glVertex3f(6,2,0.5);
        glVertex3f(6,3,0.5);
        glVertex3f(5,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(5,2,0);
        glVertex3f(5,3,0);
        glVertex3f(6,3,0);
        glVertex3f(6,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(6,2,0);
        glVertex3f(6,3,0);
        glVertex3f(6,3,0.5);
        glVertex3f(6,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(5,2,0);
        glVertex3f(5,2,0.5);
        glVertex3f(5,3,0.5);
        glVertex3f(5,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,3,0);
        glVertex3f(5,3,0.5);
        glVertex3f(6,3,0.5);
        glVertex3f(6,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,2,0);
        glVertex3f(5,2,0.5);
        glVertex3f(6,2,0.5);
        glVertex3f(6,2,0);
    glEnd();

    //kotak 49
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(6,2,0.5);
        glVertex3f(7,2,0.5);
        glVertex3f(7,3,0.5);
        glVertex3f(6,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(6,2,0);
        glVertex3f(6,3,0);
        glVertex3f(7,3,0);
        glVertex3f(7,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(7,2,0);
        glVertex3f(7,3,0);
        glVertex3f(7,3,0.5);
        glVertex3f(7,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(6,2,0);
        glVertex3f(6,2,0.5);
        glVertex3f(6,3,0.5);
        glVertex3f(6,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,3,0);
        glVertex3f(6,3,0.5);
        glVertex3f(7,3,0.5);
        glVertex3f(7,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,2,0);
        glVertex3f(6,2,0.5);
        glVertex3f(7,2,0.5);
        glVertex3f(7,2,0);
    glEnd();
    drawNine(6.0,1.95,0.7,0.1);

    //kotak 50
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(7,2,0.5);
        glVertex3f(8,2,0.5);
        glVertex3f(8,3,0.5);
        glVertex3f(7,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(7,2,0);
        glVertex3f(7,3,0);
        glVertex3f(8,3,0);
        glVertex3f(8,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(8,2,0);
        glVertex3f(8,3,0);
        glVertex3f(8,3,0.5);
        glVertex3f(8,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(7,2,0);
        glVertex3f(7,2,0.5);
        glVertex3f(7,3,0.5);
        glVertex3f(7,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,3,0);
        glVertex3f(7,3,0.5);
        glVertex3f(8,3,0.5);
        glVertex3f(8,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,2,0);
        glVertex3f(7,2,0.5);
        glVertex3f(8,2,0.5);
        glVertex3f(8,2,0);
    glEnd();


    //kotak 51
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(8,2,0.5);
        glVertex3f(9,2,0.5);
        glVertex3f(9,3,0.5);
        glVertex3f(8,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(8,2,0);
        glVertex3f(8,3,0);
        glVertex3f(9,3,0);
        glVertex3f(9,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(9,2,0);
        glVertex3f(9,3,0);
        glVertex3f(9,3,0.5);
        glVertex3f(9,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(8,2,0);
        glVertex3f(8,2,0.5);
        glVertex3f(8,3,0.5);
        glVertex3f(8,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,3,0);
        glVertex3f(8,3,0.5);
        glVertex3f(9,3,0.5);
        glVertex3f(9,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,2,0);
        glVertex3f(8,2,0.5);
        glVertex3f(9,2,0.5);
        glVertex3f(9,2,0);
    glEnd();


    //kotak 52
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(9,2,0.5);
        glVertex3f(10,2,0.5);
        glVertex3f(10,3,0.5);
        glVertex3f(9,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(9,2,0);
        glVertex3f(9,3,0);
        glVertex3f(10,3,0);
        glVertex3f(10,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(10,2,0);
        glVertex3f(10,3,0);
        glVertex3f(10,3,0.5);
        glVertex3f(10,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(9,2,0);
        glVertex3f(9,2,0.5);
        glVertex3f(9,3,0.5);
        glVertex3f(9,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,3,0);
        glVertex3f(9,3,0.5);
        glVertex3f(10,3,0.5);
        glVertex3f(10,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,2,0);
        glVertex3f(9,2,0.5);
        glVertex3f(10,2,0.5);
        glVertex3f(10,2,0);
    glEnd();
    drawTwo(9.0,1.95,0.7,0.1);


    //kotak 53
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(10,2,0.5);
        glVertex3f(11,2,0.5);
        glVertex3f(11,3,0.5);
        glVertex3f(10,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(10,2,0);
        glVertex3f(10,3,0);
        glVertex3f(11,3,0);
        glVertex3f(11,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(11,2,0);
        glVertex3f(11,3,0);
        glVertex3f(11,3,0.5);
        glVertex3f(11,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(10,2,0);
        glVertex3f(10,2,0.5);
        glVertex3f(10,3,0.5);
        glVertex3f(10,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,3,0);
        glVertex3f(10,3,0.5);
        glVertex3f(11,3,0.5);
        glVertex3f(11,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,2,0);
        glVertex3f(10,2,0.5);
        glVertex3f(11,2,0.5);
        glVertex3f(11,2,0);
    glEnd();
    drawThree(10.0,1.95,0.7,0.1);


    //kotak 54
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(11,2,0.5);
        glVertex3f(12,2,0.5);
        glVertex3f(12,3,0.5);
        glVertex3f(11,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(11,2,0);
        glVertex3f(11,3,0);
        glVertex3f(12,3,0);
        glVertex3f(12,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(12,2,0);
        glVertex3f(12,3,0);
        glVertex3f(12,3,0.5);
        glVertex3f(12,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(11,2,0);
        glVertex3f(11,2,0.5);
        glVertex3f(11,3,0.5);
        glVertex3f(11,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,3,0);
        glVertex3f(11,3,0.5);
        glVertex3f(12,3,0.5);
        glVertex3f(12,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,2,0);
        glVertex3f(11,2,0.5);
        glVertex3f(12,2,0.5);
        glVertex3f(12,2,0);
    glEnd();

    //kotak 55
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(12,2,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(13,3,0.5);
        glVertex3f(12,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(12,2,0);
        glVertex3f(12,3,0);
        glVertex3f(13,3,0);
        glVertex3f(13,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(13,2,0);
        glVertex3f(13,3,0);
        glVertex3f(13,3,0.5);
        glVertex3f(13,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(12,2,0);
        glVertex3f(12,2,0.5);
        glVertex3f(12,3,0.5);
        glVertex3f(12,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,3,0);
        glVertex3f(12,3,0.5);
        glVertex3f(13,3,0.5);
        glVertex3f(13,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,2,0);
        glVertex3f(12,2,0.5);
        glVertex3f(13,2,0.5);
        glVertex3f(13,2,0);
    glEnd();


    //kotak 56
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(13,2,0.5);
        glVertex3f(14,2,0.5);
        glVertex3f(14,3,0.5);
        glVertex3f(13,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(13,2,0);
        glVertex3f(13,3,0);
        glVertex3f(14,3,0);
        glVertex3f(14,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(14,2,0);
        glVertex3f(14,3,0);
        glVertex3f(14,3,0.5);
        glVertex3f(14,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(13,2,0);
        glVertex3f(13,2,0.5);
        glVertex3f(13,3,0.5);
        glVertex3f(13,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,3,0);
        glVertex3f(13,3,0.5);
        glVertex3f(14,3,0.5);
        glVertex3f(14,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,2,0);
        glVertex3f(13,2,0.5);
        glVertex3f(14,2,0.5);
        glVertex3f(14,2,0);
    glEnd();
    drawSix(13.0,1.95,0.7,0.1);


    //kotak 57
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(14,2,0.5);
        glVertex3f(15,2,0.5);
        glVertex3f(15,3,0.5);
        glVertex3f(14,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(14,2,0);
        glVertex3f(14,3,0);
        glVertex3f(15,3,0);
        glVertex3f(15,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(15,2,0);
        glVertex3f(15,3,0);
        glVertex3f(15,3,0.5);
        glVertex3f(15,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(14,2,0);
        glVertex3f(14,2,0.5);
        glVertex3f(14,3,0.5);
        glVertex3f(14,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,3,0);
        glVertex3f(14,3,0.5);
        glVertex3f(15,3,0.5);
        glVertex3f(15,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,2,0);
        glVertex3f(14,2,0.5);
        glVertex3f(15,2,0.5);
        glVertex3f(15,2,0);
    glEnd();
    drawSeven(14.0,1.95,0.7,0.1);


    //kotak 58
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(15,2,0.5);
        glVertex3f(16,2,0.5);
        glVertex3f(16,3,0.5);
        glVertex3f(15,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(15,2,0);
        glVertex3f(15,3,0);
        glVertex3f(16,3,0);
        glVertex3f(16,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(16,2,0);
        glVertex3f(16,3,0);
        glVertex3f(16,3,0.5);
        glVertex3f(16,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(15,2,0);
        glVertex3f(15,2,0.5);
        glVertex3f(15,3,0.5);
        glVertex3f(15,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,3,0);
        glVertex3f(15,3,0.5);
        glVertex3f(16,3,0.5);
        glVertex3f(16,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,2,0);
        glVertex3f(15,2,0.5);
        glVertex3f(16,2,0.5);
        glVertex3f(16,2,0);
    glEnd();


    //kotak 59
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(16,2,0.5);
        glVertex3f(17,2,0.5);
        glVertex3f(17,3,0.5);
        glVertex3f(16,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(16,2,0);
        glVertex3f(16,3,0);
        glVertex3f(17,3,0);
        glVertex3f(17,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(17,2,0);
        glVertex3f(17,3,0);
        glVertex3f(17,3,0.5);
        glVertex3f(17,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(16,2,0);
        glVertex3f(16,2,0.5);
        glVertex3f(16,3,0.5);
        glVertex3f(16,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,3,0);
        glVertex3f(16,3,0.5);
        glVertex3f(17,3,0.5);
        glVertex3f(17,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,2,0);
        glVertex3f(16,2,0.5);
        glVertex3f(17,2,0.5);
        glVertex3f(17,2,0);
    glEnd();
    drawNine(16.0,1.95,0.7,0.1);



    //kotak 60
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(17,2,0.5);
        glVertex3f(18,2,0.5);
        glVertex3f(18,3,0.5);
        glVertex3f(17,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(17,2,0);
        glVertex3f(17,3,0);
        glVertex3f(18,3,0);
        glVertex3f(18,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(18,2,0);
        glVertex3f(18,3,0);
        glVertex3f(18,3,0.5);
        glVertex3f(18,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(17,2,0);
        glVertex3f(17,2,0.5);
        glVertex3f(17,3,0.5);
        glVertex3f(17,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,3,0);
        glVertex3f(17,3,0.5);
        glVertex3f(18,3,0.5);
        glVertex3f(18,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,2,0);
        glVertex3f(17,2,0.5);
        glVertex3f(18,2,0.5);
        glVertex3f(18,2,0);
    glEnd();
    drawSix(17.0,1.95,0.7,0.1);


    //kotak 61
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(18,2,0.5);
        glVertex3f(19,2,0.5);
        glVertex3f(19,3,0.5);
        glVertex3f(18,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(18,2,0);
        glVertex3f(18,3,0);
        glVertex3f(19,3,0);
        glVertex3f(19,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(19,2,0);
        glVertex3f(19,3,0);
        glVertex3f(19,3,0.5);
        glVertex3f(19,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(18,2,0);
        glVertex3f(18,2,0.5);
        glVertex3f(18,3,0.5);
        glVertex3f(18,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,3,0);
        glVertex3f(18,3,0.5);
        glVertex3f(19,3,0.5);
        glVertex3f(19,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,2,0);
        glVertex3f(18,2,0.5);
        glVertex3f(19,2,0.5);
        glVertex3f(19,2,0);
    glEnd();
    drawSix(18.0,1.95,0.7,0.1);


    //kotak 62
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(19,2,0.5);
        glVertex3f(20,2,0.5);
        glVertex3f(20,3,0.5);
        glVertex3f(19,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(19,2,0);
        glVertex3f(19,3,0);
        glVertex3f(20,3,0);
        glVertex3f(20,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(20,2,0);
        glVertex3f(20,3,0);
        glVertex3f(20,3,0.5);
        glVertex3f(20,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(19,2,0);
        glVertex3f(19,2,0.5);
        glVertex3f(19,3,0.5);
        glVertex3f(19,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,3,0);
        glVertex3f(19,3,0.5);
        glVertex3f(20,3,0.5);
        glVertex3f(20,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,2,0);
        glVertex3f(19,2,0.5);
        glVertex3f(20,2,0.5);
        glVertex3f(20,2,0);
    glEnd();
    drawTwo(19.0,1.95,0.7,0.1);
    drawSix(18.7,1.95,0.7,0.1);


    //kotak 63
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(20,2,0.5);
        glVertex3f(21,2,0.5);
        glVertex3f(21,3,0.5);
        glVertex3f(20,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(20,2,0);
        glVertex3f(20,3,0);
        glVertex3f(21,3,0);
        glVertex3f(21,2,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(21,2,0);
        glVertex3f(21,3,0);
        glVertex3f(21,3,0.5);
        glVertex3f(21,2,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(20,2,0);
        glVertex3f(20,2,0.5);
        glVertex3f(20,3,0.5);
        glVertex3f(20,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,3,0);
        glVertex3f(20,3,0.5);
        glVertex3f(21,3,0.5);
        glVertex3f(21,3,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,2,0);
        glVertex3f(20,2,0.5);
        glVertex3f(21,2,0.5);
        glVertex3f(21,2,0);
    glEnd();
    drawThree(19.95,1.95,0.7,0.1);
    drawSix(19.65,1.95,0.7,0.1);


    //kotak 64
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(20,3,0.5);
        glVertex3f(21,3,0.5);
        glVertex3f(21,4,0.5);
        glVertex3f(20,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(20,3,0);
        glVertex3f(20,4,0);
        glVertex3f(21,4,0);
        glVertex3f(21,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(21,3,0);
        glVertex3f(21,4,0);
        glVertex3f(21,4,0.5);
        glVertex3f(21,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(20,3,0);
        glVertex3f(20,3,0.5);
        glVertex3f(20,4,0.5);
        glVertex3f(20,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,4,0);
        glVertex3f(20,4,0.5);
        glVertex3f(21,4,0.5);
        glVertex3f(21,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(20,3,0);
        glVertex3f(20,3,0.5);
        glVertex3f(21,3,0.5);
        glVertex3f(21,3,0);
    glEnd();
    drawSix(19.95,2.95,0.7,0.1);

    //kotak 65
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(19,3,0.5);
        glVertex3f(20,3,0.5);
        glVertex3f(20,4,0.5);
        glVertex3f(19,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(19,3,0);
        glVertex3f(19,4,0);
        glVertex3f(20,4,0);
        glVertex3f(20,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(20,3,0);
        glVertex3f(20,4,0);
        glVertex3f(20,4,0.5);
        glVertex3f(20,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(19,3,0);
        glVertex3f(19,3,0.5);
        glVertex3f(19,4,0.5);
        glVertex3f(19,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,4,0);
        glVertex3f(19,4,0.5);
        glVertex3f(20,4,0.5);
        glVertex3f(20,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(19,3,0);
        glVertex3f(19,3,0.5);
        glVertex3f(20,3,0.5);
        glVertex3f(20,3,0);
    glEnd();
    drawSix(19.0,2.95,0.7,0.1);

    //kotak 66
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(18,3,0.5);
        glVertex3f(19,3,0.5);
        glVertex3f(19,4,0.5);
        glVertex3f(18,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(18,3,0);
        glVertex3f(18,4,0);
        glVertex3f(19,4,0);
        glVertex3f(19,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(19,3,0);
        glVertex3f(19,4,0);
        glVertex3f(19,4,0.5);
        glVertex3f(19,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(18,3,0);
        glVertex3f(18,3,0.5);
        glVertex3f(18,4,0.5);
        glVertex3f(18,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,4,0);
        glVertex3f(18,4,0.5);
        glVertex3f(19,4,0.5);
        glVertex3f(19,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(18,3,0);
        glVertex3f(18,3,0.5);
        glVertex3f(19,3,0.5);
        glVertex3f(19,3,0);
    glEnd();
    drawSix(18.0,2.95,0.7,0.1);
    drawSix(17.7,2.95,0.7,0.1);


    //kotak 67
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(17,3,0.5);
        glVertex3f(18,3,0.5);
        glVertex3f(18,4,0.5);
        glVertex3f(17,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(17,3,0);
        glVertex3f(17,4,0);
        glVertex3f(18,4,0);
        glVertex3f(18,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(18,3,0);
        glVertex3f(18,4,0);
        glVertex3f(18,4,0.5);
        glVertex3f(18,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(17,3,0);
        glVertex3f(17,3,0.5);
        glVertex3f(17,4,0.5);
        glVertex3f(17,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,4,0);
        glVertex3f(17,4,0.5);
        glVertex3f(18,4,0.5);
        glVertex3f(18,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(17,3,0);
        glVertex3f(17,3,0.5);
        glVertex3f(18,3,0.5);
        glVertex3f(18,3,0);
    glEnd();
    drawSeven(17.0,2.95,0.7,0.1);
    drawSix(16.7,2.95,0.7,0.1);

    //kotak 68
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(16,3,0.5);
        glVertex3f(17,3,0.5);
        glVertex3f(17,4,0.5);
        glVertex3f(16,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(16,3,0);
        glVertex3f(16,4,0);
        glVertex3f(17,4,0);
        glVertex3f(17,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(17,3,0);
        glVertex3f(17,4,0);
        glVertex3f(17,4,0.5);
        glVertex3f(17,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(16,3,0);
        glVertex3f(16,3,0.5);
        glVertex3f(16,4,0.5);
        glVertex3f(16,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,4,0);
        glVertex3f(16,4,0.5);
        glVertex3f(17,4,0.5);
        glVertex3f(17,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(16,3,0);
        glVertex3f(16,3,0.5);
        glVertex3f(17,3,0.5);
        glVertex3f(17,3,0);
    glEnd();
    drawSix(16.0,2.95,0.7,0.1);


    //kotak 69
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(15,3,0.5);
        glVertex3f(16,3,0.5);
        glVertex3f(16,4,0.5);
        glVertex3f(15,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(15,3,0);
        glVertex3f(15,4,0);
        glVertex3f(16,4,0);
        glVertex3f(16,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(16,3,0);
        glVertex3f(16,4,0);
        glVertex3f(16,4,0.5);
        glVertex3f(16,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(15,3,0);
        glVertex3f(15,3,0.5);
        glVertex3f(15,4,0.5);
        glVertex3f(15,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,4,0);
        glVertex3f(15,4,0.5);
        glVertex3f(16,4,0.5);
        glVertex3f(16,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(15,3,0);
        glVertex3f(15,3,0.5);
        glVertex3f(16,3,0.5);
        glVertex3f(16,3,0);
    glEnd();
    drawNine(15.0,2.95,0.7,0.1);
    drawSix(14.7,2.95,0.7,0.1);



    //kotak 70
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(14,3,0.5);
        glVertex3f(15,3,0.5);
        glVertex3f(15,4,0.5);
        glVertex3f(14,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(14,3,0);
        glVertex3f(14,4,0);
        glVertex3f(15,4,0);
        glVertex3f(15,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(15,3,0);
        glVertex3f(15,4,0);
        glVertex3f(15,4,0.5);
        glVertex3f(15,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(14,3,0);
        glVertex3f(14,3,0.5);
        glVertex3f(14,4,0.5);
        glVertex3f(14,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,4,0);
        glVertex3f(14,4,0.5);
        glVertex3f(15,4,0.5);
        glVertex3f(15,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(14,3,0);
        glVertex3f(14,3,0.5);
        glVertex3f(15,3,0.5);
        glVertex3f(15,3,0);
    glEnd();
    drawSeven(14.0,2.95,0.7,0.1);


    //kotak 71
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(13,3,0.5);
        glVertex3f(14,3,0.5);
        glVertex3f(14,4,0.5);
        glVertex3f(13,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(13,3,0);
        glVertex3f(13,4,0);
        glVertex3f(14,4,0);
        glVertex3f(14,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(14,3,0);
        glVertex3f(14,4,0);
        glVertex3f(14,4,0.5);
        glVertex3f(14,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(13,3,0);
        glVertex3f(13,3,0.5);
        glVertex3f(13,4,0.5);
        glVertex3f(13,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,4,0);
        glVertex3f(13,4,0.5);
        glVertex3f(14,4,0.5);
        glVertex3f(14,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(13,3,0);
        glVertex3f(13,3,0.5);
        glVertex3f(14,3,0.5);
        glVertex3f(14,3,0);
    glEnd();
    drawSeven(13.0,2.95,0.7,0.1);


    //kotak 72
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(12,3,0.5);
        glVertex3f(13,3,0.5);
        glVertex3f(13,4,0.5);
        glVertex3f(12,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(12,3,0);
        glVertex3f(12,4,0);
        glVertex3f(13,4,0);
        glVertex3f(13,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(13,3,0);
        glVertex3f(13,4,0);
        glVertex3f(13,4,0.5);
        glVertex3f(13,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(12,3,0);
        glVertex3f(12,3,0.5);
        glVertex3f(12,4,0.5);
        glVertex3f(12,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,4,0);
        glVertex3f(12,4,0.5);
        glVertex3f(13,4,0.5);
        glVertex3f(13,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(12,3,0);
        glVertex3f(12,3,0.5);
        glVertex3f(13,3,0.5);
        glVertex3f(13,3,0);
    glEnd();
    drawTwo(12.0,2.95,0.7,0.1);
    drawSeven(11.7,2.95,0.7,0.1);

    //kotak 73
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(11,3,0.5);
        glVertex3f(12,3,0.5);
        glVertex3f(12,4,0.5);
        glVertex3f(11,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(11,3,0);
        glVertex3f(11,4,0);
        glVertex3f(12,4,0);
        glVertex3f(12,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(12,3,0);
        glVertex3f(12,4,0);
        glVertex3f(12,4,0.5);
        glVertex3f(12,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(11,3,0);
        glVertex3f(11,3,0.5);
        glVertex3f(11,4,0.5);
        glVertex3f(11,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,4,0);
        glVertex3f(11,4,0.5);
        glVertex3f(12,4,0.5);
        glVertex3f(12,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(11,3,0);
        glVertex3f(11,3,0.5);
        glVertex3f(12,3,0.5);
        glVertex3f(12,3,0);
    glEnd();
    drawThree(11.0,2.95,0.7,0.1);
    drawSeven(10.7,2.95,0.7,0.1);


    //kotak 74
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(10,3,0.5);
        glVertex3f(11,3,0.5);
        glVertex3f(11,4,0.5);
        glVertex3f(10,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(10,3,0);
        glVertex3f(10,4,0);
        glVertex3f(11,4,0);
        glVertex3f(11,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(11,3,0);
        glVertex3f(11,4,0);
        glVertex3f(11,4,0.5);
        glVertex3f(11,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(10,3,0);
        glVertex3f(10,3,0.5);
        glVertex3f(10,4,0.5);
        glVertex3f(10,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,4,0);
        glVertex3f(10,4,0.5);
        glVertex3f(11,4,0.5);
        glVertex3f(11,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(10,3,0);
        glVertex3f(10,3,0.5);
        glVertex3f(11,3,0.5);
        glVertex3f(11,3,0);
    glEnd();
    drawSeven(10.0,2.95,0.7,0.1);

    //kotak 75
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(9,3,0.5);
        glVertex3f(10,3,0.5);
        glVertex3f(10,4,0.5);
        glVertex3f(9,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(9,3,0);
        glVertex3f(9,4,0);
        glVertex3f(10,4,0);
        glVertex3f(10,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(10,3,0);
        glVertex3f(10,4,0);
        glVertex3f(10,4,0.5);
        glVertex3f(10,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(9,3,0);
        glVertex3f(9,3,0.5);
        glVertex3f(9,4,0.5);
        glVertex3f(9,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,4,0);
        glVertex3f(9,4,0.5);
        glVertex3f(10,4,0.5);
        glVertex3f(10,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(9,3,0);
        glVertex3f(9,3,0.5);
        glVertex3f(10,3,0.5);
        glVertex3f(10,3,0);
    glEnd();
    drawSeven(9.0,2.95,0.7,0.1);


    //kotak 76
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(8,3,0.5);
        glVertex3f(9,3,0.5);
        glVertex3f(9,4,0.5);
        glVertex3f(8,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(8,3,0);
        glVertex3f(8,4,0);
        glVertex3f(9,4,0);
        glVertex3f(9,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(9,3,0);
        glVertex3f(9,4,0);
        glVertex3f(9,4,0.5);
        glVertex3f(9,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(8,3,0);
        glVertex3f(8,3,0.5);
        glVertex3f(8,4,0.5);
        glVertex3f(8,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,4,0);
        glVertex3f(8,4,0.5);
        glVertex3f(9,4,0.5);
        glVertex3f(9,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(8,3,0);
        glVertex3f(8,3,0.5);
        glVertex3f(9,3,0.5);
        glVertex3f(9,3,0);
    glEnd();
    drawSix(8.0,2.95,0.7,0.1);
    drawSeven(7.7,2.95,0.7,0.1);


    //kotak 77
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(7,3,0.5);
        glVertex3f(8,3,0.5);
        glVertex3f(8,4,0.5);
        glVertex3f(7,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(7,3,0);
        glVertex3f(7,4,0);
        glVertex3f(8,4,0);
        glVertex3f(8,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(8,3,0);
        glVertex3f(8,4,0);
        glVertex3f(8,4,0.5);
        glVertex3f(8,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(7,3,0);
        glVertex3f(7,3,0.5);
        glVertex3f(7,4,0.5);
        glVertex3f(7,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,4,0);
        glVertex3f(7,4,0.5);
        glVertex3f(8,4,0.5);
        glVertex3f(8,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(7,3,0);
        glVertex3f(7,3,0.5);
        glVertex3f(8,3,0.5);
        glVertex3f(8,3,0);
    glEnd();
    drawSeven(7.0,2.95,0.7,0.1);
    drawSeven(6.7,2.95,0.7,0.1);


    //kotak 78
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(6,3,0.5);
        glVertex3f(7,3,0.5);
        glVertex3f(7,4,0.5);
        glVertex3f(6,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(6,3,0);
        glVertex3f(6,4,0);
        glVertex3f(7,4,0);
        glVertex3f(7,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(7,3,0);
        glVertex3f(7,4,0);
        glVertex3f(7,4,0.5);
        glVertex3f(7,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(6,3,0);
        glVertex3f(6,3,0.5);
        glVertex3f(6,4,0.5);
        glVertex3f(6,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,4,0);
        glVertex3f(6,4,0.5);
        glVertex3f(7,4,0.5);
        glVertex3f(7,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(6,3,0);
        glVertex3f(6,3,0.5);
        glVertex3f(7,3,0.5);
        glVertex3f(7,3,0);
    glEnd();
    drawSeven(6.0,2.95,0.7,0.1);


    //kotak 79
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(5,3,0.5);
        glVertex3f(6,3,0.5);
        glVertex3f(6,4,0.5);
        glVertex3f(5,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(5,3,0);
        glVertex3f(5,4,0);
        glVertex3f(6,4,0);
        glVertex3f(6,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(6,3,0);
        glVertex3f(6,4,0);
        glVertex3f(6,4,0.5);
        glVertex3f(6,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(5,3,0);
        glVertex3f(5,3,0.5);
        glVertex3f(5,4,0.5);
        glVertex3f(5,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,4,0);
        glVertex3f(5,4,0.5);
        glVertex3f(6,4,0.5);
        glVertex3f(6,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(5,3,0);
        glVertex3f(5,3,0.5);
        glVertex3f(6,3,0.5);
        glVertex3f(6,3,0);
    glEnd();
    drawNine(5.0,2.95,0.7,0.1);
    drawSeven(4.7,2.95,0.7,0.1);


    //kotak 80
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(4,3,0.5);
        glVertex3f(5,3,0.5);
        glVertex3f(5,4,0.5);
        glVertex3f(4,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(4,3,0);
        glVertex3f(4,4,0);
        glVertex3f(5,4,0);
        glVertex3f(5,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(5,3,0);
        glVertex3f(5,4,0);
        glVertex3f(5,4,0.5);
        glVertex3f(5,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(4,3,0);
        glVertex3f(4,3,0.5);
        glVertex3f(4,4,0.5);
        glVertex3f(4,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,4,0);
        glVertex3f(4,4,0.5);
        glVertex3f(5,4,0.5);
        glVertex3f(5,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(4,3,0);
        glVertex3f(4,3,0.5);
        glVertex3f(5,3,0.5);
        glVertex3f(5,3,0);
    glEnd();


    //kotak 81
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(3,3,0.5);
        glVertex3f(4,3,0.5);
        glVertex3f(4,4,0.5);
        glVertex3f(3,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(3,3,0);
        glVertex3f(3,4,0);
        glVertex3f(4,4,0);
        glVertex3f(4,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(4,3,0);
        glVertex3f(4,4,0);
        glVertex3f(4,4,0.5);
        glVertex3f(4,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(3,3,0);
        glVertex3f(3,3,0.5);
        glVertex3f(3,4,0.5);
        glVertex3f(3,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,4,0);
        glVertex3f(3,4,0.5);
        glVertex3f(4,4,0.5);
        glVertex3f(4,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(3,3,0);
        glVertex3f(3,3,0.5);
        glVertex3f(4,3,0.5);
        glVertex3f(4,3,0);
    glEnd();


    //kotak 82
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(2,3,0.5);
        glVertex3f(3,3,0.5);
        glVertex3f(3,4,0.5);
        glVertex3f(2,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(2,3,0);
        glVertex3f(2,4,0);
        glVertex3f(3,4,0);
        glVertex3f(3,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(3,3,0);
        glVertex3f(3,4,0);
        glVertex3f(3,4,0.5);
        glVertex3f(3,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(2,3,0);
        glVertex3f(2,3,0.5);
        glVertex3f(2,4,0.5);
        glVertex3f(2,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,4,0);
        glVertex3f(2,4,0.5);
        glVertex3f(3,4,0.5);
        glVertex3f(3,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(2,3,0);
        glVertex3f(2,3,0.5);
        glVertex3f(3,3,0.5);
        glVertex3f(3,3,0);
    glEnd();
    drawTwo(2.0,2.95,0.7,0.1);


    //kotak 83
    if (warna_transparan) {
        glColor4f(0.0f, 0.0f, 1.0f, 0.2f);  // Biru transparan
    } else {
        glColor3f(0.0f, 0.0f, 1.0f);         // Biru solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(1,3,0.5);
        glVertex3f(2,3,0.5);
        glVertex3f(2,4,0.5);
        glVertex3f(1,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(1,3,0);
        glVertex3f(1,4,0);
        glVertex3f(2,4,0);
        glVertex3f(2,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(2,3,0);
        glVertex3f(2,4,0);
        glVertex3f(2,4,0.5);
        glVertex3f(2,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(1,3,0);
        glVertex3f(1,3,0.5);
        glVertex3f(1,4,0.5);
        glVertex3f(1,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,4,0);
        glVertex3f(1,4,0.5);
        glVertex3f(2,4,0.5);
        glVertex3f(2,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(1,3,0);
        glVertex3f(1,3,0.5);
        glVertex3f(2,3,0.5);
        glVertex3f(2,3,0);
    glEnd();
    drawThree(1.0,2.95,0.7,0.1);


    //kotak 84
    if (warna_transparan) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.2f);  // Putih transparan
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);         // Putih solid
    }
    glBegin(GL_POLYGON);
        // Sisi depan
        glVertex3f(0,3,0.5);
        glVertex3f(1,3,0.5);
        glVertex3f(1,4,0.5);
        glVertex3f(0,4,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi belakang
        glVertex3f(0,3,0);
        glVertex3f(0,4,0);
        glVertex3f(1,4,0);
        glVertex3f(1,3,0);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kanan
        glVertex3f(1,3,0);
        glVertex3f(1,4,0);
        glVertex3f(1,4,0.5);
        glVertex3f(1,3,0.5);
    glEnd();
    glBegin(GL_POLYGON);
        // Sisi kiri
        glVertex3f(0,3,0);
        glVertex3f(0,3,0.5);
        glVertex3f(0,4,0.5);
        glVertex3f(0,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,4,0);
        glVertex3f(0,4,0.5);
        glVertex3f(1,4,0.5);
        glVertex3f(1,4,0);
    glEnd();
     glBegin(GL_POLYGON);
        // Sisi atas
        glVertex3f(0,3,0);
        glVertex3f(0,3,0.5);
        glVertex3f(1,3,0.5);
        glVertex3f(1,3,0);
    glEnd();
    glDisable(GL_BLEND);

    if (warna_transparan) {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
}


// Fungsi pembantu untuk pagar horizontal
void drawPagarHorizontal(float x1, float y1, float x2, float y2) {
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(x1, y1, 0.8);
    glVertex3f(x2, y1, 0.8);
    glVertex3f(x2, y2, 0.8);
    glVertex3f(x1, y2, 0.8);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(x1, y1, 0.5);
    glVertex3f(x2, y1, 0.5);
    glVertex3f(x2, y2, 0.5);
    glVertex3f(x1, y2, 0.5);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Atas
    glVertex3f(x1, y2, 0.5);
    glVertex3f(x2, y2, 0.5);
    glVertex3f(x2, y2, 0.8);
    glVertex3f(x1, y2, 0.8);

    // Bawah
    glVertex3f(x1, y1, 0.5);
    glVertex3f(x2, y1, 0.5);
    glVertex3f(x2, y1, 0.8);
    glVertex3f(x1, y1, 0.8);

    // Kiri
    glVertex3f(x1, y1, 0.5);
    glVertex3f(x1, y2, 0.5);
    glVertex3f(x1, y2, 0.8);
    glVertex3f(x1, y1, 0.8);

    // Kanan
    glVertex3f(x2, y1, 0.5);
    glVertex3f(x2, y2, 0.5);
    glVertex3f(x2, y2, 0.8);
    glVertex3f(x2, y1, 0.8);
    glEnd();
}

void drawPagar() {
    glColor3f(0.6, 0.8, 0.2);

    // ========== BAWAH ==========
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0.8);
    glVertex3f(21, 0, 0.8);
    glVertex3f(21, 0.1, 0.8);
    glVertex3f(0, 0.1, 0.8);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(21, 0, 0);
    glVertex3f(21, 0.1, 0);
    glVertex3f(0, 0.1, 0);
    glEnd();

    // Sisi Penghubung (3D Effect)
    glBegin(GL_QUADS);
    // Sisi atas
    glVertex3f(0, 0.1, 0);
    glVertex3f(21, 0.1, 0);
    glVertex3f(21, 0.1, 0.8);
    glVertex3f(0, 0.1, 0.8);

    // Sisi bawah
    glVertex3f(0, 0, 0);
    glVertex3f(21, 0, 0);
    glVertex3f(21, 0, 0.8);
    glVertex3f(0, 0, 0.8);

    // Sisi kiri
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.1, 0);
    glVertex3f(0, 0.1, 0.8);
    glVertex3f(0, 0, 0.8);

    // Sisi kanan
    glVertex3f(21, 0, 0);
    glVertex3f(21, 0.1, 0);
    glVertex3f(21, 0.1, 0.8);
    glVertex3f(21, 0, 0.8);
    glEnd();

    // ========== ATAS ==========
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(0, 3.9, 0.8);
    glVertex3f(21, 3.9, 0.8);
    glVertex3f(21, 4, 0.8);
    glVertex3f(0, 4, 0.8);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(0, 3.9, 0);
    glVertex3f(21, 3.9, 0);
    glVertex3f(21, 4, 0);
    glVertex3f(0, 4, 0);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Sisi atas
    glVertex3f(0, 4, 0);
    glVertex3f(21, 4, 0);
    glVertex3f(21, 4, 0.8);
    glVertex3f(0, 4, 0.8);

    // Sisi bawah
    glVertex3f(0, 3.9, 0);
    glVertex3f(21, 3.9, 0);
    glVertex3f(21, 3.9, 0.8);
    glVertex3f(0, 3.9, 0.8);

    // Sisi kiri
    glVertex3f(0, 3.9, 0);
    glVertex3f(0, 4, 0);
    glVertex3f(0, 4, 0.8);
    glVertex3f(0, 3.9, 0.8);

    // Sisi kanan
    glVertex3f(21, 3.9, 0);
    glVertex3f(21, 4, 0);
    glVertex3f(21, 4, 0.8);
    glVertex3f(21, 3.9, 0.8);
    glEnd();

    // ========== KIRI ==========
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0.8);
    glVertex3f(0.1, 0, 0.8);
    glVertex3f(0.1, 4, 0.8);
    glVertex3f(0, 4, 0.8);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 4, 0);
    glVertex3f(0, 4, 0);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Sisi kanan
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 4, 0);
    glVertex3f(0.1, 4, 0.8);
    glVertex3f(0.1, 0, 0.8);

    // Sisi kiri
    glVertex3f(0, 0, 0);
    glVertex3f(0, 4, 0);
    glVertex3f(0, 4, 0.8);
    glVertex3f(0, 0, 0.8);

    // Sisi atas
    glVertex3f(0, 4, 0);
    glVertex3f(0.1, 4, 0);
    glVertex3f(0.1, 4, 0.8);
    glVertex3f(0, 4, 0.8);

    // Sisi bawah
    glVertex3f(0, 0, 0);
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 0, 0.8);
    glVertex3f(0, 0, 0.8);
    glEnd();

    // ========== KANAN ==========
    // Depan
    glBegin(GL_POLYGON);
    glVertex3f(21, 0, 0.8);
    glVertex3f(20.9, 0, 0.8);
    glVertex3f(20.9, 4, 0.8);
    glVertex3f(21, 4, 0.8);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glVertex3f(21, 0, 0);
    glVertex3f(20.9, 0, 0);
    glVertex3f(20.9, 4, 0);
    glVertex3f(21, 4, 0);
    glEnd();

    // Sisi Penghubung
    glBegin(GL_QUADS);
    // Sisi kiri
    glVertex3f(20.9, 0, 0);
    glVertex3f(20.9, 4, 0);
    glVertex3f(20.9, 4, 0.8);
    glVertex3f(20.9, 0, 0.8);

    // Sisi kanan
    glVertex3f(21, 0, 0);
    glVertex3f(21, 4, 0);
    glVertex3f(21, 4, 0.8);
    glVertex3f(21, 0, 0.8);

    // Sisi atas
    glVertex3f(20.9, 4, 0);
    glVertex3f(21, 4, 0);
    glVertex3f(21, 4, 0.8);
    glVertex3f(20.9, 4, 0.8);

    // Sisi bawah
    glVertex3f(20.9, 0, 0);
    glVertex3f(21, 0, 0);
    glVertex3f(21, 0, 0.8);
    glVertex3f(20.9, 0, 0.8);
    glEnd();

    // ========== PAGAR TENGAH ==========
    // Horizontal 1
    drawPagarHorizontal(0, 0.9, 20, 1.1);
    // Horizontal 2
    drawPagarHorizontal(1, 1.9, 21, 2.1);
    // Horizontal 3
    drawPagarHorizontal(0, 2.9, 20, 3.1);
}



float offset_board_Y = 3.0f;

void drawBoard() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Naikkan board dulu
    glTranslatef(0.0f, 0.0f, -6.0f);

    // Pusatkan ke titik rotasi (tengah board)
    glTranslatef(pusat_rotasi_X, pusat_rotasi_Y, pusat_rotasi_Z);

    // Rotasi di tengah
    glRotatef(sudut_rotasi_X, 1.0f, 0.0f, 0.0f);
    glRotatef(sudut_rotasi_Y, 0.0f, 1.0f, 0.0f);
    glRotatef(sudut_rotasi_Z, 0.0f, 0.0f, 1.0f);

    // Kembalikan ke posisi semula
    glTranslatef(-pusat_rotasi_X, -pusat_rotasi_Y, -pusat_rotasi_Z);
    glTranslatef(0.0f, offset_board_Y, 0.0f);

    // Render objek
    glPointSize(4);
    if (warna_transparan) {
        drawKotak(true);
    } else {
        drawKotak(false);
    }
    drawPagar();
    drawObserver(geser_oberver_X, geser_oberver_Y);
    drawPlayer1(bidak_player1_X, bidak_player1_Y);
    drawPlayer2(bidak_player2_X, bidak_player2_Y);
    drawTangga();
    drawUlar();

    glutSwapBuffers();
    glFlush();
}


void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 22, -1,11, -30, 35);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void input(unsigned char key, int x, int y) {
    key = tolower(key); //Agar bisa menginput keyboard huruf besar dan kecil

    if (isRotated) { //Percabangan untuk rotasi papan permainan
        switch (key) {
            case 'i': // Putar Atas
                sudut_rotasi_X -= 2.0f;
                break;
            case 'k': // Putar Bawah
                sudut_rotasi_X += 2.0f;
                break;
            case 'j': // Putar Kiri
                sudut_rotasi_Y -= 2.0f;
                break;
            case 'l': // Putar Kanan
                sudut_rotasi_Y += 2.0f;
                break;
        }
    }

    switch (key) {
        case 'v':
            if (isRotated) {
                // Simpan sudut rotasi terakhir
                sudut_rotasi_terakhir_x = sudut_rotasi_X;
                sudut_rotasi_terakhir_Y = sudut_rotasi_Y;
                sudut_rotasi_terakhir_Z = sudut_rotasi_Z;
                // Reset sudut rotasi ke awal
                sudut_rotasi_X = 0.0f;
                sudut_rotasi_Y = 0.0f;
                sudut_rotasi_Z = 0.0f;
            } else {
                if (!rotasi_awal_dilakukan) {
                    sudut_rotasi_X = -20.0f;
                    rotasi_awal_dilakukan = true;
                } else {
                    sudut_rotasi_X = sudut_rotasi_terakhir_x;
                    sudut_rotasi_Y = sudut_rotasi_terakhir_Y;
                    sudut_rotasi_Z = sudut_rotasi_terakhir_Z;
                }
            }
            // Mengubah izin rotasi pada papan
            isRotated = !isRotated;
            // Mengubah mode warna pada papan
            warna_transparan = !warna_transparan;
            break;


        case 'w':
            if (geser_oberver_Y + 0.1 <= batas_observer_atas)
                geser_oberver_Y += 0.1; // Pergeseran ke atas
            break;
        case 'a':
            if (geser_oberver_X - 0.1 >= batas_observer_kiri)
                geser_oberver_X -= 0.1; // Pergeseran ke kiri
            break;
        case 's':
            if (geser_oberver_Y - 0.1 >= batas_observer_bawah)
                geser_oberver_Y -= 0.1; // Pergeseran ke bawah
            break;
        case 'd':
            if (geser_oberver_X + 0.1 <= batas_observer_kanan)
                geser_oberver_X += 0.1; // Pergeseran ke kanan
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay(); // Mengupdate dipslay atau tampilan

    //Fungsi Penggerak Bidak
    if (key == 32 && pemenang == 0) {
        if (pemenang == 1) {
            cout << "Player 1 Menang" << endl;
        } else if (pemenang == 2 ){
            cout << "Player 2 Menang" << endl;
        }else{

        if(giliran_player1) {
            int rand_player1 = rollDice();
            cout << "Player1 Main : " << rand_player1 << " Nilai Dadu"<< endl;
            jumlahlemparan += rand_player1;
            cout << "Kotak Player 1 : " << jumlahlemparan << endl;
            cout <<"===========================================================" <<endl;
            if (jumlahlemparan == 1){
                bidak_player1_X = 0.4;
                bidak_player1_Y = 0.4;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 2){
                bidak_player1_X = 1.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            // TANGGA 1
            else if (jumlahlemparan == 3) {
                bidak_player1_X = 2.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 4){
                bidak_player1_X = 3.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 5){
                bidak_player1_X = 4.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            // Naik Tangga 4
            else if (jumlahlemparan == 6){
                bidak_player1_X = 5.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
                jumlahlemparan = 76;
                cout << "Player 1 Naik Tangga" << endl;
                bidak_player1_X = 8.4;
                bidak_player1_Y = 3.7;
            }
            else if (jumlahlemparan == 7){
                bidak_player1_X = 6.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 8){
                bidak_player1_X = 7.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan== 9){
                bidak_player1_X = 8.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 10){
                bidak_player1_X = 9.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            // Naik tangga 3
            else if (jumlahlemparan == 11){
                bidak_player1_X = 10.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
                jumlahlemparan = 14;
                cout << "Player 1 Naik Tangga" << endl;
                bidak_player1_X = 13.4;
                bidak_player1_Y = 0.7;
            }
            else if (jumlahlemparan == 12){
                bidak_player1_X = 11.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 13){
                bidak_player1_X = 12.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 14){
                bidak_player1_X = 13.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 15){
                bidak_player1_X = 14.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            // naik tangga 1
            else if (jumlahlemparan == 16){
                bidak_player1_X = 15.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
                jumlahlemparan = 69;
                cout << "Player 1 Naik Tangga" << endl;
                bidak_player1_X = 15.4;
                bidak_player1_Y = 3.7;
            }
            else if (jumlahlemparan == 17){
                bidak_player1_X = 16.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 18){
                bidak_player1_X = 17.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 19){
                bidak_player1_X = 18.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 20){
                bidak_player1_X = 19.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 21){
                bidak_player1_X = 20.4;
                bidak_player1_Y = 0.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 22){
                bidak_player1_X = 20.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 23){
                bidak_player1_X = 19.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 24){
                bidak_player1_X = 18.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 25){
                bidak_player1_X = 17.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 26){
                bidak_player1_X = 16.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 27){
                bidak_player1_X = 15.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 28){
                bidak_player1_X = 14.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 29){
                bidak_player1_X = 13.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 30){
                bidak_player1_X = 12.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 31){
                bidak_player1_X = 11.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 32){
                bidak_player1_X = 10.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 33){
                bidak_player1_X = 9.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 34){
                bidak_player1_X = 8.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 35){
                bidak_player1_X = 7.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 36){
                bidak_player1_X = 6.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 37){
                bidak_player1_X = 5.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 38){
                bidak_player1_X = 4.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 39){
                bidak_player1_X = 3.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 40){
                bidak_player1_X = 2.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 41){
                bidak_player1_X = 1.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 42){
                bidak_player1_X = 0.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 43){
                bidak_player1_X = 0.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 44){
                bidak_player1_X = 1.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 45){
                bidak_player1_X = 2.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 46){
                bidak_player1_X = 3.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 47){
                bidak_player1_X = 4.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            // Tertangkap ular 3
            else if (jumlahlemparan == 48){
                bidak_player1_X = 5.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
                jumlahlemparan = 3;
                cout << "Player 1 tertangkap Ular" << endl;
                bidak_player1_X = 2.4;
                bidak_player1_Y = 0.7;
            }
            else if (jumlahlemparan == 49){
                bidak_player1_X = 6.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 50){
                bidak_player1_X = 7.4;
                bidak_player1_Y = 1.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 51){
                bidak_player1_X = 8.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 52){
                bidak_player1_X = 9.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 53){
                bidak_player1_X = 10.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 54){
                bidak_player1_X = 11.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 55){
                bidak_player1_X = 12.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 56){
                bidak_player1_X = 13.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 57){
                bidak_player1_X = 14.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 58){
                bidak_player1_X = 15.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 59){
                bidak_player1_X = 16.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 60){
                bidak_player1_X = 17.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }

            else if (jumlahlemparan == 61){
                bidak_player1_X = 18.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 62){
                bidak_player1_X = 19.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 63){
                bidak_player1_X = 20.4;
                bidak_player1_Y = 2.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 64){
                bidak_player1_X = 20.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 65){
                bidak_player1_X = 19.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 66){
                bidak_player1_X = 18.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 67){
                bidak_player1_X = 17.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 68){
                bidak_player1_X = 16.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 69){
                bidak_player1_X = 15.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 70){
                bidak_player1_X = 14.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            // Tertangkap ular 1
            else if (jumlahlemparan == 71){
                bidak_player1_X = 13.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
                jumlahlemparan = 26;
                cout << "Player 1 tertangkap Ular" << endl;
                bidak_player1_X = 16.4;
                bidak_player1_Y = 1.7;
            }
            else if (jumlahlemparan == 72){
                bidak_player1_X = 12.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 73){
                bidak_player1_X = 11.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 74){
                bidak_player1_X = 10.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 75){
                bidak_player1_X = 9.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 76){
                bidak_player1_X = 8.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 77){
                bidak_player1_X = 7.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 78){
                bidak_player1_X = 6.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 79){
                bidak_player1_X = 5.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            // Tertangkap ular 2
            else if (jumlahlemparan == 80){
                bidak_player1_X = 4.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
                jumlahlemparan = 36;
                cout << "Player 1 tertangkap Ular" << endl;
                bidak_player1_X = 6.4;
                bidak_player1_Y = 1.7;
            }
            else if (jumlahlemparan == 81){
                bidak_player1_X = 3.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 82){
                bidak_player1_X = 2.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 83){
                bidak_player1_X = 1.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan == 84){
                bidak_player1_X = 0.4;
                bidak_player1_Y = 3.7;
                giliran_player1 = false;
            }
            else if (jumlahlemparan > 84){
                bidak_player1_X = 0.4;
                bidak_player1_Y = 3.7;
                cout << "Player 1 Menang" << endl;
                pemenang = 1;
            }
         }
         else {
            cout << "Letak Awal Player2 : " << jumlahlemparan2 << endl;
            int rand_player2 = rollDice();
            cout << "Player2 mendapatkan : " << rand_player2 <<" Nilai Dadu"<< endl;
            jumlahlemparan2 += rand_player2;
            cout << "Letak Player2  : " << jumlahlemparan2 << endl;
            cout <<"===========================================================" <<endl;
            if (jumlahlemparan2 == 1){
                bidak_player2_X = 0.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 2){
                bidak_player2_X = 1.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 3) {
                bidak_player2_X = 2.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 4){
                bidak_player2_X = 3.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 5){
                bidak_player2_X = 4.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            // Naik tangga 4
            else if (jumlahlemparan2 == 6){
                bidak_player2_X = 5.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
                jumlahlemparan2 = 76;
                cout << "Player 2 Naik Tangga" << endl;
                bidak_player2_X = 8.4;
                bidak_player2_Y = 3.4;
            }
            else if (jumlahlemparan2 == 7){
                bidak_player2_X = 6.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 8){
                bidak_player2_X = 7.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2== 9){
                bidak_player2_X = 8.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 10){
                bidak_player2_X = 9.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            // Naik tangga 3
            else if (jumlahlemparan2 == 11){
                bidak_player2_X = 10.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
                jumlahlemparan2 = 14;
                cout << "Player 2 Naik Tangga" << endl;
                bidak_player2_X = 13.4;
                bidak_player2_Y = 0.4;
            }
            else if (jumlahlemparan2 == 12){
                bidak_player2_X = 11.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 13){
                bidak_player2_X = 12.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 14){
                bidak_player2_X = 13.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 15){
                bidak_player2_X = 14.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            // Naik tangga 1
            else if (jumlahlemparan2 == 16){
                bidak_player2_X = 15.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
                jumlahlemparan2 = 69;
                cout << "Player 2 Naik Tangga" << endl;
                bidak_player2_X = 15.4;
                bidak_player2_Y = 3.4;
            }
            else if (jumlahlemparan2 == 17){
                bidak_player2_X = 16.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 18){
                bidak_player2_X = 17.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 19){
                bidak_player2_X = 18.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 20){
                bidak_player2_X = 19.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 21){
                bidak_player2_X = 20.4;
                bidak_player2_Y = 0.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 22){
                bidak_player2_X = 20.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 23){
                bidak_player2_X = 19.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 24){
                bidak_player2_X = 18.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 25){
                bidak_player2_X = 17.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 26){
                bidak_player2_X = 16.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 27){
                bidak_player2_X = 15.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 28){
                bidak_player2_X = 14.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 29){
                bidak_player2_X = 13.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 30){
                bidak_player2_X = 12.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 31){
                bidak_player2_X = 11.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 32){
                bidak_player2_X = 10.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 33){
                bidak_player2_X = 9.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 34){
                bidak_player2_X = 8.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 35){
                bidak_player2_X = 7.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 36){
                bidak_player2_X = 6.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 37){
                bidak_player2_X = 5.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 38){
                bidak_player2_X = 4.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 39){
                bidak_player2_X = 3.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 40){
                bidak_player2_X = 2.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 41){
                bidak_player2_X = 1.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 42){
                bidak_player2_X = 0.4;
                bidak_player2_Y = 1.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 43){
                bidak_player2_X = 0.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 44){
                bidak_player2_X = 1.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 45){
                bidak_player2_X = 2.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 46){
                bidak_player2_X = 3.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 47){
                bidak_player2_X = 4.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            // Tertangkap ular 3
            else if (jumlahlemparan2 == 48){
                bidak_player2_X = 5.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
                jumlahlemparan2 = 3;
                cout << "Player 2 tertangkap Ular" << endl;
                bidak_player2_X = 2.4;
                bidak_player2_Y = 0.4;
            }
            else if (jumlahlemparan2 == 49){
                bidak_player2_X = 6.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 50){
                bidak_player2_X = 7.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 51){
                bidak_player2_X = 8.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 52){
                bidak_player2_X = 9.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 53){
                bidak_player2_X = 10.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 54){
                bidak_player2_X = 11.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 55){
                bidak_player2_X = 12.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 56){
                bidak_player2_X = 13.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 57){
                bidak_player2_X = 14.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 58){
                bidak_player2_X = 15.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 59){
                bidak_player2_X = 16.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 60){
                bidak_player2_X = 17.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 61){
                bidak_player2_X = 18.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 62){
                bidak_player2_X = 19.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 63){
                bidak_player2_X = 20.4;
                bidak_player2_Y = 2.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 64){
                bidak_player2_X = 20.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 65){
                bidak_player2_X = 19.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 66){
                bidak_player2_X = 18.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 67){
                bidak_player2_X = 17.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 68){
                bidak_player2_X = 16.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 69){
                bidak_player2_X = 15.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 70){
                bidak_player2_X = 14.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            // Tertangkap ular 1
            else if (jumlahlemparan2 == 71){
                bidak_player2_X = 13.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
                jumlahlemparan2 = 26;
                cout << "Player 2 tertangkap Ular" << endl;
                bidak_player2_X = 16.4;
                bidak_player2_Y = 1.4;
            }
            else if (jumlahlemparan2 == 72){
                bidak_player2_X = 12.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 73){
                bidak_player2_X = 11.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 74){
                bidak_player2_X = 10.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 75){
                bidak_player2_X = 9.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 76){
                bidak_player2_X = 8.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 77){
                bidak_player2_X = 7.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 78){
                bidak_player2_X = 6.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 79){
                bidak_player2_X = 5.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            // Tertangkap ular 2
            else if (jumlahlemparan2 == 80){
                bidak_player2_X = 4.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
                jumlahlemparan2 = 36;
                cout << "Player 2 tertangkap Ular" << endl;
                bidak_player2_X = 6.4;
                bidak_player2_Y = 1.4;
            }
            else if (jumlahlemparan2 == 81){
                bidak_player2_X = 3.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }

            else if (jumlahlemparan2 == 82){
                bidak_player2_X = 2.4;
                bidak_player2_Y = 3.4;

                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 83){
                bidak_player2_X = 1.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 == 84){
                bidak_player2_X = 0.4;
                bidak_player2_Y = 3.4;
                giliran_player1 = true;
            }
            else if (jumlahlemparan2 > 84){
                bidak_player2_X = 0.4;
                bidak_player2_Y = 3.4;
                cout << "Player 2 Menang" << endl;
                pemenang =2;
            }
         }

        }
    }

    drawBoard();
}





int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ular Tangga");
    glutDisplayFunc(drawBoard);
    glutKeyboardFunc(input);
    myinit();  // panggil setelah semua init

    glutMainLoop();
    return 0;
}

