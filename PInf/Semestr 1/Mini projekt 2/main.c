#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 45
void board_init (char *board)
{
    int i;
        for (i = 0; i < BOARD_SIZE * (BOARD_SIZE + 1); ++i)
        board[i] = '0';
    *(board + BOARD_SIZE * (BOARD_SIZE + 1)) = '\0';
    for (i = 0; i < BOARD_SIZE * (BOARD_SIZE + 1); ++i)
    {
        
    }
    return;
}

int draw_board (short start, short end, char *board)
{
    short i;
    for (i = 0; i < BOARD_SIZE; ++i)
        printf("%s", board[i]);
    return 0;
}

int main ()
{
    char *board = malloc (sizeof(char) * BOARD_SIZE * (BOARD_SIZE + 1) + 1);
    int x;
    printf ("%s\nstrlen: %d\n", board, strlen(board));
    short path [2][4] = {{1, 3, 0, 1},  // 0
                         {2, 0, 3, 2}}; // 1
    short state = 0; // obecny stan

    printf("Wprowadz ciag:\n");
    char *in = NULL;
    size_t len = 0, in_size = 0;
    in_size = getline(&in, &len, stdin);
    size_t i;
    board_init(board);
    for (i = 0; i < in_size - 1; ++i)
    {
        if (in[i] != '0' && in[i] != '1')
        {
            printf ("Symbol %c nie istnieje w alfabecie\n", in[i]);
            free(in);
            free(board);
            return 1;
        }
        draw_board(state, path[in[i] - '0'][state], board);
        state = path[in[i] - '0'][state];
    }
    free(in);
    free(board);
    return 0;
}