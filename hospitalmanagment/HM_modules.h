#include <stdlib.h>
#include "dbhandler.h"


extern dbobject db;



enum bedrank{
    noserviced,
    midservice,
    fullservice
};


struct bed{
    enum bedrank rank;
    int price; 
    int state;
};


struct patient{};

void initHM();
void indexhospitals();
void interface();
void reservation();
void documentary();
void  listbeds();

//reserv_bed()
//show_patientinfo
//showsortedbedforReserve()
