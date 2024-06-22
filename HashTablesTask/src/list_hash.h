#ifndef LIST_HASH_H
#define LIST_HASH_H
#include <inttypes.h>
#include "hash_table_value.h"
#include "hash.h"
#include <stdbool.h>
#define SIZE_L_TABLE 175499
#define list_hash_table f_list**

bool list_hash_table_insert(f_list** table, const uint64_t size,  const char *  String,  int value);

bool list_hash_table_el_delete(f_list **table, const uint64_t size, const char *const String);

bool list_hash_table_el_check(f_list **table, const uint64_t size, const char *const String);

uint64_t list_hash_table_el_count(f_list **table, const uint64_t size, const char *const String);

f_list** list_hash_table_restruct(f_list **table, uint64_t *size);

bool list_hash_table_restruction_check(const uint64_t size);

f_list **create_list_hash_table();

void print_list_hash_table(f_list **table, const uint64_t size);



#endif