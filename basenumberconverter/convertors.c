#include "convertors.h"



void insertnumarr(numarr * arr,int value){
	
	if(arr->count>=arr->length){
		arr->length=arr->length*2;
		arr->numbers=realloc(arr->numbers,arr->length*sizeof(2));
//	printf("inserting after allocation \n");
	}
	arr->numbers[arr->count++]=value;
}



numarr make_arr(){
	numarr arr={
	.numbers=malloc(sizeof(int)),
	.count=0,
	.length=1
	};

	return arr;
}



int tobinary(int number){

	int remainder;
	numarr result_arr=make_arr();

	while(number>0){	
		if(number<=1){
		       	insertnumarr(&result_arr,number);
			break;
		}
		insertnumarr(&result_arr,number%2);
		number/=2;
		//printf("number divided :%i \n",number);
		
		}

	char buff[result_arr.count];
	for(int i=result_arr.count-1,k=0;i>=0;i--,k++){
		buff[k]=(result_arr.numbers[i])+'0';
	}
	buff[result_arr.count]='\0';
	free(result_arr.numbers);
	
	return atoi(buff);
	
}



int todecimal(int number){
	

	int result=0,count=0,len=snprintf(NULL,0,"%d",number);	
	char binstring[len];
	sprintf(binstring,"%d",number);	
	

	for(int i=(sizeof(binstring)/sizeof(binstring[0]))-1; i>=0 ; i-- ){
		result+=(binstring[i]-'0')*(int)pow(2,count++);
	}

	
	return result;
};


int tooctal(int number){
	
	numarr arr=make_arr();
	
	while(number>=0){
		
		if(number<8){
			insertnumarr(&arr,number);
			break;
		}

		insertnumarr(&arr,number%8);
		number/=8;
	};
	
	char result[arr.count];
	for(int i=(arr.count)-1,k=0;i>=0;i--,k++){
		printf("number of elements in arr:%d \n current assingment %d\n",arr.count,arr.numbers[i]);
		result[k]=arr.numbers[i]+'0';
	}
	result[arr.count]='\0';

	return atoi(result);
};


int tohex(int number){};


int definebase(int number){};

