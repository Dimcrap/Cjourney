#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






typedef struct {
		CURL * curl;
		CURLcode result;
		FILE * file;
		
} curlticket ;


size_t write_callback(void *ptr,size_t size,size_t nmemb,
		FILE * stream);


int initcurl(curlticket * ticket);
void fetchurl(curlticket * ticket,char * url);
void fetchheader(curlticket * ticket,char * header);
void writeoutput(char filepath[],curlticket * ticket);
void cleanups(curlticket * ticket);

