#include <stdio.h>
#include "convertors.h"


int main(){

int number=tobinary(150);

printf("number is %i \n",number);

int todec=todecimal(number);
printf("result of todecimal: %i \n",todec);

}
