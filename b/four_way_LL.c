#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct board_structure *board;

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

struct move{
int column;
int row;
};

void add_to_board(struct board_structure *list, int x, int y, char data);
void rotate_row(struct board_structure *list, int row_num);
void free_board_content(struct board_structure *list);
void base_board_setup(struct board_structure *list, int cols);
char current_winner(struct board_structure *list);
struct node* query_board_structure(struct board_structure *list, int x, int y);
char next_player(struct board_structure *list); 
struct move read_in_move(struct board_structure* u);

struct board_structure* setup_board();
void play_move(struct move m, board u);
char is_winning_move(struct move m, board u);
void cleanup_board(board u);
int is_valid_move(struct move m, struct board_structure* u);

int r_win(struct node* current);
int l_win(struct node* current);
int u_win(struct node* current);
int d_win(struct node* current);
int tr_win(struct node* current);
int tl_win(struct node* current);
int br_win(struct node* current);
int bl_win(struct node* current);


int r_win(struct node* current){
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->right == NULL){
            return 0;
        }
        if(current->right->data != first->data){
            return 0;
        }
        
        current = current->right;
    }

    return 1;
}
int l_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->left == NULL){
            return 0;
        }
        if(current->left->data != first->data){
            return 0;
        }
        
        current = current->left;
    }

    return 1;
}
int u_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->above == NULL){
            return 0;
        }
        if(current->above->data != first->data){
            return 0;
        }
        
        current = current->above;
    }

    return 1;
}
int d_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->below == NULL){
            return 0;
        }
        if(current->below->data != first->data){
            return 0;
        }
        
        current = current->below;
    }

    return 1;
}
int tr_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->right == NULL){
            return 0;
        }
        if(current->right->above == NULL){
            return 0;
        }
        if(current->right->above->data != first->data){
            return 0;
        }
        
        current = current->right->above;
    }

    return 1;
}
int tl_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->left == NULL){
            return 0;
        }
        if(current->left->above == NULL){
            return 0;
        }
        if(current->left->above->data != first->data){
            return 0;
        }
        
        current = current->left->above;
    }

    return 1;
}
int br_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->right == NULL){
            return 0;
        }
        if(current->right->below == NULL){
            return 0;
        }
        if(current->right->below->data != first->data){
            return 0;
        }
        
        current = current->right->below;
    }

    return 1;
}
int bl_win(struct node* current){
    
    struct node* first = current;

    for(int i = 0; i < 3; i++){

        if(current->left == NULL){
            return 0;
        }
        if(current->left->below == NULL){
            return 0;
        }
        if(current->left->below->data != first->data){
            return 0;
        }
        
        current = current->left->below;
    }

    return 1;
}

void cleanup_board(board u){
    free_board_content(u);
    free(u);
}

struct move read_in_move(struct board_structure* u){
    printf("Player %c enter column to place your token: ",next_player(u));
    int column_int;
    scanf("%d", &column_int);

    printf("Player %c enter row to rotate: ",next_player(u));
    int row_int;
    scanf("%d", &row_int);

    struct move* current_move;
    current_move->column = column_int;
    current_move->row = row_int;

    return *current_move;
}

char current_winner(struct board_structure *list){
    char p1[1] = "x";
    char p2[1] = "o";
    char nw[1] = ".";
    char d[1] = "d";

    int x_win = 0;
    int o_win = 0;
    int b_full = 1;

    for(int i = 0; i< list->cols; i++){
        for(int j = 0; j< list->rows; j++){
            if((query_board_structure(list, i, j)!= list->head)){
                int current_win = 0;

                if(u_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(d_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(l_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(r_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(tr_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(tl_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(br_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                }
                if(bl_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                }

                char x_pointer[1] = "J";
                x_pointer[0]= (query_board_structure(list, i, j)->data);

                if((current_win == 1)){
                    if(((p1[0] - x_pointer[0]) == 0)){
                    x_win = 1;
                    }else{
                    o_win = 1;
                    }
                }
                
            }else{
                if(query_board_structure(list, i, j) == list->head){
                    b_full = 0;
                }
            }
        }
    }
    //both win, draw
    if((x_win == 1)&&(o_win == 1)){
        return d[0];
    }
    //none have won and board is full, draw
    if((x_win == 0)&&(o_win == 0)&&(b_full == 0)){
        return d[0];
    }
    //none win and bord is not full, no winner
    if((x_win == 0)&&(o_win == 0)){
        return nw[0];
    }

    //single wins
    if((x_win == 1)){
        return p1[0];
    }
    if((o_win == 1)){
        return p2[0];
    }

}

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

char next_player(struct board_structure *list){
    int x_count = 0;
    int o_count = 0;

    char p1[1] = "x";
    char p2[1] = "o";

    for(int x = 0; x < list->cols; x++){
        for(int y = 0; y< list->rows; y++){
            if(query_board_structure(list, x,y) != list->head){

                char char_pointer[1] = "Z";
                char_pointer[0]= query_board_structure(list, x,y)->data;


                if(((p1[0] - char_pointer[0]) == 0)){
                    x_count ++ ;
                }else{
                    o_count ++ ;
                    }
                }


            }
        }
    if((x_count == 0)&&(o_count == 0)){
        return p1[0];
    }
    if((x_count == o_count)){
        return p1[0];
    }
    if((x_count > o_count)){
        return p2[0];
    }
    if((x_count < o_count)){
        return p1[0];
    }
    }

int is_valid_move(struct move m, struct board_structure* u){
    char cw[1];
    cw[0] = current_winner(u);
    char dot[1];
    dot[0] = ".";

    //if anything other than 'no winner'. no move is valid.
    if((dot[0] - cw[0]) != 0){
        return 0;
    }

    //if any parts of m are outside of the playable area
    if((m.column > u->cols) || (m.row > u->rows) || (m.column < 1) || (m.row < 1)){
        return 0;
    }

    //if all ^ passed, then should be ok!
    return 1;

}

void play_move(struct move m, board u){
    if((is_valid_move(m, u) == 1)){
        
        char player_token = next_player(u);
        add_to_board(u, m.column,u->rows, player_token);

        rotate_row(u, m.row);
    }
}

char is_winning_move(struct move m, board u){

    struct board_structure *new_list = setup_board();
    base_board_setup(new_list, u->cols+1);
    new_list->rows = u->rows;

    //go through the board row by row starting at the bottom
    //add each to new board from left to right
    
    for(int row_num = 0; row_num <= u->rows; row_num++){
        for(int col_num = 0; col_num <= u->cols ; col_num++){
            if(query_board_structure(u, col_num, row_num) != u->head){
                add_to_board(new_list, col_num, row_num, query_board_structure(u, col_num, row_num)->data);
                int insert_x = col_num;
                int insert_y = row_num;
            }
            
        }
    }
    play_move(m, new_list);
    char test_winner[1];
    test_winner[0] = current_winner(new_list);

    //get rid of the testing baord
    free_board_content(new_list);
    free(new_list);

    return test_winner[0];
}   
    


        
    



int main(){

    
    char p1[1] = "x";
  struct board_structure *mylist = setup_board();
  base_board_setup(mylist, 6);

  mylist->rows = 10;

  //struct move mymove = read_in_move(mylist);
  add_to_board(mylist, 1,1, p1[0]);
  add_to_board(mylist, 2,1, p1[0]);
  add_to_board(mylist, 3,1, p1[0]);
  add_to_board(mylist, 4,1, p1[0]);

  //add_to_board(mylist, 3,0, p1);
  //add_to_board(mylist, 3,1, p1);


  //add_to_board(mylist, 5,0, p1);
  //add_to_board(mylist, 5,1, p1);
  
  

  //rotate_row(mylist, 1);
  int win = current_winner(mylist);

  //to free everything:
  //free_board_content(mylist);
  //free(mylist);
  

  

  
  
  

  
    cleanup_board(mylist);
  printf("done");
  return 0;
}