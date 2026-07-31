#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct{
int * numbers;
int count;
int length;
}numarr;


numarr make_arr();		
void insertnumarr(numarr * arr,int value);
int tobinary(int number);
int todecimal(int number);
int tooctal(int number);
int tohex(int number,char * result,int size);
//int definebase(int number);
int countdigits(int number);
int compare( void * a, void * b);
void filldigits(int *numarray,int length,int number); 
void interface();
void printarr(char * arr);
