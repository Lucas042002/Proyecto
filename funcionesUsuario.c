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
void cargarDatosUsuario(char*name,char*ptr,usuario*user){
    char *ptr2, *ptr3;
    char*nombre=(char*)malloc(sizeof(char));
    strcpy(nombre,name);
    user = crear_usuario(nombre);

    ptr = strtok(NULL, "\"");

    if (ptr==NULL) return;
    else{
        
            vLector*val;
            char*tipoLectura=(char *)malloc(20*sizeof(char));
            char*titulo=(char *)malloc(50*sizeof(char));
            char*genero=(char *)malloc(20*sizeof(char));
            float calificacion=0;
            ptr2=strtok(ptr,"(");
        
            ptr3=strtok(ptr2,",");
            strcpy(tipoLectura,ptr3);
            printf("%s\n",tipoLectura);
            ptr3=strtok(NULL,",");
            strcpy(titulo,ptr3);
            printf("%s\n",titulo);
            ptr3=strtok(NULL,",");
            strcpy(genero,ptr3);
            printf("%s\n",genero);
            ptr3=strtok(NULL,")");
            calificacion=atoi(ptr3);
            printf("%.2f\n",calificacion);

            val=crear_valoracion(tipoLectura,titulo,genero,calificacion);
            //agregar_lista(user,val);
            
            ptr2=strtok(NULL,"(");
            ptr3=strtok(ptr2,",");
            printf("%s\n",ptr3);
            ptr3=strtok(NULL,",");
            printf("%s\n",ptr3);
            ptr3=strtok(NULL,",");
            printf("%s\n",ptr3);
            ptr3=strtok(NULL,")");
            printf("%.2f\n",ptr3);
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
    strcat(cadena,",");
    strcat(cadena,"\"");
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
void ingresarUsuario(FILE*texto,usuario*user){
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
            if(linea){
                ptr = strtok(linea, ",");
                if (strcmp(nombre_usuario,ptr)==0){
                    ptr = strtok(NULL, ",");
                    while (intento!=3){
                        printf("Ingrese contrasenya:\n");
                        scanf ("%s", contrasena);
                        if (strcmp(contrasena,ptr)==0){
                            cargarDatosUsuario(nombre_usuario,ptr,user);
                            return;
                        }
                        intento++;
                    }
                    if (intento==3) printf ("Limite de intentos superado, se volvera al menu principal.\n");
                    return;
                }
            }
        }
        printf ("No se encontro el usuario.");
    }
}


