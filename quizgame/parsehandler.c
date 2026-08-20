#include "parsehandler.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char menupath[16];
char quizespath[16];



void initparserpaths(){

strcpy(menupath,"menu.json");
strcpy(quizespath, "quiz.json");

};



void extract_categories(){
    FILE * file=fopen(menupath,"r");
    if(file == NULL){
        printf("unnable to open file %s \n",menupath);
    }

    fseek(file, 0, SEEK_END);
    long fsize=ftell(file);
    fseek(file, 0, SEEK_SET);

    char * buffer=malloc(fsize+1);

    if(buffer){
        fread(buffer,1,fsize,file);
        buffer[fsize]= '\0';
    }
    fclose(file);

    cJSON * json = cJSON_Parse(buffer) ;
    

};

