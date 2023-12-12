#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "dictionary.h"

bool file_exists(char *file) {
    return !(access(file, F_OK) == -1);
}

int processOptions(int argc, char **argv, char *fileName, char *singleWord, char **dictionaries, int dictIdx) {

	if (argc < 2) {
		printf("No parameters were inserted\n");
		return 1;
	}
    
    char *currentDir; // Diretoria corrente

    currentDir = getcwd(NULL, 0);

    if (currentDir == NULL) {
        perror("Error getting current working directory");
        free(currentDir);
        return 1;
    }

	int option; // Variável que representa as várias opções da ferramenta 
	char filePath[1024]; // Buffer que guarda o path dos ficheiros

    while ((option = getopt(argc, argv, "t:w:d:")) != -1) {
    	
    	switch (option) {
    	
    		case 't':
    			// Juntar o path da diretoria corrente com o nome do ficheiro 
				snprintf(filePath, sizeof(filePath), "%s/%s", currentDir, optarg);
				// Caso não exista saímos da função 
				if (!file_exists(filePath)) {
					perror("Text file does not exist");
					return 1;
				}
				fileName = strdup(filePath);
				printf("Text file: %s\n", fileName);
				break;
    			
			case 'w':
				// Testar se já foi inserido um ficheiro de palavras
				if (fileName != NULL) {
					perror("You can't use -w and -t simultaneously\n");
					return 1;
				}
				singleWord = strdup(optarg);
				break;

			case 'd':
				// Juntar o path da diretoria corrente com o nome do ficheiro 
    			snprintf(filePath, sizeof(filePath), "%s/%s", currentDir, optarg);
				printf("Dictionary file: %s\n", filePath);
    			// Caso não exista saímos da função 
    			if (!file_exists(filePath)) {
    				perror("Dictionary file does not exist");
    				return 1;
    			}
				// Testar se já foi inserida uma palavra única
				if (singleWord != NULL) {
					perror("You can't use -w and -t simultaneously\n");
					return 1;
				}
    			dictionaries[dictIdx] = strdup(filePath);
    			dictIdx++;
				break;
    	}
    }
    return 0;
}

int populateMap(char **dictionaries, int dictIdx) {
	Dictionary *dictionary = dictionary_create();
	for (int i = 0; i < dictIdx; i++) {
		dictionary_add(dictionary, dictionaries[i]);
	}
}

/*
gcc `pkg-config --cflags glib-2.0` -c dictionary.c -o dictionary.o
gcc `pkg-config --cflags glib-2.0` -c spell_check.c -o spell_check.o
gcc dictionary.o spell_check.o `pkg-config --libs glib-2.0` -o spell_check
*/

int main(int argc, char **argv)
{
	char fileName[64];
	char *singleWord; // Palavra única a ser verificada (-w)
	int maxDictionaries = 3;
	char **dictionaries; // Array de dicionários que vão popular o mapa
	dictionaries = malloc(maxDictionaries * sizeof(char*)); // Alocar memória para o array de dicionários
	int dictIdx = 0;

	processOptions(argc, argv, fileName, singleWord, dictionaries, dictIdx);
	printf("passed processOptions\n");
	printf("fileName in main = %s\n", fileName);

	populateMap(dictionaries, dictIdx);

	printf("%s\n", fileName);
	printf("%s\n", singleWord);
	// printf("%s\n", dictionaries[0]);
	free(dictionaries); // Libertar a memória alocada para o array de dicionários
	return 1;
}