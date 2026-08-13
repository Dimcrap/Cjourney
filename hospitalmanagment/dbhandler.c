#include "dbhandler.h"
#include <stdlib.h>
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
		//rintf("count result in intitdatabasee: %s \n",count_str);
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
		if(i==(mapobj->margin)-1){
			offset+=snprintf(sql+offset, sizeof(sql)-offset, " %s %s "  ,
			mapobj->name[i],getstrtype(mapobj->type[i]));	
		}else{
			offset+=snprintf(sql+offset, sizeof(sql)-offset, " %s %s ," ,
			mapobj->name[i],getstrtype(mapobj->type[i]));
		}
		
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
			strcpy(mapobj->name[mapobj -> margin],name);
			mapobj->type[mapobj->margin] = type;
			mapobj->margin++;

	}else{

		strcpy(mapobj->name[index],name);
		mapobj->type[mapobj->margin] = type;
		mapobj->type[index]=type;

	};

};



char *getstrtype(enum valuetype type){
	return (type==0)?"INT":(type==1)?"VARCHAR(64)":"DATE";
};


enum valuetype getenumtype(char * str){
	return  (strcmp(str, "date")==2 ) ? 2:(strcmp(str, "integer")==0)? 0:1 ;
};


sqlhelpmap  gettablecolumns(dbobject * db , char table[]){
	char sql[96]="SELECT column_name,data_type FROM information_schema.columns WHERE table_name=";
	snprintf(sql+78, sizeof(sql)-87, "'%s' ;", table);
	sqlhelpmap  resultmap=initmap();
	
	PGresult *res =PQexec(db->conn, sql);
	

	if(PQresultStatus(res)==PGRES_TUPLES_OK){
		
		int row=PQntuples(res);
		int col=PQnfields(res);

		if(row<=0)
		{
			printf("no table data found!\n");
			return resultmap;
		};


		for(int i=0; i<row ; i++){
			for(int k=0; k < col ; k+=2){

				insertmap(&resultmap, PQgetvalue(res, i, k), 
				getenumtype(PQgetvalue(res, i, k+1) ) );

			};
		};

		

			
	}else{
		fprintf(stderr, "Query failed : %s ", PQerrorMessage(db->conn));
	};

	PQclear(res);
	return  resultmap;
};


void definetablevalues(sqlhelpmap * m_map){

	char input[64];
	int vtype=0;

	while(strcmp(input,"/q")!=0){
		printf("\ninsert column name (enter /q to exit): ");
		scanf("%s", input);

		if(strcmp(input,"/q")!=0){
			printf("enter column data type \n1-Integer \n2-Varchar \n3-Date:\n");
			scanf("%d",&vtype);
			if(vtype>3 || vtype<1)
			{
				printf("unvalid data type inputed\n");
				
			}else{
				insertmap(m_map, input,vtype-1);
			};
		};

	};
    
};


char * defineinsertsql(dbobject * db,char table[]){
	static char result[128];
	int offset=0,intinput;
	char input[64];


	offset+=snprintf(result, sizeof(result),"INSERT INTO %s (",table);
	sqlhelpmap tableinfo=gettablecolumns(db,table);
	
	
	for( int i= 0 ; i<tableinfo.margin ; i++ ){
		if(i==(tableinfo.margin-1)){
			offset+=snprintf(result+offset, sizeof(result)-offset,
		 "%s) VALUES(", tableinfo.name[i]);	
		}else{
			offset+=snprintf(result+offset, sizeof(result)-offset,
			 "%s, ", tableinfo.name[i]);
		}
	}


	for (int i=0 ; i < tableinfo.margin ; i++ )
	{	
		printf("row %d structure = name:%s type:%s \n\nenter value for it :\n",
			i,tableinfo.name[i],getstrtype( tableinfo.type[i]) );
		//(strcmp( getstrtype(tableinfo.type[i]),"INT")==0)? scanf("");
			(  strcmp(getstrtype(tableinfo.type[i]),"INT")==0)?
			scanf("%d",&intinput):scanf("%s",input);

			if(strcmp(getstrtype(tableinfo.type[i]),"INT")!=0){
				if(i==tableinfo.margin-1){
					offset+=snprintf(result+offset, sizeof(result)-offset,
					"'%s'",input);
				}else{
					offset+=snprintf(result+offset, sizeof(result)-offset,
					"'%s' , ",input);
				};
			}else{
				if(i==tableinfo.margin){
					offset+=snprintf(result+offset, sizeof(result)-offset,
					"%d ",intinput);
				}else{
					offset+=snprintf(result+offset, sizeof(result)-offset,
					"%d , ",intinput);
				};
			}
	};

	offset+=snprintf(result+offset, sizeof(result)-offset,");");
	return result;
};


void insertdata(dbobject *db,char table[]){
	if(!checktable(db->conn, table)){
		printf("table %s not exists\n",table);
	}else{
		char  *sql = defineinsertsql(db, table);
		PGresult *res =PQexec(db->conn, sql);
		if(PQresultStatus(res)!=PGRES_COMMAND_OK){
			do_exit(db->conn, res);
		};	
	};

};



