#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char** argv){
    
    if(argc == 2 || (argc > 2 && strcmp(argv[1], "--help") == 0)){
        if(strcmp(argv[1], "--help") == 0){
            fprintf(stdout, "First argument: file path (absolute or relative)\n");
            exit(EXIT_SUCCESS);
        }
    } else{
            fprintf(stderr, "Wrong args number! use --help\n");
            exit(EXIT_FAILURE);
        }

    FILE* src_file;
    src_file = fopen(argv[1], "r");
     if(!src_file){
        fprintf(stderr, "File %s can not be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    list** table = NULL;
    char String[1024];
    uint64_t size = 1021;
    while(fscanf(src_file, "%1024s", String) != EOF){
        uint64_t* el = hash_table_search(table, size, String);
        if(el == NULL){
            hash_table_insert(&table, size, String, 1);
        } else{
            *el += 1;
        }
    }

    hash_table_print(table, size);

    return 0;
}
