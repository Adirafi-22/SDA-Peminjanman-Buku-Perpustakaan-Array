#include "header.h"

void createEmptyStack(Stack *S) {
    (*S).TOP = -1;
    (*S).BOTTOM = -1;
    (*S).jumlah = 0;
}

int isEmptyStack(Stack S) {
    return (S.jumlah == 0);
}

int isFullStack(Stack S) {
    return (S.jumlah == MAX_AKTIVITAS);
}

void push(Stack *S, Aktivitas aktivitas) {
    if (isFullStack(*S)) {
        printf("Stack penuh, tidak bisa menambah data.\n");
    } else {
        if (isEmptyStack(*S)) {
            (*S).BOTTOM = 0;
            (*S).TOP = 0;
        } else {
            (*S).TOP = ((*S).TOP + 1) % MAX_AKTIVITAS;
        }
        (*S).data[(*S).TOP] = aktivitas;
        (*S).jumlah++;
    }
}

void pop(Stack *S, Aktivitas *val) {
    if (isEmptyStack(*S)) {
        printf("Stack kosong, tidak bisa menghapus data.\n");
    } else {
        *val = (*S).data[(*S).TOP];
        
        if ((*S).TOP == (*S).BOTTOM) { // Only one element
            createEmptyStack(S);
        } else {
            (*S).TOP = ((*S).TOP - 1 + MAX_AKTIVITAS) % MAX_AKTIVITAS;
            (*S).jumlah--;
        }
    }
}

void printInfoStack(Stack S) {
    if (isEmptyStack(S)) {
        printf("Stack kosong\n");
    } else {
        printf("\n=== HISTORY AKTIVITAS ===\n");
        int i;
        int count = 0;
        int idx = S.TOP;
        
        for (i = 0; i < S.jumlah; i++) {
            char tipeAktivitasStr[20];
            char tipePriorityStr[20];
            
            switch (S.data[idx].tipeAktivitas) {
                case 1:
                    strcpy(tipeAktivitasStr, "Pinjam");
                    break;
                case 2:
                    strcpy(tipeAktivitasStr, "Kembalikan");
                    break;
                case 3:
                    strcpy(tipeAktivitasStr, "Batalkan");
                    break;
                default:
                    strcpy(tipeAktivitasStr, "Unknown");
            }
            
            switch (S.data[idx].tipePriority) {
                case DOSEN:
                    strcpy(tipePriorityStr, "Dosen");
                    break;
                case MAHASISWA:
                    strcpy(tipePriorityStr, "Mahasiswa");
                    break;
                case MASYARAKAT_UMUM:
                    strcpy(tipePriorityStr, "Masyarakat Umum");
                    break;
                default:
                    strcpy(tipePriorityStr, "Unknown");
            }
            
            printf("%d. %s oleh '%s' (%s) - Buku: '%s'\n", 
                   i + 1, tipeAktivitasStr, S.data[idx].namaPeminjam, 
                   tipePriorityStr, S.data[idx].judulBuku);
            
            idx = (idx - 1 + MAX_AKTIVITAS) % MAX_AKTIVITAS;
        }
        printf("\n");
    }
}

void printInfoStackReverse(Stack S) {
    if (isEmptyStack(S)) {
        printf("Stack kosong\n");
    } else {
        printf("\n=== HISTORY AKTIVITAS (TERBALIK) ===\n");
        int i;
        int count = 0;
        int idx = S.BOTTOM;
        
        for (i = 0; i < S.jumlah; i++) {
            char tipeAktivitasStr[20];
            char tipePriorityStr[20];
            
            switch (S.data[idx].tipeAktivitas) {
                case 1:
                    strcpy(tipeAktivitasStr, "Pinjam");
                    break;
                case 2:
                    strcpy(tipeAktivitasStr, "Kembalikan");
                    break;
                case 3:
                    strcpy(tipeAktivitasStr, "Batalkan");
                    break;
                default:
                    strcpy(tipeAktivitasStr, "Unknown");
            }
            
            switch (S.data[idx].tipePriority) {
                case DOSEN:
                    strcpy(tipePriorityStr, "Dosen");
                    break;
                case MAHASISWA:
                    strcpy(tipePriorityStr, "Mahasiswa");
                    break;
                case MASYARAKAT_UMUM:
                    strcpy(tipePriorityStr, "Masyarakat Umum");
                    break;
                default:
                    strcpy(tipePriorityStr, "Unknown");
            }
            
            printf("%d. %s oleh '%s' (%s) - Buku: '%s'\n", 
                   i + 1, tipeAktivitasStr, S.data[idx].namaPeminjam, 
                   tipePriorityStr, S.data[idx].judulBuku);
            
            idx = (idx + 1) % MAX_AKTIVITAS;
        }
        printf("\n");
    }
}
