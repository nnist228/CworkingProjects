#include "hash_table.h"
#include "string.h"
#include <stdlib.h>
enum PURPORSE{FOR_DEL, FOR_INSERT, FOR_SEARCH}; // for special serach function
// static uint64_t El_count = 0; // counter for elements stored in the table
f_list* special_search(f_list** table, const uint64_t index, const char* const String, enum PURPORSE purporse);
list_hash_table alloc_list_table(const uint64_t size);

bool list_hash_table_insert(list_hash_table* table, const uint64_t size, const char *String, uint64_t value)
{
    if(*table == NULL){
        *table = alloc_list_table(size);
        if(*table == NULL){
            return false;
        }
    }
    const uint64_t index = hash_function(String) % size;
    f_list* table_el = special_search(*table, index, String, FOR_INSERT);
    if(table_el == NULL){
        f_list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        (*table)[index] = temp;
        // ++El_count;
        return true;
    }
    if(strcmp(table_el->String, String) == 0){
        table_el->value = value;
        return true;
    } else{
        f_list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        table_el->next = temp;
        // ++El_count;
        return true;
    }
    return false;
}

bool list_hash_table_delete(list_hash_table table, const uint64_t size, const char *const String)
{
    if(table == NULL){
        return false;
    }
    const uint64_t index = hash_function(String) % size;
    f_list* prev_el = special_search(table, index, String, FOR_DEL);
    if(prev_el == NULL){
        return NULL;
    }
    if(prev_el == table[index]){
        return remove_flist_el(NULL, prev_el);
    }
    return remove_flist_el(prev_el, prev_el->next);
}

list_hash_table_el list_hash_table_search(list_hash_table table, const uint64_t size, const char* const String)
{
    if(table == NULL){
        return NULL;
    }
    const uint64_t index = hash_function(String) % size;
    f_list* table_el = special_search(table, index, String, FOR_SEARCH);
    return table_el;
}

void list_hash_table_print(list_hash_table table, const uint64_t size)
{
    if(table == NULL)
        return;
    for(uint64_t i = 0; i < size; i++){
        if(table[i]){
            print_flist(table[i]);
        }
    }
}


f_list* special_search(f_list** table, const uint64_t index, const char* const String, enum PURPORSE purporse)
{
    f_list* element = table[index];
    if(element == NULL){
        return NULL;
    }
    switch(purporse){
        case FOR_DEL:
            {
                f_list* prev = element;
                while(element != NULL){
                    if(strcmp(element->String,String) == 0){
                        return prev;
                    }
                    prev = element; 
                    element = element->next;
                }
                return NULL;
            }
        break;
        case FOR_INSERT:
            {
                while(element->next != NULL){
                    if(strcmp(element->String, String) == 0){
                        return element;
                    }
                    element = element->next;
                }
                return element;
            }
        break;
        case FOR_SEARCH:
            {
                while(element != NULL){
                    if(strcmp(element->String, String) == 0){
                        return element;
                    }
                    element = element->next;
                }
                return NULL;
            }
        break;
        default:
        return NULL;
    }
}

list_hash_table alloc_list_table(const uint64_t size)
{
    list_hash_table temp = (list_hash_table) malloc(size * sizeof(f_list*));
    return temp;
}


