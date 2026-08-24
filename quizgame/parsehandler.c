#include "parsehandler.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char menupath[16];
char quizespath[16];
int lastquiz;




void initparserpaths(){

strcpy(menupath,"menu.json");
strcpy(quizespath, "quiz.json");
lastquiz=0;

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
                    "id");
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
                        
                       //cJSON_Delete(data_array);
                    }else{
                        printf("not data in json object\n");
                    }
                    
    }
    cJSON_Delete(json);
    
};


void extract_quiz(){
    /*
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
*/

};


int countkeyword( cJSON * dataarray , char key[] ){
    
        int count=0;
        if(cJSON_IsArray(dataarray)){
                cJSON * item= NULL;
                
                cJSON_ArrayForEach(item,dataarray){
                    
                if(cJSON_IsString(cJSON_GetObjectItemCaseSensitive(item,
                     key))){
                    
                    count++;
                     };
                };

        };
        
        return count;
    
}


void pickaquiz(quiz * qz){
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

    
    if(cJSON_IsFalse(success)){
        printf("pickquiz function quiz api loading failed!\n");   
    }else{
        
        cJSON * data_array = cJSON_GetObjectItemCaseSensitive(
            json,"data");
        
        
        int count=countkeyword(data_array, "quizId")-1;
        if(count<=1){
            printf("\t\tNo quiz founded\n");
        }else{
            
        cJSON * item = NULL ;
        int round=0;

        cJSON_ArrayForEach(item , data_array){
           
            if(lastquiz==count){
                printf("all questions asked! \n");
                break;
            }

            if(  round >= lastquiz && count >= round ){
                cJSON * quiztext=cJSON_GetObjectItemCaseSensitive(
                    item, "text" );
                cJSON * explanation=cJSON_GetObjectItemCaseSensitive(
                    item, "explanation" );
                cJSON * difficulty=cJSON_GetObjectItemCaseSensitive(
                    item, "difficulty" );
                cJSON * answerarr= cJSON_GetObjectItemCaseSensitive(
                    item, "answers" );
                
                
                snprintf(qz -> question, sizeof( qz -> question ),
                "%s", quiztext->valuestring );
                snprintf(qz -> explenatin, sizeof( qz -> explenatin ),
                "%s", explanation->valuestring );
                snprintf(qz -> difficulity, sizeof( qz -> difficulity ),
                "%s", difficulty->valuestring );
                
                
                extractanswers( answerarr , qz );
                

                lastquiz++;
                break;
            }

            round++;
        }

        } 
    }

    cJSON_Delete(json);
    
};


void extractanswers(cJSON * answersarray,quiz * quizinfo){

    cJSON * item=NULL;
    int indx=0;

    cJSON_ArrayForEach( item , answersarray ){
        cJSON * answertext=cJSON_GetObjectItemCaseSensitive(
            item , "text");

            strcpy(quizinfo->answers[indx],answertext->valuestring);
            if(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(item, "isCorrect"))){
                quizinfo->trueindex=indx;
            }
        indx++;
    }


};


char * extractrandom_catid(){
    
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

    cJSON * success=cJSON_GetObjectItemCaseSensitive(json,
         "success");
         
    int indx=0;
    static char catgId[10][75]={0};

    if(!cJSON_IsTrue(success)){
        printf("menu api loading failed!\n");   
    }else{

        cJSON * data_array = cJSON_GetObjectItemCaseSensitive(json,
            "data");
            

            if(cJSON_IsArray(data_array)){
                cJSON * item= NULL;
                
                cJSON_ArrayForEach(item,data_array){
                    
                cJSON * Id= cJSON_GetObjectItemCaseSensitive(item,
                    "id");
                                 
                        if(Id->string == NULL){
                            printf("no quiz id founded for %s!\n", Id->valuestring );
                        }else{
                            strcpy(catgId[indx++],Id->valuestring); 
                        }
                }              
            }


        cJSON_Delete(json);
    };
    //printf("catgory %s",  );

    
    return catgId[rand() % (--indx-0+1)+0];

};

