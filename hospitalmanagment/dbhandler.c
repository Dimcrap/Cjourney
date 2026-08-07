#include "dbhandler.h"



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
	return (exists=='t')?1:0;
	
};


//==========================================================================UNFINISHED
void createtable(dbobject * db , char * tablename , map * mp){
	
	
	PGresult *res=PQexec(conn,)

};


map initmap(){
	map mp={
		.margin=0;
	};
	return mp;
}


int getkeyindex(map * mapobj,char key[]){
	for(int i=0; i< mapobj->margin ; i++){
		if(strcmp(key,mapobj->key[i])==0){
			return i;
		}
	}
	return -1;
};


void insertmap(map * mapobj,char key[],char value[],valuetype type){
	int index=getkeyindex(key);
	
	if(index==-1){
			mapobj->key[mapobj->margin]=key;
			mapobj->value[mapobj->margin]=value;
			mapobj->margin++;
			mapobj->type[mapobj->margin]=type;
	}else{
		mapobj->value[index]->=value;
		mapobj->type[index]=type;
	};

};

