#include<stdio.h>
#include<stdlib.h>

struct node{
  void* data;
  struct node *next;
};

struct LList{
  int count;
  struct node *head;
};

void add_to_LList(struct LList *list, void* data);
void Read_LList(struct LList *list);
void free_LList(struct LList *list);

int** array_of_data_addresses(struct LList *list);
int compare(const int **x, const int **y);
void file_to_llist(FILE* fp, struct LList* list);
void file_to_linkedList(FILE* fp, struct LList* list);
int lines_in_file(FILE* fp);
char* coppy_str(char string[]);


int** array_of_data_addresses(struct LList *list){
  int **arrd; 
  *arrd = (int *)malloc(list->count * sizeof (int*));

  

  struct node *c_ptr = list->head;
  int i = 0;
  for(; i < list->count -1;i++){
    arrd[i] = c_ptr->data;


    c_ptr = c_ptr->next;
  }

  arrd[i] = (c_ptr->data);


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

int compare(const int **x, const int **y) {
    const int a = **x;
    const int b = **y;

    if(a < b)
        return -1;
    else
        return 1;
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


void file_to_linkedList(FILE* fp, struct LList* list){
  char* whole_string;
  int lower_char = 0;
  int higher_char = 0;

  file_to_llist(fp, list);

  for( ;whole_string[higher_char]; higher_char++){

    if((whole_string[higher_char] == '\n')){
      char add_string[higher_char - lower_char];

      for(int i = lower_char; i <= higher_char; i++){
        add_string[i] = whole_string[i];
      }
      add_to_LList(list,&add_string);
      lower_char = higher_char;

    }
  }


  
}






int main(){

  FILE *fp;
  fp = fopen("d/testsort.txt","r");
  struct LList *mylist = malloc(sizeof(struct LList));
  file_to_linkedList(fp, mylist);




  

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
  

  free_LList(mylist);
  printf("done");
  return 1;
}


