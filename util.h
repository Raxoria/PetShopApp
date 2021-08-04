#ifndef util_H.h
#define util_H.h

#include <windows.h>

#include "pet_prior_queue.h"
#include "disease.h"

/*
* @author : Reihan Reinaldi Suryaman
* @description : Memberikan nilai prioritas dan memproses waktu pelayanan
*/
void determinePriorityAndServiceTime(infotype *data, infotype_disease disease[9]);

/*
* @initialState : Kursor untuk menunjuk pada titik (x,y) tertentu
* @author : Internet (edited)
* @description : digunakan untuk menunjukan tempat kursor
*/
void gotoxy(int x, int y);

/*
* @author : Reihan Reinaldi Suryaman
* description  : Mendapatkan string severity
*/
char* GetSeverityString(int severity);

#endif // util_H
