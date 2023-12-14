
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "hof.h"

int read_scores(char *filename, Player *list_of_players) {
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    int index_of_player = 0;
    while (fscanf(file, "%s %d", list_of_players[index_of_player].name, &list_of_players[index_of_player].score) != EOF && index_of_player < PLAYERS_LIMIT) {
        index_of_player++;
    }
    fclose(file);
    sort_list(list_of_players, index_of_player);
    return index_of_player;

}

void save_scores(char *filename, Player *list_of_players, const int size) {
    assert(filename != NULL);
    assert(list_of_players != NULL);

    sort_list(list_of_players, size);
    FILE *file = fopen(filename, "w");
    if (file == NULL) { return; }
    for (int i = 0; i < size; i++) {
        if (i < PLAYERS_LIMIT) {
            fprintf(file, "%s %d\n", list_of_players[i].name, list_of_players[i].score);
        }
    }
    fclose(file);
}

bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player) {
    assert(list_of_players != NULL && size_of_list != NULL);

    if ( *size_of_list < PLAYERS_LIMIT ){
        list_of_players[*size_of_list] = player;
        *size_of_list = *size_of_list + 1;
    }else if( list_of_players[PLAYERS_LIMIT - 1].score > player.score && *size_of_list >= PLAYERS_LIMIT){  
        return false;
    }else{
        list_of_players[*size_of_list-1] = player;
    }
    sort_list(list_of_players, *size_of_list);
    return true;
}


void sort_list(Player* list_of_players, int size_of_list){
    if (  list_of_players == NULL || size_of_list > PLAYERS_LIMIT ){
        return;
    }
    int key = -1;
    char name_key[MAX_PLAYER_LENGTH];
    int j = -1;
    for ( int i = 1; i < size_of_list; i++ ){
        key = list_of_players[i].score;
        strcpy(name_key, list_of_players[i].name);
        j = i-1;
        while ( j >= 0 && list_of_players[j].score <= key ) {
            list_of_players[j+1].score = list_of_players[j].score;
            strcpy(list_of_players[j+1].name, list_of_players[j].name);
            j--;
        }
        list_of_players[j+1].score = key;
        strcpy(list_of_players[j+1].name, name_key);
    }
}
