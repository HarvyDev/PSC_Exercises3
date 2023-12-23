#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <limits.h>
#include <glib.h>
#include <ctype.h>
#include "dictionary.h"


bool file_exists(char *file) {
    return !(access(file, F_OK) == -1);
}

int processOptions(int argc, char **argv, char **fileName, char **singleWord, char **dictionaries, int dictIdx, int maxDictionaries) {
    if (argc < 2) {
        printf("No parameters were inserted\n");
        return 1;
    }

    char currentDir[1024]; // Diretoria corrente

    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("Error getting current working directory");
        return 1;
    }

    int option; // Variável que representa as várias opções da ferramenta 
    char filePath[PATH_MAX]; // Buffer que guarda o path dos ficheiros

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

				// Testar se já foi inserida uma palavra única
				if (*singleWord != NULL) {
					perror("You can't use -w and -t simultaneously\n");
					return 1;
				}

				*fileName = strdup(filePath);
				


				break;
			case 'w':
				// Testar se já foi inserido um ficheiro de palavras
				if (*fileName != NULL) {
					perror("You can't use -w and -t simultaneously\n");
					return 1;
				}
				
				*singleWord = strdup(optarg);
				break;

			case 'd':
				// Juntar o path da diretoria corrente com o nome do ficheiro 
				snprintf(filePath, sizeof(filePath), "%s/%s", currentDir, optarg);

				// Caso não exista saímos da função 
				if (!file_exists(filePath)) {
					perror("Dictionary file does not exist");
					return 1;
				}

				if (dictIdx < maxDictionaries) {
					dictionaries[dictIdx] = strdup(filePath);
					dictIdx++;
				} else {
					perror("You can't use more than 3 dictionaries\n");
					return 1;
				}
				break;
			}	
	}
	if (fileName == NULL && singleWord == NULL) {
		perror("You must insert a text file or a single word\n");
		return 1;
	}
    return 0;
}

Dictionary *populateMap(char **dictionaries, int dictIdx) {
    Dictionary *dictionary = dictionary_create();
    for (int i = 0; i < dictIdx; i++) {
        dictionary_add(dictionary, dictionaries[i]);
    }
	return dictionary;
}

// Define a struct que possui a informação da posição
typedef struct {
    size_t line;
    size_t column;
} Position;

// Vai criar a posição de inicio da palavra mal escrita
Position getPosition(size_t line, size_t column){
    Position pos;
    pos.line;
    pos.column;
    return pos;
}

// Testa se um character é alfanumerico
int isAlphanumeric(char c){
    return isalpha(c) || isdigit(c);
}


void *spellCheckFile(Dictionary *dictionary, char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	char *line = NULL;
	size_t len = 0;
	size_t read;
    size_t currentLine = 1;

	while ((read = getline(&line, &len, file)) != -1) {
        size_t currentColumn = 1;
		char *token = strtok(line, " ");
		while (token != NULL) {
            char *word = token;
            char *punctuation = NULL;

            for(size_t i = 0; i < strlen(token); i++){
                if(!isAlphanumeric(token[i])){
                    word[i] = '\0';
                    punctuation = &token[i];
                    break;
                }
            }

			if (!dictionary_lookup(dictionary, word)) {
                Position pos = getPosition(currentLine, currentColumn);
				printf("Word misspelled: '%s' at [ %zu , %zu ]", word, pos.line, pos.column);
			}
			token = strtok(NULL, " ");
            currentColumn += strlen(token);
		}
        currentLine++;
	}

	fclose(file);
	if (line) {
		free(line);
	}
	return 0;
}

bool spellCheckWord(Dictionary *dictionary, char *word) {
	return dictionary_lookup(dictionary, word);
}
	
int main(int argc, char **argv) {
    char *fileName = NULL;
    char *singleWord = NULL;
    int maxDictionaries = 3;
    char *dictionaries[maxDictionaries]; // Array de dicionários que vão popular o mapa
    int dictIdx = 0;

    processOptions(argc, argv, &fileName, &singleWord, dictionaries, dictIdx, maxDictionaries);

	Dictionary *dictionary = populateMap(dictionaries, dictIdx);

	if (fileName != NULL) {
		spellCheckFile(dictionary, fileName);
	}
	else {
		spellCheckWord(dictionary, singleWord);
	}

	free(fileName);
	free(singleWord);

    return 1;
}
