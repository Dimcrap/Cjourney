#include "convertors.h"


void insertnumarr(numarr * arr,int value){
	if(arr->count>=arr->lenght){
		arr->length=arr->length*2;
		arr->numbers=reallco(arr->numbers,arr->length);
	}
	arr->numbers[count++]=value;

}


int tobinary(int number){

	int remainder;
	numarr result_arr;

	while(number>0){	
		
		if(number>=1){
		       	insertnumarr(&result_arr,number);
			break;
		}
		insertnumarr(&result_arr,number%2);
		number/=2;
		
		}

	char buff[result_arr.count];
	for(int i=result_arr.count-1,k=0;i>=0;i--,k++){
		buff[k]=result_arr[i];
	}
	buffer[result_arr.count]='\0';
	
	return atoi(buffer);

	}
	
}


int todecimal(int number){};


int tooctal(int number){};


int tohex(int number){};


int definebase(int number){};

