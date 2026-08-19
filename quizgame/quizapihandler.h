#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





size_t write_callback(void *ptr,size_t size,size_t nmemb,
		FILE * stream);

int initcurl();