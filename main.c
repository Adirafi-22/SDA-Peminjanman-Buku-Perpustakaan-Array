#include "header.h"

// Fungsi untuk membersihkan layar konsol
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Untuk Windows
    #else
        system("clear"); // Untuk Linux/Unix/macOS
    #endif
}

// Implementasi fungsi-fungsi operasi perpustakaan
void tambahBuku(Array *A, char judul[], int stok) {
    int idx = findElmArray(*A, judul);
    if (idx != -1) {
        printf("Buku '%s' sudah ada. Silakan tambah stok saja.\n", judul);
    } else {
        insertArray(A, judul, stok);
        printf("Buku '%s' berhasil ditambahkan dengan stok %d.\n", judul, stok);
    }
}

void tambahStok(Array *A, char judul[], int tambahan) {
    int idx = findElmArray(*A, judul);
    if (idx != -1) {
        (*A).data[idx].stok += tambahan;
        printf("Stok buku '%s' berhasil ditambah menjadi %d.\n", judul, (*A).data[idx].stok);
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void pinjamBuku(Array *A, Stack *S, char judul[], char nama[], int priority) {
    int idx = findElmArray(*A, judul);
    if (idx == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }

    // Tambahkan ke antrian peminjam
    enqueue(&((*A).data[idx].antrianPeminjam), nama, priority);
    printf("Anda telah masuk antrian untuk meminjam buku '%s'.\n", judul);
    
    // Catat aktivitas di stack
    Aktivitas aktivitas;
    strcpy(aktivitas.namaPeminjam, nama);
    strcpy(aktivitas.judulBuku, judul);
    aktivitas.tipePriority = priority;
    aktivitas.tipeAktivitas = 1; // 1: Pinjam
    
    push(S, aktivitas);
}

void kembalikanBuku(Array *A, Stack *S, char judul[], char nama[]) {
    int idx = findElmArray(*A, judul);
    if (idx == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }

    // Tambahkan stok buku
    (*A).data[idx].stok++;
    printf("Buku '%s' berhasil dikembalikan oleh '%s'. Stok sekarang: %d\n", judul, nama, (*A).data[idx].stok);
    
    // Catat aktivitas di stack
    Aktivitas aktivitas;
    strcpy(aktivitas.namaPeminjam, nama);
    strcpy(aktivitas.judulBuku, judul);
    aktivitas.tipePriority = 0; // Tidak relevan untuk pengembalian
    aktivitas.tipeAktivitas = 2; // 2: Kembalikan
    
    push(S, aktivitas);
}

void batalkanAktivitas(Array *A, Stack *S) {
    Aktivitas aktivitas;
    pop(S, &aktivitas);
    
    if (isEmptyStack(*S)) {
        printf("Tidak ada aktivitas untuk dibatalkan.\n");
        return;
    }
    
    printf("Membatalkan aktivitas terakhir...\n");
    
    // Handle pembatalan berdasarkan jenis aktivitas
    switch (aktivitas.tipeAktivitas) {
        case 1: // Batalkan peminjaman
            {
                int idx = findElmArray(*A, aktivitas.judulBuku);
                if (idx != -1) {
                    // Hapus peminjam dari antrian (idealnya cari peminjam yang sesuai)
                    // Ini penyederhanaan - kita hanya menghapus yang terakhir
                    ElmtQueue peminjam;
                    if (!isEmptyQueue((*A).data[idx].antrianPeminjam)) {
                        dequeue(&((*A).data[idx].antrianPeminjam), &peminjam);
                    }
                }
                printf("Peminjaman buku '%s' oleh '%s' dibatalkan.\n", 
                       aktivitas.judulBuku, aktivitas.namaPeminjam);
            }
            break;
            
        case 2: // Batalkan pengembalian
            {
                int idx = findElmArray(*A, aktivitas.judulBuku);
                if (idx != -1 && (*A).data[idx].stok > 0) {
                    (*A).data[idx].stok--;
                    printf("Pengembalian buku '%s' oleh '%s' dibatalkan.\n", 
                           aktivitas.judulBuku, aktivitas.namaPeminjam);
                }
            }
            break;
            
        default:
            printf("Aktivitas tidak dikenal.\n");
    }
}

void prosesPeminjaman(Array *A, Stack *S, char judul[]) {
    int idx = findElmArray(*A, judul);
    if (idx == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }

    if ((*A).data[idx].stok <= 0) {
        printf("Stok buku '%s' habis. Tidak bisa memproses peminjaman.\n", judul);
        return;
    }

    if (isEmptyQueue((*A).data[idx].antrianPeminjam)) {
        printf("Tidak ada antrian peminjam untuk buku '%s'.\n", judul);
        return;
    }

    // Ambil peminjam dengan prioritas tertinggi
    ElmtQueue peminjam;
    dequeue(&((*A).data[idx].antrianPeminjam), &peminjam);
    
    // Kurangi stok buku
    (*A).data[idx].stok--;
    
    printf("Peminjaman buku '%s' oleh '%s' berhasil diproses. Stok tersisa: %d\n", 
           judul, peminjam.nama, (*A).data[idx].stok);
    
    // Catat aktivitas di stack
    Aktivitas aktivitas;
    strcpy(aktivitas.namaPeminjam, peminjam.nama);
    strcpy(aktivitas.judulBuku, judul);
    aktivitas.tipePriority = peminjam.priority;
    aktivitas.tipeAktivitas = 1; // 1: Pinjam (proses)
    
    push(S, aktivitas);
}

int main() {
    Array daftarBuku;
    Stack historyAktivitas;
    int pilihan, stok, priority;
    char judul[50], nama[50];
    
    createEmptyArray(&daftarBuku);
    createEmptyStack(&historyAktivitas);
    
    do {
        printf("\n=============================================\n");
        printf("    SISTEM PEMINJAMAN BUKU PERPUSTAKAAN\n");
        printf("=============================================\n");
        printf("1. Tambah Buku\n");
        printf("2. Tambah Stok\n");
        printf("3. Pinjam Buku\n");
        printf("4. Proses Peminjaman\n");
        printf("5. Kembalikan Buku\n");
        printf("6. Batalkan Aktivitas Terakhir\n");
        printf("7. Lihat Data Buku\n");
        printf("8. Lihat Data Buku (Reverse)\n");
        printf("9. Lihat History Aktivitas\n");
        printf("10. Lihat History Aktivitas (Reverse)\n");
        printf("11. Lihat Antrian Peminjam\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // clear buffer
        
        switch (pilihan) {
            case 1: // Tambah Buku
                clearScreen();
                printf("\n--- TAMBAH BUKU ---\n");
                printf("Judul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                printf("Stok: ");
                scanf("%d", &stok);
                getchar(); // clear buffer
                
                tambahBuku(&daftarBuku, judul, stok);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 2: // Tambah Stok
                clearScreen();
                printf("\n--- TAMBAH STOK ---\n");
                printf("Judul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                printf("Tambahan stok: ");
                scanf("%d", &stok);
                getchar(); // clear buffer
                
                tambahStok(&daftarBuku, judul, stok);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 3: // Pinjam Buku
                clearScreen();
                printf("\n--- PINJAM BUKU ---\n");
                printf("Judul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                printf("Nama peminjam: ");
                fgets(nama, 50, stdin);
                nama[strcspn(nama, "\n")] = 0; // hapus newline
                
                printf("Prioritas (1: Masyarakat Umum, 2: Mahasiswa, 3: Dosen): ");
                scanf("%d", &priority);
                getchar(); // clear buffer
                
                pinjamBuku(&daftarBuku, &historyAktivitas, judul, nama, priority);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 4: // Proses Peminjaman
                clearScreen();
                printf("\n--- PROSES PEMINJAMAN ---\n");
                printf("Judul buku yang akan diproses: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                prosesPeminjaman(&daftarBuku, &historyAktivitas, judul);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 5: // Kembalikan Buku
                clearScreen();
                printf("\n--- KEMBALIKAN BUKU ---\n");
                printf("Judul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                printf("Nama peminjam: ");
                fgets(nama, 50, stdin);
                nama[strcspn(nama, "\n")] = 0; // hapus newline
                
                kembalikanBuku(&daftarBuku, &historyAktivitas, judul, nama);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 6: // Batalkan Aktivitas Terakhir
                clearScreen();
                printf("\n--- BATALKAN AKTIVITAS TERAKHIR ---\n");
                batalkanAktivitas(&daftarBuku, &historyAktivitas);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 7: // Lihat Data Buku
                clearScreen();
                printInfoArray(daftarBuku);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 8: // Lihat Data Buku (Reverse)
                clearScreen();
                printInfoArrayReverse(daftarBuku);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 9: // Lihat History Aktivitas
                clearScreen();
                printInfoStack(historyAktivitas);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 10: // Lihat History Aktivitas (Reverse)
                clearScreen();
                printInfoStackReverse(historyAktivitas);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 11: // Lihat Antrian Peminjam
                clearScreen();
                printf("\n--- LIHAT ANTRIAN PEMINJAM ---\n");
                printf("Judul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0; // hapus newline
                
                // Temukan buku dan tampilkan antriannya
                int idx = findElmArray(daftarBuku, judul);
                if (idx != -1) {
                    printInfoQueue(daftarBuku.data[idx].antrianPeminjam);
                } else {
                    printf("Buku '%s' tidak ditemukan.\n", judul);
                }
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 0: // Keluar
                printf("\nTerima kasih telah menggunakan sistem perpustakaan!\n");
                break;
                
            default:
                printf("\nPilihan tidak valid, silakan coba lagi.\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
        }
        
        clearScreen();
        
    } while (pilihan != 0);
    
    return 0;
}
