#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
// #include <glib.h>

Dictionary *dictionary_create() {
	Dictionary *dictionary = g_new(Dictionary, 1);
	dictionary->wordset = g_hash_table_new(g_str_hash, g_str_equal);
	return dictionary;
}

void dictionary_add(Dictionary *dictionary, const char *filename) {
	FILE *file;
	char line[32];

	// Open the file 
	file = fopen(filename, "r");

	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	while (fgets(line, sizeof(line), file) != NULL) {		
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}
		g_hash_table_insert(dictionary->wordset, g_strdup(line), GINT_TO_POINTER(1));
	}

	fclose(file);
}

int dictionary_lookup(Dictionary *dictionary, const char *word){
	// Implement using GLib data structures
	return g_hash_table_contains(dictionary->wordset, word);
}

void dictionary_destroy(Dictionary *dictionary) {
	g_hash_table_destroy(dictionary->wordset);
	g_free(dictionary);
}

// extra functions

void print_all_values(gpointer key, gpointer value, gpointer user_data) {
    printf("Key: %s, Value: %d\n", (char*)key, GPOINTER_TO_INT(value));
}

void dictionary_print_all_values(Dictionary *dictionary) {
    g_hash_table_foreach(dictionary->wordset, print_all_values, NULL);
}