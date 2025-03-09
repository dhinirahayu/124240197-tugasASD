#include <iostream>
#include <string>

using namespace std;

// STRUKTUR DATA BUKU
struct film
{
    string judul;
    int kode;
    double rating;
};

const int MAX_FILM = 20;
film daftarfilm[MAX_FILM] = {
    {"Petaka Gunung Gede", 999, 8.5},
    {"Perayaan Mati Rasa", 222, 8.8},
    {"Pengantin Setan", 111, 9.7},
    {"1 Kakak 7 Ponakan", 555, 9.6},
    {"Cinta Tak Pernah Tepat Waktu", 444, 8.9},
    {"Iblis Dalam Kandungan", 333, 8.1},
    {"MICKY 17", 888, 7.8},
    {"Desa Mati", 666, 8.5},
    {"Legends of the Condor Heroes: The Gallants", 777, 8.4},
    {"Lovely Runner", 878, 9.9}};
int jumlahFilm = 10;

void salinArray(film sumber[], film tujuan[], int size)
{
    for (int i = 0; i < size; i++)
    {
        tujuan[i] = sumber[i];
    }
}

// MENAMPILKAN SEMUA DATA FILM MENGGUNAKAN POINTER
void tampilkanFilm(film arr[], int size, string pesan)
{
    cout << "\n"
         << pesan << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ". " << arr[i].judul << "(" << arr[i].kode << ") (" << arr[i].rating << ")\n";
    }
}

// MENAMPILKAN FILM BERDASARKAN KODE MENGGUNAKAN SEQUENTIAL SEARCH
void sequentialsearchKode(int kode)
{
    bool ditemukan = false;
    for (int i = 0; i < jumlahFilm; i++)
    {
        if (daftarfilm[i].kode == kode)
        {
            cout << "\nDitemukan: " << daftarfilm[i].judul << "(" << daftarfilm[i].kode << ")\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
        cout << "\nFilm dengan kode " << kode << " Tidak ditemukan.\n"; // Menambahkan spasi setelah kode
    cin.ignore();
    cin.get();
}

// fungsi partition untuk quicksort berdasarkan judul
int partitionJudul(film arr[], int low, int high)
{
    string pivot = arr[high].judul;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j].judul.compare(pivot) < 0)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// fungsi quicksort berdasarkan judul
void quicksortJudul(film arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionJudul(arr, low, high);
        quicksortJudul(arr, low, pi - 1);
        quicksortJudul(arr, pi + 1, high);
    }
}

// MENCARI FILM BERDASARKAN JUDUL MENGGUNAKAN BINARY SEARCH
int binarysearchJudul(film arr[], int size, string judul) // Mengubah tipe data parameter judul dari std::string ke string
{
    int kiri = 0, kanan = size - 1;
    while (kiri <= kanan)
    {
        int tengah = kiri + (kanan - kiri) / 2;
        int hasilCompare = arr[tengah].judul.compare(judul);
        if (hasilCompare == 0)
        {
            return tengah;
        }
        else if (hasilCompare < 0)
        {
            kiri = tengah + 1;
        }
        else
        {
            kanan = tengah - 1;
        }
    }
    return -1;
}

// MENGURUTKAN FILM BERDASARKAN RATING SECARA ASCENDING MENGGUNAKAN QUICK SORT
int partitionRating(film arr[], int low, int high)
{
    double pivot = arr[high].rating;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j].rating < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quicksortRating(film arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionRating(arr, low, high);
        quicksortRating(arr, low, pi - 1);
        quicksortRating(arr, pi + 1, high);
    }
}

// MENGURUTKAN FILM BERDASARKAN RATING SECARA DESCENDING MENGGUNAKAN BUBBLE SORT
void bubbleSort(film arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j].rating < arr[j + 1].rating)
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// MENAMPILKAN MENU UTAMA
int main()
{
    int pilihan, kode;
    string judul;
    do
    {
        system("cls");
        cout << "\n=============== MINI BIOSKOP ===============\n";
        cout << "1. Menampilkan semua data Film\n";
        cout << "2. Mencari Film dengan Sequential Search\n";
        cout << "3. Mencari judul Film dengan Binary Search\n";
        cout << "4. Mengurutkan Rating Film dengan Quick Sort\n";
        cout << "5. Mengurutkan Rating Film dengan Bubble Sort\n";
        cout << "6. Keluar\n";
        cout << "Pilih No: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            system("cls");
            tampilkanFilm(daftarfilm, jumlahFilm, "Daftar Film Belum urut");
            system("pause");
            break;
        case 2:
        {
            system("cls");
            cout << "\nMasukan Kode Film: ";
            cin >> kode;
            sequentialsearchKode(kode);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "\nMasukan Judul Film: ";
            cin.ignore();
            getline(cin, judul);
            film temp[MAX_FILM];
            salinArray(daftarfilm, temp, jumlahFilm);
            quicksortJudul(temp, 0, jumlahFilm - 1);
            int hasil = binarysearchJudul(temp, jumlahFilm, judul);
            if (hasil != -1)
            {
                cout << "\nDitemukan Film: " << temp[hasil].judul << " (Kode: " << temp[hasil].kode << ",Rating: " << temp[hasil].rating << ")\n";
            }
            else
            {
                cout << "\nFilm Tidak Ditemukan\n";
            }
            system("pause");
            break;
        }
        case 4:
        {
            system("cls");
            film temp[MAX_FILM];
            salinArray(daftarfilm, temp, jumlahFilm);
            quicksortRating(temp, 0, jumlahFilm - 1);
            tampilkanFilm(daftarfilm, jumlahFilm, "Daftar film Belum urut");
            tampilkanFilm(temp, jumlahFilm, "Daftar Film setelah Quick Sort (Ascending)");
            system("pause");
            break;
        }
        case 5:
        {
            system("cls");
            film temp[MAX_FILM];
            salinArray(daftarfilm, temp, jumlahFilm);
            bubbleSort(temp, jumlahFilm);
            tampilkanFilm(daftarfilm, jumlahFilm, "Rating Film Belum urut");
            tampilkanFilm(temp, jumlahFilm, "Rating Film Sudah Urut Bubble sort (Descending)");
            system("pause");
            break;
        }
        case 6:
        {
            system("cls");
            cout << "\n=============== KELUAR DARI PROGRAM ===============\n";
            break;
        }

        default:
            cout << "\nPilihan Tidak valid!\n";
            system("pause");
            break;
        }
    } while (pilihan != 6);
    return 0;
}