#include "disease.h"
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

const int SEVERE = 3;
const int MODERATE = 2;
const int MILD = 1;


/*
* @author : Reihan Reinaldi Suryaman
* @description: Memeriksa apakah data disease telah ada di dalam list
*/
bool CheckIfDiseaseAlreadyExist(infotype_disease disease[9], int totalData, enum disease data) {
    int i;

    for(i = 0; i < totalData; i++) {
        if(disease[i].disease_name == data)
            return true;
    }

    return false;
}
