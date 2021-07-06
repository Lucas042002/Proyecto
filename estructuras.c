#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "list.h"
#include "map.h"
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
vLector* crear_valoracion(char*a, char*b,char*c,float d){
    vLector *val = (vLector *) malloc (sizeof(vLector));
    val->tipoLectura=(char *)malloc(20*sizeof(char));
    val->titulo=(char *)malloc(70*sizeof(char));
    val->genero=(char *)malloc(70*sizeof(char));

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
    printf("Usuario Ingresado = %s\n", user->nombre);
}
void mostrarVal(usuario *user){
    vLector*aux=malloc(sizeof(vLector));
    aux=first(user->valoracionLecturas);
    //muestra todas las valoraciones guardadas en la lista del user
    printf("Valoraciones del Usuario:\n");
    while(aux!=NULL){
        printf("Tipo de lectura = %s\n", aux->tipoLectura);
        printf("Titulo de la lectura = %s\n", aux->titulo);
        printf("Genero(s) de la lectura = %s\n", aux->genero);
        printf("Calificacion de la lectura = %.2f\n", aux->calificacion);
        printf("\n");
        aux=next(user->valoracionLecturas);
    }

}

char* get_titulo(texto*t){
    return(t->titulo);
}
float get_valoracion(texto*t){
   return (t->valoracion);
}
char* get_autor(texto*t){
    return(t->autor);
}
char* get_genero(texto*t){
    return(t->genero);
}
char* get_sinopsis(texto*t){
    return(t->sinopsis);
}

void mostrarPorValoracion(HashMap *map){
  system("@cls||clear");
  texto *vector = malloc(sizeof(texto)*get_size(map));
  texto *vectorMapa = firstMap(map);
  int cont = 0;
  //guardo los datos del mapa en un vector de tipo texto
  while (vectorMapa != NULL){
    vector[cont] = *vectorMapa;
    cont++;
    vectorMapa = nextMap(map);
  }
  texto swap;
  //se aplica bubblesort de mayor a menor segun la valoracion
    for (int c = 0 ; c < get_size(map) -1; c++){
        for (int d = 0 ; d < get_size(map)- c-1; d++){
            if (vector[d].valoracion < vector[d+1].valoracion){
                swap       = vector[d];
                vector[d]   = vector[d+1];
                vector[d+1] = swap;   
            }
        }
    }
    printf("VALORACION\tTITULO\n");
    for(int l=0;l<cont;l++){
        char * titulo = calloc(10000,sizeof(char));
        titulo=vector[l].titulo;
         printf ("%.2f\t\t%s\n",vector[l].valoracion, vector[l].titulo);
    }

}
void modificar_user(usuario * user,vLector *a){
    pushBack(user->valoracionLecturas,a);
}

char* get_tituloL(vLector*t){
    return(t->titulo);
}
List* get_valoracionL(usuario * user){
   return (user->valoracionLecturas);
}
char* get_generoL(vLector*t){
    return(t->genero);
}
char* get_TipoL(vLector*t){
    return(t->tipoLectura);
}
float  get_calificacion(vLector *t){
    return (t->calificacion);
}
char *get_nombreUser(usuario * user){
    return (user->nombre);
}

void modificar_val(texto *t,float nueva_val){
    t->valoracion=nueva_val;
}  