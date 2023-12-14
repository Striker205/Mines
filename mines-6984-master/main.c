#include <stdlib.h>
#include "game.h"
#include "ui.h"
#include "board.h"
#include <stdio.h>
int main() {
    Game *game=create_game();
    gameloop(game);
}
