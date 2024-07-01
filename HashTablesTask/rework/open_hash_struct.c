#include "open_hash_struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

open_struct* alloc_open_stuct(const char *String, const uint64_t value)
{
    open_struct* temp = (open_struct*) malloc(sizeof(open_struct));
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
    temp->was_deleted = false;
    return temp;
}

void open_struct_clear(open_struct *list)
{
    if(list != NULL){
        if(list->String != NULL)
            free(list->String);
         free(list);
    }
}

void print_open_struct(open_struct *el)
{
    if(el){
        printf("Key: %s Value: %llu\n", el->String, el->value);
    }
}
