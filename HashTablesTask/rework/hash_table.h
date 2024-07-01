#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <inttypes.h>
#include "forward_list.h"
#include "open_hash_struct.h"
#include "hash.h"
#include <stdbool.h>
#define TABLE_SIZE 175499
#define list_hash_table f_list**
#define list_hash_table_el f_list*
#define open_hash_table open_struct**
#define open_hash_table_el open_struct*

bool list_hash_table_insert(list_hash_table* table, const uint64_t size, const char* String,  uint64_t value);

bool list_hash_table_delete(list_hash_table table, const uint64_t size, const char* const String);

list_hash_table_el list_hash_table_search(list_hash_table table, const uint64_t size, const char* const String);

bool open_hash_table_insert(open_hash_table* table, const uint64_t size, const char* String,  uint64_t value);

bool open_hash_table_delete(open_hash_table table, const uint64_t size, const char* const String);

open_hash_table_el open_hash_table_search(open_hash_table table, const uint64_t size, const char* const String);

void open_hash_table_print(open_hash_table table, const uint64_t size);

void list_hash_table_print(list_hash_table table, const uint64_t size);


#endif