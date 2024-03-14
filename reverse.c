#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Creación de lista ligada
typedef struct LineNode {
    char* line;
    struct LineNode* next;
} LineNode;

//crear lista de lineas
LineNode* crearLista(FILE *file){
    size_t read;
    char *line = NULL;
    size_t len = 0;

    LineNode* head = NULL;

    // Leer cada línea del archivo por medio de lista ligada
    while ((read = getline(&line, &len, file)) != -1) {
        LineNode* newNode = (LineNode*)malloc(sizeof(LineNode));
        newNode->line = strdup(line);
        newNode->next = head;
        head = newNode;
    }

    free(line);
    fclose(file);

    return head;
}

void imprimirLista(LineNode *head){
    //Imprimir la lista ligada
    int len = strlen(head->line);
    while (head != NULL) {
        if(len == 1){
            break;
        }
        printf("%s", head->line);
        free(head->line);  // Liberar la memoria de la línea
        LineNode* temp = head;
        head = head->next;
        free(temp);  // Liberar el nodo
    }
}


int main (int argc, char *argv[]){
    FILE *file;
    FILE *file2;

    //verificar que el usuario proporciona la cantidad correcta de archivos de entrada
    if (argc > 3){
        fprintf(stderr, "usage: reverse <input> <output>\n");             //--1--
        exit(1);
    } else if (argc == 1){
        //ingresar txt por consola

        LineNode* head = NULL;

        printf("Ingrese el texto que desea invertir linea por linea\n Ingrese un 0 para terminar: ");


        char str[50];
        while (1) {

            fgets(str, sizeof(str), stdin);
            //Comprobación
            if (strcmp(str, "0\n") == 0) {
                break;
            }
            //Pasar a Nodo
            LineNode* newNode = (LineNode*)malloc(sizeof(LineNode));
            newNode->line = strdup(str);
            newNode->next = head;
            head = newNode;

            printf("Ingrese otra linea ó Ingrese un 0 para terminar: ");

        }
        imprimirLista(head);



    } else if (argc >= 2){

        // Intentar abrir el archivo de entrada
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);    //--2--
            exit(1);
        }

        LineNode *head = crearLista(file);
        if (argc == 2){
            imprimirLista(head);                                        //--7--
            return 0;
        }

        if (argc == 3){
                //Intentar abrir archivo de salida
            file2 = fopen(argv[2], "w");
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
            }else {
                fileName2 = argv[2];
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

            //sobreescribir en archivo
            file = fopen(argv[2], "w");

            //pasar lista al archivo de salida
            while (head != NULL) {
                fprintf(file, "%s", head->line);                        //--6--
                free(head->line);  // Liberar la memoria de la línea
                LineNode* temp = head;
                head = head->next;
                free(temp);  // Liberar el nodo
            }
            
            fclose(file);
        }
    }

    return 0;

}