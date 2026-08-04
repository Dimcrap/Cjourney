#include <stdlib.h>
#include <libpq-fe.h>


extern const char * username="hospital_m";
extern const char * dbname=hbase;

typdef struct{
	 PGconn * conn;
	 int tablecounts;
}dbdata;
	

void createtables(PGconn *conn);
void do_exit(PGconn *conn,PGresult *res);
int checktable(PGconn * conn,char * tablename);
void defineDB(PGconn * connobj,PGresult * resultobj);
void insertdb();

/*
int main(){
	
PGconn * conn = PQconnectdb("user=hospital_m  dbname=hospital_m");

if(PQstatus(conn)==CONNECTION_BAD){
	fprintf(stderr,"Conncetion to database failed : %s\n",PQerrorMessages(conn));
	
	PQfinish(conn);
	exit(1);
}


PGresult * res = PQexec(conn, "Dropp IF EXISTS Beds" );

if(PQresultStatus(res)!= PGRES_COMMAND_OK){
	do_exit(conn,res);	
}

PQclear(res);

//res=PQexec(conn,"INSERT INTO Beds VALUES());

};

*/

