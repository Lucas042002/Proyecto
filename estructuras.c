#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "list.h"
#include "estructuras.h"

typedef struct texto texto;
typedef struct usuario usuario;
typedef struct vLector vLector;

struct texto{
    char * titulo;
    float valoracion;
    char * autor;
    char* genero;
    char * sinopsis;
};
struct usuario{
    char * nombre;
    List* valoracionLecturas;
};
struct vLector{
    char * tipoLectura;
    char * titulo;
    char* genero;
    float calificacion;
};

usuario* crear_usuario(char *x){
    usuario *user = (usuario *) calloc(1,sizeof(usuario));
    user->nombre=x;
    user->valoracionLecturas=createList();
    return user;
}
texto* crear_texto (char*titulo,float valoracion, char*autor,char*genero,char*sinopsis){
    texto *text = (texto *) malloc (sizeof(texto));
    text->genero=(char *)malloc(50*sizeof(char));
    text->autor=(char *)malloc(20*sizeof(char));
    text->titulo=(char *)malloc(20*sizeof(char));
    text->sinopsis=(char *)malloc(10000*sizeof(char));
    
    strcpy(text->titulo,titulo);
    strcpy(text->autor,autor);
    strcpy(text->sinopsis,sinopsis);
    text->valoracion=valoracion;
    strcpy(text->genero,genero);

    return text;
}
vLector* crear_valoracion(char*a, char*b,char*c,int d){
    vLector *val = (vLector *) malloc (sizeof(vLector));
    val->tipoLectura=(char *)malloc(20*sizeof(char));
    val->titulo=(char *)malloc(50*sizeof(char));
    val->genero=(char *)malloc(20*sizeof(char));

    strcpy(val->tipoLectura,a);
    strcpy(val->titulo,b);
    strcpy(val->genero,c);
    val->calificacion=d;
    return val;
}

void agregar_lista (usuario*user, vLector*val){
    pushBack(user->valoracionLecturas, val);
}

void mostrarUser(usuario *user){
    printf("nombre = %s\n", user->nombre);
}
void mostrarVal(usuario *user){
    vLector*aux=malloc(sizeof(vLector));
    aux=first(user->valoracionLecturas);
    while(aux!=NULL){
        printf("%s\n", aux->tipoLectura);
        printf("%s\n", aux->titulo);
        printf("%s\n", aux->genero);
        printf("%.2f\n", aux->calificacion);
        aux=next(user->valoracionLecturas);
    }

}