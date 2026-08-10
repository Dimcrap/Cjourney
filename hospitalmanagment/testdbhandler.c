#include "dbhandler.h"
#include <libpq-fe.h>



int main(){

    dbobject db =initdatabase("hospital_m", "testdb");
    printf("database have  %i tablecounts",db.tablecounts);

    sqlhelpmap mp;

    PQfinish(db.conn);

}