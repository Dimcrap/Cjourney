#include "HM_modules.h"
#include "dbhandler.h"
#include <libpq-fe.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



dbobject db;
char hospitals[10][MAX_SIZE];



void initHM(){
	db=initdatabase("hospital_m", "hospital_m");
	datapair pair = get_table_data(&db, "hospital");
	int count=0;


	for(int i=0; i< pair.indx ; i++ ){
		if(strcmp(pair.key[i], "name")==0){
			strcpy( hospitals[count++] , pair.value[i]);
		};
	};

	db.hospitalscount=count;
	db.lastbed_id=getlastrowid(db.conn,"bed");
	db.lastpatient_id=getlastrowid(db.conn,"patient");

};


void interface(){
	
	int input;
	printf("============managment menu============\n"
		"1-Reservation\n2-Documentary\n3-all hospitals\n");
	scanf("%i",&input);
	switch(input){
		case 1:
			reservation();
			break;
		case 2:
			documentary();
			break;
		case 3:
			indexhospitals();
			break;
		default:
			printf("\n unvalid input!\n");
			interface();
	}
	
};


void indexhospitals(){
	for (int i=0 ; i <= db.tablecounts ;i++){
		printf(" %d : %s\n",i+1,hospitals[i]);
	};

	char select;
	printf("going to main screen...\n");
	unsigned int retime=time(0)+5;
	while(time(0)<retime);
	/*printf("enter m to go main screen:\n");
	scanf("%c",&select);
	
	while(select!='m' || select!='M'){
		printf("unvalid input :\nenter 'm' to go main screen:");
		scanf("%c",&select);
	}*/
	interface();
};


void reservation(){

	char sql[130];
	int pickup,offset,rate,showID;

	printf("select option \n1-reserve bed\n2-register patient\n");
	scanf("%d",&pickup);
	while(pickup >2 || pickup <1){
		printf("unvalid input !\nselect option \n1-reserve bed\n2-register patient\n");
		scanf("%d",&pickup);
	}

	if(pickup==1){
		
		offset+=snprintf(sql, sizeof(sql), "UPDATE  bed SET inuse=TRUE WHERE id=");
	}else{
		
		offset+=snprintf(sql, sizeof(sql), "INSERT INTO patient(id,hospital_id,bedid,"
		"interndate) VALUES(");
	};

	for( int i=0 ; i < db.hospitalscount ; i++ ){
		printf("%d: %s \n",i+1,hospitals[i]);
	}
	printf("\n\tselect hosptial for process:\n");
	scanf("%d",&pickup);

	while( pickup > db.hospitalscount || pickup < 1 ){
		printf("unvalid input!\nselect hosptial for process:\n");
		for( int i=0 ; i < db.hospitalscount ; i++ ){
			printf(" %d: %s \n",i+1,hospitals[i]);
		};	
		scanf("%d",&pickup);	
	};

	rate=definebedrate(db.conn,pickup);
	printf("rate defined : %d\n",rate);

	if ( offset < 53 ){
		
		showID=selectbedby_id(db.conn, pickup, rate);
		snprintf(sql+offset,sizeof(sql)-offset,"%d AND hospital_id=%d ;",
		showID,pickup);
		
	}else{

		snprintf(sql+offset,sizeof(sql)-offset,"%d,%d,'%s');",
		++db.lastpatient_id,pickup,gen_current_date());
		showID=db.lastpatient_id;
	};
	
	printf("sql command exectuted just fine :%s\n",sql);
	PGresult * res=PQexec(db.conn, sql);
	if(PQresultStatus(res)!=PGRES_COMMAND_OK){
		fprintf(stderr, "Error: %s",PQresultErrorMessage(res));
	}

	PQclear(res);
	printf("registeration compeleted \n  check id : %d\n",showID);
}


void documentary(){
	printf("will be deveoped - - -\n");
	interface();
};

