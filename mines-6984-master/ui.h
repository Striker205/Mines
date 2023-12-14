#ifndef MINES_UI_H
#define MINES_UI_H

#include "game.h"

void read_player_name(Game *game);
void play_game(Game *game);
void gameloop(Game *game);
Board *read_game_parameters();
#endif //MINES_UI_H

