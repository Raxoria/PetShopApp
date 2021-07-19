#include <stdio.h>
#include <stdlib.h>
#include "linked_list_disease.h"
#include "pet_prior_queue.h"
#include <string.h>

int main()
{
    Queue q;

    CreateNewQueue(&q);

    infotype data;

    data.nama = "Kucing A";
    data.priority = 3;
    data.waktu_datang = 0;
    data.waktu_pelayaan = 45;

    EnqueueNewPatient(&q, data);

    data.nama = "Kucing B";
    data.priority = 8;
    data.waktu_datang = 5;
    data.waktu_pelayaan = 45;

    EnqueueNewPatient(&q, data);

    data.nama = "Kucing C";
    data.priority = 15;
    data.waktu_datang = 13;
    data.waktu_pelayaan = 45;

    EnqueueNewPatient(&q, data);

    data.nama = "Kucing D";
    data.priority = 10;
    data.waktu_datang = 13;
    data.waktu_pelayaan = 45;

    EnqueueNewPatient(&q, data);

    PrintQueue(q);
    return 0;
}
