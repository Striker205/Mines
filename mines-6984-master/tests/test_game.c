#include "greatest.h"
#include "../board.h"
#include "../game.h"

TEST open_mine() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if(game->board->tiles[row][column]->is_mine){
                open_tile(game, row, column);
            }
        }
    }
    ASSERT_EQ(FAILED, game->game_state);
    destroy_game(game);
    PASS();
}

TEST open_tile_with_bad_coordinates() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    open_tile(game, -1, -1);
    open_tile(game, game->board->row_count, game->board->column_count);

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
                    ASSERT_EQ(CLOSED, game->board->tiles[row][column]->tile_state);
        }
    }
    destroy_game(game);
    PASS();
}

TEST mark_tile_with_bad_coordinates() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int mark_count = 0;
    mark_count = mark_mine(game, -1, -1, mark_count);
    mark_count = mark_mine(game, game->board->row_count, game->board->column_count, mark_count);

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
                    ASSERT_EQ(CLOSED, game->board->tiles[row][column]->tile_state);
        }
    }

    ASSERT_EQ(0, mark_count);
    destroy_game(game);
    PASS();
}

TEST mark_more_tiles_than_mine_count() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int mark_count = 0;

    for(int i = 0; i < game->board->mine_count; i++){
        mark_count = mark_mine(game, i / game->board->row_count, i % game->board->column_count, mark_count);
        ASSERT_EQ(MARKED, game->board->tiles[i / game->board->row_count][i % game->board->column_count]->tile_state);
    }
    for(int i = game->board->mine_count; i < game->board->mine_count + 2; i++){
        mark_count = mark_mine(game, i / game->board->row_count, i % game->board->column_count, mark_count);
        ASSERT_EQ(CLOSED, game->board->tiles[i / game->board->row_count][i % game->board->column_count]->tile_state);
    }

    ASSERT_EQ(game->board->mine_count, mark_count);
    destroy_game(game);
    PASS();
}

TEST mark_marked_tile_removes_mark() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int mark_count = 0;

    mark_count = mark_mine(game, 2, 2, mark_count);
    mark_count = mark_mine(game, 2, 2, mark_count);
    ASSERT_EQ(CLOSED, game->board->tiles[2][2]->tile_state);

    ASSERT_EQ(0, mark_count);
    destroy_game(game);
    PASS();
}

TEST mark_closed_tile_adds_mark() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int mark_count = 0;

    mark_count = mark_mine(game, 2, 2, mark_count);
    ASSERT_EQ(MARKED, game->board->tiles[2][2]->tile_state);

    ASSERT_EQ(1, mark_count);
    destroy_game(game);
    PASS();
}

TEST mark_does_nothing_with_wrong_mark_count() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    int mark_count = -1;
    mark_count = mark_mine(game, 2, 2, mark_count);
    ASSERT_EQ(CLOSED, game->board->tiles[2][2]->tile_state);
    ASSERT_EQ(-1, mark_count);

    mark_count = game->board->mine_count + 1;
    mark_count = mark_mine(game, 2, 2, mark_count);
    ASSERT_EQ(CLOSED, game->board->tiles[2][2]->tile_state);
    ASSERT_EQ(game->board->mine_count + 1, mark_count);

    destroy_game(game);
    PASS();
}

TEST mark_open_tile_keeps_open_tile() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;
    int mark_count = 0;

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if(!game->board->tiles[row][column]->is_mine){
                open_tile(game, row, column);
                mark_count = mark_mine(game, row, column, mark_count);
                ASSERT_EQ(OPEN, game->board->tiles[row][column]->tile_state);
            }
        }
    } 

    ASSERT_EQ(0, mark_count);
    destroy_game(game);
    PASS();
}

TEST count_score_after_move() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 70);
    game->board = board;
    bool is_closed_tile_open = false;
    int score = 1;
    while (!is_closed_tile_open) {
        int row = rand() % game->board->row_count;
        int column = rand() % game->board->column_count;
        if (!game->board->tiles[row][column]->is_mine) {
            open_tile(game, row, column);
            score += game->board->tiles[row][column]->value;
            ASSERT_EQ(score, game->player->score);
            is_closed_tile_open = true;
        }
    }

    destroy_game(game);
    PASS();
}

TEST count_score_when_game_failed() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 30);
    game->board = board;
    game->player->score = 30;
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (game->board->tiles[row][column]->is_mine) {
                open_tile(game, row, column);
                ASSERT_EQ(15, game->player->score);
                break;
            }
        }
    }

    destroy_game(game);
    PASS();
}

SUITE (test_game) {
    RUN_TEST(open_mine);
    RUN_TEST(open_tile_with_bad_coordinates);
    RUN_TEST(count_score_after_move);
    RUN_TEST(count_score_when_game_failed);
    RUN_TEST(mark_tile_with_bad_coordinates);
    RUN_TEST(mark_closed_tile_adds_mark);
    RUN_TEST(mark_marked_tile_removes_mark);
    RUN_TEST(mark_more_tiles_than_mine_count);
    RUN_TEST(mark_open_tile_keeps_open_tile);
    RUN_TEST(mark_does_nothing_with_wrong_mark_count);
}
