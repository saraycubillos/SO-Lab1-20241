#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LineNode {
    char* line;
    struct LineNode* next;
} LineNode;

int main (int argc, char *argv[]){
    FILE *file;
    FILE *file2;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    LineNode* head = NULL; 
    

    //verificar que el usuario proporciona la cantidad correcta de archivos de entrada
    if (argc > 3){
        fprintf(stderr, "usage: reverse <input> <output>\n");             //--1--
        exit(1);
    } else if (argc >= 2){

        // Intentar abrir el archivo de entrada             
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);    //--2--
            exit(1);
        }
        
    } 

    if (argc == 3){
        //Intentar abrir archivo de salida
        file2 = fopen(argv[2], "r");
        if (file2 == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);    //--3--
            exit(1);
        }

        // Encontrar nombre de archivos
        char *fileName1 = strrchr(argv[1], '/');
        char *fileName2 = strrchr(argv[2], '/');
        
        if (fileName1) {
            fileName1++;
        } else {
            fileName1 = argv[1];
            
        }
        if (fileName2) {
            fileName2++;
        }
        //Comparo nombres de archivo
        if(strcmp(fileName1, fileName2) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");      //--4--
            exit(1);
        }
        //Comparo carpetas y nombres de archivo
        if(strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");      //--5--
            exit(1);
        }
    }

//-----------------------------------------------//
 
    // Leer y mostrar cada línea del archivo
    while ((read = getline(&line, &len, file)) != -1) {
        i++;
        printf("%s", line);
    }

    return 1;
}