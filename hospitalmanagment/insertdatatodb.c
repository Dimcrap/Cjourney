#include <libpq-fe.h>
#include <stdlib.h>
#include <time.h>


int h_id[4]={1,2,3,4};


int genrandom(int min,int max);





int main(){

    int result=genrandom(0, 4);
    printf("result: %d\n",result);

     result=genrandom(0, 4);
    printf("result: %d\n",result);

     result=genrandom(0, 4);
    printf("result: %d\n",result);

};


int genrandom(int min,int max){
    
    srand(time(NULL));

    //int rd = rand_r(&seed) % (max-min+1)+ min;
    int rd = min +( rand() % (min-max+1));
     return rd;
};



/*
id |  name  | beds | rate | freebed | reservedbed | patients 
----+--------+------+------+---------+-------------+----------
1 | atrin  |  300 |    6 |     200 |           0 |      100
2 | Arshin |  260 |    7 |     100 |          20 |      140
3 | Afra   |  190 |    7 |      90 |          20 |       80
4 | Parto  |  200 |    5 |     100 |          10 |       90
*/
