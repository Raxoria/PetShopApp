#ifndef pet_prior_queue.h
#define pet_prior_queue.h

#include "linked_list_disease.h"
#include <stdbool.h>

typedef struct NodeQueue* address_queue;

typedef struct NodeQueue {
    infotype data;
    address_queue next;
}NodeQueue;

typedef struct {
    char* nama;
    int waktu_datang;
    int waktu_pelayaan;
    int waktu_estimasi_mulai;
    int waktu_selesai;
    int priority;
    LinkedList_Disease penyakit;
} infotype;

typedef struct {
    address_queue Front;
    address_queue Rear;
} Queue;

/*
* @description  : Mengembalikan nilai true jika Q kosong
*/
bool IsQueueEmpty(Queue Q);

/*
* @description  : Mengirimkan address hasil alokasi satu node, return NULL jika alokasi gagal
*/
address_queue AllocNewPatientNode(infotype data);

/*
* @initialState : node terdefinisi
* @finalState   : node dibebaskan dan dikembalikan ke sistem
*/
void DeallocPatientNode(address_queue node);

/*
* @initialState : Q sembarang
* @finalState   : Terbentuk Q kosong, Q=>Front = NULL dan Q->Rear == NULL
*/
void CreateNewQueue(Queue *Q);

/*
* @initialState : Q mungkin kosong
* @finalState   : Node baru teralokasi dan ditambahkan ke Q di posisi yang sesuai dengan urutan prioritasnya
*/
void EnqueueNewPatient(Queue *Q, infotype data);

void EnqueueAtEnd(Queue *Q, address_queue newNode);

void EnqueueWithPriority(Queue *Q, address_queue newNode);

/*
* @initialState : Q mungkin kosong
* @finalState   : Q->Front menunjuk ke antrian selanjutnya atau menjadi NILL, Q->Front sebelumya di Dealokasi
*/
void DequeuePatient(Queue *Q);

/*
* description  : Mencetak data data di dalam antrian ke layar
*/
void PrintQueue(Queue Q);

#endif // pet_prior_queue
