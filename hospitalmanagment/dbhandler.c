#include "dbhandler.h"

void do_exit(PGconn * conn,PGresult * res){
	
	fprintf(stderr,"%s\n",PQerrorMessage(conn));
	
	PQclear(res);
	PQfinish(conn);

	exit(1);
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


void createtables(PGconn *conn){

};