#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "estructuras.h"

void Ingresar_valoracion(usuario*user,char*tipoLec,HashMap*Map_titulo,HashMap*Map_genero,HashMap*Map_autor){
    char*titulo_ingresado=(char *)malloc(sizeof(char));
    char* val_ingresada=(char *)malloc(sizeof(char));
    texto*aux;
    List *auxiliar;
    system("@cls||clear");
    //Se ingresa titulo de lectura a valorar
    printf("Escriba el nombre de la lectura a valorar \n");
    do{
        
        scanf("%[^\n]", titulo_ingresado);

        fgets(titulo_ingresado,40,stdin);
        fgets(titulo_ingresado,40,stdin);
        titulo_ingresado[strlen(titulo_ingresado)-1]=0;
        //corroboramos que el titulo exista en nuestra base de datos
        aux = searchMap(Map_titulo,titulo_ingresado);
        vLector* auxTexto;
        if (aux==NULL) {
            printf ("No se encontro el titulo ingresado,retornando al menu.\n");
            return;
        }
        //corroboramos que no haya sido valorado anteriormente
        auxiliar = get_valoracionL(user);
        auxTexto = first(auxiliar);
        while (auxTexto!=NULL){
            if (strcmp(titulo_ingresado,get_tituloL(auxTexto))==0){
                printf ("El titulo ya se encuentra valorado, retornando al menu.\n");
                return;
            }
            auxTexto=next(auxiliar);
        }
        
    }while (aux==NULL);
    //Pedimos una valoracion a este titulo
    printf ("Escriba la valoracion, recuerde que puede valorar desde el 1 al 10.\n");
    scanf("%s",val_ingresada);
          float val_fl = atof(val_ingresada);

        //Ingresar la valoracion en el usuario//
        char*cadena_usuario=(char *)malloc(1000*sizeof(char));
        char*genero=get_genero(aux);
        char*titulo=get_titulo(aux);
        strcpy(cadena_usuario,",");
        strcat(cadena_usuario,tipoLec);
        strcat(cadena_usuario,",");
        strcat(cadena_usuario,titulo);
        strcat(cadena_usuario,",");
        strcat(cadena_usuario,"\"");
        strcat(cadena_usuario,genero);
        strcat(cadena_usuario,"\"");
        strcat(cadena_usuario,",");
        strcat(cadena_usuario,val_ingresada);
        vLector * auxiliar2 = crear_valoracion(tipoLec, titulo, genero, val_fl);

        //Para ingresarlos en csv usuarios
        char *linea;
        char * linea2;
        char *ptr, *ptr2;
        FILE*csv = fopen("usuarios.csv", "r+");
        FILE *copiacsv = fopen("usuarioscopia.csv", "w");
        //Creamos una copia del csv actual
        while (!feof(csv)){
            linea2 = (char *) malloc(50000*sizeof(char));
            fgets(linea2, 50000, csv);
            if (linea2!=NULL){
                linea2[strlen(linea2)-1]=0;
                fputs(linea2,copiacsv);
            }
        }
        rewind(csv);
        fclose(copiacsv);
        while (!feof(csv)){
            linea = (char *) malloc(5000*sizeof(char));
            fgets(linea, 5000, csv);
            if(linea){
                ptr = strtok(linea, ",");
                if (strcmp(get_nombreUser(user),ptr)==0){
                        //Ingresamos la valoracion al usuario
                        long donde = ftell(csv);
                        donde=donde-2;
                        fseek( csv, donde , SEEK_SET);
                        fprintf(csv,"%s",cadena_usuario);
                        copiacsv = fopen("usuarioscopia.csv", "r+");
                        fseek(copiacsv, donde+2, SEEK_SET);
                        fputs("\n",csv);
                        //copiamos todo lo posterior, ya que se elimina en el
                        //csv original despues de agregar la valoracion
                        while (!feof(copiacsv)){
                            fgets(linea2, 50000, copiacsv);
                            if (linea2!=NULL){
                                fputs(linea2,csv);
                            }
                        }
                        
                        fclose(copiacsv);
                        fclose(csv);
                        break;
                }
            }
        }
        //Ingresar en la estructura usuario la nueva valoracion
        modificar_user(user,auxiliar2);
        //Ingresar en los mapas la valoracion
        float nueva_val;
        nueva_val = (get_valoracion(aux)*0.95) + (val_fl*0.05);
        modificar_val(aux,nueva_val);
        //Ingresar en Map_titulo
        eraseMap(Map_titulo,titulo_ingresado);
        insertMap(Map_titulo,titulo_ingresado,aux);

        //Ingresar en Map_genero
        texto*aux3 = firstMap(Map_genero);
        while (aux3!=NULL){
            if (strcmp(get_titulo(aux),get_titulo(aux3))==0){
                char *auxGenero=malloc(sizeof(char));
                strcpy(auxGenero,get_genero(aux3));
                eraseMap(Map_genero,auxGenero);
                insertMap(Map_genero,auxGenero,aux);
                break;
            }
            aux3=nextMap(Map_genero);
        }
        //Ingresar en Map_Autor
        aux3 = firstMap(Map_autor);
        while (aux3!=NULL){
            if (strcmp(get_titulo(aux),get_titulo(aux3))==0){
                char *auxAutor=malloc(sizeof(char));
                strcpy(auxAutor,get_autor(aux3));
                eraseMap(Map_autor,auxAutor);
                insertMap(Map_autor,auxAutor,aux);
                break;
            }
            aux3=nextMap(Map_autor);
        }
    printf("Valoracion agregada exitosamente!\n");    
}
void Buscar_Titulo(HashMap*map){
    char*titulo=malloc(sizeof(char));
    texto*auxtitulo;
    system("@cls||clear");
    printf("Que titulo deseas buscar?\n");
    scanf("%[^\n]", titulo);
    fgets(titulo,40,stdin);
    fgets(titulo,40,stdin);
    titulo[strlen(titulo)-1]=0;
    printf("\n");
    auxtitulo=searchMap(map,titulo);
    //se busca en el mapa y no se encuentra se retorna el primer printf en caso contrario se imprimen sus datos
    if(auxtitulo==NULL){
        printf("El titulo que busca no existe en nuestra base de datos\n"); return;
    }
    else{
        printf("Titulo de la obra: ");
        printf("%s", get_titulo(auxtitulo));
        printf("\n");
        printf("Autor de la obra: ");
        printf("%s", get_autor(auxtitulo));
        printf("\n");
        printf("Genero(s) de la obra: ");
        printf("%s", get_genero(auxtitulo));
        printf("\n");
        printf("Valoracion de la obra: ");
        printf("%.2f", get_valoracion(auxtitulo)); 
        printf("\n");
        printf("Sinopsis de la obra: ");
        printf("%s", get_sinopsis(auxtitulo));
        printf("\n");       
    }

}
void buscar_autor(HashMap*mapAutor){
    char*autor=malloc(sizeof(char));
    texto*auxautor;
    system("@cls||clear");
    printf("Que autor deseas buscar?\n");
    scanf("%[^\n]", autor);
    fgets(autor,40,stdin);
    fgets(autor,40,stdin);
    autor[strlen(autor)-1]=0;
    //Se busca al autor en el mapa autor, para ver en un principio si se encuentran
    if(searchMap(mapAutor,autor)==NULL){
        printf("El autor ingresado no se encuentra en nuestra base de datos\n");
        return;
    }
    //Si se encuentran, se imprimen
    auxautor=firstMap(mapAutor);
    printf("Obras pertenecientes al autor ingresado : \n ");
    printf("\n");
    while(auxautor!=NULL){
        if(strcmp(get_key(mapAutor),autor)==0){
            printf("Titulo de la obra: ");
            printf("%s", get_titulo(auxautor));
            printf("\n");
            printf("Genero(s) de la obra: ");
            printf("%s", get_genero(auxautor));
            printf("\n");
            printf("Valoracion de la obra: ");
            printf("%.2f", get_valoracion(auxautor)); 
            printf("\n");
            printf("-----------------------------------\n");
        }  
    auxautor=nextMap(mapAutor);
    }
   free (autor);
   free (auxautor);
}

void mostrar_afinidad (HashMap *Map_genero, usuario * user, HashMap *Map_titulo, char *tipoLec){
    system("@cls||clear");
vLector* txt;
    //Importamos a la funcion las valoraciones actuales del user
    List * valoraciones = get_valoracionL(user);
    //si no tiene, se retorna porque no tendria sentido la funcion
    if (valoraciones==NULL) {
        printf("El usuario de sesion activa no tiene valoraciones. Ingrese previamente al menos una valoracion.\n");
        return;
    }
    int almenos =0;
txt = first(valoraciones);
    while(txt!=NULL){
        if(strcmp(get_TipoL(txt),tipoLec)==0){
            almenos=1;
            break;
        }
        txt=next(valoraciones);
    }
    if (almenos==0){
        printf("El usuario de sesion activa no tiene valoraciones de este tipo de lectura. Ingrese previamente al menos una valoracion.\n");
        return;
    }
    //creamos una lista donde almacenaremos los titulos recomendados
    List * recomendacion = createList();
    //creamos un vector donde guardaremos los generos 
    char * vector [20];
    for (int l=0;l<20;l++){
         vector[l] = calloc (200, sizeof(char));
    }
    char* auxTipo= malloc (sizeof(char));
    
    int verdad;
    //accedemos a los textos valorados por el usuario actualmente
     txt = first(valoraciones);
    int a=0;
    //accedemos al tipo de lectura del primer texto valorado
    auxTipo = get_TipoL (txt);
    while(txt!=NULL){    
        //si el tipo de texto coindice, corroboramos la calificacion
        if (strcmp(auxTipo,tipoLec)==0){
            float calificacion = get_calificacion(txt);
            char* auxGen = malloc (sizeof(char));
            char * ptr = calloc (1000,sizeof(char));
            //si la calificacion es mayor o igual a 6, accedemos a los generos de la valoracion
            if (calificacion>=6){
                auxGen=get_generoL(txt);     
                //agregamos el primer genero y analizamos desde el segundo genero en adelante 
                //si ya esta escrito en nuestro vector          
                ptr=strtok(auxGen, ",");                
                while(ptr!=NULL){
                    verdad=0;
                    if (a==0) {
                        vector[a]=ptr; 
                        a++;
                    }
                    else{
                        for (int k=0; k<a; k++){
                            if (strcmp(vector[k],ptr)==0) {
                                verdad=1;
                            }  
                        }
                        if (verdad==0){
                            //si no esta escrito, escribimos en el vector
                             strcpy(vector[a],ptr);
                             
                             a++;
                        }   
                    }
                    ptr=strtok(NULL, ",");  
                }
            }  
        }
        txt=next(valoraciones);
    }

    for (int m=0; m<a;m++){ 
        //por cada genero guardado en el vector
        //buscaremos un titulo con una calificacion mayor a 8
        //corroborando si no esta ya escrito en la lista
        texto * new = firstMap(Map_genero);
        char* auxGen1 = calloc (1000000,sizeof(char));
        char * ptr1 = calloc (1000,sizeof(char));
        
        while (new!=NULL){
            strcpy(auxGen1,get_key(Map_genero));
            ptr1= strtok(auxGen1, ",\n");
            while (ptr1!=NULL){
                if (strcmp(vector[m],ptr1)==0 && get_valoracion(new)>8){
                    int repetido =0;                    
                    List * aux = get_valoracionL(user);
                    vLector *aux1 = first(aux);
                    while(aux1!=NULL){
                        if (strcmp(get_titulo(new),get_tituloL(aux1))==0) {
                            repetido=1;
                            break;
                        }
                        aux1=next(aux);
                    }
                    if (repetido==0){
                        int repetido2 =0;
                        if (get_sizelist(recomendacion)>0){
                            texto * aux4= first(recomendacion);
                            while(aux4!=NULL){
                                if (strcmp(get_titulo(new),get_titulo(aux4))==0) {
                                    repetido2=1;
                                    break;
                                }
                                aux4=next(recomendacion);
                            }
                        }
                        if (repetido==0 && repetido2==0){
                            char * aux3= (char*) calloc (1000, sizeof(char));
                            aux3=get_titulo(new);
                            
                            texto *datRec=searchMap(Map_titulo, aux3);
                            
                            pushBack(recomendacion, datRec);
                        }   
                    }
                }
                ptr1=strtok(NULL, ",\n");
            }
            new= nextMap(Map_genero);
        }
        if (get_sizelist(recomendacion)>15) break;
        //la lista contendra un maximo de 15 titulos diferentes
    }
   //mostramos las recomendaciones
    printf("Nuestras recomendaciones para la sesion en curso son: \n");
    printf("TITULO                     AUTOR                  GENERO                                                      VALORACION\n");
    texto * dataRec=first(recomendacion);
    while(dataRec!=NULL){
        printf("%s", get_titulo(dataRec));
        for (int k=0; k<27-strlen(get_titulo(dataRec));k++){
            printf(" ");
        }
        printf("%s", get_autor(dataRec));
        for (int k=0; k<23-strlen(get_autor(dataRec));k++){
                printf(" ");
        }
        printf("%s", get_genero(dataRec));
        for (int k=0; k<60-strlen(get_genero(dataRec));k++){
            printf(" ");
        }
        printf("%.2f \n", get_valoracion(dataRec));
        dataRec=next(recomendacion);
    }
    
   
}

void mostrar_genero(HashMap*Map_genero){
    char*genero=malloc(sizeof(char));
    system("@cls||clear");
    //Solicitamos especificar que genero desea encontrar
    printf("Que genero desea encontrar:\n");
    scanf("%[^\n]s", genero);
    fgets(genero,400,stdin);
    fgets(genero,400,stdin);
    genero[strlen(genero)-1]=0;
    char * vector [10];
    //creamos un vector de maximo 10 generos distintos
    for (int l=0;l<10;l++){
         vector[l] = calloc (100, sizeof(char));
    }
    char* auxTipo= malloc (sizeof(char));
    
    int verdad;
    
    int a=0;
    char* auxGen = malloc (sizeof(char));
    strcpy(auxGen,genero);
    char * ptr = calloc (1000,sizeof(char));
    ptr=strtok(auxGen, ",\n");  
    int cont=0;              
    //agregamos el primer genero y analizamos desde el segundo genero en adelante 
     //si ya esta escrito en nuestro vector, para que todos sean distintos      
    while(ptr!=NULL && cont<10){
       verdad=0;
       if (a==0) {
           vector[a]=ptr; 
           a++;
       }
       else{
           for (int k=0; k<a; k++){
               if (strcmp(vector[k],ptr)==0) {
                   verdad=1;
               }  
           }
           if (verdad==0){
                strcpy(vector[a],ptr); 
                a++;
           }   
       }
       ptr=strtok(NULL, ", \n"); 
       cont++; 
    }
    //creamos un vector de maximo 100 titulos que coincidan con uno o mas de los generos
        texto* vector2[100];
        int control=0;
    for (int m=0; m<a;m++){

    texto * new = firstMap(Map_genero);
    char* auxGen1 = calloc (1000000,sizeof(char));
    char * ptr1 = calloc (1000,sizeof(char));
        //buscamos recorriendo el mapa manualmente
        //los titulos que coincidan con alguno o todos los generos
        while (new!=NULL){
            strcpy(auxGen1,get_key(Map_genero));
            ptr1= strtok(auxGen1, ",\n");
            while (ptr1!=NULL){
                if (strcmp(vector[m],ptr1)==0){                                  
                        int repetido2=0;
                        if (control==0){
                            vector2[control]=new;
                            control++;
                        }
                        else{
                            //si el titulo ya esta escrito no lo volveremos a escribir
                            for(int k=0;k<control;k++){
                                if(strcmp(get_titulo(vector2[k]),get_titulo(new))==0){
                                    repetido2=1;
                                }
                            }
                            if(repetido2==0){
                                vector2[control]=new;
                                control++; 
                            }
                        }
                }
                ptr1=strtok(NULL, ",\n");
            }
            new=nextMap(Map_genero);
        }
    }
    //si nunca se agrego ningun titulo, no existe el genero
    if(control==0){

        printf("No existe el genero ingresado, volviendo al menu...\n");
        return; 
    }
    //si tiene titulos agregados, preguntamos si ordenamos o no estos 
    printf("Como desea ver las lecturas?\n");
    printf("1 para mostrar de mayor a menor valoracion.\n");
    printf("2 para mostrar de menor a mayor valoracion.\n");
    printf("3 para no ordenar.\n");
    
    int opcion;
    do{ 
        scanf("%d", &opcion);
    }while(opcion!=1 && opcion!=2 && opcion!=3);
    system("@cls||clear");
    
    texto *swap;
    //bubble sort mayor a menor
    if(opcion==1){
        for (int c = 0 ; c < control -1; c++){
            for (int d = 0 ; d < control- c-1; d++){
                if (get_valoracion(vector2[d]) < get_valoracion(vector2[d+1])){
                    swap       = vector2[d];
                    vector2[d]   = vector2[d+1];
                    vector2[d+1] = swap;   
                }
            }
        }
    }
    // bubble sort menor a mayor
    if(opcion==2){
        for (int c = 0 ; c < control -1; c++){
            for (int d = 0 ; d < control- c-1; d++){
                if (get_valoracion(vector2[d]) > get_valoracion(vector2[d+1])){
                    swap       = vector2[d];
                    vector2[d]   = vector2[d+1];
                    vector2[d+1] = swap;   
                }
            }
        }
    }
    printf("TITULO                     VALORACION\n");
    for (int j=0; j<control; j++){
        printf("%s",get_titulo(vector2[j]));
            for (int k=0; k<27-strlen(get_titulo(vector2[j])); k++){
            printf(" ");
        }
        printf("%.2f \n",get_valoracion(vector2[j]));
    }
    

}

void agregarTexto(HashMap *Map_genero, HashMap* Map_autor, HashMap *Map_titulo, char*tipo){
    char * titulo    = (char *)calloc(1000,sizeof(char));
    char * autor     = (char *)calloc(1000,sizeof(char));
    char * sinopsis  = (char *)calloc(10000,sizeof(char));
    char * genero    = (char *)calloc(1000,sizeof(char));
    char * valoracion= (char *)calloc(20,sizeof(char));
    //Se busca el nombre del titulo
    printf("Ingrese titulo de Lectura a Ingresar. Recuerde que este tipo de lectura debe corresponder a %s\n", tipo);
    scanf("%[^\n]", titulo);
    fgets(titulo,100,stdin);
    fgets(titulo,100,stdin);
    titulo[strlen(titulo)-1]=0;
    if (searchMap(Map_titulo, titulo)!=NULL){
        printf("Titulo ya existente, retornando a menu...\n");
        return;
    }
    //Si no se encuentra el texto, se piden los demas datos para ingresarlos
    printf("Ingrese genero de lectura ingresada. Si es mas de un genero ingresar separados por comas y sin espacios, por favor:\n");
    scanf("%s", genero);
    printf("Ingrese autor de lectura ingresada:\n");
    scanf("%[^\n]", autor);
    fgets(autor,10000,stdin);
    fgets(autor,10000,stdin);
    autor[strlen(autor)-1]=0;
    printf("Ingrese valoracion  de lectura ingresada:\n");
    scanf("%s", valoracion);
    printf("Ingrese sinopsis. Sin saltos de linea (ENTER) hasta llegar al final de esta:\n");
    scanf("%[^\n]", sinopsis);
    fgets(sinopsis,10000,stdin);
    fgets(sinopsis,10000,stdin);
    sinopsis[strlen(sinopsis)-1]=0;
    texto * auxTexto;
    float valoracion2= atof(valoracion);
    auxTexto = crear_texto(titulo,valoracion2, autor, genero, sinopsis);

    //insercion en mapa titulo
    insertMap (Map_titulo,titulo,auxTexto);
    insertMap(Map_genero,genero,auxTexto);
    insertMap(Map_autor, autor, auxTexto);
    char * linea = (char*) calloc (100000, sizeof(char));
    FILE * fp= NULL;
    if (strcmp(tipo,"Mangas")==0) fp = fopen ("mangas.csv", "a");
    if (strcmp(tipo,"Libros")==0) fp = fopen ("libros.csv", "a");
    if (strcmp(tipo,"Comics")==0) fp = fopen ("comics.csv", "a");
    //Con esto se crea la linea donde se guardara el csv
    strcat(linea, titulo);
    strcat(linea, ",");
    strcat(linea, "\"");
    strcat(linea, genero);
    strcat(linea, "\"");
    strcat(linea, ",");
    strcat(linea, autor);
    strcat(linea, ",");
    strcat(linea, valoracion);
    strcat(linea, ",");
    strcat(linea, "\"");
    strcat(linea, sinopsis);
    strcat(linea, "\"");
    strcat(linea, "\n");
    fprintf(fp,"%s",linea);
    printf("\nTexto agregado correctamente.\n");
    fclose(fp);
                
}