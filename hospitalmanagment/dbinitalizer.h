#include <stdlib.h>
#include <libpq-fe.h>



void createtables(){};
void do_exit();

int main(){

PGconn * conn = PQconnectdb("user=hospitalManagement  dbname=testdb");

	if(PQstatus(conn)==CONNECTION_BAD){
		fprintf(stderr,"Conncetion to database failed : %s\n",PQerrorMessages(conn));
		
		PQfinish(conn);
		exit(1);
	}
	
	
	PGresult * res = PQexec(conn, "Dropp IF EXISTS Beds" );
	
	if(PQresultStatus

}



void do_exit(PGconn * conn,PGresult * res){
	
	fprintf(stderr,"%s\n",PQerrorMessage(conn));
	
	PQclear(res);
	PQfinish(conn);

	exit(1);
}
