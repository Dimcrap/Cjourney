#include <stdlib.h>
#include <libpq-fe.h>

#define MAX_SIZE 100

const char * username=NULL;
const char * dbname=NULL;

typedef struct{
	PGconn * conn;
	int tablecounts;
	int reservedtables;
	int freetables;
}dbobject;

extern dbobject db;//===================need controllls

enum valuetype{
	intger,
	varchar,
	date
};

typedef struct{
char name[MAX_SIZE][100];
int type[MAX_SIZE];
int margin;
}sqlhelpmap;
sqlhelpmap initmap();
int getkeyindex(char key[]);
void insertmap(sqlhelpmap * mapobj,char name[],valuetype type);
void makeline(char * buffer,char name,valuetype);


void createtable(dbobject * db,sqlhelpmap * mapobj);
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

