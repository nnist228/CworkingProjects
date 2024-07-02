#ifdef CHAIN_TYPE
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

struct list{
    char* String; // String, dynamic alloc!
    uint64_t value; 
    struct list* next; 
};

static list* alloc_list(const char* String, const int value);

static bool remove_list_el(list* prev, list* el);

static void list_clear(list* list);

static void destruct_cur_list(list *list);

static void print_list(list* list);

static void print_list_el(list* el);


enum PURPORSE{FOR_DEL, FOR_INSERT, FOR_SEARCH}; // for special serach function

static list* special_search(list** table, const uint64_t index, const char* const String, enum PURPORSE purporse);
static list** alloc_list_table(const uint64_t size);

bool list_hash_table_insert(list*** table_ptr, const uint64_t size, const char *String, uint64_t value)
{
    list** table = *table;
    if(table == NULL){
        table = alloc_list_table(size);
        if(table == NULL){
            return false;
        }
    }
    const uint64_t index = hash_function(String) % size;
    list* table_el = special_search(table, index, String, FOR_INSERT);
    if(table_el == NULL){
        list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        table[index] = temp;
        // ++El_count;
        return true;
    }
    if(strcmp(table_el->String, String) == 0){
        table_el->value = value;
        return true;
    } else{
        list* temp = alloc_flist(String, value);
        if(temp == NULL){
            return false;
        }
        table_el->next = temp;
        return true;
    }
    return false;
}

bool list_hash_table_delete(list** table, const uint64_t size, const char *const String)
{
    if(table == NULL){
        return false;
    }
    const uint64_t index = hash_function(String) % size;
    list* prev_el = special_search(table, index, String, FOR_DEL);
    if(prev_el == NULL){
        return NULL;
    }
    if(prev_el == table[index]){
        return remove_flist_el(NULL, prev_el);
    }
    return remove_flist_el(prev_el, prev_el->next);
}

uint64_t* list_hash_table_search(list** table, const uint64_t size, const char* const String)
{
    if(table == NULL){
        return NULL;
    }
    const uint64_t index = hash_function(String) % size;
    list* table_el = special_search(table, index, String, FOR_SEARCH);
    if(table_el != NULL)
    return &table_el->value;
    return NULL;
}

void list_hash_table_print(list** table, const uint64_t size)
{
    if(table == NULL)
        return;
    for(uint64_t i = 0; i < size; i++){
        if(table[i]){
            print_flist(table[i]);
        }
    }
}


list* special_search(list** table, const uint64_t index, const char* const String, enum PURPORSE purporse)
{
    list* element = table[index];
    if(element == NULL){
        return NULL;
    }
    switch(purporse){
        case FOR_DEL:
            {
                list* prev = element;
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

list** alloc_list_table(const uint64_t size)
{
    list** temp = (list**) malloc(size * sizeof(list*));
    return temp;
}


list* alloc_list(const char * String, const int value) // dynamic alloc! String is also dynamically allocated
{
    list* temp = (list*) malloc(sizeof(list));
    if(temp == NULL){
        return NULL;
    }
    temp->String = (char*) calloc(strlen(String), sizeof(char));
    if(temp->String == NULL){
        free(temp);
        return NULL;
    }
    strcpy(temp->String, String);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

bool remove_list_el(list *prev, list* el)
{   
    if(el == NULL){
       return false; 
    }
    if(prev == NULL){
        destruct_cur_list(el);
        return true;
    }
    if(prev->next == el){
        list* temp = el->next;
        destruct_cur_list(el);
        prev->next = temp;
        return true;
    }
    return false;
}

void list_clear(list *el) // remove all elements
{
    list* temp = el;
    while(el != NULL){
        el = el->next;
        destruct_cur_list(temp);
        temp = el;
    }
}

void destruct_cur_list(list *list){ // destruct the element
    if(list != NULL){
        if(list->String != NULL)
            free(list->String);
         free(list);
    }
}

void print_flist(list* list){ // print all possible elements
    if(list){
        while(list != NULL){
            printf("Key: %s Value: %llu\n", list->String, list->value);
            list = list->next;
        }
    }
}

void print_list_el(list* el){ // print one element per call
    if(el){
        printf("Key: %s Value: %llu\n", el->String, el->value);
    }
}

#endif