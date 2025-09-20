#include <stdio.h>
#include <stdlib.h>

#define MAX 50

/* Struktur Node untuk Queue */

typedef struct {
    int items[MAX];
    int front;
    int rear;
}  Queue;

/* Inisialisasi queue kosong.
   front = -1 dan rear = -1 menandakan queue belum berisi elemen. Digunakan sebelum BFS dimulai */
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

/* Cek Queue kosong. Mengembalikan nilai true (1) jika kosong, atau false (0) jika ada isinya.
Penting agar BFS tahu kapan traversal selesai */

int isEmpty(Queue *q) {
    return q->rear == -1;
}

/* Enqueue (Memasukkan elemen baru ke belakang queue.) 
   Jika queue penuh = cetak peringatan.
   Jika queue kosong (front = -1), maka front di-set ke 0.
   BFS sangat bergantung pada enqueue untuk mengantri tetangga node */

void enqueue(Queue *q, int value) {
    if(q->rear == MAX -1) {
        printf("Queue penuh!\n");
        return;
    }
    if(q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

/* Dequeue (Mengambil elemen dari depan queue)
   Jika kososng = kembalikan -1
   Setelah elemen terakhir diambil, queue di-reset (front = rear = -1).
   Inilah yang membuat BFS selalu mengambil node paling awal (FIFO) */

int dequeue(Queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return -1;
    }
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// Graph menggunakan adjacency list
int adj[MAX][MAX];
int visited[MAX];
int n; // jumlah node

/* Fungsi utama BFS. Langkah kerja:
   Inisialisasi queue kosong. Tandai startNode sebagai visited lalu enqueue.
   Selama queue belum kosong:
        Dequeue node paling depan (current)
        Cetak node tersebut
        Cek semua tetangga (adj[current][i]): jika belum di kunjungi > tandai visited + masukkan ke queue 
   Hasil traversal BFS dicetak ke layar*/

void bfs(int startNode) {
    Queue q;
    initQueue(&q);

    visited[startNode] = -1;
    enqueue(&q, startNode);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d", current);

        for (int i = 1; i <= n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
}

/* Menentukan jumlah node n = 8.
   Inisialisasi matrix sesuai struktur tree.
   Menjalankan BFS dari node 1.
   Menampilkan urutan traversal BFS */

int main(){
    n = 8;

    // Inisialisasi adjacency matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
    }

    // Tambah edge sesuai tree di modul
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;
    adj[3][4] = adj[4][3] = 1;
    adj[4][5] = adj[5][4] = 1;
    adj[4][6] = adj[6][4] = 1;
    adj[5][7] = adj[7][5] = 1;
    adj[6][8] = adj[8][6] = 1;

    printf("Hasil BFS mulai dari node 3:\n");
    bfs(3);
    return 0;
}
