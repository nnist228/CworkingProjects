#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"

static list** alloc_table(const uint64_t size);
static list* alloc_list(const char* string, const uint64_t value);
static void print_list(list* el);
static void el_delete(list* el);

#ifdef OPEN_TYPE
 struct list{
    char* key_string; 
    uint64_t value; 
    bool was_deleted;
};

static uint64_t search_pos(list ** table, const uint64_t table_size, const char* const key_string, bool for_insert);

bool hash_table_insert(list*** table_ptr, const uint64_t table_size, const char* key_string,  uint64_t value){
    list** table = *table_ptr;
    if(table == NULL){
        table = alloc_table(table_size);
        if(table == NULL){
            return false;
        }
        *table_ptr = table;
    }
    uint64_t index = search_pos(table, table_size, key_string, true); 
    if(table[index] != NULL){  // here only if the el is deleted
        if(table[index]->was_deleted){
            table[index]->key_string = (char*) malloc(sizeof(char) * strlen(key_string));
            if(table[index]->key_string == NULL)
                return false;
            table[index]->value = value;
            table[index]->was_deleted = false;
        } else{
            table[index]->value = value;
        }
        return true;
    }
    list* temp = alloc_list(key_string, value);
    if(temp == NULL){
        return false;
    }
    table[index] = temp;
    return true;
}

bool hash_table_delete(list** table, const uint64_t table_size, const char* const key_string)
{
    if(table == NULL){
        return false;
    }
    uint64_t index = search_pos(table, table_size, key_string, false);
    if(table[index] == NULL){
        return false;
    } 
    el_delete(table[index]);
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


static uint64_t search_pos( list ** table, const uint64_t table_size, const char* const key_string, bool for_insert)
{
    uint64_t index = hash_function(key_string) % table_size; // hashing 
     list * temp = table[index];
    if(temp == NULL){
        return index;
    }
    uint64_t k = 7; // k coef
    for(size_t i = 1; temp != NULL && (for_insert ? temp->was_deleted == false : true) && i < table_size; i++){
        if(temp->key_string != NULL && strcmp(temp->key_string, key_string) == 0){
            break;
        }
        index += k * i % table_size;  
        temp = table[index];
    }
    return index;
}

static list* alloc_list(const char *string, const uint64_t value)
{
    list* temp = (list*) malloc(sizeof(list));
    if(temp == NULL){
        return NULL;
    }
    temp->key_string = (char*) calloc(strlen(string), sizeof(char));
    if(temp->key_string == NULL){
        free(temp);
        return NULL;
    }
    strcpy(temp->key_string, string);
    temp->value = value;
    temp->was_deleted = false;
    return temp;
}

 static void el_delete(list *el) // remove all elements
{
    free(el->key_string);
    el->key_string = NULL;
    el->was_deleted = true;
}

#else
    struct list{
        char* key_string; // string, dynamic alloc!
        uint64_t value; 
        struct list* next; 
        struct list* prev;
    };

    static void list_delete(list *list);
    static list* special_search(list** table, const uint64_t index, const char* const string, bool for_insert);

    bool hash_table_insert(list*** table_ptr, const uint64_t table_size, const char *key_string, uint64_t value)
    {
        list** table = *table_ptr;
        if(table == NULL){
            table = alloc_table(table_size);
            if(table == NULL){
                return false;
            }
            *table_ptr = table;
        }
        const uint64_t index = hash_function(key_string) % table_size;
        list* table_el = special_search(table, index, key_string, true);
        if(table_el == NULL){
            list* temp = alloc_list(key_string, value);
            if(temp == NULL){
                return false;
            }
            table[index] = temp;
            return true;
        }
        if(strcmp(table_el->key_string, key_string) == 0){
            table_el->value = value;
            return true;
        } else{
            list* temp = alloc_list(key_string, value);
            if(temp == NULL){
                return false;
            }
            table_el->next = temp;
            temp->prev = table_el;
            return true;
        }
        return false;
    }

    bool hash_table_delete(list** table, const uint64_t table_size, const char *const key_string)
    {
        if(table == NULL){
            return false;
        }
        const uint64_t index = hash_function(key_string) % table_size;
        list* el = special_search(table, index, key_string, false);
        if(el == NULL){
            return false;
        }
        el_delete(el);
        return true;
    }

    uint64_t* hash_table_search(list** table, const uint64_t table_size, const char* const key_string)
    {
        if(table == NULL){
            return NULL;
        }
        const uint64_t index = hash_function(key_string) % table_size;
        list* table_el = special_search(table, index, key_string, false);
        if(table_el != NULL)
        {
            if(strcmp(table_el->key_string, key_string) == 0)
                return &table_el->value;
        }
        return NULL;
    }

    static list* special_search(list** table, const uint64_t index, const char* const string, bool for_insert)
    {
        list* element = table[index];
        if(element == NULL){
            return NULL;
        }
       if(for_insert){
             while(element->next != NULL){
                if(strcmp(element->key_string, string) == 0){
                    return element;
                }
                element = element->next;
            }
            return element;
        } else{
             while(element != NULL){
                if(strcmp(element->key_string,string) == 0){
                    return element;
                }
                element = element->next;
            }
            return NULL;
        }
    }

    static list* alloc_list(const char * string, const uint64_t value) // dynamic alloc! string is also dynamically allocated
    {
        list* temp = (list*) malloc(sizeof(list));
        if(temp == NULL){
            return NULL;
        }
        temp->key_string = (char*) calloc(strlen(string), sizeof(char));
        if(temp->key_string == NULL){
            free(temp);
            return NULL;
        }
        strcpy(temp->key_string, string);
        temp->value = value;
        temp->next = NULL;
        temp->prev = NULL;
        return temp;
    }

    static void el_delete(list* el)
    {   
        if(el->next != NULL){
            el->next->prev = el->prev;
        }
        if(el->prev != NULL){
            el->prev->next = el->next;
        } 
        free(el->key_string);
        free(el);
    }

    static void list_delete(list *el) // remove all elements
    {
        list* temp = el;
        while(el != NULL){
            el = el->next;
            free(temp->key_string);
            free(temp);
            temp = el;
        }
    }
#endif


static list** alloc_table(const uint64_t size)
{
    list** temp = (list**) malloc(size * sizeof(list*));
    return temp;
}


static void print_list(list* el){ // print one element per call
        if(el){
            printf("Key: %s Value: %llu\n", el->key_string, el->value);
        }
    }

void hash_table_print(list** table, const uint64_t size)
    {
        if(table == NULL)
            return;
        for(uint64_t i = 0; i < size; i++){
            print_list(table[i]);
        }
    }

