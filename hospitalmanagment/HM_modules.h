#include <stdlib.h>
#include "dbhandler.h"


//dbobject  db;

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

void interface();
void reservation();
void documentary();
void  listbeds();


//reserv_bed()
//show_patientinfo
//showsortedbedforReserve()
