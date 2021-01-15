#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<ctype.h>

typedef struct board_structure *board;

struct node{
  char data;
  struct node *above;
  struct node *below;
  struct node *right;
  struct node *left;
};

struct board_structure{
    //rows and cols are the max indexes of the queryable nodes. as count goes from 0->rows/cols
  int rows;
  int cols;
  struct node *head;
};

struct move{
int column;
int row;
};

void add_to_board(board list, int x, int y, char data);
void rotate_row(board list, int row_num);
void free_board_content(board list);
void base_board_setup(board list, int cols);
char current_winner(board list);
struct node* query_board_structure(board list, int x, int y);
char next_player(board list); 
struct move read_in_move(board u);
void highlight_win_rows(board u);


struct board_structure* setup_board();
void play_move(struct move m, board u);
char is_winning_move(struct move m, board u);
void cleanup_board(board u);
int is_valid_move(struct move m, board u);
void read_in_file(FILE *infile, board u);
int number_cols(FILE *infile);
void write_out_file(FILE *outfile, board u);

int r_win(struct node* current);
int l_win(struct node* current);
int u_win(struct node* current);
int tr_win(struct node* current);
int tl_win(struct node* current);


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

void cleanup_board(board u){
    free_board_content(u);
    free(u);
}

struct move read_in_move(board u){
    int accept_input = 0;

    int column_int;
    char collumn_char[3];
    
    while (accept_input == 0)
    {
        printf("Player %c enter column to place your token: ",next_player(u));

        int counter = 0;
        int flush_char;
        while ((flush_char = getchar()) != '\n' && flush_char != EOF){
            collumn_char[counter] = flush_char;
            counter++;
        }

        
        for(int check_counter = 0; check_counter < counter; check_counter++ ){

        if ((isdigit(collumn_char[check_counter]))){
            column_int = atoi(collumn_char);
            accept_input = 1 ;
        }

        else{
            column_int = -1;
            accept_input = 0 ;
            check_counter = counter;
            
            }
        }
    }
    

    accept_input = 0 ;
    int row_int;
    char row_char[3];
    while (accept_input == 0)
    {
        printf("Player %c enter row to rotate: ",next_player(u));

        int counter = 0;
        int flush_char;
        while ((flush_char = getchar()) != '\n' && flush_char != EOF){
            row_char[counter] = flush_char;
            counter++;
        }

        
        for(int check_counter = 0; check_counter < counter; check_counter++ ){

        if ((isdigit(row_char[check_counter]))){
            row_int = atoi(row_char);
            accept_input = 1 ;
        }

        else{
            accept_input = 0;
            row_int = -1 ;
            check_counter = counter;
            
            }
        }
    }


    struct move current_move = {
   .column = column_int,  .row = row_int};

    return current_move;
}

void highlight_win_rows(board list){
    char p1[1] = "x";

    char p1_win[1] = "X";

    int x_win = 0;
    int o_win = 0;
    

    

    for(int i = 0; i <= list->cols; i++){
        for(int j = 0; j <= list->rows -1; j++){
            if((query_board_structure(list, i, j)!= list->head) && ((x_win == 0) || (o_win == 0))){

                struct node* current = query_board_structure(list, i, j);
                
                int char_win_found = 1;

                char x_pointer[1];
                x_pointer[0]= (query_board_structure(list, i, j)->data);

                char win_char;
                if(( (p1[0] - x_pointer[0]) == 0) || ((p1_win[0] - x_pointer[0]) == 0) ){
                    win_char = 'X';
                    if((x_win == 0)){
                        char_win_found = 0;
                    }
                    }
                else{
                    win_char = 'O';
                    if((o_win == 0)){
                        char_win_found = 0;
                    }
                }
                
                if((char_win_found == 0)){

                    if( u_win(query_board_structure(list, i, j)) ){
                    

                    current->data = win_char;
                    current->above->data = win_char;
                    current->above->above->data = win_char;
                    current->above->above->above->data = win_char;

                    }

                    if(l_win(query_board_structure(list, i, j)) == 1){
                        
                        
                        current->data = win_char;
                        current->left->data = win_char;
                        current->left->left->data = win_char;
                        current->left->left->left->data = win_char;
                    }
                    if(r_win(query_board_structure(list, i, j)) == 1){
                        

                        current->data = win_char;
                        current->right->data = win_char;
                        current->right->right->data = win_char;
                        current->right->right->right->data = win_char;
                    }
                    if(tr_win(query_board_structure(list, i, j)) == 1){
                        

                        current->data = win_char;
                        current->right->above->data = win_char;
                        current->right->above->right->above->data = win_char;
                        current->right->above->right->above->right->above->data = win_char;

                    }
                    if(tl_win(query_board_structure(list, i, j)) == 1){
                      
                        current->data = win_char;
                        current->left->above->data = win_char;
                        current->left->above->left->above->data = win_char;
                        current->left->above->left->above->left->above->data = win_char;
                    }


                }
                
            }
        }
    }
}

char current_winner(board list){
    char p1[1] = "x";
    char p2[1] = "o";
    char nw[1] = ".";
    char d[1] = "d";

    int x_win = 0;
    int o_win = 0;
    int b_full = 1;

    

    for(int i = 0; i <= list->cols; i++){
        for(int j = 0; j <= list->rows - 1; j++){
            if((query_board_structure(list, i, j)!= list->head)){
                int current_win = 0;

                if(u_win(query_board_structure(list, i, j)) == 1){
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
        highlight_win_rows(list);
        return d[0];
    }
    //none have won and board is full, draw
    if((x_win == 0)&&(o_win == 0)&&(b_full == 1)){
        return d[0];
    }
    //none win and bord is not full, no winner
    if((x_win == 0)&&(o_win == 0)){
        return nw[0];
    }

    //single wins
    if((x_win == 1)){
        highlight_win_rows(list);
        return p1[0];
    }
    if((o_win == 1)){
        highlight_win_rows(list);
        return p2[0];
    }
    //we should not get here
    return p2[0];

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
    if((mylist == NULL)){
        exit(1);
    }
    mylist->head = NULL;
    mylist->cols = 0;
    mylist->rows = 0;
    return mylist;
}

void base_board_setup(board list, int cols){
    struct node* previous = NULL;

    char blank = '_';

    for(int i = 1; i < cols; i++){
        struct node* newnode = malloc(sizeof(struct node));
        if((newnode == NULL)){
            exit(1);
        }
        newnode->data = blank;
        newnode->above = NULL;
        newnode->below = NULL;
        
        if((previous == NULL)){
            list->head = newnode;
            previous = newnode;
            
            list->cols ++;
        }else{
            newnode->left = previous;
            previous->right = newnode;

            previous = newnode;
            
            list->cols++;
        }
        
    }
    struct node* newnode = malloc(sizeof(struct node));
    if((newnode == NULL)){
            exit(1);
        }
    newnode->data = blank;
    newnode->above = NULL;
    newnode->below = NULL;

    newnode->right = list->head;
    list->head->left = newnode;

    previous->right = newnode;
    newnode->left = previous;
    

    return;
        
    }

struct node* query_board_structure(board list, int x, int y){
    //y starts from 1, x starts from 0
    
    //returnin list.head means the slot is on the borad but is free
    //returning list.head.next means that the x or y are out of bounds

    struct node* blank = list->head;
    if(x > list->cols || y >= list->rows ){
        //returning list.head.next means that the x or y are out of bounds
        return blank->right;
    }

    y++;

    struct node* current = list->head;
    for(int i = 0; i < x; i++){
        current = current->right;
    }

    
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
    
void add_to_board(board list, int x, int y, char data){
    //x and y should come in with indexes starting from 0

    if(query_board_structure(list, x,y ) == list->head){
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
        if((newnode == NULL)){
            // node failed to be allocated memeory. 
            exit(1);
        }

        newnode->data = data;
        //ficing above and below neighbors
        //only connects to bellow if it is not a base node
        
        newnode->below =current;
        newnode->above = NULL;
        newnode->right = NULL;
        newnode->left = NULL;
        
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

void rotate_row(board u, int rotation_num){
    //rotation number comes in with row number beginning at 1, with either + or - at the beginning
    int row_to_rotate = abs(rotation_num) - 1;

    struct board_structure *new_list = setup_board();
    base_board_setup(new_list, u->cols+1);
    new_list->rows = u->rows;

    char bad_token[1] = "_" ;
    for(int y = 0; y <= u->rows - 1; y++){
        for(int x = 0; x <= u->cols; x++){
            struct node* current = query_board_structure(u, x, y);
            
            
            if((current->data - bad_token[0] != 0)){
                int insert_x = x;
                if((row_to_rotate == y)){

                    if((rotation_num < 0)){
                        insert_x = insert_x - 1;
                        if((insert_x < 0)){
                            insert_x = u->cols;
                        }
                    }
                    if((rotation_num > 0)){
                        insert_x = insert_x + 1;
                        if((insert_x > u->cols)){
                            insert_x = 0;
                        }
                    }

                }

                add_to_board(new_list, insert_x, u->rows - 1, current->data);



            }

        }
    }
    //write_out_file(stdout,u);
    //printf("\n");
    //write_out_file(stdout,new_list);
    //printf("\n");

    //free up everything from the old head
    free_board_content(u);
    
    //now set the head of the hold list equal to the head of the new shifted list
    u->head = new_list->head;
    new_list->head = NULL;

    //free the new_list structure as its content has been assighned to the old list
    free(new_list);
}

char next_player(struct board_structure *list){
    int x_count = 0;
    int o_count = 0;

    char p1[1] = "x";
    char p2[1] = "o";

    for(int x = 0; x <= list->cols; x++){
        for(int y = 0; y <= list->rows -1; y++){
            if(query_board_structure(list, x,y) != list->head){

                char char_pointer[1] = "Z";
                char_pointer[0]= query_board_structure(list, x,y)->data;


                if(((p1[0] - char_pointer[0]) == 0)){
                    x_count ++ ;
                }else{
                    o_count ++ ;
                    }
                }else{
                    //printf("ZZZ");
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

int is_valid_move(struct move m, board u){
    char cw[1];
    cw[0] = current_winner(u);
    char dot[1];
    dot[0] = '.';

    int absalute_row = abs(m.row);

    //if anything other than 'no winner'. no move is valid.
    if((dot[0] - cw[0]) != 0){
        return 0;
    }

    //if any parts of m are outside of the playable area
    if((m.column -1 > u->cols) || (absalute_row > u->rows) || (m.column <= 0)){
        return 0;
    }

    //if all ^ passed, then should be ok!
    return 1;

}

void play_move(struct move m, board u){
    if((is_valid_move(m, u) == 1)){
        
        char player_token = next_player(u);
        add_to_board(u, m.column -1,u->rows -1, player_token);

        if((m.row != 0)){
            rotate_row(u, m.row);
        }
        
        highlight_win_rows(u);
    }
}

char is_winning_move(struct move m, board u){

    struct board_structure *new_list = setup_board();
    base_board_setup(new_list, u->cols+1);
    new_list->rows = u->rows;

    //go through the board row by row starting at the bottom
    //add each to new board from left to right

    
    
    for(int row_num = 0; row_num <= u->rows; row_num++){
        for(int col_num = 0; col_num <= u->cols -1 ; col_num++){
            if(query_board_structure(u, col_num, row_num) != u->head){
                add_to_board(new_list, col_num, row_num, query_board_structure(u, col_num, row_num)->data);

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
    

int main(){
  FILE *infile,*outfile;

  board my_board=setup_board();
  infile=fopen("b/initial_board.txt","r");
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




