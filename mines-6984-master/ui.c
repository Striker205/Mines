#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "ui.h"
#include "view.h"
#include "board.h"
#include "str_utils.h"

#define HOF_FILENAME "score.txt"

/* private functions */
void game_loop(Game *game);
void print_play_field(Game *game, int input_row, int input_column);
void print_score(Player *list_of_players, int number_of_all_players);
void print_input_rules();
void gameloop(Game *game);

/**
 * Set game difficulty 
 */
Board *read_game_parameters(){
    
    int num[3] = {9, 9, 9};
    printf("Zadajte veľkosť herného poľa, s ktorým chcete hrať[S-V-M]. Napr. 5 5 9 : \n");
    scanf("%d %d %d", &num[0], &num[1], &num[2]);
    getchar();
 
    Board *board = create_board(num[0], num[1], num[2]);
    
    return board;
}


/**
 * Ask a player for his name and store in the game.
 */
void read_player_name(Game *game) {
    assert(game != NULL);
    printf("Zadajte vaše meno prosím: \n");
    char name_of_player[MAX_PLAYER_LENGTH];
    fgets(name_of_player, MAX_PLAYER_LENGTH, stdin);
    str_remove_spaces(name_of_player);
    strcpy(game->player->name, name_of_player);
}

/**
 * Handle whole process of the Game
 */
void play_game(Game *game) {
    assert(game != NULL);

    Player list_of_players[PLAYERS_LIMIT];
    int size_of_list = read_scores(HOF_FILENAME, list_of_players);
    if (size_of_list > 0) {
        print_score(list_of_players, size_of_list);
    }
    game_loop(game);

    if (game->game_state == SOLVED) {
        printf("Gratulujem %s. Riešenie je správne!\n", game->player->name);
    } else {
        printf("Ľutujem %s. Riešenie je nesprávne!\n", game->player->name);
    }
    printf("Vaše skóre je: %d\n", game->player->score);

    bool is_player_added_to_list =
            add_player_to_list(list_of_players, &size_of_list, *game->player);

    if (is_player_added_to_list) {
        save_scores(HOF_FILENAME, list_of_players, size_of_list);
    }
}


/**
 * Handles players input process
 * Loops until game state is playing
 */
void game_loop(Game *game) {
    assert(game != NULL);
    int input, input_row = -1, input_column = -1, marks = 0, firstMove = 1;
    do {
        print_play_field(game, input_row, input_column);
        print_input_rules();

        char choice = 0;
        while ((input = scanf("%c %d %d", &choice, &input_row, &input_column)) == 0) {
            scanf("%*[^\n] %*[^\n] %*[^\n]");
            print_input_rules();
        }
        if (input != EOF) {
            if(game->board->tiles[input_row - 1][input_column - 1]->is_mine && firstMove == 1){ //if there is a mine on first take, create new map and new values
                    create_new_board(game->board, input_row - 1, input_column - 1);
            }
            // if input is not empty and is correct then open tile or mark tile
            switch (choice){
            case 'o':
                open_tile(game, input_row - 1, input_column - 1);
                break;
            case 'm':
                marks = mark_mine(game, input_row - 1, input_column - 1, marks);
                break;
            default:
                break;
            }
            firstMove = 0;
        }

    } while (game->game_state == PLAYING);
    print_play_field(game, input_row, input_column);
}


void print_score(Player *list_of_players, int number_of_all_players) {
    char *text = view_hof(list_of_players, number_of_all_players);
    printf("%s", text);
    free(text);
}


void print_play_field(Game *game, int input_row, int input_column) {
    char *field = view_play_field(game->board, input_row, input_column);
    printf("\n%s\n", field);
    free(field);
}


void print_input_rules() {
    printf("Zadajte o ako \"open\" alebo m ako \"mark\", číslo riadka, medzeru a číslo stĺpca. Napr. o 2 3, m 5 9\n");
}

void gameloop(Game *game){
    char input[4];
    bool gameplay=true;
    while(gameplay==true){
        Game *game=create_game();
        Board *board = read_game_parameters();
        game->board=board;
        read_player_name(game);
        play_game(game);
        while(1){
            printf("\nPrajete si hru zopakovat? V pripade, ze ano, potvrdte to napisanim 'yes' v opacnom pripade 'no'\n");
            scanf("%3s",input);
            if(input[0]=='y'||input[0]=='n'){
                break;
            }
        }
        if(input[0]=='y'){
            destroy_game(game);
        }
        if(input[0]=='n'){
            destroy_game(game);
            exit(EXIT_SUCCESS);
        }
    }
}
