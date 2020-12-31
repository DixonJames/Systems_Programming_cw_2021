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

void free_board_content(struct board_structure *list);
void base_board_setup(struct board_structure *list, int cols);
struct node* query_board_structure(struct board_structure *list, int x, int y);
struct board_structure* setup_board();

void free_board_content(struct board_structure *list){
    //for each base (starting at the final base)
    //work way down the collumb, freeing each node along the way. then free base

    
    for(int i = 0; i <= list->cols; i++){
        
        struct node* current = list->head;
        for(int ii = 0; ii < (list->cols - i); ii++){
            current = current->right;
        }
        //current now at base of col

        while (current->above != NULL)
        {
            current = current->above;
        }
        //current now at top of col

        while (current->below != NULL)
        {
            current = current->below;
            free(current->above);
        }
        //now freed the collumb
        free(current);
        //now freed the base of the collumb
    }


}

struct board_structure* setup_board(){
    struct board_structure *mylist = malloc(sizeof(struct board_structure));
    return mylist;
}

void base_board_setup(struct board_structure *list, int cols){

    struct node* current = list->head;
    struct node* previous = NULL;

    char blank = '_';

    for(int i = 1; i < cols; i++){
        struct node* newnode = malloc(sizeof(struct node));
        newnode->data = blank;
        
        if((previous == NULL)){
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
    y++;
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
            if(newnode->below->right->above != NULL){
                newnode->below->right->above->left = newnode;
            }
            
        }

        if(newnode->below->left != NULL){
            newnode->left = newnode->below->left->above;
            if(newnode->below->left->above != NULL){
                newnode->below->left->above->right = newnode;
            }
        }
        


        
    }
}

void rotate_row(struct board_structure *list, int row_rotaion_num){
    //!!!!!!!!!!!have to input rows as starting at 1 from bottom!!!!!!!! (beacause -0 == 0)
    int direction = row_rotaion_num;
    row_rotaion_num = abs(row_rotaion_num) -1;
    //create the new board
    struct board_structure *new_list = setup_board();
    base_board_setup(new_list, list->cols+1);
    new_list->rows = list->rows;

    //go through the board row by row starting at the bottom
    //add each to new board from left to right
    //when get to the row that is shifting, place in new board either to the right or left by 2 (depending on sighn on row_num)

    for(int row_num = 0; row_num <= list->rows; row_num++){
        for(int col_num = 0; col_num <= list->cols ; col_num++){
            int insert_x = col_num;
            int insert_y = row_num;

            if((row_num == row_rotaion_num && (abs(direction) == direction))){
                insert_x ++;
                if(insert_x > list->cols){
                    insert_x = 0;
                }
            }
            if((row_num == row_rotaion_num && (abs(direction) != direction))){
                insert_x --;
                if(insert_x < 0){
                    insert_x = list->cols;
                }
            }

            if(query_board_structure(list, col_num, row_num) != list->head){
                add_to_board(new_list, insert_x, insert_y, query_board_structure(list, col_num, row_num)->data);
            }
        }
        
    }
    //free up everything from the old head
    free_board_content(list);
    
    //now set the head of the hold list equal to the head of the new shifted list
    list->head = new_list->head;

    //free the new_list structure as its content has been assighned to the old list
    free(new_list);

    
    
    }



int main(){
    char p1 = "x";
  struct board_structure *mylist = setup_board();
  base_board_setup(mylist, 6);

  mylist->rows = 10;
  add_to_board(mylist, 1,1, p1);
  add_to_board(mylist, 1,1, p1);

  //add_to_board(mylist, 3,0, p1);
  //add_to_board(mylist, 3,1, p1);


  //add_to_board(mylist, 5,0, p1);
  //add_to_board(mylist, 5,1, p1);
  
  

  rotate_row(mylist, -1);

  //to free everything:
  //free_board_content(mylist);
  //free(mylist);
  

  

  
  struct node* peice = query_board_structure(mylist, 1,1);
  

  

  printf("done");
  return 0;
}