#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "hash_table.h"
#include <string.h>

struct State{
    open_hash_table table; 
    uint64_t size;
    char* String;
    int value;
};

static int setup(void** state){
    struct State* s = (struct State*) malloc(sizeof(struct State));
    s->table = NULL;
    s->size = TABLE_SIZE;
    s->String = (char*) malloc(sizeof(char) * strlen("Alex"));
    s->value = 1;
    if(s->String == NULL){
        return -1;
    }
    strcpy(s->String, "Alex");
    *state = s;
    return 0;
}

static int teardown(void** state){
    struct State* s = (struct State*) (*state);
    for(uint64_t i = 0; i < s->size; ++i){
            if(s->table[i] != NULL){
                open_struct_clear(s->table[i]);  
            }  
        }
    free(s->table);
    return 0;
}

static void insert_open_single_el_test(void** state){
    struct State* s = (struct State*) (*state);
    open_hash_table_insert(&s->table, s->size, s->String, s->value);
    open_hash_table_el target = open_hash_table_search(s->table, s->size, s->String);
    assert_non_null(s->table);
    assert_non_null(target);
    assert_string_equal(target->String, "Alex");
    assert_int_equal(target->value, 1); 
    assert_true(!(target->was_deleted));

}

static void insert_open_same_multiple_test(void** state){
    struct State* s = (struct State*) (*state);
    for(int i = 1; i <= 1000; i++){
        open_hash_table_insert(&s->table, s->size, s->String, i);
    }
    open_hash_table_el target = open_hash_table_search(s->table, s->size, s->String);
    assert_non_null(s->table);
    assert_non_null(target);
    assert_string_equal(target->String, "Alex");
    assert_int_equal(target->value, 1000);
    assert_true(!(target->was_deleted));
}

static void delete_open_same_multiple_test(void** state){
    insert_open_same_multiple_test(state);
    struct State* s = (struct State*) (*state);
    open_hash_table_delete(s->table, s->size, s->String);
    uint64_t index = hash_function(s->String) % s->size;
    open_hash_table_el target = open_hash_table_search(s->table, s->size, s->String);
    assert_null(target);
    assert_non_null(s->table);
    assert_non_null(s->table[index]);
    assert_string_equal(s->table[index]->String, "Alex");
    assert_int_equal(s->table[index]->value, 1000);
    assert_true(s->table[index]->was_deleted);
}




int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(insert_open_single_el_test, setup, teardown),
        cmocka_unit_test_setup_teardown(insert_open_same_multiple_test, setup, teardown),
        cmocka_unit_test_setup_teardown(delete_open_same_multiple_test, setup, teardown)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
