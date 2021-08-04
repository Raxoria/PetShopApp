#include "pet_prior_queue.h"
#include <stdlib.h>
#include <stdio.h>

/*
* @author : Reihan Reinaldi Suryaman
* @description  : Mengembalikan nilai true jika Q kosong
*/
bool IsQueueEmpty(Queue Q) {
    return Q.Front == NULL && Q.Rear == NULL;
}

/*
* @author : Reihan Reinaldi Suryaman
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
* @author : Reihan Reinaldi Suryaman
* @initialState : Q sembarang
* @finalState   : Terbentuk Q kosong, Q=>Front = NULL dan Q->Rear == NULL
*/
void CreateNewQueue(Queue *Q){
    Q->Front = NULL;
    Q->Rear = NULL;
}

/*
* @author : Reihan Reinaldi Suryaman
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

/*
* @author : Reihan Reinaldi Suryaman
& @description: Menambah data antrian di akhir
*/
void EnqueueAtEnd(Queue *Q, address_queue newNode){
    newNode->data.waktu_estimasi_mulai = Q->Rear->data.waktu_selesai + 1;
    newNode->data.waktu_selesai = newNode->data.waktu_estimasi_mulai + newNode->data.waktu_pelayaan;

    Q->Rear->next = newNode;
    Q->Rear = newNode;
}

/*
* @author : Reihan Reinaldi Suryaman
& @description: Menambah data antrian sesuai prioritas
*/
void EnqueueWithPriority(Queue *Q, address_queue newNode){
    address_queue current = Q->Front->next;
    address_queue prev = Q->Front;

    while(current != NULL){
        if(current->data.priority >= newNode->data.priority){
            prev = current;
            current = current->next;
            continue;
        }

        //melengkapi data pasien
        newNode->next = prev->next;
        newNode->data.waktu_estimasi_mulai = prev->data.waktu_selesai + 1;
        newNode->data.waktu_selesai = newNode->data.waktu_estimasi_mulai + newNode->data.waktu_pelayaan;
        prev->next = newNode;

        address_queue currentEdit = newNode->next;
        address_queue prevEdit = newNode;

        //memperbaharui data di bawah
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
* @author : Khansa Rafifah Taqiyyah
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
* @author : Khansa Rafifah Taqiyyah
* description  : Mencetak data - data di dalam antrian ke layar
*/
void PrintQueue(Queue Q) {
    address_queue current = Q.Front;
    int i = 1;

    while(current != NULL) {
        infotype temp = current->data;
    	address_linked_list curr_link = temp.penyakit.First;
	int j = 1;
		
    	if(i == 1){
  		printf("||                                                                                   ||\n");
  		printf("=======================================================================================\n");
	        printf("||                               PERSIAPAN DIPERIKSA                                 ||\n");
	        printf("=======================================================================================\n");
	        printf("||                                                                                   ||\n");
	        printf("|| Queue Number	        : %-16d                                           ||\n", i);
	        printf("|| Time of Arrival	: %-16d                                           ||\n", temp.waktu_datang);
	        printf("|| Name			: %-20s                                       ||\n", temp.nama);
	        printf("|| \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF||\n");
	        printf("|| \xB3    Category Disease    \xB3                       Disease                         \xB3||\n");
	        printf("|| \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4||\n");
	    	while(curr_link != NULL) {
	            char* severityString = GetSeverityString(curr_link->data_disease.severity);
	            printf("|| \xB3 %-d. %-8s            \xB3 %-54s\xB3||\n", j, severityString, disease_string[curr_link->data_disease.disease_name]);
	            curr_link = curr_link->next;
		    j++;
	    	}
	    	printf("|| \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9||\n");
	        printf("|| Time of Service	: %-15d                                            ||\n", temp.waktu_pelayaan);
	        printf("|| Start of Service	: %-14d                                             ||\n", temp.waktu_estimasi_mulai);
	        printf("|| End of Service	: %-13d    	                                     ||\n", temp.waktu_selesai);
	        printf("||                                                                                   ||\n");
	        printf("=======================================================================================\n");
	        printf("||                              RUANG TUNGGU ANTRIAN                                 ||\n");
		printf("=======================================================================================\n");
	        current = current->next;
	        i++;
	}
	else{
		printf("||                                                                                   ||\n");
		printf("|| Queue Number	        : %-16d                                           ||\n", i);
		printf("|| Time of Arrival	: %-16d                                           ||\n", temp.waktu_datang);
	        printf("|| Name			: %-20s                                       ||\n", temp.nama);
	        printf("|| \xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF||\n");
	        printf("|| \xB3    Category Disease    \xB3                       Disease                         \xB3||\n");
		printf("|| \xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4||\n");
		while(curr_link != NULL) {
		     char* severityString = GetSeverityString(curr_link->data_disease.severity);
		     printf("|| \xB3 %-d. %-8s            \xB3 %-54s\xB3||\n", j, severityString, disease_string[curr_link->data_disease.disease_name]);
		     curr_link = curr_link->next;
		     j++;
	    	}
		printf("|| \xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC1\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9||\n");
	 	printf("|| Time of Service	: %-15d                                            ||\n", temp.waktu_pelayaan);
		printf("|| Start of Service	: %-14d                                             ||\n", temp.waktu_estimasi_mulai);
		printf("|| End of Service	: %-13d    	                                     ||\n", temp.waktu_selesai);
		printf("||                                                                                   ||\n");
		printf("=======================================================================================\n");
		current = current->next;
		i++;  
	}	
   }	
	printf("   Enter to Main Menu                                                                  \n");
}

/*
* @author : Reihan Reinaldi Suryaman
* description  : Mendapatkan string severity
*/
char* GetSeverityString(int severity) {
    switch(severity) {
        case 1 :
            return "Mild";
            break;
        case 2 :
            return "Moderate";
            break;
        case 3 :
            return "Severe";
            break;
    }

    return "";
}
