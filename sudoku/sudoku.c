/*sudoku in c
 * By: Alex Petrov*/
/*Gameplan
 * 1. find a way to check if game is correct
 * 2. figure out formatting of board
 * 3. make random generation of game boards
 *    a.easy, medium, and hard gamemodes
 * 4. prompt and insert number   
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 9
#define COLUMNS 9
#define BOX 9
#define MODE 10

void print_board(char board[ROWS][COLUMNS]);
int prompt_mode(char *buffer);
int check_win(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS]);
int randoms(int upper, int lower);
void generate_game(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS], 
                   int mode);
int check_dups(int value[ROWS][COLUMNS]);
void val_to_board(int values[ROWS][COLUMNS], char board[ROWS][COLUMNS]);
char int_to_str(int number);
int check_box(int box_vals[ROWS][COLUMNS]);
void fill_diag(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS]);
int fill_rest(int row, int col, int values[ROWS][COLUMNS], 
               int box_val[ROWS][COLUMNS]);
int safety_check(int row, int col, int num, int values[ROWS][COLUMNS], 
                 int box_val[ROWS][COLUMNS]);
void remove_nums(int clues, int values[ROWS][COLUMNS], 
                 int box_val[ROWS][COLUMNS]);
int check_full(int values[ROWS][COLUMNS]);
int prompt_entry(int values[ROWS][COLUMNS], int boxes[ROWS][COLUMNS]);

int main(){
    char board[ROWS][COLUMNS];
    int values[ROWS][COLUMNS];
    int boxes[BOX][COLUMNS];
    char *mode_buf;
    int mode;
    /*generate the puzzle with corresponding mode*/
    mode_buf = calloc(MODE, sizeof(char));
    mode = prompt_mode(mode_buf);
    free(mode_buf);
    memset(&values, 0, sizeof(values));
    memset(&boxes, 0, sizeof(boxes));
    generate_game(values, boxes, mode);
    memset(&board, ' ', sizeof(board));
    val_to_board(values, board);
    print_board(board);
    /*enter loop to prompt nummber/space*/
    while(check_win(values, boxes)){
        if(prompt_entry(values, boxes)){
            continue;
        }
        val_to_board(values, board);
        print_board(board);
    }
    printf("----------- YOU WIN! ----------- \n");
    return 1;
}

int check_win(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS]){
    /*check sums and square sums of each row, col, and box
     * eq for each box space is (col%3) + ((row%3)*3) */
    if(check_full(values) || check_dups(values) || check_box(box_val)){
        return 1;
    }
    else{
        return 0;
    }
}

void val_to_board(int values[ROWS][COLUMNS], char board[ROWS][COLUMNS]){
    int i, j;
    
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            if(values[i][j] != 0){
                board[i][j] = int_to_str(abs(values[i][j]));
            }
        }
    }
}

int check_dups(int value[ROWS][COLUMNS]){
    int i, j, k;
    int size = 9;
    /*rows*/
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            for(k=j+1; k < size; k++){
                if(abs(value[i][j]) == abs(value[i][k]) && value[i][j] != 0){
                    return 1;
                }
            }
        }
    }

    /*columns*/
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            for(k=j+1; k < size; k++){
                if(abs(value[j][i]) == abs(value[k][i]) && value[j][i] != 0){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_box(int box_vals[ROWS][COLUMNS]){
    int i, j, k;
    int size = 9;
    /*box*/
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            for(k=j+1; k < size; k++){
                if(abs(box_vals[i][j]) == abs(box_vals[i][k])
                     && box_vals[i][j] != 0){
                    return 1;
                }
            }
        }
    }

    return 0;
}

int check_full(int values[ROWS][COLUMNS]){
    int i, j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            if(values[i][j] == 0){
                return 1;
            }
        }
    }
    return 0;
}

int prompt_entry(int values[ROWS][COLUMNS], int boxes[ROWS][COLUMNS]){
    char *buf;
    char **end;
    int row, col, num, box, bind;
    buf = calloc(100, sizeof(char));
    while(1){
        printf("Enter a row number 1-9: ");
        fgets(buf, 100, stdin);
        row = strtol(buf, end, 10);
        if(**end != '\n' || row > 9 || row < 1){
            printf("Please enter a valid number between 1-9.\n");
            continue;
        }
        break;
    }

    while(1){
        printf("Enter a col number 1-9: ");
        fgets(buf, 100, stdin);
        col = strtol(buf, end, 10);
        if(**end != '\n' || col > 9 || col < 1){
            printf("Please enter a valid number between 1-9.\n");
            continue;
        }
        break;
    }

    while(1){
        printf("Enter a number entry 1-9: ");
        fgets(buf, 100, stdin);
        num = strtol(buf, end, 10);
        if(**end != '\n' || num > 9 || num < 1){
            printf("Please enter a valid number between 1-9.\n");
            continue;
        }
        break;
    }
    row -= 1;
    col -= 1;
    if(values[row][col] < 0){
        printf("You can not change a given number. Choose again.\n");
        return 1;
    }
    else{
        values[row][col] = num;
        box = (col/3) + ((row/3)*3);
        bind = (col%3) + ((row%3)*3);  
        boxes[box][bind] = num;
    }
    free(buf);
    return 0;
}

char int_to_str(int number){
    switch(number){
        case 1: return '1';

        case 2: return '2';

        case 3: return '3';

        case 4: return '4';

        case 5: return '5';
        
        case 6: return '6';

        case 7: return '7';
        
        case 8: return '8';

        case 9: return '9';

        default: return ' ';
    }
}

int prompt_mode(char *buffer){
    while(1){
        printf("Please choose mode (easy, medium, hard): ");
        fgets(buffer, 10, stdin);
        if(!strcmp(buffer, "easy\n")){
            return 0;
        }
        else if(!strcmp(buffer, "medium\n")){
            return 1;
        }
        else if(!strcmp(buffer, "hard\n")){
            return 2;
        }
        else{
            printf("Please enter easy, medium, or hard.\n");
        }
    }
}

void generate_game(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS], 
                   int mode){
    int clues;
    srand(time(0));
    if(!mode){
        /*easy*/
        clues = randoms(38, 36);
    }
    else if(mode == 1){
        /*medium*/
        clues = randoms(35, 27);
    }
    else if(mode == 2){
        /*hard*/
        clues = randoms(26, 19);
    }
    printf("---------------------------------------------\n");
    printf("generating puzzle.....\n");
    printf("---------------------------------------------\n");
    fill_diag(values, box_val);
    fill_rest(0, 3, values, box_val);
    remove_nums(clues, values, box_val);
}

void fill_diag(int values[ROWS][COLUMNS], int box_val[ROWS][COLUMNS]){
    int num, col, row, box, bind;
    int step = 3;
    while(step <= 9){
        for(col = step-3; col < step; col++){
            for(row = step-3; row < step; row++){
                do{
                    num = -1 * randoms(9,1);
                    values[row][col] = num;
                    box = (col/3) + ((row/3)*3);
                    bind = (col%3) + ((row%3)*3);  
                    box_val[box][bind] = num;
                }while(check_box(box_val));
                
            }
        }
        step += 3;
    }
}

int fill_rest(int row, int col, int values[ROWS][COLUMNS], 
               int box_val[ROWS][COLUMNS]){
    int num, box, bind;
    if(col>=9 && row<8){
        row += 1;
        col = 0;
    }
    if(row>=9 && col>=9){
        return 1;
    }

    if(row < 3){
        if(col < 3){
            col = 3;
        }
    }
    else if(row < 6){
        if(col == (row/3)*3){
            col = col + 3;
        }
    }
    else{
        if(col == 6){
            row = row + 1;
            col = 0;
            if(row >= 9){
                return 1;
            }
        }
    }

    for(num = 1; num <= 9; num++){
        if(safety_check(row, col, num, values, box_val)){
            values[row][col] = num * -1;
            box = (col/3) + ((row/3)*3);
            bind = (col%3) + ((row%3)*3);  
            box_val[box][bind] = num * -1;
            if(fill_rest(row, col+1, values, box_val)){
                return 1;
            }
            values[row][col] = 0;
            box_val[box][bind] = 0;
        }
    }
    return 0;
}

void remove_nums(int clues, int values[ROWS][COLUMNS], 
                 int box_val[ROWS][COLUMNS]){
    int row, col, box, bind, total, tot_clues;
    int count = 0;
    total = ROWS * COLUMNS;
    tot_clues = total - clues;
    while(count < tot_clues){
        row = randoms(8,0);
        col = randoms(8,0);
        box = (col/3) + ((row/3)*3);
        bind = (col%3) + ((row%3)*3); 
        if(values[row][col] == 0){
            continue;
        }
        else{
            values[row][col] = 0;
            box_val[box][bind] = 0;
            count++; 
        }
    }
}

int safety_check(int row, int col, int num, int values[ROWS][COLUMNS], 
                 int box_val[ROWS][COLUMNS]){
    int box, bind;
    values[row][col] = num * -1;
    box = (col/3) + ((row/3)*3);
    bind = (col%3) + ((row%3)*3);  
    box_val[box][bind] = num * -1;
    if(check_dups(values) || check_box(box_val)){
        values[row][col] = 0;
        box_val[box][bind] = 0;
        return 0;
    }
    else{
        values[row][col] = 0;
        box_val[box][bind] = 0;
        return 1;
    }
}

int randoms(int upper, int lower){
    int num;
    num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void print_board(char board[ROWS][COLUMNS]){
    printf("    1   2   3   4   5   6   7   8   9\n");
    printf("  _____________________________________\n");
    printf("1 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[0][0], board[0][1], board[0][2], board[0][3], board[0][4],
            board[0][5], board[0][6], board[0][7], board[0][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("2 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[1][0], board[1][1], board[1][2], board[1][3], board[1][4],
            board[1][5], board[1][6], board[1][7], board[1][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("3 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[2][0], board[2][1], board[2][2], board[2][3], board[2][4],
            board[2][5], board[2][6], board[2][7], board[2][8]);
    printf("  |===========|===========|===========|\n");
    printf("4 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[3][0], board[3][1], board[3][2], board[3][3], board[3][4],
            board[3][5], board[3][6], board[3][7], board[3][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("5 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[4][0], board[4][1], board[4][2], board[4][3], board[4][4],
            board[4][5], board[4][6], board[4][7], board[4][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("6 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[5][0], board[5][1], board[5][2], board[5][3], board[5][4],
            board[5][5], board[5][6], board[5][7], board[5][8]);
    printf("  |===========|===========|===========|\n");
    printf("7 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[6][0], board[6][1], board[6][2], board[6][3], board[6][4],
            board[6][5], board[6][6], board[6][7], board[6][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("8 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[7][0], board[7][1], board[7][2], board[7][3], board[7][4],
            board[7][5], board[7][6], board[7][7], board[7][8]);
    printf("  |---+---+---|---+---+---|---+---+---|\n");
    printf("9 | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", 
            board[8][0], board[8][1], board[8][2], board[8][3], board[8][4],
            board[8][5], board[8][6], board[8][7], board[8][8]);
    printf("  -------------------------------------\n");
}

