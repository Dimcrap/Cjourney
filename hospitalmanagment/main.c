#include "HM_modules.h"
#include <libpq-fe.h>
#include <stdlib.h>
#include <stdio.h>

void do_exit(PGconn *conn){
	PQfinish(conn);
	exit(1);
};


int main(){

	PGconn * conn = PQconnectdb("user=hospitalManagement password=qwe123  dbname=testdb");
	
	if(PQstatus(conn) == CONNECTION_BAD){
		
		fprintf(stderr, "Connection to database failed : %s\n",
			PQerrorMessage(conn));
		do_exit(conn);
	}

		
	char * user = PQuser(conn);
	char *db_name = PQdb(conn);
	char *paswd = PQpass(conn);
	
	printf("User : %s\n",user);
	printf("Database name: %s\n",db_name);
	printf("Password: %s\n",paswd);
	
	int lib_var=PQlibVersion();
	printf("Version oflibpq: %d \n",lib_var);

	PQfinish(conn);

	return 0;
}
