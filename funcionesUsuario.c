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
void cargarDatosUsuario(char*copyLinea,usuario*user){
    char *ptr, *ptr2;
    /*Se cargan los datos desde el csv, creando la struct valoracion que se guardara en la list de la struct usuario*/
    ptr = strtok(copyLinea, ";");
    ptr = strtok(NULL, "\n");
    
    if (ptr==NULL) return;
    else{
        vLector*val;
        char*tipoLectura=(char *)malloc(20*sizeof(char));
        char*titulo=(char *)malloc(50*sizeof(char));
        char*genero=(char *)malloc(70*sizeof(char));
        float calificacion=0;
        ptr2=strtok(ptr,",");
        strcpy(tipoLectura,ptr2);
        ptr2=strtok(NULL,",");
        strcpy(titulo,ptr2);
        ptr2=strtok(NULL,"\"");
        strcpy(genero,ptr2);
        ptr2=strtok(NULL,",");
        calificacion=atof(ptr2);
        val=crear_valoracion(tipoLectura,titulo,genero,calificacion);
        agregar_lista(user,val);
        ptr2=strtok(NULL,",");
        //Si llega a tener mas de una valoracion se sigue leyendo hasta que el ptr sea NULL
        while (ptr2!=NULL){
            strcpy(tipoLectura,ptr2);
            ptr2=strtok(NULL,",");
            strcpy(titulo,ptr2);
            ptr2=strtok(NULL,"\"");
            strcpy(genero,ptr2);
            ptr2=strtok(NULL,",");
            calificacion=atof(ptr2);
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
    //Se pide el Nombre y contrasena y luego se revisa si el csv usuarios esta vacio, si esta vacio se agrega y si no se revisa que el nombre no este
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
    //Primero se pide el nombre de usuario
    char*linea;
    //Se revisa que hayan usuarios creados
    char*ptr;
    if (get_file_size(texto)==0){
        printf ("Por favor cree un usuario primero\n");
        return NULL;
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
                        /*Cuando ingrese la contrasena mas de 3 veces fallidas, se retoenara al menu, sino se cargaran los datos del csv
                        con los datos de si ha valorado alguna obra*/
                        printf("Ingrese contrasenya:\n");
                        scanf ("%s", contrasena);
                        if (strcmp(contrasena,ptr)==0){
                            user = crear_usuario(nombre_usuario);
                            cargarDatosUsuario(copyLinea,user);
                            fclose(texto);
                            return user;
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
    return NULL;
}
char* importarTipoLectura(HashMap*Map_titulo,HashMap*Map_autor,HashMap*Map_genero){
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
    texto * auxTexto;
    system("@cls||clear");
    //Cuando se selecciona el tipo de lectura que se quiera, se crean las struct texto y se guardan en los distintos mapas, con distintas claves
    char *linea,*ptr;  
    while (!feof(fp) ){
        linea = (char *) calloc(10000,sizeof(char));
        fgets(linea, 10000, fp);
        if( linea ){
            char * titulo    = (char *)calloc(1000,sizeof(char));
            char * autor     = (char *)calloc(1000,sizeof(char));
            char * sinopsis  = (char *)calloc(1000,sizeof(char));
            char * genero    = (char *)calloc(1000,sizeof(char));
            
            float valoracion;
            ptr = strtok(linea, ",");

            if( ptr ){
                strcpy(titulo,ptr);
                ptr = strtok(NULL, "\"");
                strcpy(genero, ptr);

                ptr = strtok(NULL, ",");
                strcpy(autor,ptr);

                ptr = strtok(NULL, ",");
                valoracion = atof(ptr);

                ptr = strtok(NULL, "\"\n");
                strcpy(sinopsis, ptr);
                
                auxTexto = crear_texto(titulo,valoracion, autor, genero, sinopsis);
                //insercion en mapa titulo
                insertMap (Map_titulo,titulo,auxTexto);
                insertMap(Map_genero,genero,auxTexto);
                insertMap(Map_autor, autor, auxTexto);
            }
        }
    }
    //Por ultimo se retorna el tipo de texto que se selecciono para otros usos dentro de la ejecucion
    if (opcion==1) return "Mangas";
    if (opcion==2) return "Libros";
    if (opcion==3) return "Comics";
}


