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
    free(node->data.nama);
    DestructDiseaseList(node->data.penyakit.First);
    node->data.penyakit.First = NULL;
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
        newPatient->data.waktu_estimasi_mulai = data.waktu_datang + 1;
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
* @finalState   : Q->Front menunjuk ke antrian selanjutnya atau menjadi NULL, Q->Front sebelumya di Dealokasi
*/
void DequeuePatient(Queue *Q){
	address_queue P;

	if(IsQueueEmpty(*Q)){
		printf("Queue is empty!\n");
	}

	else{
        P = Q->Front;

        if(P == Q->Rear){
            Q->Front = NULL;
            Q->Rear = NULL;
        } else {
            Q->Front = P->next;
        }

        P->next = NULL;
        DeallocPatientNode(P);
	}
}

/*
* description  : Mencetak data data di dalam antrian ke layar
*/
void PrintQueue(Queue Q) {
    address_queue current = Q.Front;
	
    while(current != NULL) {
    	infotype temp = current->data;
    	address_linked_list curr_link = temp.penyakit.First;
    	
    printf("||                                                                                   ||\n");
    printf("|| Time of Arrival	: %-16d                                           ||\n", temp.waktu_datang);
    printf("|| Name			: %-20s                                       ||\n", temp.nama);
	printf("|| \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF||\n");
	printf("|| \xB3    Category Disease    \xB3                       Disease                         \xB3||\n");
	printf("|| \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4||\n");
    	while(curr_link != NULL) {
		printf("|| \xB3           %-5d        \xB3 %-54s\xB3||\n", curr_link->data_disease.severity, disease_string[curr_link->data_disease.disease_name]);
		curr_link = curr_link->next;
    	}
    	printf("|| \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9||\n");
    printf("|| Time of Service	: %-15d                                            ||\n", temp.waktu_pelayaan);
    printf("|| Start of Service	: %-14d                                             ||\n", temp.waktu_estimasi_mulai);
    printf("|| End of Service	: %-13d    	                                     ||\n", temp.waktu_selesai);
    printf("||                                                                                   ||\n");
	printf("|| Enter to Main Menu                                                                ||\n");
	printf("=======================================================================================\n");

	current = current->next;
	}
}

