#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

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
void output_sorted_array(FILE* out_pointer, char** sorted_arraym, int length);
int reverse_compare(const void *first_in, const void *second_in);
int numeric_compare(const void *first_in, const void *second_in);
int reverse_numeric_compare(const void *first_in, const void *second_in);
void stdin_to_llist(struct LList* list);

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

int reverse_compare(const void *first_in, const void *second_in){
  const char *A = *(const char **)first_in;
  const char *B = *(const char **)second_in;
  int res = strcmp(A, B);
  return res * -1;
}

int numeric_compare(const void *first_in, const void *second_in){
  const char *A = *(const char **)first_in;
  const char *B = *(const char **)second_in;

  int A_is_int = isdigit(A[0]);
  int B_is_int = isdigit(B[0]);

  if((A_is_int > 0)&&(B_is_int > 0)){
    return compare(first_in, second_in);
  }
  if((A_is_int == 0)&&(B_is_int > 0)){
    return -1 ;
  }
  if((A_is_int > 0)&&(B_is_int == 0)){
    return 1;
  }
  return strcmp(first_in, second_in);
}

int reverse_numeric_compare(const void *first_in, const void *second_in){
  const char *A = *(const char **)first_in;
  const char *B = *(const char **)second_in;

  int A_is_int = isdigit(A[0]);
  int B_is_int = isdigit(B[0]);

  if((A_is_int > 0)&&(B_is_int > 0)){
    return compare(first_in, second_in) * -1;
  }
  if((A_is_int == 0)&&(B_is_int > 0)){
    return 1 ;
  }
  if((A_is_int > 0)&&(B_is_int == 0)){
    return -1;
  }
  return reverse_compare(first_in, second_in);
}

void stdin_to_llist(struct LList* list){
  char* new_line = "\n";
  char* line = NULL;
  size_t size=0;
  
  while(getline(&line, &size, stdin) >0){
    int number = 0;
    sscanf(line,"%d", &number);
    if(("\n" != line)){
      int final_index = strlen(line);

      if((line[final_index-1] != '\n')){
        strncat(line, new_line, 1);
      }
      

      add_to_LList(list, coppy_str(line));
    }
    
  }
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
    char new_line = '\n';
    strncat(string, &new_line ,1 );
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

void output_sorted_array(FILE* out_pointer, char** sorted_array, int length){
  
  for(int i = 0; i< length; i++){
    if((sorted_array[i] != "\n")){
      fprintf(out_pointer, "%s",sorted_array[i]);
    }
  }
  //fprintf(out_pointer, "\n");
}







int main(int argc, char *argv[]){
  //int argc, char *argv[]
  

  /*
  int argc = 3;
  char *argv[argc];
  argv[0] = "-n";
  argv[1] = "-r";
  //argv[2] = "thisifle";
  argv[2] = "d/testsort.txt";
  //argv[2] = "d/testsort.txt";
  */
  
  
  
  

  char* option_char[1];
  option_char[0]= "-";

  int o_option = 0;
  int r_option = 0;
  int n_option = 0;
  int h_option = 0;

  int found_outfile = 0;
  int found_infile = 0;

  for(int arg_num = 0; arg_num < argc; arg_num++){
    int size_of_arg = strlen(argv[arg_num]);
    if(((argv[arg_num])[0] == *option_char[0])){
      for(int arg_char = 0; arg_char < size_of_arg; arg_char ++){

        switch ((argv[arg_num])[arg_char]){
          case '-':
            break;

          case 'o':
            o_option = 1;
            break;

          case 'r':
            r_option = 1;
            break;

          case 'h':
            h_option = 1;
            break;

          case 'n':
            n_option = 1;
            break;

          default:
            fprintf(stderr, "invalid option entered");
            exit(1);
        }
      }
    }
  }
  if((h_option)){
    printf("done:\n> taking an arbortratitly long line from a arbritary number of rows via dynamic allocation of memory depending on the length and number of input strings to sort.\n> sorting said lines with q-sort \n> can sort numeric, reversed and a compination of the two \n> can output sorted lines into a new file, or stdout\n");
    return 1;
  }
    
  char* files[2];
  int file_num = 0;
  
  for(int arg_num = 1; arg_num < argc; arg_num++){
    if(((argv[arg_num])[0] != *option_char[0])){

      if((found_outfile == 0)||(found_outfile == o_option)){
        files[file_num] = argv[arg_num];
        file_num++ ;
      }
      else{
        fprintf(stderr, "\ninvalid number of files entered\n");
        exit(1);
      }
    }
  }

  if((o_option == 1)&&(file_num == 0)){
    fprintf(stderr, "\noutput file option selected, but no output file name provided\n");
    exit(1);
  }
  if((o_option == 0)&&(file_num > 1)){
    fprintf(stderr, "\noutput file option not selected, and too many output file names provided\n");
    exit(1);
  }
  







  //opens file and puts its lines into a ll
  struct LList *mylist = malloc(sizeof(struct LList));

  char* inputfile[1];
  char* outputfile[1];

  if((o_option == 1)){
    
    if((file_num == 2)){
      inputfile[0] = files[1];
      outputfile[0] = files[0];
    }
    if((file_num == 1)){
      inputfile[0] = NULL;
      outputfile[0] = files[0];
    }

  }
  else{
    if((file_num == 1)){
      inputfile[0] = files[0];
      outputfile[0] = NULL;
    }
    else{
      inputfile[0] = NULL;
      outputfile[0] = NULL;
    }
  }


//working out where to take input from
  if((inputfile[0] != NULL)){
    FILE *fp;
    
    fp = fopen(inputfile[0],"r");
    file_to_llist(fp, mylist);
  }
  else{
    stdin_to_llist(mylist);
  }
  
  
  

  //takes all addresses pointers in linked list and puts them into an array
  char* dummy_val = "null";
  add_to_LList(mylist, dummy_val);
  char** data = array_of_data_addresses(mylist);

  char* unpacked[mylist->count -1];
  for(int i = 0; i< mylist->count -1; i++ ){
    unpacked[i] = data[i];
  }


  //sorts the array of pointers
  if((n_option == 0)&&(r_option == 0)){
    qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), compare);
  }
  if((n_option == 1)&&(r_option == 0)){
    qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), numeric_compare);
  }
  if((n_option == 0)&&(r_option == 1)){
    qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), reverse_compare);
  }
  if((n_option == 1)&&(r_option == 1)){
    qsort(unpacked, mylist->count -1, sizeof(unpacked[0]), reverse_numeric_compare);
  }
  
  char* sorted_arr[mylist->count -1];
  for(int i = 0; i< mylist->count -1; i++ ){
    sorted_arr[i] = unpacked[i];

  }




  //outputs the aarray of pointers
  if(outputfile[0] == NULL){
    output_sorted_array(stdout, sorted_arr, mylist->count -1);
  }
  else{
    FILE* fp = fopen(outputfile[0], "w");
    output_sorted_array(fp, sorted_arr, mylist->count -1);
  }
  


  //free_LList(mylist);
  
  return 1;
}


