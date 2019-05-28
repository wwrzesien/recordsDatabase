#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "structures.h"
#include "function.h"
#include "shell.h"
#include "list.h"

// Funkcja wczytujaca komende
char *readLine(){
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line,&bufsize,stdin);
    return line;
}
// Funkcja wydobywajaca argumenty z wpisanego wiersza
char **splitLine(char *line){
    int bufSize = 50;
    char *copyreader = ", \n"; // Rozdzielacz argumentow
    char **tokens = malloc(bufSize * sizeof(char*));
    char *token;
    int position = 0;

    if(!tokens){
        fprintf(stderr, "Bład alokacji\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, copyreader); // Wczytanie znaku
    while(token!= NULL){
        tokens[position] = token;
        position++;

        // Realokacja pamieci
        if(position >= bufSize){
            bufSize += bufSize;
            tokens = realloc(tokens, bufSize * sizeof(char*));

            if(!tokens){
            fprintf(stderr, "Bład alokacji\n");
            exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, copyreader);
    }
    tokens[position] = NULL;
    return tokens; // Tablica argumentow
}
// Funckja prztwarzajaca argumenty
int launch(char **args, struct HandlerC *headC, struct HandlerR *headR){
    // Deklaracja dozwolonych rodzajow nosnika
    char *typeCorrect[] = {"CD", "DVD", "BR", "WINYL"};

    if(args[0] == NULL){
        // Wprowadzono pusta komende
        return 1;
    }
    // Wczytanie komendy
    else if(strcmp(args[0], "add-c") == 0 && numArgs(args) == 2){
            addCatFunc(args, headC);
        }
    else if(strcmp(args[0], "rem-c") == 0 && numArgs(args) == 2){
            remCatFunc(args, headC, headR);
        }
    else if(strcmp(args[0], "mod-c") == 0 && numArgs(args) == 2){
            modCatFunc(args, headC);
        }
    else if(strcmp(args[0], "show-c") == 0 && numArgs(args) == 2){
            showCatFunc(args, headC);
        }
    else if(strcmp(args[0], "show-c-all") == 0 && numArgs(args) == 1){
            showCatFunc(args, headC);
        }
    else if(strcmp(args[0], "show-r-all") == 0 && numArgs(args) == 1){
            showRecFunc(args, headR);
        }
    else if(strcmp(args[0], "add-r") == 0 && numArgs(args) == 2){
            addRecFunc(args, typeCorrect, headR, headC);
        }
    else if(strcmp(args[0], "add-r-c") == 0 && numArgs(args) == 2){
            addRecToCatFunc(args, headR, headC);
        }
    else if(strcmp(args[0], "mod-r") == 0 && numArgs(args) == 2){
            modRecFunc(args, headR, typeCorrect);
        }
    else if(strcmp(args[0], "srch-r") == 0 && numArgs(args) == 2){
            srchRecFunc(args, headR);
        }
    else if(strcmp(args[0], "mov-r") == 0 && numArgs(args) == 2){
            movRecFunc(args, headC, headR);
        }
    else if(strcmp(args[0], "rem-r") == 0 && numArgs(args) == 2){
            remRecFunc(args, headR, headC);
        }
    else if(strcmp(args[0], "save") == 0 && numArgs(args) == 2){
            saveFunc(args, headR, headC);
        }
    else if(strcmp(args[0], "load") == 0 && numArgs(args) == 2){
            loadFunc(args, headR, headC, typeCorrect);
        }
    else if (strcmp(args[0], "help") == 0 && numArgs(args) == 1){
            helpFunc();
    }
    else if (strcmp(args[0], "end") == 0 && numArgs(args) == 1){
            return 0;
    }
    else
        puts("Nieprawidłowa składnia!");

    return 1;
}
// Funkcja głowna
void loop(struct HandlerC *headC, struct HandlerR *headR){
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = readLine();
    args = splitLine(line);
    status = launch(args, headC, headR);

    free(line);
    free(args);
  } while (status);
}

