#include "hash_table_value.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

f_list* alloc_flist(const char * String, const int value) // dynamic alloc! String is also dynamically allocated
{
    f_list* temp = (f_list*) malloc(sizeof(f_list));
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
    temp->count = 1;
    temp->next = NULL;
    return temp;
}

bool f_list_clear(f_list *list) // remove all elements
{
    f_list* temp = list;
    while(list != NULL){
        list = list->next;
        destruct_cur_list(temp);
        temp = list;
    }
    return true;
}

void destruct_cur_list(f_list *list){ // destruct the element
    free(list->String);
    free(list);
}

void process_existence(f_list *el, int value) // actions if the element with the same key found
{
    el->value = value;
    el->count += 1;
}


void print_flist(f_list* list){ // print all possible elements
    if(list){
        while(list != NULL){
            printf("Key: %s Counter: %llu\n", list->String, list->count);
            list = list->next;
        }
    }
}

void print_list_el(f_list* el){ // print one element per call
    if(el){
        printf("Key: %s Counter: %llu\n", el->String, el->count);
    }
}

