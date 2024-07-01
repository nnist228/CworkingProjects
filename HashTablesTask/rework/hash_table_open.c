#include "hash_table.h"
#include <string.h>
#include <stdlib.h>
enum PURPORSE{FOR_INSERT, FOR_SEARCH};
uint64_t search_pos(open_hash_table, const uint64_t size, const char* const String, enum PURPORSE purporse);
open_hash_table alloc_open_table(const uint64_t size); 


bool open_hash_table_insert(open_hash_table* table, const uint64_t size, const char* String,  uint64_t value){
    if(*table == NULL){
        *table = alloc_open_table(size);
        if(*table == NULL){
            return false;
        }
    }
    uint64_t index = search_pos(*table, size, String, FOR_INSERT); 
    if((*table)[index] != NULL){  // here only if we find el with the same key or el is deleted or both
        if(strcmp((*table)[index]->String, String) == 0){
            (*table)[index]->value = value;
            (*table)[index]->was_deleted = false;
            return true;
        }
        open_struct_clear((*table)[index]);
    }
    open_hash_table_el temp = alloc_open_stuct(String, value);
    if(temp == NULL){
        return false;
    }
    (*table)[index] = temp;
    return true;
}

bool open_hash_table_delete(open_hash_table table, const uint64_t size, const char* const String)
{
    if(table == NULL){
        return false;
    }
    uint64_t index = search_pos(table, size, String, FOR_SEARCH);
    if(table[index] == NULL){
        return false;
    }
    table[index]->was_deleted = true;
    return true;
}

open_hash_table_el open_hash_table_search(open_hash_table table, const uint64_t size, const char *const String)
{
    if(table == NULL){
        return NULL;
    }
    uint64_t index = search_pos(table, size, String, FOR_SEARCH);
    if(table[index] == NULL || table[index]->was_deleted){
        return NULL;
    }
    return table[index];
}

void open_hash_table_print(open_hash_table table, const uint64_t size)
{
    if(table == NULL)
        return;
    for(uint64_t i = 0; i < size; i++){
        if(table[i]){
            print_open_struct(table[i]);
        }
    }
}

uint64_t search_pos(open_hash_table table, const uint64_t size, const char* const String, enum PURPORSE purporse)
{
    uint64_t index = hash_function(String) % size; // hashing 
    open_hash_table_el temp = table[index];
    if(temp == NULL){
        return index;
    }
    uint64_t k = 7; // k coef
    for(size_t i = 1; temp != NULL && (purporse == FOR_INSERT ? temp->was_deleted == false : true) && strcmp(temp->String, String) != 0 && i < size; i++){
        index += k * i % size;  
        temp = table[index];
    }
    return index;
}

open_hash_table alloc_open_table(const uint64_t size)
{
    open_hash_table temp = (open_hash_table) malloc(size * sizeof(open_struct*));
    return temp;
}