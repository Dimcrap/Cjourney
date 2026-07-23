#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>


size_t write_callback(void *ptr,size_t size,size_t nmemb,
		void * userdata){

	size_t total_size = size * nmemb;
	//append ptr to buffer
	retur  total_size;
}


void fetch_url(const char *url){
	CURL *curl=curl_easy_init();
	if(curl){
	}
}

