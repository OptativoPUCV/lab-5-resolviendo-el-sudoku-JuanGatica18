#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    int i,j;

    for(i = 0; i<9;i++)
    {
      int seen[10] = {0};
      for (j = 0; j < 9; j++)
      {
        int val = n->sudo[i][j];
        if (val != 0)
        {
          if (seen[val]) return 0;
          seen[val] = 1;
        }
      }
      
    }

    for(j = 0; j<9;j++)
    {
      int seen[10] = {0};
      for (i = 0; i < 9; i++)
      {
        int val = n->sudo[i][j];
        if (val != 0)
        {
          if (seen[val]) return 0;
          seen[val] = 1;
        }
      }
    }

    for (int k = 0; k < 9; k++)
    {
      int seen[10]= {0};
      int fila = 3 * (k/3);
      int col = 3 * (k % 3);
      for (int i = fila; i < fila; i++)
      {
        for (int j = col; j < col; j++)
        {
          int valor = n->sudo[i][j];
          if (valor != 0)
          {
            if (seen[valor]) return 0;
            seen[valor] = 1;
            
          }
          /* code */
        }
        
      }
      
    }
    

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int buscar = 0;

    for (int i = 0; i< 9 && !buscar; i++)
    {
      for(int j = 0; j<9 && !buscar; j++)
      {
        if (n->sudo[i][j] == 0)
        {
          buscar = 1;
          for (int num = 1; num <= 9; num++)
          {
            Node* nuevo_nodo = copy(n);
            nuevo_nodo->sudo[i][j] = num;
            if (is_valid(nuevo_nodo))
            {
              pushBack(list, nuevo_nodo);
            }
            else
            {
              free(nuevo_nodo);
            }
            
          }
          
        }
      }
    }
    return list;
}


int is_final(Node* n)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        return 0;
      }
      
    }
    
  }
  

    return 1;
}

Node* DFS(Node* initial, int* cont){
  List* lista = createList();
  pushFront(lista, initial);
  *cont = 0;

  while (get_size(lista) > 0)
  {
    (*cont)++;
    Node* siguiente = front(lista);
    popFront(lista);
    if (is_final(siguiente))
    {
      while (!is_empty(lista))
      {
        Node* aux = front(lista);
        popFront(lista);
        free(aux);
      }
      return siguiente;
    }
    List* nodos_adjuntos = get_adj_nodes(siguiente);
    Node* nodo_adjunto = first(nodos_adjuntos);
    while (nodo_adjunto != NULL)
    {
      pushFront(lista, nodo_adjunto);
      nodo_adjunto = next(nodos_adjuntos);
      /* code */
    }
    

  }
  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/