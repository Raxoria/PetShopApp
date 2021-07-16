#ifndef linked_list_disease.h
#define linked_list_disease.h

extern const *disease_string[];

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

#endif // linked_list_disease
