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
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

#endif // util_H
