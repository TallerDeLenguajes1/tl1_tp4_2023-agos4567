#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Tarea{
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{

    Tarea * T;
    struct Nodo * Siguiente;

}Nodo;

Nodo * start;
Nodo * startPendiente;
Nodo * startRealizado;
Nodo * startProceso;

Nodo * ListaVacia();

Nodo * CrearNodo(Tarea * t);
void InsertarNodo(Nodo ** start, Tarea * t);
Tarea * CrearTarea(int i);

void MostrarLista(Nodo * start);
void MostrarNodo(Nodo * Nodo);//no lo usa
void MostrarDatos(Nodo * start);//calculo pedido

Nodo * QuitarNodoID(Nodo ** start, int id);
Nodo * QuitarNodoChar(Nodo ** start, char palabra[]);
void BuscarNodo(Nodo ** start, Nodo ** startRealizado);
// Nodo * BuscarNodoLista(Nodo ** start, int id);

void AgregarNodo(Nodo ** start, Nodo * Tnodo);


void eliminarNodoID(Nodo ** start,int id);

int main(){

srand(time(NULL));
start = ListaVacia();
startPendiente = ListaVacia();
startRealizado = ListaVacia();
startProceso = ListaVacia();



Nodo * aux;
int ID;
int opcion1 = 2; 
int opcion2; 
int opcion3;
int aux1 = 1;
int canTareas = 0;
int cont = 0;
int i = 0;


while (aux1 != 0)
{

printf("Quiere insertar una tarea?(si:1/no:0)\n");
scanf("%d", &aux1);    


if (aux1 == 1)
{
    i++;

    InsertarNodo(&startPendiente, CrearTarea(i));
}


}


while (opcion1 != 0)
{
    /*muestro todas las listas*/
            printf("******************\n 1_Mostrando lista de pendientes  \n ");
            MostrarLista(startPendiente);
            printf("******************\n 2_Mostrando lista de procesos  \n ");
            MostrarLista(startProceso);            
            printf("  ******************\n 3_Mostrando lista de realizado  \n");
            MostrarLista(startRealizado);

            printf("indique el id de la tarea que desea seleccionar \n");
            scanf("%d", &ID);
            fflush(stdin);
     
          
  
             printf("-----------Muevo Tareas--------------\n");

            printf("-------OPCIONES----------\n1_Mover tarea a otras listas\n2_Eliminar tarea de la lista\n");
            scanf("%d", &opcion2);
            fflush(stdin);


                switch (opcion2)
                {
                case 1:

                aux = QuitarNodoID(&startPendiente, ID);// si encuentra al nodo con el id identico, lo saca y lo devuelve a aux, es decir aux = nodoencontrado y si no lo encuentra devuelve NULL
                if (aux)// aux != NULL; si lo encontro, es decir que no es null, le pregunta a que lista lo quiere pasar
                {
                    printf("Su tarea esta en pendiente.\n");
                    printf("A que lista desea mover su Tarea:\n1- En proceso\n2- Realizada\n");//a que lista lo queres mover
                    scanf("%d", &opcion3);

                    switch (opcion3)
                    { 
                    case 1:
                        AgregarNodo(&startProceso, aux);
                        break;
                    case 2:
                        AgregarNodo(&startRealizado, aux);
                        break;
                    }

                }else 
                {
                    aux = QuitarNodoID(&startProceso, ID); 
                    if (aux)
                    {
                         printf("Su tarea esta en proceso.\n");
                         printf("Situacion de la tarea\n1- En Pendientes.\n2- realizada.\n");
                            scanf("%d", &opcion3);

                            switch (opcion3)
                            {
                            case 1:
                                AgregarNodo(&startPendiente, aux);
                                break;
                            case 2:
                                AgregarNodo(&startRealizado, aux);
                                break;
                            }
                    }else
                    {
                        aux = QuitarNodoID(&startRealizado, ID);
                        if (aux)
                        {
                               printf("Su tarea esta en realizada.\n");
                            printf("Situacion de la tarea\n1- En Pendientes.\n2- En proceso.\n");
                            scanf("%d", &opcion3);

                            switch (opcion3)
                            {
                            case 1:
                                AgregarNodo(&startPendiente, aux);
                                break;
                            case 2:
                                AgregarNodo(&startProceso, aux);
                                break;
                            }
                        }else
                        {
                           printf("No se encuentra el nodo.\n");
                        }
                        
                        
                    }
                    
                    
                }

                    printf("Desea modificar otra tarea?(si:1/no:0)\n");
                    scanf("%d", &opcion1);

                    break;

            /*ELIMINACION DE NODO*/
                    case 2:
              
                    eliminarNodoID(&startPendiente, ID);
                    eliminarNodoID(&startProceso, ID);
                    eliminarNodoID(&startRealizado, ID);

                    
                    printf("Desea modificar otra tarea?(si:1/no:0)\n");
                    scanf("%d", &opcion1);
                    break;
                
                }

}
printf("----MUESTRO CALCULO--- \n");
printf("----Lista pendientes-----\n");
MostrarDatos(startPendiente);
printf("----Liste en proceso----\n");
MostrarDatos(startProceso);
printf("----Lista realizadas----\n");
MostrarDatos(startRealizado);
           


while (startPendiente)
    {
        free(startPendiente);
        startPendiente = startPendiente->Siguiente;
    }
 while (startRealizado)
    {
        free(startRealizado);
        startRealizado = startRealizado->Siguiente;
    }


while (startProceso)
    {
        free(startProceso);
        startProceso = startProceso->Siguiente;
    }




    return 0;

}


Nodo * ListaVacia(){

    return NULL;
}

Nodo * CrearNodo(Tarea * t){

    Nodo * NuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    NuevoNodo->T = t;
    NuevoNodo->Siguiente = NULL;

    return NuevoNodo;
     }

 void InsertarNodo(Nodo ** start, Tarea * t){

    Nodo * NodoNuevo = CrearNodo(t);
    NodoNuevo->Siguiente = *start;
    *start = NodoNuevo;

 }    

 Tarea * CrearTarea(int i){

    char buffer[100];
    printf("Ingrese la descripcion de la tarea %d:\n",i);
    fflush(stdin);
    gets(buffer);

    Tarea * NuevaTarea = (Tarea*)malloc(sizeof(Tarea));

    NuevaTarea->TareaID = i;
    NuevaTarea->Descripcion = (char*)malloc(sizeof(char)*strlen(buffer));
    strcpy(NuevaTarea->Descripcion, buffer);
    
    NuevaTarea->Duracion = 0;

    while (NuevaTarea->Duracion < 10 || NuevaTarea->Duracion > 100)
    {
        printf("Ingrese la duracion de la tarea %d:\n", i);
        scanf("%d", &NuevaTarea->Duracion);

    }
    
    return NuevaTarea;
}

void MostrarLista(Nodo * start){

    printf("Tareas\n");

    Nodo * aux = start;

    while (aux != NULL)
    {
        printf("ID:%d\n", aux->T->TareaID);
        printf("Descripcion: %s\n", aux->T->Descripcion);
        printf("Duracion: %d\n", aux->T->Duracion);
        printf("------------------------------\n");
        
        aux = aux->Siguiente;
    }
    

}

void MostrarNodo(Nodo * Nodo){

        printf("ID:%d\n", Nodo->T->TareaID);
        printf("Descripcion: %s\n", Nodo->T->Descripcion);
        printf("Duracion: %d\n", Nodo->T->Duracion);
        printf("------------------------------\n");
}

void MostrarDatos(Nodo * start){

    int cant = 0;
    int tiempoAsociado = 0;
    Nodo *aux = start;
    if (aux == NULL)
    {
        printf("\n No hay elementos en la lista \n       ***************** \n \n");
    }
    else
    {
        while (aux)
        {
            cant++;
            tiempoAsociado += aux->T->Duracion;
            aux = aux->Siguiente;
        }
        printf("Esta lista contiene %d  tareas\n ", cant);
        printf("el tiempo asociado es de : %d \n ", tiempoAsociado);
    }
   
}

/*************************************************************************************************************************************************/
void AgregarNodo(Nodo ** start, Nodo * Tnodo){

    Tnodo->Siguiente = *start;
    *start = Tnodo;
}


Nodo * QuitarNodoChar(Nodo ** start, char palabra[]){

    Nodo * aux = *start;
    Nodo * antAux = *start;

    while (aux && strcmp(aux->T->Descripcion, palabra) != 1)
    {
        antAux = aux;
        aux = aux->Siguiente;
    }
    
    if (aux)
    {
        if (aux == *start)
        {
            *start = aux->Siguiente;
        }else
        {
            antAux->Siguiente = aux->Siguiente;
        }
        
        aux->Siguiente = NULL;
        
    }
    
}


Nodo * QuitarNodoID(Nodo ** start, int id){

    Nodo * aux = *start;
    Nodo * antAux = *start;

    while (aux && aux->T->TareaID != id)
    {
        antAux = aux;
        aux = aux->Siguiente;
    }

    if (aux)
    {
        if (aux == *start)
        {
            *start = aux->Siguiente;
        }else
        {
            antAux->Siguiente = aux->Siguiente;
        }
        
        aux->Siguiente = NULL;
        
    }
    
    
    return aux;

}



// Nodo * BuscarNodoLista(Nodo ** start, int id){

//     Nodo * aux = *start;

//     while (aux && aux->T->TareaID != id)
//     {
//         aux = aux->Siguiente;
//     }

//      return aux;   
    

// }

void BuscarNodo(Nodo ** start, Nodo ** startRealizado){

    Nodo * aux;
     Nodo * aux2;



    int opcion;
    int id;
    char clave[40];

    printf("Buscar Nodo:\n1_ID\n2_Palabra\n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        printf("Ingrese el id de la tarea:\n");
        scanf("%d", &id);
        aux = QuitarNodoID(start, id);
        aux2 =  QuitarNodoID(startRealizado, id);

        if (aux)
        {
            printf("Tarea %d Realizada", aux->T->TareaID);
            printf("Descripcion: %s\n", aux->T->Descripcion);
            printf("Duracion: %d\n", aux->T->Duracion);
            printf("------------------------------\n");

        }else
        {
            if (aux2)
            {
                printf("Tarea %d Realizada", aux2->T->TareaID);
                printf("Descripcion: %s\n", aux2->T->Descripcion);
                printf("Duracion: %d\n", aux2->T->Duracion);
                printf("------------------------------\n");
            }else
            {
                printf("No se encuentra el nodo.\n");
            }
            
            
        }
        
        
        break;
    
        case 2:

        printf("Ingrese la palabra clave:\n");
        fflush(stdin);
        gets(clave);

        printf("Ingrese el id de la tarea:\n");
        scanf("%d", &id);
         aux = QuitarNodoChar(start, clave);
         aux2 =  QuitarNodoChar(startRealizado, clave);

        if (aux)
        {
            printf("Tarea %d Realizada", aux->T->TareaID);
            printf("Descripcion: %s\n", aux->T->Descripcion);
            printf("Duracion: %d\n", aux->T->Duracion);
            printf("------------------------------\n");

        }else
        {
            if (aux2)
            {
                printf("Tarea %d Realizada", aux2->T->TareaID);
                printf("Descripcion: %s\n", aux2->T->Descripcion);
                printf("Duracion: %d\n", aux2->T->Duracion);
                printf("------------------------------\n");
            }else
            {
                printf("No se encuentra el nodo.\n");
            }
            
            
        }


        break;

    }


}



void eliminarNodoID(Nodo ** start,int id){
    Nodo * aux = *start;
    Nodo * antAux = *start;


    while (aux && aux->T->TareaID != id)
    {
        
        antAux = aux;
        aux = aux->Siguiente;
    }

    if (aux)
    {
        if (aux == *start)
        {
            *start = aux->Siguiente;
        }else
        {
            antAux->Siguiente = aux->Siguiente;
        }

        aux->Siguiente = NULL;
        free(aux);      
    }
    
    
}
