#include <stdlib.h>
#include <libpq-fe.h>

#define MAX_SIZE 100

extern const char * username=NULL;
extern const char * dbname=NULL;

typedef struct{
	PGconn * conn;
	int tablecounts;
	int reservedtables;
	int freetables;
}dbobject;

extern dbobject db;//===================need controllls

enum valuetype{
	int,
	varchar,
	date
}

typedef struct{
char key[MAX_SIZE];
char value[MAX_SIZE];
int type[MAX_SIZE];
int margin;
}map;
map initmap();
int getkeyindex(char key[]);
void insertmap(map * mapobj,char key[],char value[],valuetype type);



void createtable(dbobject * db,map * mapobj);
void do_exit(PGconn *conn,PGresult * res);
int checktable(PGconn * conn,char * tablename);
void defineDB(char * username,char * dbname);
void insertdb();
void definetablevalues();




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

