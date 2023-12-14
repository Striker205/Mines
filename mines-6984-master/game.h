#ifndef MINES_GAME_H
#define MINES_GAME_H
#include "hof.h"
#include "board.h"

typedef enum  {
    FAILED,
    PLAYING,
    SOLVED,
} GameState;

typedef struct {
    Board *board;          /* Struct of the play field */
    Player *player;        /* Struct of user who is playing the Game */
    GameState game_state;  /* Enum for status of the Game */
} Game;

Game *create_game();
void open_tile(Game *game, int input_row, int input_column);
int mark_mine(Game *game, int input_row, int input_column, int marks_count);
void destroy_game(Game *game);

#endif //MINES_GAME_H