#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    printf("%d \n",argc);

    //verificar que el usuario proporciona un archivo de entrada
    if (argc<2){
        fprintf(stderr, "Uso: %s <archivo_de_entrada>\n", argv[0]);
        exit(1);
    }

    // Intentar abrir el archivo de entrada
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    // Leer y mostrar cada línea del archivo
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }

    return 9;
}