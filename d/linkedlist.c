#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node *next;
};

struct LList{
  int count;
  struct node *head;
};

void add_to_LList(struct LList *list, int data);
void Read_LList(struct LList *list);
void free_LList(struct LList *list);
int** array_of_data_addresses(struct LList *list);
int compare(const int **x, const int **y);




int** array_of_data_addresses(struct LList *list){
  int **arrd; 
  *arrd = (int *)malloc(list->count * sizeof (int*));

  

  struct node *c_ptr = list->head;
  int i = 0;
  for(; i < list->count -1;i++){
    arrd[i] = &(c_ptr->data);
    printf("\n%d\n",c_ptr->data );

    c_ptr = c_ptr->next;
  }

  arrd[i] = &(c_ptr->data);
  printf("\nj%d\n",c_ptr->data );

  return arrd;
}


void Read_LList(struct LList *list){
  struct node *c_ptr = list->head;
  while (c_ptr->next != NULL)
  {
    printf("%d", c_ptr->data);
    c_ptr = c_ptr->next;
  }
  printf("%d", c_ptr->data);
  return;
}

void free_LList(struct LList *list){
  if(list->head != NULL){
    struct node *curret_ptr = list->head;
    struct node *next_ptr = list->head;
    while (curret_ptr != NULL){
      next_ptr = curret_ptr->next;
      free(curret_ptr);
      curret_ptr = next_ptr;
    }
  free(list);
  return;
  }
  

}

void add_to_LList(struct LList *list, int data){
  struct node *head = list->head;
  struct node *new_node = malloc(sizeof(struct node));

  if(new_node == NULL){
    exit(1);
  }
  list->count ++ ;

  new_node->data = data;
  new_node->next = NULL;

  if(head == NULL){
    list->head = new_node;
    return;
  }
  
  struct node *c_ptr = list->head;
  while (c_ptr->next != NULL)
  {
    c_ptr = c_ptr->next;
  }
  
  c_ptr->next = new_node;

  
  return;
}

int compare(const int **x, const int **y) {
    const int a = **x;
    const int b = **y;

    if(a < b)
        return -1;
    else
        return 1;
}

void main(){

  struct LList *mylist = malloc(sizeof(struct LList));
  add_to_LList(mylist,  3);
  add_to_LList(mylist,  2);
  add_to_LList(mylist,  'a');
  add_to_LList(mylist,  0);

  int** data = array_of_data_addresses(mylist);
  int* unpacked[mylist->count -1];

  for(int i = 0; i< mylist->count; i++ ){
    unpacked[i] = data[i];
  }

  int num = sizeof(unpacked)/sizeof(unpacked[0]);
  int width = sizeof(unpacked[0]);

  qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), compare);
  

  free_LList(mylist);
  printf("done");
}


