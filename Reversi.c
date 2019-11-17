#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//define board size and winning conditions
#define GRID 10
#define WIN_SCORE 21
//printed board defined by grid size
#define PRINT_ROW GRID+2
#define PRINT_COL 2*GRID + 3
//define players discs
#define BLACK_DISC 'B'
#define WHITE_DISC 'W'
//defining functions
void init_array(int board[GRID][GRID]);
void init_printed_board(char printed_board[PRINT_ROW][PRINT_COL]);
void print_intro();
void print_board(char printed_board[PRINT_ROW][PRINT_COL],
                 int board[GRID][GRID],int turn,int b_score,int w_score);
void starting_game(char printed_board[PRINT_ROW][PRINT_COL],
                   int board[GRID][GRID],int turn,int b_score,int w_score);
void print_winner(int b_score,int w_score);
int check_user_input(int *user_row,int *user_column);
int in_array_empty (int user_row, int user_column,int board[GRID][GRID]);
void board_count(int board[GRID][GRID],int *b_score, int *w_score,
                 int *turn);
void array_change(int board[GRID][GRID],int user_row,
                  int user_column,int user_disc);
int main()
//16 lines
{
    //define array and variables
    int board[GRID][GRID]={{0}},turn=1,b_score=2,w_score=2, user_disc=1;
    int  user_row, user_column;
    char printed_board[PRINT_ROW][PRINT_COL];
    //initiating the array and prints
    starting_game(printed_board,board,turn,b_score,w_score);
    //main while loop for game moves, runs until a player wins
    while (b_score<WIN_SCORE && w_score<WIN_SCORE)
    {
        //while loop for input check
        do
        {
            if (check_user_input(&user_row,&user_column))
                {
                    printf("Error: Illegal input.\nGame Over!");
                    return 0;
                }
        } while (in_array_empty(user_row,user_column,board)==0);
        user_disc=2-turn%2;//determents which player is now playing
        //every turn changes the array, prints updated board
        array_change(board,user_row,user_column,user_disc);
        board_count(board,&b_score,&w_score,&turn);
        print_board(printed_board,board,turn,b_score,w_score);
    }

    print_winner(b_score,w_score);

    return 0;
}
void init_array(int board[GRID][GRID])
//4 lines
//function initiates the starting board
{
   board[(int)GRID/2-1][(int)GRID/2-1]=2;
   board[(int)GRID/2][(int)GRID/2]=2;
   board[(int)GRID/2][(int)GRID/2-1]=1;
   board[(int)GRID/2-1][(int)GRID/2]=1;
}
void init_printed_board(char printed_board[PRINT_ROW][PRINT_COL])
//11 lines
//function initiates printed board
{
    for (int i=0; i<PRINT_ROW; i++)
    {
         for (int j=0;j<PRINT_COL; j++)
        {
            printed_board[i][j]=(' ');
        }
        for (int j=1;j<PRINT_COL; j+=2)
        {
            printed_board[i][j]=('|');
        }
    }
    //prints the indexes on the sides, top and bottom
    for (int j=2; j<PRINT_COL-2; j+=2)
    {
        printed_board[0][j]=('0'+j/2-1);
        printed_board[PRINT_ROW-1][j]=('0'+j/2-1);
    }
    for (int i=1; i<PRINT_ROW-1; i++)
    {
    printed_board[i][0]=('0'+i-1);
    printed_board[i][PRINT_COL-1]=('0'+i-1);
    }
}

void print_intro()
//4 lines
//function prints welcome message
{
    printf("Welcome to Reversi-%d!!!\n", WIN_SCORE);
    printf("The winner is the first one to reach %d disks.\n", WIN_SCORE);
    printf("**********************************************\n");
    return;
}
void print_board(char printed_board[PRINT_ROW][PRINT_COL],
                 int board[GRID][GRID],int turn,int b_score,int w_score)
//16 lines
//function updates printed board and prints it
{
     for (int i=1; i<PRINT_ROW-1; i++)
    {
        for (int j=2;j<PRINT_COL-2; j+=2)
        {
           if (board[i-1][j/2-1]==1)
           {
                printed_board[i][j]=BLACK_DISC;
           }
            if (board[i-1][j/2-1]==2)
           {
                printed_board[i][j]=WHITE_DISC;
           }
        }
    }
     for (int i=0; i<PRINT_ROW; i++)
    {
        for (int j=0;j<PRINT_COL; j++)
        {
            printf("%c",printed_board[i][j]);
        }
        printf("\n");
    }

    printf("Black disks: %d, White disks: %d\n", b_score, w_score);
    if (b_score<WIN_SCORE && w_score<WIN_SCORE)
    {
        if (turn % 2 ==1)
            {
                printf("Turn %d: Black player's turn.\n",turn);
            }
        if (turn%2 ==0)
            {
                printf("Turn %d: White player's turn.\n",turn);
            }
    }

}
void starting_game(char printed_board[PRINT_ROW][PRINT_COL],
                   int board[GRID][GRID],int turn,int b_score,int w_score)
//4 lines
//function initiates all arrays and prints starting situation
{
    init_array(board);
    init_printed_board(printed_board);
    print_intro();
    print_board(printed_board,board,turn,b_score,w_score);
}
void print_winner(int b_score,int w_score)
//4 lines
//functions print winner result
{
    if (b_score>=WIN_SCORE)
    {
        printf("The winner is: Black player.\n");
    }
     if (w_score>=WIN_SCORE)
    {
        printf("The winner is: White  player.\n");
    }
}
void board_count(int board[GRID][GRID],int *b_score, int *w_score,
                 int *turn)
//10 lines
//counts the score on the board and changes values of turn
{

    int temp_black=0, temp_white=0;
    for (int i=0; i<GRID; i++)
    {
        for (int j=0;j<GRID; j++)
        {
            if (board[i][j]==1)
            {
                temp_black++;
            }
            if (board[i][j]==2)
            {
                temp_white++;
            }
        }
    }
    *b_score=temp_black;
    *w_score=temp_white;
    *turn+=1;
}
int check_user_input(int *user_row,int *user_column)
//14 lines
//function checks input from user is valid
// return 1 if ok, return 0 if problem
{
    int temp_row, temp_column;
    printf("Please enter the indexes of the desired cell.\nRow index:\n");
    if(scanf(" %d" , &temp_row)!=1)
    {
        return 1;
    }
    if (temp_row==EOF)
    {
        return 1;
    }
    printf("Column index:\n");
    if(scanf(" %d" , &temp_column)!=1)
    {
        return 1;
    }
    if (temp_column==EOF)
    {
        return 1;
    }
    *user_column=temp_column;
    *user_row= temp_row;
    return 0;
}
int in_array_empty(int user_row, int user_column,int board[GRID][GRID])
//8 lines
//function checks if entered indexes are in bound and free
{
    if (user_row>GRID-1 || user_row<0 ||
        user_column>GRID-1 || user_column<0)
    {
        printf("Error: Indexes are out of bounds.\n");
        return 0;
    }
    if (board[user_row][user_column]!=0)
    {
        printf("Error: Cell is not empty.\n");
        return 0;
    }
    return 1;
}
void array_change(int board[GRID][GRID],int user_row,
                  int user_column, int user_disc)
//15 lines
/*function replaces all required discs in all directions using two
for loops that cover all rows, column and diagonals.*/
{
    for(int side=-1; side<=1;side++)
    {
        for(int height=-1; height<=1; height++)
        {
        //if condition makes sure function doesn't check the number itself
            if (height==0 && side==0) continue;
            int i=1;
            /*while loop check if numbers are in bound, and how many
            numbers in a row, column or diagonal are different from disc*/
            while (user_row+side*i<GRID && user_row+side*i>=0
            && user_column+height*i<GRID && user_column+height*i>=0
            && board[user_row+side*i][user_column+height*i]!=0
            && board[user_row+side*i][user_column+height*i]!=user_disc)
                {
                    i++;
                }
            /*if checks whether numbers are in bound, and if last number
            checked is equal to first number, then changes the middle*/
            if (user_row+side*i<GRID && user_row+side*i>=0
            && user_column+height*i<GRID && user_column+height*i>=0
            && board[user_row+side*i][user_column+height*i]==user_disc)
            {
                for (int j=1; j<i; j++)
                {
                    board[user_row+j*side][user_column+j*height]=user_disc;
                }
            }
        }
    }
    //changes the empty spot in the array to user disc
    board[user_row][user_column]=user_disc;
}
