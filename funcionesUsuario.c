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
usuario *cargarDatosUsuario(char*name,char*copyLinea,usuario*user){
    char *ptr, *ptr2;
    char*nombre=(char*)malloc(sizeof(char));
    strcpy(nombre,name);
    user = crear_usuario(nombre);
    if(user==NULL) printf("aaaaaaaaaaaa\n");
    ptr = strtok(copyLinea, ";");
    ptr = strtok(NULL, "\n");
    
    if (ptr==NULL) return NULL;
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
            calificacion=atof(ptr2);
            val=crear_valoracion(tipoLectura,titulo,genero,calificacion);
            agregar_lista(user,val);
            ptr2=strtok(NULL,",");
        }
    }
    return user;
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
            linea = (char *) malloc(5000*sizeof(char));
            fgets(linea, 5000, texto);
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
usuario* ingresarUsuario(FILE*texto,usuario*user){
    char*nombre_usuario=(char *)malloc(45*sizeof(char));
    char*contrasena=(char *)malloc(45*sizeof(char));
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
            linea = (char *) malloc(5000*sizeof(char));
            fgets(linea, 5000, texto);
            char*copyLinea=(char *) malloc(5000*sizeof(char));
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
                            fclose(texto);
                            free(linea);
                            return (usuario*)nombre_usuario;
                        }
                        intento++;
                    }
                    if (intento==3) printf ("Limite de intentos superado, se volvera al menu principal.\n");
                }
            }
        }
        printf ("No se encontro el usuario.\n");
        fclose(texto);
    }
    free(linea);
    return user;
}
void importarTipoLectura(HashMap*Map_titulo,HashMap*Map_autor,HashMap*Map_genero){
    FILE * fp;
    int opcion;
    printf ("Que recomendaciones deseeas ver en esta sesion:\n");
    printf("1.- Mangas\n");
    printf("2.- Libros\n");
    printf("3.- Comics\n");
    scanf ("%d",&opcion);
    if (opcion == 1) fp = fopen ("mangas.csv", "r");
    if (opcion == 2) fp = fopen ("libros.csv", "r");
    if (opcion == 3) fp = fopen ("comics.csv", "r");
    List * genero=createList();
    texto * auxTexto;
    //system("pause");
    //system("@cls||clear");
    char *linea,*ptr;  
    while (!feof(fp) ){
        linea = (char *) calloc(100000,sizeof(char));
        fgets(linea, 100000, fp);
        if( linea ){

            char * titulo    = (char *)calloc(1000,sizeof(char));
            char * autor     = (char *)calloc(1000,sizeof(char));
            char * sinopsis  = (char *)calloc(10000,sizeof(char));
            char * auxGenero = (char *)calloc(1000,sizeof(char));
            
            float valoracion;
            ptr = strtok(linea, ",");

            if( ptr ){
                strcpy(titulo,ptr);
                printf ("%s\n",titulo);
                ptr = strtok(NULL, "\"");
                strcpy(auxGenero, ptr);
                printf ("%s\n",auxGenero);

                ptr = strtok(NULL, ",");
                strcpy(autor,ptr);
                printf ("%s\n",autor);

                ptr = strtok(NULL, ",");
                valoracion = atof(ptr);
                printf ("%.2f\n",valoracion);

                ptr = strtok(NULL, "\"\n");
                strcpy(sinopsis, ptr);
                printf ("%s\n",sinopsis);
                /*
                //esto se segmenta
                auxTexto = crear_texto(titulo,valoracion, autor, genero, sinopsis);
                List* auxAutor = createList();
                insertMap (Map_titulo,titulo,auxTexto);
                if (get_size(Map_autor)==0)  {
                    pushBack(auxAutor, auxTexto);
                    insertMap(Map_autor, autor, auxAutor);
                }
                else{
                    if (searchMap(Map_autor, autor)!=NULL){
                        auxAutor=searchMap(Map_autor, autor);
                        eraseMap(Map_autor,autor);
                        pushBack(auxAutor, auxTexto);
                        insertMap(Map_autor, autor, auxAutor);
                    }
                    else{

                        pushBack(auxAutor, auxTexto);
                        insertMap(Map_autor, autor, auxAutor);
                    }
                }   
                */
            }
        }
    }
}


