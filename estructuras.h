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

#endif /* estructuras_h */