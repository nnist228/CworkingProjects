#ifdef OPEN_TYPE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"

 struct list{
    char* key_string; 
    uint64_t value; 
    bool was_deleted;
};


static list* alloc_list(const char* String, const uint64_t value);
static void list_delete(list* list);
static void print_list(list* el);




static uint64_t search_pos( list ** table, const uint64_t table_size, const char* const key_string, bool for_insert);
static  list** alloc_open_table(const uint64_t table_size); 


bool hash_table_insert(list*** table_ptr, const uint64_t table_size, const char* key_string,  uint64_t value){
    list** table = *table_ptr;
    if(table == NULL){
        table = alloc_open_table(table_size);
        if(table == NULL){
            return false;
        }
	*table_ptr = table;
    }
    uint64_t index = search_pos(table, table_size, key_string, true); 
    if(table[index] != NULL){  // here only if the el is deleted
        list_delete(table[index]);
    }
    list* temp = alloc_list(key_string, value);
    if(temp == NULL){
        return false;
    }
    table[index] = temp;
    return true;
}

bool hash_table_delete( list** table, const uint64_t table_size, const char* const key_string)
{
    if(table == NULL){
        return false;
    }
    uint64_t index = search_pos(table, table_size, key_string, false);
    if(table[index] == NULL){
        return false;
    }
    free(table[index]->key_string);
    table[index]->key_string = NULL;
    table[index]->was_deleted = true;
    return true;
}

uint64_t* hash_table_search( list** table, const uint64_t table_size, const char* const key_string)
{
    if(table == NULL){
        return NULL;
    }
    uint64_t index = search_pos(table, table_size, key_string, false);
    if(table[index] != NULL)
    return &table[index]->value;
    return NULL;
}

void hash_table_print(list** table, const uint64_t table_size)
{
    if(table == NULL)
        return;
    for(uint64_t i = 0; i < table_size; i++){
        if(table[i]){
            print_list(table[i]);
        }
    }
}

static uint64_t search_pos( list ** table, const uint64_t table_size, const char* const key_string, bool for_insert)
{
    uint64_t index = hash_function(key_string) % table_size; // hashing 
     list * temp = table[index];
    if(temp == NULL){
        return index;
    }
    uint64_t k = 7; // k coef
    for(size_t i = 1; temp != NULL && for_insert ? temp->was_deleted == false : true && i < table_size; i++){
        if(temp->key_string != NULL && strcmp(temp->key_string, key_string) == 0){
            break;
        }
        index += k * i % table_size;  
        temp = table[index];
    }
    return index;
}

static list ** alloc_open_table(const uint64_t table_size)
{
     list ** temp = ( list **) malloc(table_size * sizeof( list*));
    return temp;
}


static list* alloc_list(const char *String, const uint64_t value)
{
    list* temp = (list*) malloc(sizeof(list));
    if(temp == NULL){
        return NULL;
    }
    temp->key_string = (char*) calloc(strlen(String), sizeof(char));
    if(temp->key_string == NULL){
        free(temp);
        return NULL;
    }
    strcpy(temp->key_string, String);
    temp->value = value;
    temp->was_deleted = false;
    return temp;
}

static void list_delete(list* list)
{
    if(list != NULL){
        if(list->key_string != NULL)
            free(list->key_string);
        free(list);
    }
}

static void print_list(list* el)
{
    if(el){
        printf("Key: %s Value: %lu\n", el->key_string, el->value);
    }
}
#endif
