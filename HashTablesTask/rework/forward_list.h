#ifndef HASH_TABLE_VALUE_H
#define HASH_TABLE_VALUE_H
#include <stdbool.h>
#include <inttypes.h>

struct f_list {
    char* String; // String, dynamic alloc!
    uint64_t value; 
    struct f_list* next; 
};
typedef struct f_list f_list;


f_list* alloc_flist(const char* String, const int value);

bool remove_flist_el(f_list* prev, f_list* el);

void f_list_clear(f_list* list);

void destruct_cur_list(f_list *list);

void print_flist(f_list* list);

void print_list_el(f_list* el);

#endif