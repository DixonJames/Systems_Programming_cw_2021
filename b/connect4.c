//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connect4.h"
int number_cols(FILE *infile);
void free_board_content( board list);
struct node* query_board_structure(board list, int x, int y);
void base_board_setup(board list, int cols);
void add_to_board(board list, int x, int y, char data);
void rotate_row(board list, int row_num);

int r_win(struct node* current);
int l_win(struct node* current);
int u_win(struct node* current);
int d_win(struct node* current);
int tr_win(struct node* current);
int tl_win(struct node* current);
int br_win(struct node* current);
int bl_win(struct node* current);


struct board_structure {
    //rows and cols are the max indexes of the queryable nodes. as count goes from 0->rows/cols
  int rows;
  int cols;
  struct node *head;
};

struct node{
  char data;
  struct node *above;
  struct node *below;
  struct node *right;
  struct node *left;
};



//my declarations: 



//my functions:


struct node* query_board_structure(board list, int x, int y){
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

void free_board_content( board list){
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

int number_cols(FILE *infile){
    char ch;
    char cmp_char[4] = {'x', 'o', '.', '_'};
    int i = 0;

    int valid_char = 0;

    while ((ch = fgetc(infile)) != EOF){
        cmp_char[3] = ch;

        for(int j = 0; j < 3; j++){
            if((cmp_char[j] - cmp_char[3] == 0)){
                valid_char = 1 ;
            }
        }

        if((valid_char == 1)){
            i++ ;
        }else{
            return i;
        }

        valid_char = 0;
    }
    return -1;
} 

void highlight_win_rows(board list){
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

                struct node* current = query_board_structure(list, i, j);
                int current_win = 0;

                char x_pointer[1];
                x_pointer[0]= (query_board_structure(list, i, j)->data);

                char win_char;
                if(((p1[0] - x_pointer[0]) == 0)){
                    win_char = 'X';
                    }
                else{
                    win_char = 'O';
                }
                

                if(u_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->above->data = win_char;
                    current->above->above->data = win_char;
                    current->above->above->above->data = win_char;


                }
                if(d_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                    current->data = win_char;
                    current->below->data = win_char;
                    current->below->below->data = win_char;
                    current->below->below->below->data = win_char;
                }
                if(l_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;
                    
                    current->data = win_char;
                    current->left->data = win_char;
                    current->left->left->data = win_char;
                    current->left->left->left->data = win_char;
                }
                if(r_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->right->data = win_char;
                    current->right->right->data = win_char;
                    current->right->right->right->data = win_char;
                }
                if(tr_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->right->above->data = win_char;
                    current->right->above->right->above->data = win_char;
                    current->right->above->right->above->right->above->data = win_char;

                }
                if(tl_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->left->above->data = win_char;
                    current->left->above->left->above->data = win_char;
                    current->left->above->left->above->left->above->data = win_char;
                }
                if(br_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->below->right->data = win_char;
                    current->below->right->below->right->data = win_char;
                    current->below->right->below->right->below->right->data = win_char;

                    
                }
                if(bl_win(query_board_structure(list, i, j)) == 1){
                    current_win = 1;

                    current->data = win_char;
                    current->below->left->data = win_char;
                    current->below->left->below->left->data = win_char;
                    current->below->left->below->left->below->left->data = win_char;
                }
            }
        }
    }
}

void rotate_row(board list, int row_rotaion_num){
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


///required functions:

board setup_board(){
    struct board_structure *mylist = malloc(sizeof(struct board_structure));
    return mylist;
}

void cleanup_board(board u){
  free_board_content(u);
  free(u);
}

void read_in_file(FILE *infile, board u){
int i = 0;
    int chars_to_print = 0;

    char cmp_char[4] = {'x', 'o', '.'};
    

    int col_num = number_cols(infile) ;
    if((col_num < 4)||(col_num > 512)){
        exit(1);
    }
    
    base_board_setup(u, col_num);
    u->rows = 1 ;

    //as col number starts at 0 
    fseek(infile, 0, SEEK_END);
    chars_to_print = ftell(infile);

    int current_col = 0;
    int current_row = 0;
    
    while (i < chars_to_print)
    {
        i++ ;
        fseek(infile, -i, SEEK_END);
        char char_from_file[1] ;
        char_from_file[0] = fgetc(infile);
        //printf("%c",  char_from_file[0]);

        
        if((current_col % (col_num +1) == 0)){
            
            current_col = 0;
            current_row ++ ;
            u->rows =current_row;
        }

        for(int j = 0; j < 2; j++){
            if((cmp_char[j] - char_from_file[0] == 0)){
                int inset_x = (col_num) - current_col;
                int insert_y = current_row-1;
                struct node* test = query_board_structure(u, (col_num) - current_col, current_row-1);
                printf("%c: %d, %d \n",  char_from_file[0], (col_num) - current_col, current_row -1);
                add_to_board(u, (col_num) - current_col, current_row-1, char_from_file[0]);
            }
        }
        current_col ++;
    }
}

void write_out_file(FILE *outfile, board u){
  char current_to_insert[1];

      for(int row_num = u->rows -1; row_num >= 0; row_num--){
          for(int col_num = 0; col_num <= u->cols ; col_num++){


              if(query_board_structure(u, col_num, row_num) != u->head){
                  current_to_insert[0] = query_board_structure(u, col_num, row_num)->data;
              }
              else{
                      current_to_insert[0] = '.' ;
              }

              fprintf(outfile, "%s",current_to_insert);

              
          }
          fprintf(outfile, "\n");
  }
}

char next_player(board u){
  int x_count = 0;
      int o_count = 0;

      char p1[1] = "x";
      char p2[1] = "o";

      for(int x = 0; x < u->cols; x++){
          for(int y = 0; y< u->rows; y++){
              if(query_board_structure(u, x,y) != u->head){

                  char char_pointer[1] = "Z";
                  char_pointer[0]= query_board_structure(u, x,y)->data;


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
      //we hopefully should not get here...
      return p1[0];
  }

char current_winner(board u){
    char p1[1] = "x";
    char p2[1] = "o";
    char nw[1] = ".";
    char d[1] = "d";

    int x_win = 0;
    int o_win = 0;
    int b_full = 1;

    for(int i = 0; i< u->cols; i++){
        for(int j = 0; j< u->rows; j++){
            if((query_board_structure(u, i, j)!= u->head)){
                int current_win = 0;

                if(u_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(d_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(l_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(r_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(tr_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(tl_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(br_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;
                }
                if(bl_win(query_board_structure(u, i, j)) == 1){
                    current_win = 1;

                }

                char x_pointer[1] = "J";
                x_pointer[0]= (query_board_structure(u, i, j)->data);

                if((current_win == 1)){
                    if(((p1[0] - x_pointer[0]) == 0)){
                    x_win = 1;
                    }else{
                    o_win = 1;
                    }
                }
                
            }else{
                if(query_board_structure(u, i, j) == u->head){
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
    //we should not get here
    return p2[0];
  }

struct move read_in_move(board u){
  printf("Player %c enter column to place your token: ",next_player(u));
  int column_int;
  scanf("%d", &column_int);

  printf("Player %c enter row to rotate: ",next_player(u));
  int row_int;
  scanf("%d", &row_int);

    

  struct move current_move = {.column = column_int,  .row = -row_int};

  return current_move;
  }

int is_valid_move(struct move m, board u){
  char cw[1];
    cw[0] = current_winner(u);
    char dot[1];
    dot[0] = '.';

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

void play_move(struct move m, board u){
  if((is_valid_move(m, u) == 1)){
        
        char player_token = next_player(u);
        add_to_board(u, m.column,u->rows, player_token);

        rotate_row(u, m.row);
    }
}

//You may put additional functions here if you wish.


int main(){
  FILE *infile,*outfile;

  board my_board=setup_board();
  infile=fopen("initial_board.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);

  write_out_file(stdout,my_board);
   
  while(current_winner(my_board)=='.') {
    struct move next_move = read_in_move(my_board);
    if (is_valid_move(next_move,my_board)) {
    play_move(next_move,my_board);
    write_out_file(stdout,my_board);
    }
  }

  outfile=fopen("final_board.txt","w");
  write_out_file(outfile,my_board);
  fclose(outfile);

  cleanup_board(my_board);
  return 0;
}