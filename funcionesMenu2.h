#include <stdio.h>
#include <stdlib.h>

#ifndef funcionesMenu2_h
#define funcionesMenu2_h

typedef struct texto texto;

void Buscar_Titulo(HashMap*Map_Titulo);
void buscar_autor(HashMap*Map_titulo,HashMap*Map_Autor);
void mostrar_afinidad (HashMap *Map_genero, usuario * user, HashMap *Map_titulo, char *tipoLec);
void mostrar_genero(HashMap*map);
#endif /* funcionesMenu2_h */