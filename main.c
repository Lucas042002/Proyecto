#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "estructuras.h"
#include "funcionesUsuario.h"
#include "funcionesMenu2.h"

void menuRecomendacion(usuario*user){
    //Se inicializan los mapas y se rellenan antes de pasar al mapa
    HashMap*Map_titulo=createMap(100);
    HashMap*Map_autor=createMap(50);
    HashMap*Map_genero=createMap(50);
    mostrarUser(user);
    printf("\n");
    mostrarVal(user);
    char* tipoLec = malloc (sizeof(char));
    printf("\n");

    tipoLec = importarTipoLectura(Map_titulo,Map_autor,Map_genero);

    int numero = -1;
    while(numero != 0){
        printf("-----------------------------------------\n");
        printf("                MENU\n");
        printf("-----------------------------------------\n");
        printf("1.- Ingresar Valoracion\n");
        printf("2.- Mostrar por afinidad\n");
        printf("3.- Mostrar por valoracion\n");
        printf("4.- Buscar titulo\n");
        printf("5.- Busqueda de lecturas segun autor\n");
        printf("6.- Mostrar lecturas segun genero\n");
        printf("7.- Ingresar nuevo texto\n");
        printf("0.- Salir\n");
        printf("\n");
        printf("Indica la opcion: ");
        scanf("%d", &numero);
        printf("\n");

        switch(numero){
            case 1: Ingresar_valoracion(user,tipoLec,Map_titulo,Map_genero,Map_autor);break;
            case 2: mostrar_afinidad(Map_genero,user,Map_titulo,tipoLec);break;
            case 3: mostrarPorValoracion(Map_titulo);break;
            case 4: Buscar_Titulo(Map_titulo);break;
            case 5: buscar_autor(Map_autor);break;
            case 6: mostrar_genero(Map_genero);break;
            case 7: agregarTexto(Map_genero,Map_autor,Map_titulo,tipoLec);break;
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        
    }
}

int main (){
    FILE * texto = fopen ("usuarios.csv", "r");
    int numero = -1;
    usuario*user=NULL;
    while(numero != 0){
        
        printf("-----------------------------------------\n");
        printf("            Inicio de sesion\n");
        printf("-----------------------------------------\n");
        printf("1.- Crear usuario\n");
        printf("2.- Ingresar usuario\n");~
        printf("0.- Salir\n");
        printf("\n");
        printf("Indica la opcion: ");

        scanf("%d", &numero);

        printf("\n");

        switch(numero){
            case 1: crearUsuario(texto); break;
            case 2:{
                user = ingresarUsuario(texto,user);
                
                if (user!=NULL) {

                    system("@cls||clear");
                    menuRecomendacion (user);
                    return 0;
                }
                break;
            }
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        
    }
    return 0;
}