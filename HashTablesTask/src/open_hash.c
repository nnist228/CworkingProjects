#include "open_hash.h"
#include <string.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

enum PURPORSE{FOR_INSERT, FOR_SEARCH}; // for search_pos function
static uint64_t El_count = 0; // counter for elements stored in the table

uint64_t search_pos(f_list **table, const uint64_t size, const char* const String, enum PURPORSE purporse); // find a pos for inserting
uint64_t NOD(uint64_t n1, uint64_t n2); // greatest common factor calc function


bool ohash_table_insert(f_list** table, const uint64_t size,  const char *  String, int value){ // Function for inserting a new element
    uint64_t index = search_pos(table, size, String, FOR_INSERT);                           // if element exists, count + 1 and values are swapped
    if(table[index] != NULL){  // here only if we find el with the same key or el is deleted or both
        if(strcmp(table[index]->String, String) == 0){
            table[index]->value = value;
            table[index]->count += 1;
            table[index]->next = NULL;
            return true;
        }
        destruct_cur_list(table[index]);
    }
    f_list* temp = alloc_flist(String, value);
    if(temp == NULL){
        return false;
    }
    table[index] = temp;
    ++El_count;
    return true;
}

bool ohash_table_delete(f_list **table, const uint64_t size, const char *const String) // Deletion if element exists (true) else false
{   
    uint64_t index = search_pos(table, size, String, FOR_SEARCH);
    if(table[index] == NULL){
        return false;
    }
    table[index]->count -= 1;
    table[index]->next = (f_list*) 0x1;
    --El_count;
    return true;
}

bool otable_el_exists(f_list **table, const uint64_t size, const char *const String) // True if el exist else false
{
    uint64_t index = search_pos(table, size, String, FOR_SEARCH);
    if(table[index] == NULL){
        return false;
    }
    return true;
}

void open_hash_table_print_el(f_list **table, const uint64_t size, const char *const String) // Print el in format: Key: Counter:
{                                                                                            // Value is not shown, see print_list_el implementation
    uint64_t index = search_pos(table, size, String, FOR_SEARCH);
    if(table[index] != NULL){
        print_list_el(table[index]);
    }
}

uint64_t search_pos(f_list **table, const uint64_t size, const char* const String, enum PURPORSE purporse)
{
    uint64_t hash = hash_function(size, String); // hashing 
    if(table[hash] == NULL){
        return hash;
    }

    static uint64_t k = 1; // k coef
    while(NOD(k, size) > 1){ // k and size should be coprime numbers, size can be changed during restruction
        k /= NOD(k, size);
    }

    f_list* temp = table[hash];
    for(size_t i = 1; temp != NULL && ((purporse == FOR_INSERT) ? (temp->next == NULL) : true) && strcmp(temp->String, String) != 0 && i < size; i++){
        hash += (k*i % size);  
        temp = table[hash];
    }
    return hash;
}

uint64_t NOD(uint64_t a, uint64_t b)
{
    while(a > 0 && b > 0) {     
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a+b;
}

f_list **ohash_table_restruct(f_list **table, uint64_t *size) // restruction if needed based on the loading factor (3/4)
{
    long double a = (long double) El_count / (long double) *size;
    bool need = fabsl(a - 3. / 4.) > DBL_EPSILON;
     if(need){
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

f_list **create_open_hash_table() // table creation
{
    f_list** temp = (f_list**) calloc(SIZE_O_TABLE, sizeof(f_list*));
    return temp;
}


void open_hash_table_print(f_list **table, const uint64_t size) // print all elements in format Key: Counter: 
{                                                               // see print_list_el implementation
    for(uint64_t i = 0; i < size; i++){
        if(table[i]){
            print_list_el(table[i]);
        }
    }
}