#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "estructuras.h"

void Buscar_Titulo(HashMap*map){
    char*titulo=malloc(sizeof(char));
    texto*auxtitulo;
    printf("Que titulo deseas buscar?\n");
    scanf("%[^\n]", titulo);
    fgets(titulo,40,stdin);
    fgets(titulo,40,stdin);
    titulo[strlen(titulo)-1]=0;
    auxtitulo=searchMap(map,titulo);

    if(auxtitulo==NULL){
        printf("El titulo que busca no existe en nuestra base de datos\n"); return;
    }
    else{
        printf("Titulo de la obra: ");
        printf("%s", get_titulo(auxtitulo));
        printf("\n");
        printf("Autor de la obra: ");
        printf("%s", get_autor(auxtitulo));
        printf("\n");
        printf("Genero(s) de la obra: ");
        printf("%s", get_genero(auxtitulo));
        printf("\n");
        printf("Valoracion de la obra: ");
        printf("%.2f", get_valoracion(auxtitulo)); 
        printf("\n");
        printf("Sinopsis de la obra: ");
        printf("%s", get_sinopsis(auxtitulo));
        printf("\n");       
    }

}