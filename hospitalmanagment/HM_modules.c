#include "HM_modules.h"


void interface(){
	
	int input;
	printf("============managment menu============\n"
		"1-Reservation\n2-Documentary\n3-");
	scanf("%i",&input);
	switch(input){
		case 1:
			reservation();
		case 2:
			documentary();
		default:

	}
	
	
};


void reservation(){
	//show bed ranks
	//rerve bed 
	

}


void documentary(){

};