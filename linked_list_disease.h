#ifndef linked_list_disease.h
#define linked_list_disease.h

#include <stdbool.h>

extern const char* disease_string[];
extern const int SEVERE;
extern const int MODERATE;
extern const int MILD;

enum disease {
    KULIT,
    LUKA_RINGAN,
    BERSIN,
    CACINGAN,
    DIARE,
    LUKA_DALAM,
    KERONGKONGAN,
    KUNING,
    VIRUS
};

/*
* severity 1 = ringan
* severity 2 = sedang
* severity 3 = berat
*/
typedef struct {
    enum disease disease_name;
    int severity;
} infotype_disease;

typedef struct node_disease* address_linked_list;

typedef struct node_disease {
    infotype_disease data_disease;
    address_linked_list next;
} node_disease;

typedef struct {
    address_linked_list First;
} LinkedList_Disease;

/*
* @description  : Mengembalikan nilai true jika List kosong
*/
bool IsListEmpty(LinkedList_Disease List);

/*
* @initialState : List sembarang
* @finalState   : Terbentuk List kosong
*/
void CreateNewDiseaseList(LinkedList_Disease *List);

/*
* @description  : Mengirimkan address hasil alokasi satu node, return NULL jika alokasi gagal
*/
address_linked_list AllocNewDiseaseNode(infotype_disease data);

/*
* @initialState : node terdefinisi
* @finalState   : node dibebaskan dan dikembalikan ke sistem
*/
void DeallocDiseaseNode(address_linked_list node);

/*
* @initialState : List mungkin kosong
* @finalState   : Node baru ditambahkan di awal List
*/
void InsertNewDiseaseAtStart(LinkedList_Disease *List, infotype_disease data);

/*
* @initialState : List mungkin kosong
* @finalState   : Node baru ditambahkan di akhir List
*/
void InsertNewDiseaseAtEnd(LinkedList_Disease *List, infotype_disease data);

#endif // linked_list_disease
