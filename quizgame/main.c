#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t write_callback(void *ptr,size_t size,size_t nmemb,
		void * userdata){

	size_t total_size = size * nmemb;
	//append ptr to buffer
	return  total_size;
}


void fetch_url(const char *url){
	CURL *curl=curl_easy_init();
	if(curl){
	}
}



int main(){
		CURL * curl;
		CURLcode result=curl_global_init(CURL_GLOBAL_ALL);
		if(result!= CURLE_OK)
			return (int) result;

		curl = curl_easy_init();
		if(curl){
			curl_easy_setopt(
			curl , CURLOPT_URL, "wttr.in/China?format=3");
			
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION , 1L);


			result = curl_easy_perform(curl);
			if(result != CURLE_OK){
				fprintf(stderr, "curl_easy_platform() failed: %s\n",
					 curl_easy_strerror(result));
				}

			curl_easy_cleanup(curl);
		};

		curl_global_cleanup();
}