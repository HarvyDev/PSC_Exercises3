
// Unit Test for the functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glib.h>
#include "dictionary.h"


struct CaseTest{
    const char *filename;
    const char *words[3];
};

struct CaseTest cases[3] = {
        {"ex.txt", {"vagina", "joao", "test"}},
        {"test1.txt", {"test", "test1", "test2"}},
        {"test2.txt", {"test", "test1", "test2"}}
};

const char *testWords[] = {"maçã", "karanja", "azul", "ar", "test"};


// Test for dictionary_create
void test_dictionary_create() {
    Dictionary *dictionary = dictionary_create();

    if ( dictionary == NULL || dictionary->wordset == NULL ) {
        printf("Error creating dictionary\n");
    }
    else {
        printf("Dictionary created successfully\n");
    }
    dictionary_destroy(dictionary);
}


// Test for dictionary_lookup
void test_dictionary_lookup() {

    Dictionary *dictionary = dictionary_create();

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++){
        dictionary_add(dictionary,cases[i].filename);

        for (size_t j = 0; j < sizeof(cases[i].words) / sizeof(cases[i].words[0]); j++) {
            const char *word = cases[1].words[j];

            if (dictionary_lookup(dictionary,word) == 1){
                printf("Word '%s' found in the dictionary.\n", word);
            }else{
                printf("Word '%s' not found in the dictionary.\n", word);
            }
        }
    }
    dictionary_destroy(dictionary);
}

// Test for dictionary_add
void test_dictionary_add() {

    Dictionary *dictionary = dictionary_create();

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {

        dictionary_add(dictionary, cases[i].filename);

        for ( size_t j = 0; j < sizeof(cases[i].words) / sizeof(cases[i].words[0]); j++ ) {
            const char *word = cases[i].words[j];

            if ( dictionary_lookup(dictionary, word) == 1 ) {
                printf("Word '%s' found in the dictionary.\n", word);
            }
            else {
                printf("Word '%s' not found in the dictionary.\n", word);
            }

        }
    }
    dictionary_destroy(dictionary);
}

// Test for dictionary_destroy
void test_dictionary_destroy() {
    Dictionary *dictionary = dictionary_create();
    dictionary_destroy(dictionary);
    if ( dictionary == NULL ) {
        printf("Dictionary destroyed successfully\n");
    }
    else {
        printf("Error destroying dictionary\n");
    }
}

// Test for print_all_values
void test_print_all_values() {
    Dictionary *dictionary = dictionary_create();
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        dictionary_add(dictionary, cases[i].filename);
    }
    print_all_values(dictionary);
    dictionary_destroy(dictionary);

}

// Test for dictionary_print_all_values
void test_dictionary_print_all_values() {
    Dictionary *dictionary = dictionary_create();
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        dictionary_add(dictionary, cases[i].filename);
    }
    dictionary_print_all_values(dictionary);
    dictionary_destroy(dictionary);

}

int main(){
    test_dictionary_create();
    test_dictionary_lookup();
    test_dictionary_add();
    test_dictionary_destroy();
    test_print_all_values();
    test_dictionary_print_all_values();
}
