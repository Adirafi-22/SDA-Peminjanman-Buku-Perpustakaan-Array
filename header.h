#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi konstanta prioritas
#define MASYARAKAT_UMUM 1
#define MAHASISWA 2
#define DOSEN 3

// Definisi maksimum ukuran array
#define MAX_BUKU 100
#define MAX_ANTRIAN 50
#define MAX_AKTIVITAS 100

void clearScreen();

// Struktur data untuk aktivitas (digunakan di stack)
typedef struct {
    char namaPeminjam[50];
    char judulBuku[50];
    int tipePriority;
    int tipeAktivitas; // 1: Pinjam, 2: Kembalikan, 3: Batalkan
} Aktivitas;

// Struktur data untuk pengguna/peminjam (digunakan di queue)
typedef struct {
    char nama[50];
    int priority;
} ElmtQueue;

// Struktur data untuk antrian dengan prioritas
typedef struct {
    ElmtQueue data[MAX_ANTRIAN];
    int HEAD;
    int TAIL;
    int jumlah;
} Queue;

// Struktur data untuk stack
typedef struct {
    Aktivitas data[MAX_AKTIVITAS];
    int TOP;
    int BOTTOM;
    int jumlah;
} Stack;

// Struktur data untuk buku
typedef struct {
    char judul[50];
    int stok;
    Queue antrianPeminjam;
} ElmtArray;

// Struktur data untuk array buku
typedef struct {
    ElmtArray data[MAX_BUKU];
    int jumlah;
} Array;

// Deklarasi fungsi untuk Array
void createEmptyArray(Array *A);
int findElmArray(Array A, char judul[]);
void insertArray(Array *A, char judul[], int stok);
void deleteArray(Array *A, int idx);
void printInfoArray(Array A);
void printInfoArrayReverse(Array A);

// Deklarasi fungsi untuk Queue
void createEmptyQueue(Queue *Q);
int isEmptyQueue(Queue Q);
int isFullQueue(Queue Q);
void enqueue(Queue *Q, char nama[], int priority);
void dequeue(Queue *Q, ElmtQueue *val);
void printInfoQueue(Queue Q);
void printInfoQueueReverse(Queue Q);

// Deklarasi fungsi untuk Stack
void createEmptyStack(Stack *S);
int isEmptyStack(Stack S);
int isFullStack(Stack S);
void push(Stack *S, Aktivitas aktivitas);
void pop(Stack *S, Aktivitas *val);
void printInfoStack(Stack S);
void printInfoStackReverse(Stack S);

// Deklarasi fungsi untuk operasi perpustakaan
void tambahBuku(Array *A, char judul[], int stok);
void tambahStok(Array *A, char judul[], int tambahan);
void pinjamBuku(Array *A, Stack *S, char judul[], char nama[], int priority);
void kembalikanBuku(Array *A, Stack *S, char judul[], char nama[]);
void batalkanAktivitas(Array *A, Stack *S);
void prosesPeminjaman(Array *A, Stack *S, char judul[]);

#endif
