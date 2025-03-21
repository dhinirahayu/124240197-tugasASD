#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pegawai
{
    int id;
    string nama;
    double gaji;
};

void tambahdata()
{
    FILE *file = fopen("pegawai.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file!" << endl;
    }

    {
        pegawai p;
        cout << "Masukan id pegawai:";
        cin >> p.id;
        cout << "Masukan nama pegawai:";
        cin >> p.nama;
        cout << "Masukan gaji pegawai:\n";
        cin >> p.gaji;
        cin.ignore();

        fwrite(&p, sizeof(pegawai), 1, file);
        cout << "Data pegawai berhasil ditambahkan!" << endl;
    }
    fclose(file);
}

void lihat()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Data pegawai tidak tersedia!" << endl;
    }
    pegawai p;
    cout << "\nDaftar Data Pegawai\n";
    while (fread(&p, sizeof(pegawai), 1, file))
    {
        cout << "ID: " << p.id << "| Nama: " << p.nama << "| Gaji: " << p.gaji << endl;
    }
    fclose(file);
}

void mencari()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Data Pegawai tidak tersedia!" << endl;
    }
    int cariId;
    cout << "Masukan ID Pegawai yang ingin di cari: ";
    cin >> cariId;
    pegawai p;
    bool ditemukan = false;
    while (fread(&p, sizeof(pegawai), 1, file))
    {
        if (p.id == cariId)
        {
            cout << "Data pegawai ditemukan:\n";
            cout << "ID:" << p.id << "| Nama: " << p.nama << "| Gaji: " << p.gaji << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << cariId << "Tidak ditemukan." << endl;
    }
    fclose(file);
}

void perbaruiGaji()
{
    FILE *file = fopen("pegawai.dat", "rb+");
    if (!file)
    {
        cout << "Data Pegawai tidak ditemukan!" << endl;
    }

    int cariId;
    double Gajibaru;
    cout << "Masukan ID pegawai yang ingin diperbarui: ";
    cin >> cariId;
    pegawai p;
    bool ditemukan = false;
    while (fread(&p, sizeof(pegawai), 1, file))
    {
        if (p.id == cariId)
        {
            cout << "Masukan gaji baru: ";
            cin >> Gajibaru;
            p.gaji = Gajibaru;
            fseek(file, -sizeof(pegawai), SEEK_CUR);
            fwrite(&p, sizeof(pegawai), 1, file);
            cout << "Gaji berhasil diperbarui!" << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Pegawai dengan id " << cariId << "tidak ditemukan." << endl;
    }
    fclose(file);
}
int main()
{
    int pilihan;
    do
    {
        cout << "\n======== SI Kepegawaian ========\n";
        cout << "1. Tambah data pegawai\n";
        cout << "2. Lihat data pegawai\n";
        cout << "3. Cari data pegawai\n";
        cout << "4. Perbarui gaji\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            int jumlah;
            cout << "Masukan jumlah data : ";
            cin >> jumlah;
            cin.ignore();
            for (int i = 0; i < jumlah; i++)
            {
                tambahdata();
            }

            break;
        case 2:
            lihat();
            break;
        case 3:
            mencari();
        case 4:
            perbaruiGaji();
            break;
        case 0:
            cout << "Keluar dari program!" << endl;
            break;

        default:
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 0);
    return 0;
}