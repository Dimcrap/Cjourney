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
		//printf("count result in intitdatabasee: %s \n",count_str);
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
	return (type==0)?"INT":(type==1)?"VARCHAR(64)":(type==2)?"DATE":"BOOl";
};


enum valuetype getenumtype(char * str){
	return   (strcmp(str, "integer" ) == 0 )? 0: 
	(strcmp(str, "boolean")==0)?3: strcmp(str, "date")==0 ? 2 : 1 ;
};


sqlhelpmap  gettablecolumns(dbobject * db , char table[]){
	char sql[128]="SELECT column_name,data_type FROM information_schema.columns WHERE table_name=";
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
		fprintf(stderr, "Query failed : %s \n", PQerrorMessage(db->conn));
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
	static char result[256];
	int offset=0,intinput;
	char input[64];


	offset+=snprintf(result, sizeof(result),"INSERT INTO %s (",table);
	sqlhelpmap tableinfo=gettablecolumns(db,table);

	
	for( int i= 0 ; i<tableinfo.margin ; i++ ){
		printf(" type value of %s : %d \n",tableinfo.name[i],tableinfo.type[i]);
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
		printf("row %d structure => name:%s type:%s \n\nenter value for it :\n",
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

void insertdata(dbobject *db,char table[]){	if(!checktable(db->conn, table)){		printf("table %s not exists\n",table);	}else{
		char  *sql = defineinsertsql(db, table);
		PGresult *res =PQexec(db->conn, sql);
		if(PQresultStatus(res)!=PGRES_COMMAND_OK){
			do_exit(db->conn, res);
		};	
		printf("data inserted completely!\n");
	};


};


void insert_data_pair(datapair * pairobj , char key[] , char value[] ){
	strcpy(pairobj->key[pairobj->indx],key);
	strcpy(pairobj->value[pairobj->indx],value);
	pairobj->indx++;
};


int getcolnames( dbobject * db , char tablename[] , char buff[20][MAX_SIZE]){
	char * sql="SELECT column_name FROM information_schema.columns WHERE table_name="
	"'hospital' ORDER BY ordinal_position ASC";

	PGresult * res=PQexec(db->conn, sql);

	if(PQresultStatus(res)==PGRES_TUPLES_OK){

		int row=PQntuples(res);
		if(row>0){
			for (int i = 0 ; i < row ; i++){
				//printf("assingin row%d :%s",i,PQgetvalue(res, i, 0));
				strcpy(buff[i],PQgetvalue(res, i, 0));
			};
		};

		return row;
	}else{
		printf("\n didn't found any table data!\n");
		PQclear(res);
		return -1;
	}

};


datapair get_table_data(dbobject * db,char tablename[]){
	datapair pair={.indx=0};
	char columns[MIN_LENGTH][MAX_SIZE];
	int cols=getcolnames(db,tablename,columns);
	printf("");

	char sql[32];
	snprintf(sql,sizeof(sql),"SELECT * FROM %s ;",tablename);

	PGresult * res=PQexec(db->conn, sql);

	if(PQresultStatus(res)==PGRES_TUPLES_OK){
		int row=PQntuples(res);
			if( row > 0 ){

				for(int i = 0 ; i < row ; i++){
					for(int j=0 ; j < cols ; j++){
						insert_data_pair(&pair, columns[j],
							PQgetvalue(res, i, j));
					};
				}
			}else{
				printf("\ntable is empty\n");
				return pair;
		}
	}else{
		printf("\ncould't find out table with info named as :%s\n",tablename);
		PQclear(res);
	};
	return pair;
}


int getlastrowid(PGconn * conn,char tablename[]){
	char sql[64];
	snprintf(sql, sizeof(sql), "SELECT * FROM %s"
	" ORDER BY id DESC LIMIT 1 ;",tablename);

	PGresult * res=PQexec(conn, sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK){
		if(PQntuples(res)>0){
			return atoi(PQgetvalue(res, 0, 0));
		}else{
			printf("no result founded int table %s\n",tablename);
		};
	}else{
		fprintf(stderr, "error: %s",PQresultErrorMessage(res));
	};

	return -1;
	
};


int getextant_bedrates(int * result , PGconn * conn , int hospitalid){
	char sql[74];
	int indx=0;

	snprintf(sql,sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id = %d AND rate = 1 ;",hospitalid);

	//printf("the row have values :%s",PQgetvalue(res, 0, 0));
	PGresult * res= PQexec(conn,sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK && PQntuples(res)>0 ){
		result[indx++]=1;
	}else{
		fprintf(stderr, "%s",PQresultErrorMessage(res));
	}
	
	snprintf(sql,sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id = %d AND  rate = 2 ;",hospitalid);

	res= PQexec(conn,sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK && PQntuples(res)>0 ){
		result[indx++]=2;
	}else{
		fprintf(stderr, "%s",PQresultErrorMessage(res));
	}

	snprintf(sql,sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id = %d AND  rate = 3 ;",hospitalid);

	res= PQexec(conn,sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK && PQntuples(res)>0 ){
		result[indx++]=3;
	}else{
		fprintf(stderr, "%s",PQresultErrorMessage(res));
	}

	snprintf(sql,sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id = %d AND  rate = 4 ;",hospitalid);

	res= PQexec(conn,sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK && PQntuples(res)>0 ){
		result[indx++]=4;
	}else{
		fprintf(stderr, "%s",PQresultErrorMessage(res));
	}

	snprintf(sql,sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id = %d AND rate = 5 ;",hospitalid);

	res= PQexec(conn,sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK && PQntuples(res)>0 ){
		result[indx++]=5;
	}else{
		fprintf(stderr, "%s",PQresultErrorMessage(res));
	}

	PQclear(res);
	return indx-1;
};


int definebedrate(PGconn * conn,int hospital){
	int pickup;
	int availbedrates[6];
	
	int avail_count=getextant_bedrates((int *) availbedrates,
	conn, hospital);
	
	if(avail_count<=0){
		printf("no bed available :%d\n",avail_count);
	}

	for ( int i=0 ; i <= avail_count ; i++ ){
		if(i+1>avail_count){
			printf("%d\n",availbedrates[i]);	
		}else{
			printf("%d",availbedrates[i]);
		};
	};
		printf("pick rate for a bed of hospital :\n");
		
	scanf("%d",&pickup);
	
	while( pickup > avail_count || pickup <= 0 ){
		printf("unvalid input \n");
		for ( int i=0 ; i <= avail_count ; i++ ){
		if(i+i>=avail_count){
		printf("%d\n",availbedrates[i]);	
		}else{
			printf("%d ",availbedrates[i]);
		
		};
		}
		printf("\npick rate for a bed of hospital \n");
		scanf("%d",&pickup);
	};

	
	return pickup;
};


int selectbedby_id(PGconn * conn,int hospital_id,int rate){
	char sql[75];
	snprintf(sql, sizeof(sql), "SELECT * FROM bed WHERE inuse=FALSE AND "
	"hospital_id=%d AND rate=%d LIMIT 1;",hospital_id,rate);
	
	PGresult * res = PQexec(conn, sql);
	if(PQresultStatus(res)==PGRES_TUPLES_OK){
		if(PQntuples(res)>0){
			return atoi(PQgetvalue(res, 0, 0));
		}else{
			printf("didn't found any bed for seleceting!\n");
		};	
	}else {
		fprintf(stderr, "error:%s\n",PQresultErrorMessage(res));
	}
	return -1;
};


char * gen_current_date(){
        time_t now = time(NULL);
        struct tm * t =localtime(&now);
        static char res[16];
        snprintf(res,sizeof(res),"%d-%d-%d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
        return res;
}

