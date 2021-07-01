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
#endif /* estructuras_h */