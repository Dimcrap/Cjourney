#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>


#define MAX_SIZE 100


typedef struct{
	PGconn * conn;
	int tablecounts;
	//int reservedtables;
}dbobject;
dbobject initdatabase(char username[],char dbname[]);


enum valuetype{
	intger,
	varchar,
	date
};
char *getstrtype(enum valuetype type);
enum valuetype getenumtype(char * str);


/*====================================MAP====================================*/
typedef struct{
char name[MAX_SIZE][100];
int type[MAX_SIZE];
int margin;
}sqlhelpmap;
sqlhelpmap initmap();
int getkeyindex(sqlhelpmap * mapobj,char key[]);
void insertmap(sqlhelpmap * mapobj,char name[],enum valuetype type);
sqlhelpmap gettablecolumns(dbobject * db , char table[]);
/*=====================================================================================================*/


void createtable(dbobject * db,sqlhelpmap * mapobj,char * tablename);
void do_exit(PGconn *conn,PGresult * res);
int checktable(PGconn * conn,char * tablename);
void definetablevalues(sqlhelpmap * m_map);


void insertdata(dbobject * db,char tablename[]);
char * defineinsertval(dbobject * db,char table[]);	


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

