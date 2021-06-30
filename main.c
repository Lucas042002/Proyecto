#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "estructuras.h"
#include "funcionesUsuario.h"


void menuRecomendacion(usuario*user){
    HashMap*Map_titulo=createMap(100);
    HashMap*Map_autor=createMap(50);
    HashMap*Map_genero=createMap(50);

    importarTipoLectura(Map_titulo,Map_autor,Map_genero);

    int cont = 0, numero = -1;
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
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        
    }
}

int main (){
    FILE * texto = fopen ("usuarios.csv", "r");
    int cont = 0, aux = 0;
    int numero = -1;
    usuario*user;
    while(numero != 0){
        
        printf("-----------------------------------------\n");
        printf("            Inicio de sesion\n");
        printf("-----------------------------------------\n");
        printf("1.- Crear usuario\n");
        printf("2.- Ingresar usuario\n");
        printf("0.- Salir\n");
        printf("\n");
        printf("Indica la opcion: ");

        scanf("%d", &numero);

        printf("\n");

        switch(numero){
            case 1: crearUsuario(texto); break;
            case 2: {
                aux = ingresarUsuario(texto,user); 
                if (aux==0) menuRecomendacion (user);
                break;
            }
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        //system("pause");
        //system("@cls||clear");
    }
    return 0;
}