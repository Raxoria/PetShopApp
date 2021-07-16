#ifndef pet_prior_queue.h
#define pet_prior_queue.h

#include "linked_list_disease.h"

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

#endif // pet_prior_queue
