#include "quizapihandler.h"







int main(){
		CURL * curl;
		CURLcode result;
		FILE * file;
		

		curl_global_init(CURL_GLOBAL_ALL);
		
		if(result!= CURLE_OK)
		return (int) result;
	
	    curl = curl_easy_init();
		
		if( curl ){

			file=fopen("curlres.txt", "wb");
			if(!file){
				fprintf(stderr,"Error oponing file!\n");
				return 1;
			};

			
			curl_easy_setopt(
				curl , CURLOPT_URL, "wttr.in/China?format=3");
				//curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION , 1L);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
				
				result = curl_easy_perform(curl);
				
				if(result != CURLE_OK){
					fprintf(stderr, "curl_easy_platform() failed: %s\n",
						curl_easy_strerror(result));
				}
				fclose(file);
				curl_easy_cleanup(curl);

			};


		curl_global_cleanup();
		return 0;
}


