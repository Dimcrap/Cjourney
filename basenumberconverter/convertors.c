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



int tohex(int number,char * result,int size){

	int lastindx=0;
	numarr arr=make_arr();
	

	while(number>=16){
		insertnumarr(&arr,number%16);
		lastindx++;
		number/=16;	
		
	}

	insertnumarr(&arr,number);
	
	if((++lastindx)+1>size){
		return -1;
	}

	for(int i=0;i<lastindx;i++)
	{
		
		
		if(arr.numbers[lastindx-1-i]<16&&
		arr.numbers[lastindx-1-i]>9)
		{
			result[i]=arr.numbers[lastindx-1-i]+55;	
		}else{

			result[i]=arr.numbers[lastindx-1-i]+'0';
		}
	}
	result[++lastindx]='\0';
	

	return lastindx;
	
};


int countdigits(int number){
		int count=0;

	while(number>0){
		count++;
		number/=10;
	//	printf("number is changed to :%d\n",number);
	}
	printf("count calculated: %d\n",count);
	return count;
}


/*
int compare(void * a,void * b){
	int * v1=a;
	int * v2=b;
	return *v1-*v2;
}


void fillnumdigits(int * numarr,int length,int number){
	for(int i = 0 ; i < length ; i++){
		//numarr=number%10;
		//numarr=
	}	
}


int definebase(int number){

int length=0,  temp=number,base,per;
while(temp!=0){
	temp/=10;
	length++;
}

int arr[length];

//sprintf(arr,"%ld",number);
arr[length]='\0';

qsort(arr,sizeof(arr)/sizeof(arr[0]),sizeof(arr[0]),compare);

//if((arr[length-1])=<9&&arr[length-1]>

printf("\n");
//if(arr[len;
return 0;
//}


};
*/


void printarr(char *arr){
}



void interface(){

	int userinput,typetoC, intresult,charwrittenlength,allocsize;
	char * charresult;
	printf("======welcome to base number converter======\n\n");
	
	while(true){
	printf("enter you number in decimal :\n");
	scanf("%d",&userinput);

	printf("enter the type you want to convert to (2,8,16):\n");
	scanf("%d",&typetoC);

	switch(typetoC)
	{
		case 16:
			//printf("hello:=");
			allocsize=(countdigits(userinput)+1)*sizeof(char);
		        charresult=malloc(allocsize);
			charwrittenlength=tohex(userinput,charresult,allocsize);
			printf("result to hex is : %.*s \n",--charwrittenlength,charresult);
			free(charresult);	
			break;
		case 8:
			intresult=tooctal(userinput);
			printf("result to octal is : %i\n",intresult);
			break;
		case 2:
			intresult=tobinary(userinput);
			printf("result to binary is : %i\n",intresult);
			break;
		 default:
			printf("inputed base number isn't valid  \n");
		}
		
	}
}




