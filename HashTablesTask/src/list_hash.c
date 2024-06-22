#include "list_hash.h"
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

enum PURPORSE{FOR_DEL, FOR_INSERT, FOR_SEARCH}; // for special serach function
static uint64_t El_count = 0; // counter for elements stored in the table

f_list* special_search(f_list** table, const uint64_t hash, const char *const String, enum PURPORSE purporse); 

bool list_hash_table_insert(f_list** table, const uint64_t size,  const char * String,  int value) // inserting a new element
{                                                                                                  // false if memory alloc problems
    const uint64_t index = hash_function(size, String);
    f_list* table_el = special_search(table, index, String, FOR_INSERT);
    if(table_el == NULL){
        f_list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        table[index] = temp;
        ++El_count;
        return true;
    }
    if(strcmp(table_el->String, String) == 0){
        process_existence(table_el, value);
    } else{
        f_list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        table_el->next = temp;
        ++El_count;
    }
    return true;
}

bool list_hash_table_el_delete(f_list **table, const uint64_t size, const char *const String) // removing an element
{
    const uint64_t index = hash_function(size, String);
    f_list* table_el = special_search(table, index, String, FOR_DEL);
    if(table_el == NULL){
        return false;
    }
    f_list* temp = table_el->next->next;
    destruct_cur_list(table_el->next);
    table_el->next = temp;
    --El_count;
    return true;
}

bool list_hash_table_el_check(f_list **table, const uint64_t size, const char *const String) // true if el exists else false
{
    const uint64_t index = hash_function(size, String);
    f_list* table_el = special_search(table, index, String, FOR_SEARCH);
    if(table_el != NULL){
        return true;
    }
    return false;
}

uint64_t list_hash_table_el_count(f_list **table, const uint64_t size, const char *const String) // print counter for the el with String key
{
    const uint64_t index = hash_function(size, String);
    f_list* table_el = special_search(table, index, String, FOR_SEARCH);
      if(table_el != NULL){
        return table_el->count;
    }
    return 0;
}

f_list* special_search(f_list** table, const uint64_t hash, const char *const String, enum PURPORSE purporse)
{
    f_list* element = table[hash];
    if(element == NULL){
        return NULL;
    }
    f_list* prev = element;
    switch(purporse){
        case FOR_DEL:
            goto DEL;
        break;
        case FOR_INSERT:
            goto INS;
        break;   
        case FOR_SEARCH:
            goto SEARCH;
        break;
        default: 
            goto SEARCH;
        break;
    }
    DEL: // returns prev or NULL
        while(element != NULL){
            if(strcmp(element->String,String) == 0){
                return prev;
            }
            prev = element;
            element = element->next;
        }
        return NULL;
    INS: // returns last or with the same key
        while(element->next != NULL){
            if(strcmp(element->String, String) == 0){
                return element;
            }
            element = element->next;
        }
        return element;
    SEARCH: // returns with the same key or NULL
        while(element != NULL){
            if(strcmp(element->String, String) == 0){
                return element;
            }
            element = element->next;
        }
        return NULL;
}


f_list** list_hash_table_restruct(f_list **table, uint64_t *size) // restruction if needed, size will be changed if needed
{
    if(list_hash_table_restruction_check(*size)){
        f_list **temp = (f_list **) malloc((*size * 2 + 1) * sizeof(f_list*));
        for(uint64_t i = 0; i < *size; ++i){
            f_list_clear(table[i]);
        }
        free(table);
        table = temp;
        *size = *size * 2 + 1;
        El_count = 0;
        return table;
    }
    return NULL;
}

bool list_hash_table_restruction_check(const uint64_t size) // true if needed else false
{
    long double a = (long double) El_count / (long double) size;
    bool r = fabsl(a - 3. / 4.) > DBL_EPSILON;
    return r;
}

f_list **create_list_hash_table() // table creation 
{
    f_list** temp = (f_list**) calloc(SIZE_L_TABLE, sizeof(f_list*));
    return temp;
}

void print_list_hash_table(f_list **table, const uint64_t size) // print hash table in format Key: Counter: 
{                                                               // no value, see print_flist
    for(uint64_t i = 0; i < size; i++){
        if(table[i]){
            print_flist(table[i]);
        }
    }
}
