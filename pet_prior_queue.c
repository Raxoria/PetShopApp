#include "pet_prior_queue.h"
#include <stdlib.h>
#include <stdio.h>

/*
* @description  : Mengembalikan nilai true jika Q kosong
*/
bool IsQueueEmpty(Queue Q) {
    return Q.Front == NULL && Q.Rear == NULL;
}

/*
* @description  : Mengirimkan address hasil alokasi satu node, return NULL jika alokasi gagal
*/
address_queue AllocNewPatientNode(infotype data) {
    address_queue temp = malloc(sizeof(NodeQueue));

    if(temp != NULL) {
        temp->data = data;
        temp->next = NULL;
    }

    return temp;
}

/*
* @initialState : node terdefinisi
* @finalState   : node dibebaskan dan dikembalikan ke sistem
*/
void DeallocPatientNode(address_queue node) {
    free(node);
}

/*
* @initialState : Q sembarang
* @finalState   : Terbentuk Q kosong, Q=>Front = NULL dan Q->Rear == NULL
*/
void CreateNewQueue(Queue *Q){
    Q->Front = NULL;
    Q->Rear = NULL;
}

/*
* @initialState : Q mungkin kosong
* @finalState   : Node baru teralokasi dan ditambahkan ke Q di posisi yang sesuai dengan urutan prioritasnya
*/
void EnqueueNewPatient(Queue *Q, infotype data){

    address_queue newPatient = AllocNewPatientNode(data);

    if(newPatient == NULL)
        return;

    if(IsQueueEmpty(*Q)){
        newPatient->data.waktu_estimasi_mulai = 1;
        newPatient->data.waktu_selesai = newPatient->data.waktu_estimasi_mulai + newPatient->data.waktu_pelayaan;

        Q->Front = newPatient;
        Q->Rear = newPatient;
        return;
    }

    if(newPatient->data.priority <= Q->Rear->data.priority || (Q->Front == Q->Rear)){
        EnqueueAtEnd(Q, newPatient);
    } else {
        EnqueueWithPriority(Q, newPatient);
    }
}

void EnqueueAtEnd(Queue *Q, address_queue newNode){
    newNode->data.waktu_estimasi_mulai = Q->Rear->data.waktu_selesai + 1;
    newNode->data.waktu_selesai = newNode->data.waktu_estimasi_mulai + newNode->data.waktu_pelayaan;

    Q->Rear->next = newNode;
    Q->Rear = newNode;
}

void EnqueueWithPriority(Queue *Q, address_queue newNode){
    address_queue current = Q->Front->next;
    address_queue prev = Q->Front;

    while(current != NULL){
        if(current->data.priority >= newNode->data.priority){
            prev = current;
            current = current->next;
            continue;
        }

        newNode->next = prev->next;
        newNode->data.waktu_estimasi_mulai = prev->data.waktu_selesai + 1;
        newNode->data.waktu_selesai = newNode->data.waktu_estimasi_mulai + newNode->data.waktu_pelayaan;
        prev->next = newNode;

        address_queue currentEdit = newNode->next;
        address_queue prevEdit = newNode;

        while(currentEdit != NULL) {
            currentEdit->data.waktu_estimasi_mulai = prevEdit->data.waktu_selesai + 1;
            currentEdit->data.waktu_selesai = currentEdit->data.waktu_estimasi_mulai + currentEdit->data.waktu_pelayaan;

            prevEdit = currentEdit;
            currentEdit = currentEdit->next;
        }

        break;
    }
}

/*
* @initialState : Q mungkin kosong
* @finalState   : Q->Front menunjuk ke antrian selanjutnya atau menjadi NILL, Q->Front sebelumya di Dealokasi
*/
void DequeuePatient(Queue *Q);

/*
* description  : Mencetak data data di dalam antrian ke layar
*/
void PrintQueue(Queue Q) {
    address_queue current = Q.Front;

    printf("%-20s | prioritas | waktu kedatangan | estimasi mulai | waktu pelayanan | waktu selesai |\n", "Nama");
    while(current != NULL) {
        printf("%-20s | %-9d | %-16d | %-14d | %-15d | %-13d |\n", current->data.nama, current->data.priority, current->data.waktu_datang, current->data.waktu_estimasi_mulai, current->data.waktu_pelayaan, current->data.waktu_selesai);
        current = current->next;
    }
}
