#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "hash.h"
#include <inttypes.h>
#include <stdbool.h>

typedef struct list list;

bool hash_table_insert(list ***table_ptr, const uint64_t table_size,
                       const char *key_string, uint64_t value);

bool hash_table_delete(list **table, const uint64_t table_size,
                       const char *const key_string);

uint64_t *hash_table_search(list **table, const uint64_t table_size,
                            const char *const key_string);

void hash_table_print(list **table, const uint64_t table_size);

#endif