#include "quizgame.h"



int main(){

    char ids[10][75];
    quiz q;


    initAPP();
    //extract_categories(ids);
    //pickaquiz(&q);
    //printf("%s\n",q.question);
    askquiz();

    gamecleanup();
    return 1;
}