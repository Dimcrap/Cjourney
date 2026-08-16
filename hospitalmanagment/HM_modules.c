#include "HM_modules.h"
#include "dbhandler.h"
#include <cstdio>
#include <string.h>




void initHM(){
	db=initdatabase("hospital_m", "hospital");
	datapair pair = get_table_data(&db, "hospital");
	int count=0;


	for(int i=0; i< pair.indx ; i++ ){
		if(strcmp(pair.key[i], "name")==0){
			strcpy( hospitals[count++] , pair.value[i] );
		};
	};
	db.tablecounts=count;

};



void interface(){
	
	int input;
	printf("============managment menu============\n"
		"1-Reservation\n2-Documentary\n3-all hospitals\n");
	scanf("%i",&input);
	switch(input){
		case 1:
			reservation();
		case 2:
			documentary();
		case 3:
			indexhospitals();
		default:
			printf("\n unvalid input!\n");
			interface();
	}
	
};



void indexhospitals(){
	for (int i=0 ; i < db.tablecounts ;i++){
		printf(" %d : %s\n",i,hospitals[i]);
	};

	char select;
	printf("enter m to go main screen:\n");
	scanf("%c",&select);
	while(select!='m' || select!='M'){
		printf("unvalid input :\nenter 'm' to go main screen:");
	}
	interface();
};


void reservation(){

	char sql[64];
	int pickup,offset;

	printf("select option \n1-resrve bed\n2-register patient\n");
	scanf("%d",&pickup);
	while(pickup >2 || pickup <1){
		printf("unvalid input !\nselect option \n1-reserve bed\n2-register patient\n");
		scanf("%d",&pickup);
	}

	if(pickup==1){
		offset+=snprintf(sql, sizeof(sql), "INSERT INTO bed(id,hospital_id"
		",rate,inuse) VALUES(");
	}else{
		offset+=snprintf(sql, sizeof(sql), "INSERT INTO patient(");
	}


	printf("\n\t==========resrevation==========\nselect hosptial for process:\n");
	for(int i=0 ; i < db.hospitalscount ; i++){
			printf("%d: %s \n",i+1,hospitals[i]);
	}
	scanf("%d",&pickup);
	


}


void documentary(){

};