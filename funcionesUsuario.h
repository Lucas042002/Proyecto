#include <stdio.h>
#include <stdlib.h>

#ifndef funcionesUsuario_h
#define funcionesUsuario_h

void crearUsuario(FILE*texto);
usuario* ingresarUsuario(FILE*texto,usuario*user);
char* importarTipoLectura(HashMap*Map_titulo,HashMap*Map_autor,HashMap*Map_genero);

#endif /* funcionesUsuario_h */