#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

// Struktur data nasabah
typedef struct {
    int id;
    char nama[50];
    float saldo;
    float pinjaman;
    int punya_kartu_kredit;
    float limit_kartu_kredit;
    float tagihan_kartu_kredit;
} Nasabah;

Nasabah nasabah[MAX];
int jumlah_nasabah = 0;

// Prototipe fungsi
void menu();
void buatRekening();
void setorUang();
void tarikUang();
void pinjamUang();
void buatKartuKredit();
void tampilkanNasabah();
Nasabah* cariNasabah(int id);

int main() {
    int pilihan;
    do {
        menu();
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1: buatRekening(); break;
            case 2: setorUang(); break;
            case 3: tarikUang(); break;
            case 4: pinjamUang(); break;
            case 5: buatKartuKredit(); break;
            case 6: tampilkanNasabah(); break;
            case 0: printf("Terima kasih, program selesai.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
        printf("\n");
    } while (pilihan != 0);
    return 0;
}

void menu() {
    printf("===== SISTEM OPERASI PERBANKAN =====\n");
    printf("1. Buat Rekening Baru\n");
    printf("2. Setor Uang (Deposit)\n");
    printf("3. Tarik Uang\n");
    printf("4. Pinjam Uang\n");
    printf("5. Buat Kartu Kredit\n");
    printf("6. Tampilkan Data Nasabah\n");
    printf("0. Keluar\n");
}

// Cari nasabah berdasarkan ID
Nasabah* cariNasabah(int id) {
    for (int i = 0; i < jumlah_nasabah; i++) {
        if (nasabah[i].id == id) return &nasabah[i];
    }
    return NULL;
}

// Membuat rekening baru
void buatRekening() {
    if (jumlah_nasabah >= MAX) {
        printf("Kapasitas penuh!\n");
        return;
    }

    Nasabah n;
    n.id = jumlah_nasabah + 1;
    printf("Masukkan nama nasabah: ");
    scanf(" %[^\n]", n.nama);
    n.saldo = 0;
    n.pinjaman = 0;
    n.punya_kartu_kredit = 0;
    n.limit_kartu_kredit = 0;
    n.tagihan_kartu_kredit = 0;

    nasabah[jumlah_nasabah++] = n;
    printf("Rekening berhasil dibuat!\nID: %d | Nama: %s\n", n.id, n.nama);
}

// Menyimpan uang
void setorUang() {
    int id; float jumlah;
    printf("Masukkan ID nasabah: ");
    scanf("%d", &id);
    Nasabah *n = cariNasabah(id);
    if (!n) { printf("Rekening tidak ditemukan!\n"); return; }

    printf("Masukkan jumlah deposit: ");
    scanf("%f", &jumlah);
    if (jumlah <= 0) {
        printf("Jumlah tidak valid!\n");
        return;
    }

    n->saldo += jumlah;
    printf("Setoran berhasil! Saldo sekarang: Rp%.2f\n", n->saldo);
}

// Menarik uang
void tarikUang() {
    int id; float jumlah;
    printf("Masukkan ID nasabah: ");
    scanf("%d", &id);
    Nasabah *n = cariNasabah(id);
    if (!n) { printf("Rekening tidak ditemukan!\n"); return; }

    printf("Masukkan jumlah penarikan: ");
    scanf("%f", &jumlah);
    if (jumlah > n->saldo) {
        printf("Saldo tidak mencukupi!\n");
    } else {
        n->saldo -= jumlah;
        printf("Penarikan berhasil! Saldo sekarang: Rp%.2f\n", n->saldo);
    }
}

// Meminjam uang
void pinjamUang() {
    int id; float jumlah;
    printf("Masukkan ID nasabah: ");
    scanf("%d", &id);
    Nasabah *n = cariNasabah(id);
    if (!n) { printf("Rekening tidak ditemukan!\n"); return; }

    printf("Masukkan jumlah pinjaman: ");
    scanf("%f", &jumlah);
    if (jumlah <= 0) {
        printf("Jumlah tidak valid!\n");
        return;
    }

    n->pinjaman += jumlah;
    n->saldo += jumlah;
    printf("Pinjaman disetujui!\nSaldo sekarang: Rp%.2f | Total pinjaman: Rp%.2f\n",
           n->saldo, n->pinjaman);
}

// Membuat kartu kredit
void buatKartuKredit() {
    int id;
    printf("Masukkan ID nasabah: ");
    scanf("%d", &id);
    Nasabah *n = cariNasabah(id);
    if (!n) { printf("Rekening tidak ditemukan!\n"); return; }

    if (n->punya_kartu_kredit) {
        printf("Nasabah sudah memiliki kartu kredit.\n");
        return;
    }

    // Limit kartu kredit ditentukan dari saldo nasabah
    if (n->saldo < 1000000) {
        printf("Saldo tidak mencukupi untuk membuat kartu kredit (min Rp1.000.000)\n");
        return;
    }

    n->punya_kartu_kredit = 1;
    n->limit_kartu_kredit = n->saldo * 2;  // contoh: limit = 2x saldo
    n->tagihan_kartu_kredit = 0;

    printf("Kartu kredit berhasil dibuat!\n");
    printf("Limit kartu kredit: Rp%.2f\n", n->limit_kartu_kredit);
}

// Menampilkan semua nasabah
void tampilkanNasabah() {
    printf("\n=== DATA NASABAH ===\n");
    if (jumlah_nasabah == 0) {
        printf("Belum ada nasabah terdaftar.\n");
        return;
    }

    for (int i = 0; i < jumlah_nasabah; i++) {
        Nasabah n = nasabah[i];
        printf("ID: %d | Nama: %s | Saldo: Rp%.2f | Pinjaman: Rp%.2f",
               n.id, n.nama, n.saldo, n.pinjaman);
        if (n.punya_kartu_kredit)
            printf(" | Kartu Kredit: YA (Limit Rp%.2f)\n", n.limit_kartu_kredit);
        else
            printf(" | Kartu Kredit: TIDAK\n");
    }
}


