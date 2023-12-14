#ifndef MINES_HOF_H
#define MINES_HOF_H

#include <stdbool.h>

//limit of score file
#define PLAYERS_LIMIT 10

//limit of Player length
#define MAX_PLAYER_LENGTH 30

typedef struct {
    char name[MAX_PLAYER_LENGTH];       /* name of Player */
    int score;                          /* value of score */
} Player;

int read_scores(char *filename, Player *list_of_players);
void save_scores(char *filename, Player *list_of_players, const int size);
bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player);
void sort_list(Player* list_of_players, int size_of_list);
#endif //MINES_HOF_H
