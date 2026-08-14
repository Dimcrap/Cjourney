#pragma once

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


/*===========database data pair============*/
typedef struct{
	char key[20][MAX_SIZE];
	char value[20][MAX_SIZE];
	int indx;
} datapair;
void insert_data_pair(datapair * pairobj,char key[],char value[]);
datapair get_table_data(dbobject * db,char tablename[]);
int getcolnames( dbobject * db , char tablename[],char buff[20][MAX_SIZE]);



enum valuetype{
	intger,
	varchar,
	date,
	boolean
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



/*======================== SEEK INTO && MODIFY  DATABASE ================================*/
void createtable(dbobject * db,sqlhelpmap * mapobj,char * tablename);
void do_exit(PGconn *conn,PGresult * res);
int checktable(PGconn * conn,char * tablename);
void definetablevalues(sqlhelpmap * m_map);
/*=============================================================================*/



void insertdata(dbobject * db,char tablename[]);
char * defineinsertsql(dbobject * db,char table[]);	



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

