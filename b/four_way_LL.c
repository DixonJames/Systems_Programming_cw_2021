#include<stdio.h>
#include<stdlib.h>


struct node{
  char data;
  struct node *above;
  struct node *below;
  struct node *right;
  struct node *left;
};

struct board_structure{
  int rows;
  int cols;
  struct node *head;
};

void add_to_board(struct board_structure *list, int x, int y, char data);
void rotate_row(struct board_structure *list, int row_num);

void free_board(struct board_structure *list);
void base_board_setup(struct board_structure *list, int cols);
struct node* query_board_structure(struct board_structure *list, int x, int y);
struct board_structure* setup_board();


struct board_structure* setup_board(){
    struct board_structure *mylist = malloc(sizeof(struct board_structure));
    return mylist;
}

void base_board_setup(struct board_structure *list, int cols){

    struct node* current = list->head;
    struct node* previous = NULL;

    char blank = '_';

    for(int i = 0; i < cols; i++){
        struct node* newnode = malloc(sizeof(struct node));
        newnode->data = blank;
        
        if(previous == NULL){
            list->head = newnode;
            previous = newnode;
            current = newnode->right;
            list->cols ++;
        }else{
            newnode->left = previous;
            previous->right = newnode;

            previous = newnode;
            current = newnode->right;
            list->cols++;
        }
        
    }
    struct node* newnode = malloc(sizeof(struct node));
    newnode->data = blank;
    newnode->right = list->head;
    list->head->left = newnode;

    previous->right = newnode;
    newnode->left = previous;
    

    return;
        
    }


struct node* query_board_structure(struct board_structure *list, int x, int y){

    //returnin list.head means the slot is on the borad but is free
    //returning list.head.next means that the x or y are out of bounds
    struct node* blank = list->head;
    if(x > list->cols || y > list->rows){
        //returning list.head.next means that the x or y are out of bounds
        return blank->right;
    }

    struct node* current = list->head;
    for(int i = 0; i < x; i++){
        current = current->right;
    }

    struct node* base = current;
    
    //goes up y
    //j is number of things alrady in collumb
    int j = 0;
    while (current->above != NULL){
        j++ ;
        current = current->above;
        //if reach the specifed y, then list[y][x] != NULL
        if(j == y){
            return current;
        }
    }
    //if reach the specifed y, then list[y][x] == NULL
    return list->head;

    
    }
    
    

void add_to_board(struct board_structure *list, int x, int y, char data){
    if(query_board_structure(list, x,y) == list->head){
        //mean that the spot is free and is not off the board
        //now go up collumb to find first available slot
        struct node* current = list->head;
        for(int i = 0; i < x; i++){
            current = current->right;

        }

        //goes to top of collumb (or stays at base if no collumb)
        int i = 0;
        while (current->above != NULL){
            current = current->above;
            i++;
        }

        struct node* newnode = malloc(sizeof(struct node));
        newnode->data = data;
        //ficing above and below neighbors
        //only connects to bellow if it is not a base node
        
        newnode->below =current;
        
        current->above = newnode;
        if(newnode->below->right != NULL){
            newnode->right = newnode->below->right->above;
        }

        if(newnode->below->left != NULL){
            newnode->right = newnode->below->right->above;
        }
        


        
    }
}


void rotate_row(struct board_structure *list, int row_num){
    for(int i= 0; i <= list->cols; i++){
        struct node* current;
        struct node* temp;

        if(query_board_structure(list, i, row_num) != list->head){
            current = query_board_structure(list, i, row_num);
            while(current->right != NULL){
                temp = current->right;

                current->above = temp->above;
                current->below =temp->below;
                current->right = temp->right;
                current->left = temp->left;
                temp = current;
                i++;
            }
            
        }
        //now have current being next to a gap to the right of it

        //need to find the top of the col to the right

        //goes up y
        struct node* r_col_interator = query_board_structure(list, i, 0)->right;
        int top_r_col;
        while (r_col_interator->above != NULL){
            top_r_col++ ;
            r_col_interator = r_col_interator->above;
        }

        current->below = r_col_interator;
        current->right = r_col_interator->right->above;
        current->left = r_col_interator->left->above;
        current->above  = NULL;
            
        if(top_r_col + 1 == row_num){
            i++;
        }
            
        //if the top_r_col is one less than the row we are on, skip a col as we have just moved to the same row

        struct node* top_of_right_col;

        }
    }



void main(){
    char p1 = "x";
  struct board_structure *mylist = setup_board();
  base_board_setup(mylist, 6);

  mylist->rows = 10;
  add_to_board(mylist, 1,1, p1);
  add_to_board(mylist, 1,2, p1);
  add_to_board(mylist, 2,3, p1);

  
  struct node* peice = query_board_structure(mylist, 1,1);
  

  

  printf("done");
}