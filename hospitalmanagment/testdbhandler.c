#include "dbhandler.h"
#include <stdio.h>
#include <libpq-fe.h>



int main(){

    char tablename[32];

    dbobject db = initdatabase("hospital_m", "hospital_m");
    //printf("database have %i tablecounts",db.tablecounts);
    
    /*
    sqlhelpmap mp=gettablecolumns(&db, "prof");
    definetablevalues(&mp);

    

    printf("enter table name : \n");
    scanf("%s",tablename);

    createtable(&db, &mp, tablename);*/
    /*for( int i=0 ; i < mp.margin ; i++ ){
        printf("value name is  %s type is %s \n", mp.name[i],getstrtype( mp.type[i]));
    };*/

    //insertdata(&db, "prof");


    printf("something is not working");
    PQfinish(db.conn);

}


/*
hospital -id -name -bedcount -rate -availablebeds -reserved/using beds
-patients count     

bed  -id -hospitalid -rate -inuse 

patient -id -hospitalid -bedid  -interndate

*/