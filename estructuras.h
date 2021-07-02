#include <stdio.h>
#include <stdlib.h>

typedef struct texto texto;
typedef struct usuario usuario;
typedef struct vLector vLector;

#ifndef estructuras_h
#define estructuras_h


usuario* crear_usuario(char *x);
vLector* crear_valoracion(char*a, char*b,char*c,int d);
void agregar_lista (usuario*user, vLector*val);
texto* crear_texto (char*titulo,float valoracion, char*autor,char*genero,char*sinopsis);
void mostrarUser(usuario *user);
void mostrarVal(usuario *user);

char* get_titulo(texto*t);
float get_valoracion(texto*t);
char* get_autor(texto*t);
char* get_genero(texto*t);
char* get_sinopsis(texto*t);
long get_size (HashMap * map);
void mostrarPorValoracion(HashMap*Map_titulo);
int comparar(texto* aComparar, char *aux);
#endif /* estructuras_h */