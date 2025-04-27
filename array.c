#include "header.h"

void createEmptyArray(Array *A) {
    (*A).jumlah = 0;
}

int findElmArray(Array A, char judul[]) {
    int i;
    for (i = 0; i < A.jumlah; i++) {
        if (strcmp(A.data[i].judul, judul) == 0) {
            return i;
        }
    }
    return -1;
}

void insertArray(Array *A, char judul[], int stok) {
    if ((*A).jumlah < MAX_BUKU) {
        strcpy((*A).data[(*A).jumlah].judul, judul);
        (*A).data[(*A).jumlah].stok = stok;
        createEmptyQueue(&((*A).data[(*A).jumlah].antrianPeminjam));
        (*A).jumlah++;
    } else {
        printf("Array penuh, tidak bisa menambah data baru.\n");
    }
}

void deleteArray(Array *A, int idx) {
    if (idx >= 0 && idx < (*A).jumlah) {
        int i;
        for (i = idx; i < (*A).jumlah - 1; i++) {
            strcpy((*A).data[i].judul, (*A).data[i + 1].judul);
            (*A).data[i].stok = (*A).data[i + 1].stok;
            (*A).data[i].antrianPeminjam = (*A).data[i + 1].antrianPeminjam;
        }
        (*A).jumlah--;
    }
}

void printInfoArray(Array A) {
    if (A.jumlah == 0) {
        printf("Array kosong\n");
    } else {
        printf("\n=== DAFTAR BUKU ===\n");
        printf("%-30s | %s\n", "Judul Buku", "Stok");
        printf("-----------------------------------\n");
        int i;
        for (i = 0; i < A.jumlah; i++) {
            printf("%-30s | %d\n", A.data[i].judul, A.data[i].stok);
        }
        printf("\n");
    }
}

void printInfoArrayReverse(Array A) {
    if (A.jumlah == 0) {
        printf("Array kosong\n");
    } else {
        printf("\n=== DAFTAR BUKU (TERBALIK) ===\n");
        printf("%-30s | %s\n", "Judul Buku", "Stok");
        printf("-----------------------------------\n");
        int i;
        for (i = A.jumlah - 1; i >= 0; i--) {
            printf("%-30s | %d\n", A.data[i].judul, A.data[i].stok);
        }
        printf("\n");
    }
}
