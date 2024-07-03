#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <inttypes.h>
#include <stdbool.h>
#include "hash.h"

typedef struct list list;
typedef list** hash_table;
typedef list*** hash_table_ptr;

bool hash_table_insert(hash_table_ptr table_ptr, const uint64_t table_size, const char* key_string,  uint64_t value);

bool hash_table_delete(hash_table table, const uint64_t table_size, const char* const key_string);

uint64_t* hash_table_search(hash_table table, const uint64_t table_size, const char* const key_string);

void hash_table_print(hash_table table, const uint64_t table_size);


#endif