#include "dbhandler.h"
#include <stdio.h>



void do_exit(PGconn * conn,PGresult * res){
	
	fprintf(stderr,"%s\n",PQerrorMessage(conn));
	
	PQclear(res);
	PQfinish(conn);

	exit(1);

};


void defineDB(char * username,char * dbname){
	username=username;
	dbname=dbname;
};


int checktable(PGconn * conn,char * tablename){

	char sql[64];

	sprintf(sql,"SELECT EXISTS( SELECT 1 FROM pg_tables WHERE tablename = '%s' );",tablename);
	PGresult *res=PQexec(conn,sql);

	if(PQresultStatus(res)!= PGRES_TUPLES_OK){
	do_exit(conn,res);

	}

	char * exists=PQgetvalue(res,0,0);

	PQclear(res);
	return (*exists=='t')?1:0;
	
};


//==========================================================================UNFINISHED
void createtable(dbobject * db , char * tablename , sqlhelpmap * mp){
	
	char sql[256] ;
	int offset=0;

	offset+=snprintf(sql,sizeof(sql), "CREATE TABLE %s (", tablename);

	for(int i=0 ; i < mp->margin ; i++ ){
		mp->value,mp->type,mp->
		;
	}
	PGresult *res=PQexec(conn,)

};


sqlhelpmap initmap(){
	sqlhelpmap mp={
		.margin=0
	};
	return mp;
}


int getkeyindex(sqlhelpmap * mapobj,char key[]){
	for(int i=0; i< mapobj->margin ; i++){
		if(strcmp(key,mapobj->name[i])==0){
			return i;
		}
	}
	return -1;
};


void insertmap(sqlhelpmap * mapobj,char name[],valuetype type){
	int index=getkeyindex(name);
	
	if(index==-1){
			mapobj->name[mapobj->margin]=name;
			mapobj->type[mapobj->margin]=type;
			mapobj->margin++;

	}else{
		mapobj->name[index]=name;
		mapobj->type[index]=type;
	};

};

