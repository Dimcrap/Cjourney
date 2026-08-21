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


void extract_categories(char  catgeoryId[10][75]){
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

    cJSON * json = cJSON_Parse(buffer);
    //int count=0;

    cJSON * success=cJSON_GetObjectItemCaseSensitive(json,
         "success");

    if(!cJSON_IsTrue(success)){
        printf("menu api loading failed!\n");   
    }else{

        cJSON * data_array = cJSON_GetObjectItemCaseSensitive(json,
            "data");
            char catgId[10][75]={0};
            int indx=0;

            if(cJSON_IsArray(data_array)){
                cJSON * item= NULL;
                
                cJSON_ArrayForEach(item,data_array){
                    cJSON * topic=cJSON_GetObjectItemCaseSensitive(item,
                 "topic");
                 cJSON * difficulty = cJSON_GetObjectItemCaseSensitive(item,
                "difficulty");
                cJSON * Id= cJSON_GetObjectItemCaseSensitive(item,
                    "categoryId");
                    cJSON * name = cJSON_GetObjectItemCaseSensitive(item,
                        "categoryName");
                        
                        
                        if(Id->string == NULL){
                            printf("no quiz id founded for %s!\n", Id->valuestring );
                        }
                        strcpy(catgId[indx++],Id->valuestring); 
                        
                        
                        if(cJSON_IsString(topic)&&cJSON_IsString(difficulty)){
                            printf("%d-%s\n\t %s \t %s \n\n",indx,name->valuestring
                                ,topic->valuestring,difficulty->valuestring);
                            }
                            
                            memcpy(catgeoryId,catgId,sizeof(catgId));
                        }
                        
                        cJSON_Delete(data_array);
                    }else{
                        printf("not data in json object\n");
                    }
                    
                }
    cJSON_Delete(json);
};




void extract_quiz(char cateoryId[10][75]){
    FILE * file=fopen(quizespath,"r");
    if(file == NULL){
        printf("unable to open file %s \n",menupath);
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

    cJSON * json = cJSON_Parse(buffer);
    
    cJSON * success = cJSON_GetObjectItemCaseSensitive(json,
    "success");
        
    if(!cJSON_IsTrue(success)){
        printf("quiz api loading failed!\n");   
    }else{
        cJSON * data_array = cJSON_GetObjectItemCaseSensitive(json,
            "data");

        if(cJSON_IsArray(data_array)){
                cJSON * item= NULL;
                
                cJSON_ArrayForEach(item,data_array){
                    cJSON * explain=cJSON_GetObjectItemCaseSensitive(
                        item,"explanation");
                    cJSON * question=cJSON_GetObjectItemCaseSensitive(
                        item,"text");
                    cJSON * ;
                    

                };



        }else{
            printf("undefined data in quiq.json file\n");
        }


    }
        
    
    cJSON_Delete(json);

};


