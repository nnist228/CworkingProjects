#include "forward_list.h"
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
    temp->next = NULL;
    return temp;
}

bool remove_flist_el(f_list *prev, f_list* el)
{   
    if(el == NULL){
       return false; 
    }
    if(prev == NULL){
        destruct_cur_list(el);
        return true;
    }
    if(prev->next == el){
        f_list* temp = el->next;
        destruct_cur_list(el);
        prev->next = temp;
        return true;
    }
    return false;
}

void f_list_clear(f_list *list) // remove all elements
{
    f_list* temp = list;
    while(list != NULL){
        list = list->next;
        destruct_cur_list(temp);
        temp = list;
    }
}

void destruct_cur_list(f_list *list){ // destruct the element
    if(list != NULL){
        if(list->String != NULL)
            free(list->String);
         free(list);
    }
}

void print_flist(f_list* list){ // print all possible elements
    if(list){
        while(list != NULL){
            printf("Key: %s Value: %llu\n", list->String, list->value);
            list = list->next;
        }
    }
}

void print_list_el(f_list* el){ // print one element per call
    if(el){
        printf("Key: %s Value: %llu\n", el->String, el->value);
    }
}

