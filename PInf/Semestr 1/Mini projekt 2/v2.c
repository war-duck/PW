#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define BOARD_SIZE 35    // wys/szer planszy
#define RADIUS 5         // promień kółka
#define DIST_FROM_EDGE 8 // odległość środka kółka od krawędzi
#ifndef uint 
typedef unsigned int uint;
#endif
uint path_col_row (int start, int end) // jeżeli rząd, to zaprzeczenie więc będzie > BOARD_SIZE
{
    switch (start)
    {
        case 0: return end == 1 ? ~(uint)(DIST_FROM_EDGE - 1) : (uint)(DIST_FROM_EDGE + 1);
        case 1: return end == 0 ? ~(uint)(DIST_FROM_EDGE + 1) : (uint)(DIST_FROM_EDGE + 1);
        case 2: return end == 1 ? ~(uint)(DIST_FROM_EDGE - 1) : (uint)(DIST_FROM_EDGE + 1);
        case 3: return end == 1 ? ~(uint)(DIST_FROM_EDGE - 1) : (uint)(DIST_FROM_EDGE + 1);
    }
    return ~0;
}
void draw_paths (char board[])
{
    board[(DIST_FROM_EDGE - 2) * (2*BOARD_SIZE + 1) + BOARD_SIZE] = '0';
    board[(DIST_FROM_EDGE + 2) * (2*BOARD_SIZE + 1) + BOARD_SIZE] = '1';
    board[(BOARD_SIZE - DIST_FROM_EDGE - 3) * (2*BOARD_SIZE + 1) + BOARD_SIZE] = '1';
    board[(BOARD_SIZE - DIST_FROM_EDGE + 1) * (2*BOARD_SIZE + 1) + BOARD_SIZE] = '1';
    board[(BOARD_SIZE / 2) * (2*BOARD_SIZE + 1) + 2*DIST_FROM_EDGE - 3] = '0';
    board[(BOARD_SIZE / 2) * (2*BOARD_SIZE + 1) + 2*DIST_FROM_EDGE + 4] = '1';
    board[(BOARD_SIZE / 2) * (2*BOARD_SIZE + 1) + 2*(BOARD_SIZE - DIST_FROM_EDGE) - 5] = '0';
    board[(BOARD_SIZE / 2) * (2*BOARD_SIZE + 1) + 2*(BOARD_SIZE - DIST_FROM_EDGE) + 2] = '0';
}

char calc_val (int i, int j)
{
    if (BOARD_SIZE - i - 1 < i) // dzięki temu rysowane są kółka we wszystkich czterech ćwiartkach
        i = BOARD_SIZE - i - 1;
    if (BOARD_SIZE - j - 1 < j)
        j = BOARD_SIZE - j - 1;
    double coord_dist = (i - DIST_FROM_EDGE) * (i - DIST_FROM_EDGE) + (j - DIST_FROM_EDGE) * (j - DIST_FROM_EDGE);
    if ((RADIUS-3)*(RADIUS-3) < coord_dist && coord_dist <= (RADIUS-2)*(RADIUS-2))
        return (char)176; // 176, 177, 178, 219 - gradient. Może nie działać poprawnie z domyślną czcionką dla Win11. Consolas działa
    if ((RADIUS-2)*(RADIUS-2) < coord_dist && coord_dist <= (RADIUS-1)*(RADIUS-1))
        return (char)177;
    if ((RADIUS-1)*(RADIUS-1) < coord_dist && coord_dist <= RADIUS*RADIUS)
        return (char)178;
    if (RADIUS*RADIUS < coord_dist && coord_dist <= (RADIUS+1)*(RADIUS+1))
        return (char)219;
    if ((i == DIST_FROM_EDGE - 1 || i == DIST_FROM_EDGE + 1) && j > DIST_FROM_EDGE + RADIUS) // strzałki
        return i == DIST_FROM_EDGE - 1 ? '>' : '<';
    if ((j == DIST_FROM_EDGE - 1 || j == DIST_FROM_EDGE + 1) && i > DIST_FROM_EDGE + RADIUS)
        return j == DIST_FROM_EDGE - 1 ? '^' : 'v';
    return ' ';
}

void anim (char board[], int start, int end, int coord[4][2])
{
    
    int i;
    if (coord[start][0] == coord[end][0]) // kolumna
    {
        int diff = (2*BOARD_SIZE + 1) * (start > end ? -1 : 1);
        for ()
    }
    else
    {
        int diff = 1 * (start > end ? -1 : 1);
    }
}

void board_init (char board[]) // tworzy plansze
{
    int i, j; // koordynaty char na planszy
    for (i = 0; i < BOARD_SIZE; ++i)
    {
        for (j = 0; j < BOARD_SIZE; ++j)
            board[i * (BOARD_SIZE * 2 + 1) + (j * 2) + 1] = board[i * (BOARD_SIZE * 2 + 1) + (j * 2)] = calc_val(i, j); // każdy char ma parę, ponieważ znaki w terminalu mają proporcje 2:1
        board[(i + 1) * (BOARD_SIZE * 2 + 1) - 1] = '\n';
    }
    for (i = 0; i < 4; ++i) // podpisuje wierzchołki
    {
        int coord = ((1-i/2) * DIST_FROM_EDGE + i/2 * (BOARD_SIZE - DIST_FROM_EDGE - 1)) * (2*BOARD_SIZE + 1) + i%2 * 2 * (BOARD_SIZE - DIST_FROM_EDGE - 1) + (i+1)%2 * 2 * DIST_FROM_EDGE;
        board[coord] = 'q';
        board[coord+1] = i+'0';
    }
    draw_paths(board);
    printf ("\n%s\n", board);
}

int main (void)
{
    char board [BOARD_SIZE * (BOARD_SIZE * 2 + 1) + 1];
    short path [2][4] = {{1, 3, 0, 1},  // 0
                         {2, 0, 3, 2}}; // 1
    short state = 0; // obecny stan
    printf("Wprowadz ciag:\n");
    int coord[4][2] =  {{2*DIST_FROM_EDGE, DIST_FROM_EDGE}, // 0.x, 0.y
                        {2*(BOARD_SIZE - DIST_FROM_EDGE), DIST_FROM_EDGE}, // 1
                        {2*DIST_FROM_EDGE, BOARD_SIZE - DIST_FROM_EDGE}, // 2
                        {2*(BOARD_SIZE - DIST_FROM_EDGE), BOARD_SIZE - DIST_FROM_EDGE}}; // 3 
    char *in = NULL;
    size_t len = 0, in_size = 0;
    size_t i;
    in_size = getline(&in, &len, stdin);
    board_init(board);
              
    for (i = 0; i < in_size - 1; ++i)
    {
        if (in[i] != '0' && in[i] != '1')
        {
            printf ("Symbol '%c' nie istnieje w alfabecie [symbol nr %d]\n", in[i], i+1);
            free(in);
            return 1;
        }
    }
    for (i = 0; i < in_size - 1; ++i)
    {
        anim (board, start, end, coord);
        //printf ("q%d--%c-->q%d\n", state, in[i], path[in[i] - '0'][state]);
        state = path[in[i] - '0'][state];
    }
    if (state != 2)
    {
        printf ("stan koncowy q%d nie jest stanem akceptujacym\nSlowo %s nie nalezy do jezyka regularnego automatu\n", state, in);
        free(in);
        return 2;
    }
    printf ("Stan koncowy q%d jest stanem akceptujacym\nSlowo %s nalezy do jezyka regularnego automatu\n", state, in);
    free(in);
    return 0;
}