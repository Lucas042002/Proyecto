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
void buscar_autor(HashMap*map, HashMap*mapAutor){
    char*autor=malloc(sizeof(char));
    texto*auxautor;
    printf("Que autor deseas buscar?\n");
    scanf("%[^\n]", autor);
    fgets(autor,40,stdin);
    fgets(autor,40,stdin);
    autor[strlen(autor)-1]=0;
    //auxautor=searchMap(map,autor);
    if(searchMap(mapAutor,autor)==NULL){
        printf("El autor ingresado no se encuentra en nuestra base de datos\n");
        return;
    }
    auxautor=firstMap(map);
    while(auxautor!=NULL){
        //printf("%s", autor);
        if(comparar(auxautor,autor)==0){
            printf("Titulo de la obra: ");
            printf("%s", get_titulo(auxautor));
            printf("\n");
            printf("Genero(s) de la obra: ");
            printf("%s", get_genero(auxautor));
            printf("\n");
            printf("Valoracion de la obra: ");
            printf("%.2f", get_valoracion(auxautor)); 
            printf("\n");
            printf("-----------------------------------\n");
        }  
    auxautor=nextMap(map);
    }
   
}

void mostrar_afinidad (HashMap *Map_genero, usuario * user, HashMap *Map_titulo, char *tipoLec){
    List * valoraciones = get_valoracionL(user);
    if (valoraciones==NULL) return;
    List * recomendacion = createList();
    char * vector [200];
    for (int l=0;l<200;l++){
         vector[l] = calloc (200, sizeof(char));
    }
    char* auxTipo= malloc (sizeof(char));
    
    int verdad;
    
    vLector* txt = first(valoraciones);
    int a=0;
    auxTipo = get_TipoL (txt);
    while(txt!=NULL){    
        if (strcmp(auxTipo,tipoLec)==0){
            float calificacion = get_calificacion(txt);
            char* auxGen = malloc (sizeof(char));
            char * ptr = calloc (1000,sizeof(char));
            if (calificacion>5){
                auxGen=get_generoL(txt);               
                ptr=strtok(auxGen, ",\n");                
                while(ptr!=NULL){
                    verdad=0;
                    if (a==0) {
                        vector[a]=ptr; 
                        a++;
                    }
                    else{
                        for (int k=0; k<a; k++){
                            if (strcmp(vector[k],ptr)==0) {
                                verdad=1;
                            }  
                        }
                        if (verdad==0){
                             strcpy(vector[a],ptr);
                             
                             a++;
                        }   
                    }
                    ptr=strtok(NULL, ", \n");  
                }
            }  
        }
        txt=next(valoraciones);
    }

    for (int m=0; m<a;m++){
       
        texto * new = firstMap(Map_genero);
        char* auxGen1 = calloc (1000000,sizeof(char));
        char * ptr1 = calloc (1000,sizeof(char));
        
        while (new!=NULL){
            strcpy(auxGen1,get_key(Map_genero));
            ptr1= strtok(auxGen1, ",\n");
            while (ptr1!=NULL){
                if (strcmp(vector[m],ptr1)==0 && get_valoracion(new)>8){
                    int repetido =0;                    
                    List * aux = get_valoracionL(user);
                    vLector *aux1 = first(aux);
                    while(aux1!=NULL){
                        if (strcmp(get_titulo(new),get_tituloL(aux1))==0) {
                            repetido=1;
                            break;
                        }
                        aux1=next(aux);
                    }
                    if (repetido==0){
                        int repetido2 =0;
                        if (get_sizelist(recomendacion)>0){
                            texto * aux4= first(recomendacion);
                            while(aux4!=NULL){
                                if (strcmp(get_titulo(new),get_titulo(aux4))==0) {
                                    repetido2=1;
                                    break;
                                }
                                aux4=next(recomendacion);
                            }
                        }
                        if (repetido==0 && repetido2==0){
                            char * aux3= (char*) calloc (1000, sizeof(char));
                            aux3=get_titulo(new);
                            
                            texto *datRec=searchMap(Map_titulo, aux3);
                            
                            pushBack(recomendacion, datRec);
                        }   
                    }
                }
                ptr1=strtok(NULL, ",\n");
            }
            new= nextMap(Map_genero);
        }
        if (get_sizelist(recomendacion)>15) break;
    }
   
    printf("Nuestras recomendaciones para la sesion en curso son:\n");
    printf("TITULO                     AUTOR                  GENERO                                                      VALORACION\n");
    texto * dataRec=first(recomendacion);
    while(dataRec!=NULL){
        printf("%s", get_titulo(dataRec));
        for (int k=0; k<27-strlen(get_titulo(dataRec));k++){
            printf(" ");
        }
        printf("%s", get_autor(dataRec));
        for (int k=0; k<23-strlen(get_autor(dataRec));k++){
                printf(" ");
        }
        printf("%s", get_genero(dataRec));
        for (int k=0; k<60-strlen(get_genero(dataRec));k++){
            printf(" ");
        }
        printf("%.2f\n", get_valoracion(dataRec));
        dataRec=next(recomendacion);
    }
}

void mostrar_genero(HashMap*map){
    char*genero=malloc(sizeof(char));
    printf("Que genero desea encontrar:\n");
    scanf("%s", genero);

}