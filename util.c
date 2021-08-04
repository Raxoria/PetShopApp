#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/*
* @author : Reihan Reinaldi Suryaman
* @description : Memberikan nilai prioritas dan memproses waktu pelayanan
*/
void determinePriorityAndServiceTime(infotype *data, infotype_disease disease[9]){

	int severeCount, moderateCount, mildCount, totalTime , i;
    severeCount = moderateCount = mildCount = totalTime = 0;

    data->priority = 1;
    data->waktu_pelayaan = 0;

    for(i = 0; i < data->totalDisease; i++) {
        int severity = disease[i].severity;
        if(severity == MILD) {
            mildCount++;
            totalTime+=15;
        } else if(severity == MODERATE) {
            moderateCount++;
            totalTime+=30;
        } else if(severity == SEVERE) {
            severeCount++;
            totalTime+=45;
        }
    }

    (data->priority) += severeCount * 4;

    if(moderateCount >= 2) {
        (data->priority) += 3;
    } else if (moderateCount > 0) {
        (data->priority)++;
    }

    if(mildCount >= 3) {
        (data->priority) += 2;
    } else if (mildCount > 0) {
        (data->priority)++;
    }

    data->waktu_pelayaan = totalTime;
}

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
* @description : mengembalikan string severity
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
