#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int h_id[4]={1,2,3,4};


int genrandom(int min,int max);
void gendate(char * result);


void insert_bed(PGconn * conn , int id , int hospital_id , 
    int rate , char *inuse );
void insert_patient(PGconn * conn,int  id,int hospital_id,
    int bedid,char *date);



int main(){

    srand(time(NULL));
int bedid=891;
//891
PGconn * conn = PQconnectdb("user=hospital_m dbname=hospital_m");


for(int i=0 ; i < 90 ; i++){
    if(i<=10){
        //insert_bed(conn, bedid++ , 4, 2, "TRUE");
        insert_bed(conn, bedid++ , 3, 2, "FALSE");
    }else if( i < 60 && i > 10 ){
        //insert_bed(conn, bedid++ , 4, 3, "TRUE");
        insert_bed(conn, bedid++ , 3, 5, "FALSE");
    }else if(i >=60 && i < 80){
        insert_bed(conn, bedid++ , 3, 2, "FALSE");
        //insert_bed(conn, bedid++ , 4, 2, "TRUE");
}else{
    insert_bed(conn, bedid++ , 3, 2, "FALSE");
    //insert_bed(conn, bedid++ , 4, 4, "TRUE");
};
};


/*
int bedid2 =771;
char date[10];
gendate(date);
for( int i = 319 ; i < 410 ; i++ ){
    gendate(date);
    insert_patient(conn , i, 3 , bedid2++ , date );
};*/

/*
char date[10];
gendate(date);
insert_patient(conn, 297, 2 ,708 ,date );
*/

PQfinish(conn);

};


int genrandom(int min,int max){
    return  min +( rand() % (max-min+1));
     
};


void insert_bed(PGconn * conn,int id,int hospital_id,int rate,char *inuse){
char sql[120];
int offset=snprintf(sql, sizeof(sql),
"INSERT INTO bed (id,hospital_id,rate,inuse) VALUES('%d','%d','%d','%s');",
id,hospital_id,rate,inuse);


PGresult * res=PQexec(conn, sql);

if(PQresultStatus(res)!=PGRES_COMMAND_OK){
    fprintf(stderr, "%s\n",PQresultErrorMessage(res));
};

PQclear(res);

};


void gendate(char * res){
    char result[64];
    FILE * fp=popen("date +%Y", "r");
    fgets(result, sizeof(result),fp);
    int curryear=atoi(result);
    
    fp=popen("date +%m", "r");
    fgets(result, sizeof(result),fp);
    int currmonth=atoi(result);

    fp=popen("date +%d", "r");
    fgets(result, sizeof(result),fp);
    int currday=atoi(result);

    curryear-=genrandom(0, 4);
    
    int random=genrandom(1, 12);
    currmonth-=(currmonth-random<0 && currmonth-random!=0)?(currmonth-random) * -1 :
    (currmonth-random<0 && currmonth-random==0) ? currmonth - random + 1 * -1:currmonth-random;

    random=genrandom(1, 29);
    currday-=(currday-random<0 && currday-random!=0)?(currday-random) * -1 :
    (currday-random<0 && currday-random==0) ? currday - random + 1 * -1:currday-random;

    //printf("day value is %d:\n",currday);
    snprintf(res, 10, "%d-%d-%d",
    curryear,currday,currmonth);

};

void insert_patient(PGconn * conn,int  id,int hospital_id,int bedid,char *date){
    char sql[90];
    snprintf(sql, sizeof(sql), "INSERT INTO patient (id,hospital_id"
        ",bedid,interndate) VALUES(%d,%d,%d, '%s');",id,hospital_id,bedid,date);
    
    PGresult * res=PQexec(conn, sql);
    if(PQresultStatus(res)!=PGRES_COMMAND_OK){
        fprintf(stderr, "%s", PQresultErrorMessage(res));
    }
};


/*
id |  name  | beds | rate | freebed | reservedbed | patients 
----+--------+------+------+---------+-------------+----------
1 | atrin  |  300 |    6 |     200 |           0 |      100
2 | Arshin |  260 |    7 |     100 |          20 |      140
3 | Afra   |  190 |    7 |      90 |          20 |       80
4 | Parto  |  200 |    5 |     100 |          10 |       90
*/
