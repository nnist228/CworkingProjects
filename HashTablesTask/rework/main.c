#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char** argv){
    
    if(argc >= 2){
        if(strcmp(argv[1], "--help") == 0){
            fprintf(stdout, "First argument: file path (absolute or relative)\n");
            exit(EXIT_SUCCESS);
        }
    } else{
            fprintf(stderr, "Wrong args number! use --help\n");
            exit(EXIT_FAILURE);
        }

    FILE* src_file = fopen("Text.txt", "r");
     if(!src_file){
        fprintf(stderr, "File %s can not be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    hash_table table = NULL;
    hash_table_ptr table_ptr = &table;
    char string[1024];
    uint64_t size = 1021;
    while(fscanf(src_file, "%1024s", string) != EOF){
        uint64_t* el = hash_table_search(table, size, string);
        if(el == NULL){
            hash_table_insert(table_ptr, size, string, 1);
        } else{
            *el += 1;
        }
    }

    hash_table_print(table, size);

    return 0;
}
