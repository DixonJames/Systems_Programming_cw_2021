#include<stdio.h>
#include<stdlib.h>

struct node{
  char* data;
  struct node *next;
};

struct LList{
  int count;
  struct node* head;
};

int compare(const int **x, const int **y);
void add_to_LL(struct LList* list, char* data);
void file_to_LL(struct LList* list, FILE* fp);
char** LL_to_arrayOfPointers(struct LList* list);
char** sort_arrayOfPointers(char** array);
void output_sorted_arrayOfPointers(char** array);
char* coppy_str(char string[]);


int compare(const int **x, const int **y) {
    const int a = **x;
    const int b = **y;

    if(a < b)
        return -1;
    else
        return 1;
}

void add_to_LL(struct LList* u, char* data){
  int len_string = sizeof(*data)/sizeof('a');
  char* data_coppy = malloc(sizeof(data));

  struct node* newnode = malloc(sizeof(struct node));
  data_coppy = data;

  newnode->data = data_coppy;
  newnode->next = NULL;

  if((u->head == NULL)){
    u->head = newnode;
  }
  else{
    struct node* current = u->head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newnode;
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

void file_to_LL(struct LList* list, FILE* fp){
  //returns a char pointer to memory containing a string of (inicialy) unknown length
  char* string;
  int charactar;
  int length = 0;
  int starting_size =2;

  string = malloc(sizeof(*string)*starting_size);
  if((string == NULL)){
    return string;
  }

  while((charactar != '/n') && (EOF !=(charactar = fgetc(fp)))){
    string[length] = charactar;
    length++ ;

    if((length == starting_size)){
      starting_size += 16;
      string = realloc(string, sizeof(*string)*(starting_size));
      if((string == NULL)){
        return string;
      }
    }
  }

  length++ ;
  string[length] = '\0';
  
  return string;
}

int main() { 
  FILE *fp;
  fp = fopen("d/testfile.txt","r");
  if((fp == NULL)){
    exit(1);
  }
  struct LList *mylist = malloc(sizeof(struct LList));

  file_to_LL(fp, mylist);




  char* test_data = "hello";
  add_to_LL(mylist, test_data);
}


