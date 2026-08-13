#include "HM_modules.h"


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
	//get all hosptials data
	//show the list of them 
};


void reservation(){
	//show bed ranks
	//rerve bed 

}


void documentary(){

};