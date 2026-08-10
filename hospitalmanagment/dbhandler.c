#include "dbhandler.h"
#include <string.h>
#include <libpq-fe.h>
#include <stdio.h>




void do_exit(PGconn * conn,PGresult * res){
	
	fprintf(stderr,"%s\n",PQerrorMessage(conn));
	
	PQclear(res);
	PQfinish(conn);

	exit(1);

};



dbobject initdatabase(char username[],char dbname[]){
	
	char info[64];
	snprintf(info, sizeof(info), "user=%s dbname=%s",username,dbname);
	dbobject db={
		.conn=PQconnectdb(info)
	};

	PGresult * res=PQexec(db.conn,"SELECT count(*) FROM information_schema.tables " 
							"WHERE table_schema NOT IN ('information_schema', 'pg_catalog');");
	if(PQresultStatus(res) == PGRES_TUPLES_OK){
		
		if( PQntuples(res) > 0 ){
		char * count_str = PQgetvalue(res, 0, 0);
		printf("count result in intitdatabasee: %s \n",count_str);
		 db.tablecounts=atoi(count_str);			
		}

	}else{
		fprintf(stderr, "Query failed : %s",PQerrorMessage(db.conn));	
	}

	
	return db;
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



void createtable(dbobject * db,sqlhelpmap * mapobj , char * tablename){
	
	char sql[256] ;
	int offset=0;

	offset+=snprintf(sql,sizeof(sql), "CREATE TABLE %s (", tablename);

	char line[64];
	for(int i=0 ; i < mapobj->margin ; i++ ){
		offset+=snprintf(sql+offset, sizeof(sql)-offset, "%s %s"  ,
		mapobj->name[i],getstrtype(mapobj->type[i]));
		
	}
	snprintf(sql+offset, sizeof(sql)-offset,"%s", " );");
	PGresult *res=PQexec(db->conn,sql);
	if(PQresultStatus(res)!= PGRES_COMMAND_OK){
	do_exit(db->conn,res);	
}
	db->tablecounts++;
};



sqlhelpmap initmap(){
	sqlhelpmap mp={
		.margin=0
	};
	return mp;
}


int getkeyindex(sqlhelpmap * mapobj,char key[]){
	for( int i=0 ; i< mapobj->margin ; i++ ){
		if(strcmp(key,mapobj->name[i])==0){
			return i;
		}
	}
	return -1;
};


void insertmap(sqlhelpmap * mapobj,char name[],enum valuetype type){
	int index=getkeyindex(mapobj,name);
	
	if(index==-1){
			strcpy(mapobj->name[mapobj->margin],name);
			mapobj->type[mapobj->margin] = type;
			mapobj->margin++;

	}else{

		strcpy(mapobj->name[index],name);
		mapobj->type[mapobj->margin] = type;
		mapobj->type[index]=type;

	};

};


char *getstrtype(enum valuetype type){
	return (type==0)?"INT":(type==2)?"VARCHAR(64)":"DATE";
};


void definetablevalues(sqlhelpmap * m_map){

	char input[64];
	int vtype=0;

	while(strcmp(input,"/q")!=0){
		printf("\ninsert column name (enter /q to exit): ");
		scanf("%s", input);

		if(strcmp(input,"/q")!=0){
			printf("enter column data type 1-Integer \n2-Varchar \n3-Date:");
			scanf("%d",vtype);
			insertmap(m_map, input,vtype);
		};

	};
    
};

