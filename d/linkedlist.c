#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node{
  char* data;
  struct node *next;
};

struct LList{
  int count;
  struct node *head;
};

void add_to_LList(struct LList *list, void* data);
void Read_LList(struct LList *list);
void free_LList(struct LList *list);

char** array_of_data_addresses(struct LList *list);
int compare(const void *first_in, const void *second_in);
void file_to_llist(FILE* fp, struct LList* list);
char* coppy_str(char string[]);
void output_sorted_array(FILE* out_pointer, char** sorted_array);


char** array_of_data_addresses(struct LList *list){
  //need to add a null onto the end of LL
  
  char **arrd; 
  *arrd = (char *)malloc((list->count ) * sizeof (char*));

  

  struct node *c_ptr = list->head;
  int i = 0;
  for(; i < list->count -1 ;i++){
    arrd[i] = (char*)c_ptr->data;


    c_ptr = c_ptr->next;
  }

  


  return arrd;
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

void add_to_LList(struct LList *list, void* data){
  struct node *head = list->head;
  struct node *new_node = malloc(sizeof(struct node));

  if(new_node == NULL){
    exit(1);
  }
  list->count ++ ;

  new_node->data = data;
  new_node->next = NULL;

  if(list->head == NULL){
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

int compare(const void *first_in, const void *second_in){
    const char *A = *(const char **)first_in;
    const char *B = *(const char **)second_in;
    return strcmp(A, B);
}

void file_to_llist(FILE* fp, struct LList* list){
  
  //returns a char pointer to memory containing a string of (inicialy) unknown length
  char* string;
  int charactar;
  int length = 0;
  int starting_size = 2;
  int cont = 1;


  while((EOF !=(charactar = fgetc(fp)))){

    string = malloc(sizeof(*string)*starting_size);
    if((string == NULL)){
      exit(1);
    }

    while((charactar != '\n') && (EOF !=(charactar))&& (cont == 1)){
      string[length] = charactar;
      length++ ;

      if((length == starting_size)){
        starting_size += 16;
        string = realloc(string, sizeof(*string)*(starting_size));
        if((string == NULL)){
          cont = 0;
        }
      }

      charactar = fgetc(fp);
    }

    length++ ;
    string[length] = '\0';
    length = 0;

    char* string_cpy = coppy_str(string);
    free(string);
    
    add_to_LList(list, string_cpy);

    
}
}

char* coppy_str(char string[]){
  char* copy;
  copy = (char*)malloc(strlen(string)+1);

  int i;
  for(i = 0; i < strlen(string); i++){
    copy[i] = string[i];
  }
  copy[i] = '\0';
  return copy;
}

void output_sorted_array(FILE* out_pointer, char** sorted_array){
  int sorted_array_len = sizeof(sorted_array)/sizeof(sorted_array[0]);
  for(int i = 0; i< sorted_array_len; i++){
    fprintf(out_pointer, "\n%s",sorted_array[i]);
  }
}







int main(){

  FILE *fp;
  fp = fopen("testsort.txt","r");
  struct LList *mylist = malloc(sizeof(struct LList));
  file_to_llist(fp, mylist);

  char* dummy_val = "null";
  add_to_LList(mylist, dummy_val);
  char** data = array_of_data_addresses(mylist);

  char* unpacked[mylist->count -2];
  for(int i = 0; i< mylist->count -1; i++ ){
    unpacked[i] = data[i];
  }

  qsort(unpacked, mylist->count -2, sizeof(unpacked[0]), compare);

  

  output_sorted_array(stdout, unpacked);

  

  /*
  int** data = array_of_data_addresses(mylist);
  int* unpacked[mylist->count -1];

  for(int i = 0; i< mylist->count; i++ ){
    unpacked[i] = data[i];
  }

  int num = sizeof(unpacked)/sizeof(unpacked[0]);
  int width = sizeof(unpacked[0]);

  qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), compare);
  */
  

  //free_LList(mylist);
  printf("\ndone\n");
  return 1;
}


