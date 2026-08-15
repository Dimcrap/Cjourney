#include "dbhandler.h"
#include <libpq-fe.h>



int main(){

    char tablename[32];

    dbobject db = initdatabase("hospital_m", "hospital_m");
    //printf("database have %i tablecounts",db.tablecounts);
    
    //insertdata(&db, "hospital");


    datapair data= get_table_data(&db, "hospital");

    for(int i =0 ; i < data.indx ; i++){
        printf("key : %s  value:%s \n",data.key[i],data.value[i]);
    }
    
    PQfinish(db.conn);

}



/*
hospital -id -name -bedcount -rate -availablebeds -reserved/using beds
-patients count     

bed  -id -hospitalid -rate -inuse 

patient -id -hospitalid -bedid  -interndate

*/