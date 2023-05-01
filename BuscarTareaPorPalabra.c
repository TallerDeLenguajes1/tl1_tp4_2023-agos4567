#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
    // Tarea *tarea
} typedef Tarea;

// void Cargar

void cargarTarea(Tarea ** tareas, int can );
void MoverTareas(Tarea ** tareas, Tarea ** tareasR, int can);
void mostrarTareasRyP(Tarea ** tareas, Tarea ** tareasR, int can);
void BuscarTarea(Tarea **tareas, Tarea **tareasR, int can,  char *palabra);


int main(){



    int can;
    printf("ingrese cantidad de tareas: \n");
    scanf("%d", &can);
    fflush(stdin);
    Tarea **tareas = (struct Tarea **)malloc(sizeof(struct Tarea *) * can); // reserva de memoeria a un puntero que va a apuntar a una estrcutura

    for (int i = 0; i < can; i++)

    {

        tareas[i] = NULL;
   
        
    }
    //reserva del puntero doble
    //reserva de la estructura
    //reserva de la descripcion


// CARGAR TAREAS

cargarTarea(tareas,  can );



//tareas realizadas y pendientes (LAS PENDIENTES SON LAS **TAREAS)
    Tarea **tareasR = (struct Tarea **)malloc(sizeof(struct Tarea *) * can); // reserva de memoeria a un puntero que va a apuntar a una estrcutura
      for (int i = 0; i < can; i++)

    {

        tareasR[i] = NULL;
        
   
        
    }
   //TAREAS PREGUNTAS
   MoverTareas(tareas, tareasR,  can);


    /*5. Mostrar por pantalla todas las tareas realizadas y luego listar las tareas
pendientes.*/

mostrarTareasRyP( tareas,  tareasR,  can);




/*BUSCAR TAREA POR PALABRA*/

    char *aux;

    aux=malloc(sizeof(char)*30);

    printf("ingrese la palabra a buscar:\n");
    gets(aux);
    fflush(stdin);

 BuscarTarea(tareas,tareasR, can, aux);


/*HAGO FREE A SOLO A LO QUE SEA PUNTERO */
for (int i = 0; i < can; i++)
{
    free(tareas[i]->Descripcion);
    free(tareasR[i]->Descripcion);    

}
free(tareas); 
free(tareasR);



    // tareas[i].Duracion = 3;
    return 0;



}



void cargarTarea(Tarea ** tareas, int can ){
    
    srand(time(NULL));
    char aux[500];
 
    for (int i = 0; i < can; i++)

    {
        tareas[i] =malloc(sizeof(Tarea));
        tareas[i]->TareaID=i+1;
        
        
        tareas[i]->Duracion = 10+ rand()% (100-10);  

        printf("ingrese una descripcion de la tarea \n"); 
        gets(aux); 
        fflush(stdin); 
        tareas[i]->Descripcion = malloc(sizeof(char) * strlen(aux));
        strcpy( tareas[i]->Descripcion, aux);
        


        
    }

}





void MoverTareas(Tarea ** tareas, Tarea ** tareasR, int can){
     char respuesta[10];
    int j = 0;
    
     for (int i = 0; i < can; i++)

    {
        printf(" Realizo la tarea numero %d ?\n",  tareas[i]->TareaID);
        // printf(" duracion de la tarea %d\n",  tareas[i]->Duracion);
        printf("Cuya descripcion es: \n");  
        puts(tareas[i]->Descripcion);

        printf("ingrese SI para confirmar, NO para denegar\n"); 
        gets(respuesta); 
        fflush(stdin); 
        if (strcmp(respuesta, "si") == 0)
        {   
            tareasR[j] = tareas[i];
            printf("la respuesta es si funciona\n"); //para comprobar
            tareas[i] = NULL; // POR QUE???
            j++;
        }
        
    }
}







void mostrarTareasRyP(Tarea ** tareas, Tarea ** tareasR, int can){


printf("************* \n");
      printf("        Tareas realizadas      \n");
    for (int i = 0; i < can; i++)
    {

       
       
        if (tareasR[i] != NULL)// por que 
        {   
           
             printf(" la tarea numero %d \n",  tareasR[i]->TareaID);
             printf(" duracion de la tarea %d\n",  tareasR[i]->Duracion);
             printf("Cuya descripcion es: \n");  
        puts(tareasR[i]->Descripcion);
        }
        
    }
    


            printf("********************* \n");
            printf("          tareas pendiente         \n");
        for (int i = 0; i < can; i++)

        {
            if (tareas[i] != NULL)
            {   
                
                printf(" la tarea numero %d \n",  tareas[i]->TareaID);
            printf(" duracion de la tarea %d\n",  tareas[i]->Duracion);
                printf("Cuya descripcion es: \n");  
            puts(tareas[i]->Descripcion);
            }
            
        
    
    }


}





void BuscarTarea(Tarea **tareas, Tarea **tareasR, int can,  char *palabra){

int bandera=0;

           printf("      Buscar tarea:      \n");

        for (int i = 0; i < can; i++)
        {
            if (tareas[i] != NULL && strstr(tareas[i]->Descripcion, palabra))
            {
               
               
              printf("Tarea encontrada es :\n");
             printf("ID %d:\n",tareas[i]->TareaID);
             printf("Duracion de la tarea: %d\n", tareas[i]->Duracion);
             printf("Descripcion de la tarea:\n");
             puts(tareas[i]->Descripcion);
             bandera++;


            }else if (tareasR[i] != NULL &&  strstr(tareasR[i]->Descripcion, palabra))
                
                {
                          
                    printf("Tarea encontrada es: \n");
                    printf("ID %d:\n",tareasR[i]->TareaID);
                    printf("Duracion de la tarea: %d\n", tareasR[i]->Duracion);
                    printf("Descripcion de la tarea: ");
                    puts(tareasR[i]->Descripcion);
                    bandera++;
              
                }
                



            }

       

         if (bandera >0)
         {
        //    printf("se encontro la tarea buscada:\n");
         }else
         {
            printf("no se encontro la tarea buscada:\n");
         }


}





 
        


      