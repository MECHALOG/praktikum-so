#include <stdio.h>      // printf(), fflush()
#include <unistd.h>     // fork(), sleep() (jika perlu), getpid(), getppid()
#include <stdlib.h>     // exit()
#include <sys/wait.h>   // wait()

int main() {
    pid_t pid;          // menyimpan nilai return dari fork(): 0 di child, >0 di parent, <0 jika gagal
    int i;              // variabel counter untuk loop
    int endvalue = 10;  // jumlah iterasi yang diinginkan (10 kali)

    // Membuat proses baru (child). Setelah pemanggilan ini, ada dua proses:
    // - proses parent (fork() mengembalikan PID child > 0)
    // - proses child  (fork() mengembalikan 0)
    pid = fork();

    // Cek apakah fork gagal (nilai < 0)
    if (pid < 0) {
        // Jika fork gagal, beri pesan ke pengguna
        printf("Fork failed\n");
        // Keluar dari program dengan kode error 1
        exit(1);
    }
    // Jika fork berhasil dan nilai yang dikembalikan adalah 0 => kita berada di proses child
    else if (pid == 0) {
        // INI BAGIAN CHILD

        // Loop child dari 1 sampai endvalue (10)
        for (i = 1; i <= endvalue; i++) {
            // Cetak iterasi ke terminal, sesuai format yang diminta
            printf("Child running %d\n", i);
            // fflush memastikan output langsung ditampilkan (tanpa buffering)
            fflush(stdout);
        }

        // Cetak baris kosong lalu pesan bahwa child selesai dijalankan
        printf("\nChild selesai dijalankan.\n");

        // Pesan "Child Complete" dicetak dari proses child (sesuai permintaan)
        printf("Child Complete\n");

        // Child selesai -> keluar dengan status 0 (normal)
        exit(0);
    }
    // Jika pid > 0 berarti kita berada di proses parent
    else {
        // INI BAGIAN PARENT

        // Parent menunggu child selesai; wait(NULL) adalah blocking call
        // sehingga parent tidak akan melanjutkan sampai child exit()
        wait(NULL);

        // Setelah child selesai, parent melakukan loop 1..10
        for (i = 1; i <= endvalue; i++) {
            // Cetak iterasi parent
            printf("Parent running %d\n", i);
            // Pastikan teks muncul segera
            fflush(stdout);
        }

        // Tambah baris kosong agar output sama dengan contoh
        printf("\nParent Complete\n");

        // Parent juga mencetak "Child Complete" lagi (opsional, sesuai permintaan)
        // Ini akan menghasilkan dua baris "Child Complete": satu dari child, satu dari parent.
        printf("Child Complete\n");

        // Parent selesai -> keluar normal
        exit(0);
    }

    // Tidak akan tercapai karena kita selalu exit() di atas, namun return 0 melengkapi fungsi main.
    return 0;
}

