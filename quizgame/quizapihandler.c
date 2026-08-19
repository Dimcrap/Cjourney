#include "quizapihandler.h"
#include <curl/curl.h>




typedef struct {
		CURL * curl;
		CURLcode result;
		FILE * file;
} curlticket ;



size_t write_callback(void *ptr,size_t size,size_t nmemb,
		FILE * stream){

	size_t written= fwrite(ptr, size, nmemb, stream);			
	return  written;
}



int initcurl(){
    
    curlticket ticket;

    curl_global_init( CURL_GLOBAL_ALL );

    if(ticket.result != CURLE_OK)
		return (int) ticket.result;
	
	    curl = curl_easy_init();


};