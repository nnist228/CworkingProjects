#ifndef HASH_TABLE_VALUE_H
#define HASH_TABLE_VALUE_H
#include <stdbool.h>
#include <inttypes.h>

struct f_list {
    char* String; // String, dynamic alloc!
    int value; 
    uint64_t count; // counter for counting elements with the same key
    struct f_list* next; // next list element or tombstone element for open hashing (deletion flag)
};

typedef struct f_list f_list;


f_list* alloc_flist(const char* String, const int value);

bool f_list_clear(f_list* list);

void destruct_cur_list(f_list *list);

void process_existence(f_list* el, int value);

void print_flist(f_list* list);

void print_list_el(f_list* el);

#endif