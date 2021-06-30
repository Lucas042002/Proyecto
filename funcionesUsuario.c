#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "estructuras.h"

int get_file_size (FILE *fp) {
   int len;
   if( fp == NULL )  {
      perror ("Error opening file");
      return(-1);
   }
   fseek(fp, 0, SEEK_END);
   len = ftell(fp);
   fclose(fp);
   return(len);
}
void cargarDatosUsuario(char*name,char*copyLinea,usuario*user){
    char *ptr, *ptr2;
    char*nombre=(char*)malloc(sizeof(char));
    strcpy(nombre,name);
    user = crear_usuario(nombre);
    ptr = strtok(copyLinea, ";");
    ptr = strtok(NULL, "\n");
    
    if (ptr==NULL) return;
    else{
        vLector*val;
        char*tipoLectura=(char *)malloc(20*sizeof(char));
        char*titulo=(char *)malloc(50*sizeof(char));
        char*genero=(char *)malloc(20*sizeof(char));
        float calificacion=0;
        ptr2=strtok(ptr,",");
        strcpy(tipoLectura,ptr2);
        ptr2=strtok(NULL,",");
        strcpy(titulo,ptr2);
        ptr2=strtok(NULL,",");
        strcpy(genero,ptr2);
        ptr2=strtok(NULL,",");
        calificacion=atoi(ptr2);
        val=crear_valoracion(tipoLectura,titulo,genero,calificacion);
        agregar_lista(user,val);
        ptr2=strtok(NULL,",");
        while (ptr2!=NULL){
            strcpy(tipoLectura,ptr2);
            ptr2=strtok(NULL,",");
            strcpy(titulo,ptr2);
            ptr2=strtok(NULL,",");
            strcpy(genero,ptr2);
            ptr2=strtok(NULL,",");
            calificacion=atoi(ptr2);
            val=crear_valoracion(tipoLectura,titulo,genero,calificacion);
            agregar_lista(user,val);
            ptr2=strtok(NULL,",");
        }
    }
}
void crearUsuario(FILE*texto){
    char*nombre_usuario=(char *)malloc(20*sizeof(char));
    char*contrasena=(char *)malloc(20*sizeof(char));
    char*cadena=(char *)malloc(40*sizeof(char));
    
    printf("Ingrese nombre de usuario:\n");
    scanf ("%s", nombre_usuario);
    printf("Ingrese contrasenya:\n");
    scanf ("%s", contrasena);

    strcpy(cadena,nombre_usuario);
    strcat(cadena,",");
    strcat(cadena,contrasena);
    strcat(cadena,";");
    strcat(cadena,"\n");

    
    char*linea;
    char*ptr;
    if (get_file_size(texto)==0){
        texto = fopen("usuarios.csv", "a");
        fputs(cadena,texto);
        fclose(texto);
    }
    else{
        texto = fopen("usuarios.csv", "r");
        while (!feof(texto)){
            linea = (char *) malloc(10000*sizeof(char));
            fgets(linea, 10000, texto);
            if(linea){
                ptr = strtok(linea, ",");
                if (strcmp(nombre_usuario,ptr)==0){
                    printf("El nombre ya existe, ingrese uno nuevo.\n");
                    return;
                }
            }
        }
        fclose(texto);
        texto = fopen("usuarios.csv", "a");
        fputs(cadena,texto);
        fclose(texto);
    }
    
}
int ingresarUsuario(FILE*texto,usuario*user){
    char*nombre_usuario=(char *)malloc(20*sizeof(char));
    char*contrasena=(char *)malloc(20*sizeof(char));
    int intento=0;

    printf("Ingrese nombre de usuario:\n");
    scanf ("%s", nombre_usuario);

    char*linea;
    
    char*ptr;
    if (get_file_size(texto)==0){
        printf ("Por favor cree un usuario primero\n");
    }
    else{
        texto = fopen("usuarios.csv", "r");
        while (!feof(texto)){
            linea = (char *) malloc(10000*sizeof(char));
            fgets(linea, 10000, texto);
            char*copyLinea=(char *) malloc(10000*sizeof(char));
            strcpy(copyLinea,linea);
            if(linea){
                ptr = strtok(linea, ",");
                if (strcmp(nombre_usuario,ptr)==0){
                    ptr = strtok(NULL, ";");
                    while (intento!=3){
                        printf("Ingrese contrasenya:\n");
                        scanf ("%s", contrasena);
                        if (strcmp(contrasena,ptr)==0){
                            cargarDatosUsuario(nombre_usuario,copyLinea,user);
                            return 0;
                        }
                        intento++;
                    }
                    if (intento==3) printf ("Limite de intentos superado, se volvera al menu principal.\n");
                    return 1;
                }
            }
        }
        printf ("No se encontro el usuario.");
    }
}
void importarTipoLectura(HashMap*Map_titulo,HashMap*Map_autor,HashMap*Map_genero){
    FILE * txt;
    int opcion;
    printf ("Que recomendaciones deseeas ver en esta sesion:");
    printf("1.- Mangas\n");
    printf("2.- Libros\n");
    printf("3.- Comics\n");
    scanf ("%d",&opcion);
    switch(opcion){
        case 1: txt = fopen ("mangas.csv", "r"); break;
        case 2: txt = fopen ("libros.csv", "r"); break;
        case 3: txt = fopen ("comics.csv", "r"); break;
        default: printf("Opcion no valida.\n"); break;
    }
    //system("pause");
    //system("@cls||clear");
    char *linea,*ptr;

    int n = 0;
    while (!feof(txt) ){
        linea = (char *) calloc(10000, sizeof(char));
        fgets(linea, 10000, txt);
        if( linea ){
            texto * auxTexto;
            char * titulo = (char *)malloc(sizeof(char));
            char * autor = (char *)malloc(sizeof(char));
            char * sinopsis = (char *)malloc(10000*sizeof(char));
            char * auxGenero = (char *)malloc(sizeof(char));
            List * genero=createList();
            float valoracion;
            ptr = strtok(linea, ",");
            ptr = strtok(NULL, ",");
            if( ptr ){
                strcpy(titulo,ptr);
                ptr = strtok(NULL, ",");

                if (ptr[0]=='\"'){
                        strcpy(auxGenero, ptr);
                        while(ptr[strlen(ptr)-1]!='\"'){
                            ptr=strtok(NULL, ",");
                            strcpy(auxGenero, ptr);
                            pushBack(genero,auxGenero);
                        }
                }
                ptr = strtok(NULL, ",");
                strcpy(autor,ptr);
                ptr = strtok(NULL, ",");
                valoracion = atoi(ptr);
                if (ptr[0]=='\"'){
                        strcpy(sinopsis, ptr);
                        while(ptr[strlen(ptr)-1]!='\"'){
                            ptr=strtok(NULL, ",");
                            strcat(sinopsis, ptr);
                        }
                }
                auxTexto = crear_texto();
                insertMap (Map_titulo,titulo,auxTexto);

                
                

            }
        }
    }
}


