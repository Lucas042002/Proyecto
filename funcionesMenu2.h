#include <stdio.h>
#include <stdlib.h>

#ifndef funcionesMenu2_h
#define funcionesMenu2_h

typedef struct texto texto;
void Ingresar_valoracion(usuario*user,char*tipoLec,HashMap*Map_titulo,HashMap*Map_genero,HashMap*Map_autor);
void Buscar_Titulo(HashMap*Map_Titulo);
void buscar_autor(HashMap*Map_Autor);
void mostrar_afinidad (HashMap *Map_genero, usuario * user, HashMap *Map_titulo, char *tipoLec);
void mostrar_genero(HashMap*map);
void agregarTexto(HashMap *Map_genero, HashMap* Map_autor, HashMap *Map_titulo, char*tipo);
#endif /* funcionesMenu2_h */