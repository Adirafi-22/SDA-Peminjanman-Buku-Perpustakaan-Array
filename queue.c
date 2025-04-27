#include "header.h"

void createEmptyQueue(Queue *Q) {
    (*Q).HEAD = 0;
    (*Q).TAIL = -1;
    (*Q).jumlah = 0;
}

int isEmptyQueue(Queue Q) {
    return (Q.jumlah == 0);
}

int isFullQueue(Queue Q) {
    return (Q.jumlah == MAX_ANTRIAN);
}

// Utility function to find correct position for new element based on priority
int findPosition(Queue Q, int priority) {
    int i;
    for (i = Q.HEAD; i <= Q.TAIL; i++) {
        int idx = i % MAX_ANTRIAN;
        if (priority > Q.data[idx].priority) {
            return i;
        }
    }
    return Q.TAIL + 1;
}

void enqueue(Queue *Q, char nama[], int priority) {
    if (isFullQueue(*Q)) {
        printf("Queue penuh, tidak bisa menambah data.\n");
    } else {
        if (isEmptyQueue(*Q)) {
            (*Q).HEAD = 0;
            (*Q).TAIL = 0;
            strcpy((*Q).data[0].nama, nama);
            (*Q).data[0].priority = priority;
        } else {
            // Find position based on priority
            int position = findPosition(*Q, priority);
            
            // Shift elements to make space
            if (position <= (*Q).TAIL) {
                int i;
                for (i = (*Q).TAIL; i >= position; i--) {
                    int curr = i % MAX_ANTRIAN;
                    int next = (i + 1) % MAX_ANTRIAN;
                    strcpy((*Q).data[next].nama, (*Q).data[curr].nama);
                    (*Q).data[next].priority = (*Q).data[curr].priority;
                }
            }
            
            // Insert at proper position
            int idx = position % MAX_ANTRIAN;
            strcpy((*Q).data[idx].nama, nama);
            (*Q).data[idx].priority = priority;
            (*Q).TAIL = ((*Q).TAIL + 1) % MAX_ANTRIAN;
        }
        (*Q).jumlah++;
    }
}

void dequeue(Queue *Q, ElmtQueue *val) {
    if (isEmptyQueue(*Q)) {
        printf("Queue kosong, tidak bisa menghapus data.\n");
    } else {
        strcpy((*val).nama, (*Q).data[(*Q).HEAD].nama);
        (*val).priority = (*Q).data[(*Q).HEAD].priority;
        
        if ((*Q).HEAD == (*Q).TAIL) { // Only one element
            createEmptyQueue(Q);
        } else {
            (*Q).HEAD = ((*Q).HEAD + 1) % MAX_ANTRIAN;
            (*Q).jumlah--;
        }
    }
}

void printInfoQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
    } else {
        printf("\n=== ANTRIAN PEMINJAM ===\n");
        printf("%-20s | %s\n", "Nama", "Prioritas");
        printf("-----------------------------------\n");
        int i;
        int count = 0;
        for (i = Q.HEAD; count < Q.jumlah; i = (i + 1) % MAX_ANTRIAN) {
            char prioritasStr[20];
            switch (Q.data[i].priority) {
                case DOSEN:
                    strcpy(prioritasStr, "Dosen");
                    break;
                case MAHASISWA:
                    strcpy(prioritasStr, "Mahasiswa");
                    break;
                case MASYARAKAT_UMUM:
                    strcpy(prioritasStr, "Masyarakat Umum");
                    break;
                default:
                    strcpy(prioritasStr, "Unknown");
            }
            printf("%-20s | %s\n", Q.data[i].nama, prioritasStr);
            count++;
        }
        printf("\n");
    }
}

void printInfoQueueReverse(Queue Q) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
    } else {
        printf("\n=== ANTRIAN PEMINJAM (TERBALIK) ===\n");
        printf("%-20s | %s\n", "Nama", "Prioritas");
        printf("-----------------------------------\n");
        int i;
        int count = 0;
        int idx = Q.TAIL;
        
        for (i = 0; i < Q.jumlah; i++) {
            char prioritasStr[20];
            switch (Q.data[idx].priority) {
                case DOSEN:
                    strcpy(prioritasStr, "Dosen");
                    break;
                case MAHASISWA:
                    strcpy(prioritasStr, "Mahasiswa");
                    break;
                case MASYARAKAT_UMUM:
                    strcpy(prioritasStr, "Masyarakat Umum");
                    break;
                default:
                    strcpy(prioritasStr, "Unknown");
            }
            printf("%-20s | %s\n", Q.data[idx].nama, prioritasStr);
            idx = (idx - 1 + MAX_ANTRIAN) % MAX_ANTRIAN;
        }
        printf("\n");
    }
}
