#include "linked_list_disease.h"
#include <stdlib.h>
#include <stdio.h>

const char* disease_string[] = {
    "Penyakit Kulit",
    "Luka Ringan",
    "Bersin",
    "Cacingan",
    "Diare",
    "Luka Dalam",
    "Gangguan kerongkongan yang berlendir dan berbau busuk",
    "Kuning",
    "Terkena Virus"
};

/*
* @description  : Mengembalikan nilai true jika List kosong
*/
bool IsListEmpty(LinkedList_Disease List) {
    return List.First == NULL;
}

/*
* @initialState : List sembarang
* @finalState   : Terbentuk List kosong
*/
void CreateNewDiseaseList(LinkedList_Disease *List) {
    List->First = NULL;
}

/*
* @description  : Mengirimkan address hasil alokasi satu node, return NULL jika alokasi gagal
*/
address_linked_list AllocNewDiseaseNode(infotype_disease data) {
    address_linked_list temp = malloc(sizeof(node_disease));

    if(temp == NULL){
        return NULL;
    }

    temp->data_disease = data;
    temp->next = NULL;

    return temp;
}

/*
* @initialState : node terdefinisi
* @finalState   : node dibebaskan dan dikembalikan ke sistem
*/
void DeallocDiseaseNode(address_linked_list node){
    free(node);
}

/*
* @initialState : List mungkin kosong
* @finalState   : Node baru ditambahkan di awal List
*/
void InsertNewDiseaseAtStart(LinkedList_Disease *List, infotype_disease data){
    if(List->First == NULL){
        List->First = AllocNewDiseaseNode(data);
    } else {
        address_linked_list newElm = malloc(sizeof(node_disease));
        if(newElm == NULL){
            printf("Alokasi gagal");
        } else {
            newElm->data_disease = data;
            newElm->next = List->First;
            List->First = newElm;
        }
    }
}

/*
* @initialState : List mungkin kosong
* @finalState   : Node baru ditambahkan di akhir List
*/
void InsertNewDiseaseAtEnd(LinkedList_Disease *List, infotype_disease data) {
    if(List->First == NULL){
        List->First = AllocNewDiseaseNode(data);
    } else {
        address_linked_list current = List->First;
        address_linked_list newElm = malloc(sizeof(node_disease));
        if(newElm == NULL){
            printf("Alokasi gagal");
        }else {
            newElm->data_disease = data;
            newElm->next = NULL;
            while(current->next != NULL){
                current = current->next;
            }
            current->next = newElm;
        }
    }
}
