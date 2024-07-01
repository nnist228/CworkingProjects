#ifndef OPEN_HASH_STRUCT_H
#define OPEN_HASH_STRUCT_H
#include <stdbool.h>
#include <inttypes.h>

struct open_struct{
    char* String; 
    uint64_t value; 
    bool was_deleted;
};
typedef struct open_struct open_struct;


open_struct* alloc_open_stuct(const char* String, const uint64_t value);

void open_struct_clear(open_struct* list);

void print_open_struct(open_struct* el);


#endif