#include <stdio.h>

typdef struct{
int * numbers=NULL;
int count=0;
int length=1;
}numarr;


void insertnumarr(numarr * arr,int value);
int tobinary(int number);
int todecimal(int number);
int tooctal(int number);
int tohex(int number);
int definebase(int number);
