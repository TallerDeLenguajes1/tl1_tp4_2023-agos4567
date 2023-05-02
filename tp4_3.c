#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<ctype.h>

struct Tarea
{
    int id;
    char *descripcion;
    int duracion;
} typedef Tarea;

struct Nodo
{
    Tarea tarea;
    struct Nodo *siguiente;
} typedef Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
Tarea cargarTarea();
void AgregarLibro(Nodo **Lista, Tarea Tarea);
void agregarNodo(Nodo **lista, Nodo *newNodo);
void MostrarLista(Nodo *lista);
void moverTarea(Nodo **listaPend, Nodo **listaRealizado);
Nodo *BuscarTareaID(Nodo *tareasPend, Nodo *tareasReal);
void BuscarTareaPorPalabra(Nodo *tareasP, Nodo *tareasR, char *palabra);
void eliminarTareaPorId(Nodo **listaP, Nodo **listaR);
Nodo *extraerTareaPorId(Nodo **lista, int id);
int main()
{
    int idEliminar;

    Nodo *listaPendientes = CrearListaVacia();
    Nodo *listaR = CrearListaVacia();
    Nodo *auxPBorrar;
    Nodo *aux;
    int opcion = 0;
    int Op2 = 1;
    Tarea libroAux;
    int idAux = 0;
    int *id= idAux;//error de casteo??

    // char Buff[50];
    // char *palabra;
    do
    {
        Op2 = 1;
        printf("Seleccione una opcion:\n");
        printf("1-Cargar nueva tarea \n");
        printf("2-Mover tareas \n");
        printf("3-Mostrar tareas realizadas \n");
        printf("4-Mostrar tareas pendientes \n");
        printf("5-Eliminar tareas  \n");

        printf("6-Cerrar \n");
        scanf("%d", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            while (Op2 == 1)
            {
                libroAux = cargarTarea(&id);
                AgregarLibro(&listaPendientes, libroAux);
                printf("quiere cargar otra tarea \n 1: para si, 0 para no \n");
                scanf("%d", &Op2);
                fflush(stdin);
            }

            break;

        case 2:

            printf("Comienza a mover \n ********************* \n");

            moverTarea(&listaPendientes, &listaR);
            break;


        case 3:

            printf("  ******************\n Mostrar lista de realizado  \n");
            MostrarLista(listaR);
            break;

        case 4:
            printf("******************\n Mostrar lista de pendientes  \n ");
            MostrarLista(listaPendientes);
            break;
        case 5:
            eliminarTareaPorId(&listaPendientes, &listaR);

            break;

        default:
            break;
        }

    } while (opcion != 6);

    while (listaPendientes)
    {
        free(listaPendientes);
        listaPendientes = listaPendientes->siguiente;
    }

    return 0;
}



Nodo *CrearListaVacia()
{
    return NULL;
}
Nodo *CrearNodo(Tarea tarea)
{
    Nodo *aux = (Nodo *)malloc(sizeof(Nodo));
    aux->tarea.id = tarea.id;
    aux->tarea.descripcion = malloc(sizeof(char) * strlen(tarea.descripcion));
    strcpy(aux->tarea.descripcion, tarea.descripcion);
    aux->tarea.duracion = tarea.duracion;
    aux->siguiente = NULL;
    return aux;
}
Tarea cargarTarea(int *id)
{
    Tarea aux;
    char buffer[20];
    (*id)++;
    aux.id = *id;
    printf("ingrese la descripcion de la tarea \n");
    gets(buffer);
    fflush(stdin);
    aux.descripcion = malloc(sizeof(char) * strlen(buffer));
    strcpy(aux.descripcion, buffer);

    printf("ingrese la duracion de la tarea \n");
    scanf("%d", &aux.duracion);
    fflush(stdin);

    return aux;
}
void AgregarLibro(Nodo **Lista, Tarea Tarea)
{
    Nodo *nuevoNodo = CrearNodo(Tarea);
    nuevoNodo->siguiente = *Lista;
    *Lista = nuevoNodo;
}
void agregarNodo(Nodo **lista, Nodo *newNodo)
{
    newNodo->siguiente = *lista;
    *lista = newNodo;
}
void MostrarLista(Nodo *lista)
{

    int indice = 0;
    Nodo *aux = lista;
    while (aux)
    {
        printf("************* \n ");
      
        printf("el id del tarea es : %d \n ", aux->tarea.id);
        printf("el descripcion del tarea es : ");
        puts(aux->tarea.descripcion);

        printf("la duracion de la tarea es : %d \n ", aux->tarea.duracion);

        aux = aux->siguiente;
        indice++;
    }
}



void eliminarTareaPorId(Nodo **listaP, Nodo **listaR)
{
    int id;
    printf("ingrese el id de la tarea a buscar \n");
    scanf("%d", &id);
    fflush(stdin);
    Nodo *aux = *listaP;
    Nodo *auxAnterior = NULL;
    while (aux && aux->tarea.id != id)
    {
        auxAnterior = aux;
        aux = aux->siguiente;
    }
    if (aux == *listaP)
    {
        *listaP = aux->siguiente;
        free(aux);
        printf("Se elimino la tarea de id nro %d de la lista de Pendientes\n", id);
    }
    else if (aux)
    {
        auxAnterior->siguiente = aux->siguiente;
        free(aux);
        printf("Se elimino la tarea de id nro %d de la lista de Pendientes\n", id);
    }
    else if (aux == NULL)
  
    { 
        printf("ingresa al aux == null y redefine aux");
        aux = *listaR;
        while (aux!= NULL && aux->tarea.id != id)
        {
            auxAnterior = aux;
            aux = aux->siguiente;
        }
        if (aux == NULL)
        {
            printf("no se encontro la tarea de id nro %d\n", id);

        } else
       
        if (aux == *listaR)
        {
            *listaR = aux->siguiente;
            free(aux);
            printf("Se elimino la tarea de id nro %d de la lista de Realizados\n", id);
        }
        else if (aux!=NULL)
        {
            auxAnterior->siguiente = aux->siguiente;
            free(aux);
            printf("Se elimino la tarea de id nro %d de la lista de Realizados\n", id);
         }
     
        }
        
    
  

}




Nodo *extraerTareaPorId(Nodo **lista, int id)
{
    Nodo *aux = *lista;
    Nodo *auxAnterior = *lista;
    while (aux && aux->tarea.id != id)
    {
        auxAnterior = aux;
        aux = aux->siguiente;
    }
    if (aux == *lista)
    {
        *lista = aux->siguiente;
    }
    else
    {
        auxAnterior->siguiente = aux->siguiente;
    }

    return aux;
}
void moverTarea(Nodo **listaPend, Nodo **listaR)
{
    int opcion = 0;
    Nodo *aux = *listaPend;
    Nodo *auxDos = NULL;
    while (aux)
    {
        printf("Tarea nro : %d \n ", aux->tarea.id);
        printf("el descripcion del tarea es : ");
        puts(aux->tarea.descripcion);
        printf("la duracion de la tarea es : %d \n ", aux->tarea.duracion);
        printf("realizo este tarea? \n ingrese 1 para si 0 para no");
        scanf("%d", &opcion);
        fflush(stdin);
        if (opcion == 1)
        {
            auxDos = aux;
            aux = aux->siguiente;
            auxDos = extraerTareaPorId(listaPend, auxDos->tarea.id);
            agregarNodo(listaR, auxDos);
        }
        else
        {
            aux = aux->siguiente;
        }
    }
}