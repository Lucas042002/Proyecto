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
    List* genero;
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
    usuario *user = (usuario *) malloc (sizeof(usuario));
    strcpy(user->nombre,x);
    user->valoracionLecturas=createList();
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
