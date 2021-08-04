#ifndef disease_H.h
#define disease_H.h

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

bool CheckIfDiseaseAlreadyExist(infotype_disease disease[9], int totalData, enum disease data);

#endif // disease

