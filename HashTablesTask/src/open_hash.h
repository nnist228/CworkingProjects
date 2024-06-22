#ifndef OPEN_HASH_H
#define OPEN_HASH_H
#include <inttypes.h>
#include "hash_table_value.h"
#include "hash.h"
#include <stdbool.h>
#define SIZE_O_TABLE 175499
#define open_hash_table f_list**

bool ohash_table_insert(f_list** table, const uint64_t size,  const char *  String, int value);

bool ohash_table_delete(f_list** table, const uint64_t size, const char* const String);

bool otable_el_exists(f_list** table, const uint64_t size, const char* const String);

void open_hash_table_print_el(f_list** table, const uint64_t size, const char* const String);

f_list** ohash_table_restruct(f_list **table, uint64_t* size);

f_list** create_open_hash_table();

void open_hash_table_print(f_list** table, const uint64_t size);

#endif