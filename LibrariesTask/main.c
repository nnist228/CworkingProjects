#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>


struct MemoryStruct {
  char *memory;
  size_t size;
};

// static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
// {
//   size_t realsize = size * nmemb;
//   struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
//   char *ptr = realloc(mem->memory, mem->size + realsize + 1);
//   if(!ptr) {
//     /* out of memory! */
//     printf("not enough memory (realloc returned NULL)\n");
//     return 0;
//   }
 
//   mem->memory = ptr;
//   memcpy(&(mem->memory[mem->size]), contents, realsize);
//   mem->size += realsize;
//   mem->memory[mem->size] = 0;
 
//   return realsize;
// }

int main(void)
{
  CURL *curl_handle;
  CURLcode res;
 
//   struct MemoryStruct chunk;
 
//   chunk.memory = malloc(1);  /* grown as needed by the realloc above */
//   chunk.size = 0;    /* no data at this point */
 
  FILE* file = fopen("Output.txt", "r+");
  if(!file){
    fprintf(stderr, "File can not be opened\n");
    exit(EXIT_FAILURE);
  }

  curl_global_init(CURL_GLOBAL_ALL);
 

  /* init the curl session */
  curl_handle = curl_easy_init();
 
  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://wttr.in/Moscow?format=j1");
 
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, NULL);

  curl_easy_setopt(curl_handle, CURLOPT_HSTS_CTRL, (long) CURLHSTS_ENABLE);
 
  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*) file);
 
  /* some servers do not like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
//   else {
//     /*
//      * Now, our chunk.memory points to a memory block that is chunk.size
//      * bytes big and contains the remote file.
//      *
//      * Do something nice with it!
//      */
 
//     printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
//   }
 
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
 
//   free(chunk.memory);
fclose(file);
 
  /* we are done with libcurl, so clean it up */
  curl_global_cleanup();
 
  return 0;
}