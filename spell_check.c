#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

bool file_exists(char *file) {
    return !(access(file, F_OK) == -1);
}

int processOptions(int argc, char **argv) {

	if (argc < 2) {
		printf("No parameters were inserted\n");
		return 1;
	}

    
    char *fileName; // Nome do ficheiro 
    char *currentDir; // Diretoria corrente

    currentDir = getcwd(NULL, 0);

    if (currentDir == NULL) {
        perror("Error getting current working directory");
        free(currentDir);
        return 1;
    }

	int option; // Variável que representa as várias opções da ferramenta 
	char filePath[1024]; // Buffer que guarda o path dos ficheiros
	
	
	int maxDictionaries = 3;
	char **dictionaries; // Array de dicionários que vão popular o mapa
	dictionaries = char( **)malloc(maxDictionaries * sizeof(char *));
	int dictIdx = 0;

    while ((option = getopt(argc, argv, "t:w:d")) != -1) {
    	
    	switch (option) {
    	
    		case 't':
    			// Juntar o path da diretoria corrente com o nome do ficheiro 
    			snprintf(filePath, sizeof(filePath), "%s/%s", currentDir, optarg);
    			// Caso não exista saímos da função 
    			if (!file_exists(optarg)) {
    				perror("Dictionary file does not exist");
    				return 1;
    			}
    			dictionaries[dictIdx] = filePath;
    			dictIdx++;
    			break;	
    			
			case 'w':

				break;

			case 'd':

				break; 

    	}
    }

    return 0;
}

int main(int argc, char **argv)
{
	processOptions(argc, argv);
	return 1;
}