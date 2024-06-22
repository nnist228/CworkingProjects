#include <stdio.h>
#include "list_hash.h"
#include "open_hash.h"
#include <stdlib.h>
#include <string.h>

// enum HASH_ {Open_t, List_t};

void test_list_hash_table(const char* const);
void test_open_hash_table(const char* const);

int main(int argc, char** argv){
    // enum HASH_ t = Open_t;
    // if(argc == 2 || (argc > 2 && strcmp(argv[1], "--help") == 0)){
    //     if(strcmp(argv[1], "--help") == 0){
    //         fprintf(stdout, "First argument: file path (absolute or relative)\n");
    //         fprintf(stdout, "Second argument: hashing type (--open-adressing or --separate-chaining), can be skipped (--open-adressing by default)\n");
    //         exit(EXIT_SUCCESS);
    //     }
    //     test_open_hash_table(argv[1]);
    // } else{
    //     if(argc == 3){
    //         if(strcmp(argv[2], "--open-adressing") == 0){
    //             test_open_hash_table(argv[1]);
    //         }
    //         else if(strcmp(argv[2], "--separate-chaining") == 0){
    //             test_list_hash_table(argv[1]);
    //         } else{
    //             fprintf(stderr, "Wrong hashing type argument! use --help\n");
    //             exit(EXIT_FAILURE);
    //         }
    //     } else{
    //         fprintf(stderr, "Wrong args number! use --help\n");
    //         exit(EXIT_FAILURE);
    //     }
    // }

    test_open_hash_table("Text");

    return 0;
}

void test_list_hash_table(const char* file_name)
{
    FILE* src_file;
    src_file = fopen(file_name, "r");
    if(!src_file){
        fprintf(stderr, "File %s can not be opened\n", file_name);
        exit(EXIT_FAILURE);
    }
    char* String;
    list_hash_table table = create_list_hash_table();
    uint64_t size = SIZE_L_TABLE;
    while(fscanf(src_file, "%s", String) != EOF){
        list_hash_table_insert(table, size, String, 0);
    }
    fclose(src_file);
    printf("Separate chaining Hash Table Test\n");
    print_list_hash_table(table, size);
}

void test_open_hash_table(const char* file_name)
{
    
    FILE* src_file;
    src_file = fopen(file_name, "r");
    if(!src_file){
        fprintf(stderr, "File %s can not be opened\n", file_name);
        exit(EXIT_FAILURE);
    }
    char* String;
    list_hash_table table = create_open_hash_table();
    uint64_t size = SIZE_O_TABLE;
     while(fscanf(src_file, "%s", String) != EOF){
        ohash_table_insert(table, size, String, 0);
    }
    fclose(src_file);
    printf("Open addressing Hash Table Test\n");
    open_hash_table_print(table, size);
}
