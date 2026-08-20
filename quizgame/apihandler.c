#include "apihandler.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>





size_t write_callback(void *ptr,size_t size,size_t nmemb,
		FILE * stream){

	size_t written= fwrite(ptr, size, nmemb, stream);			
	return  written;
}


int initcurl(curlticket * ticket){

    ticket->result= curl_global_init( CURL_GLOBAL_ALL );

    if(ticket->result != CURLE_OK){
		fprintf(stderr,"curl_global_init failed: %s\n",
			curl_easy_strerror(ticket->result));
		return (int) ticket->result;
	}

	
	    ticket->curl = curl_easy_init();
		if(!ticket->curl){
			fprintf(stderr,"curl_easy_intit failed!\n");
			return -1;
		};
	return 1;
};


void fetchurl(curlticket * ticket,char * url){
	curl_easy_setopt(
				ticket->curl , CURLOPT_URL, url);
	curl_easy_setopt(ticket->curl, CURLOPT_WRITEFUNCTION
		, write_callback);
};


void writeoutput(char filepath[],curlticket * ticket){
	FILE * file=fopen(filepath, "wb");

	curl_easy_setopt(ticket->curl, CURLOPT_WRITEDATA, file);

	ticket->result = curl_easy_perform(ticket->curl);
				
				if ( ticket->result != CURLE_OK ) {
					fprintf(stderr, "curl_easy_platform() failed: %s\n",
						curl_easy_strerror(ticket->result));
				};

				fclose(file);
};


void cleanups(curlticket * ticket){
	curl_easy_cleanup(ticket->curl);
    curl_global_cleanup();
};


void fetchheader(curlticket * ticket,char * header){
struct curl_slist * headers=NULL;
headers=curl_slist_append(headers, header);


curl_easy_setopt(ticket->curl,CURLOPT_HTTPHEADER,
	 headers);

};


