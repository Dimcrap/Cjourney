#include "dbhandler.h"
#include <stdio.h>
#include <libpq-fe.h>



int main(){

    char tablename[32];

    dbobject db =initdatabase("hospital_m", "testdb");
    printf("database have  %i tablecounts",db.tablecounts);

    sqlhelpmap mp;
    definetablevalues(&mp);

    printf("enter table name : \n");
    scanf("%s",tablename);

    createtable(&db, &mp, tablename);

    PQfinish(db.conn);

}