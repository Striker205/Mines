#include "greatest.h"
#include "../board.h"
#include "../game.h"

TEST loosing_on_first_move() {
    Board *board = create_board(9, 9, 9);
    
    create_new_board(board, 5, 5);

    ASSERT(board->row_count == 9);
    PASS();
}

TEST verify_with_high_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT_FALSE(is_input_data_correct(board, 6, 11));
    PASS();
}

TEST verify_with_low_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT_FALSE(is_input_data_correct(board, -1, 4));
    PASS();
}

TEST verify_with_correct_coordinates() {
    Board *board = create_board(10, 10, 5);
    ASSERT(is_input_data_correct(board, 0, 9));
    PASS();
}

TEST is_game_solved_at_the_start() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    bool is_solved = is_game_solved(game->board);
    ASSERT_FALSE(is_solved);
    destroy_game(game);
    PASS();
}

TEST is_game_solved_if_solved() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (!game->board->tiles[row][column]->is_mine) {
                open_tile(game, row, column);
            }
        }
    }
    ASSERT(is_game_solved(game->board));
    destroy_game(game);
    PASS();
}

TEST open_mines_after_win() {
    Game *game = create_game();
    Board *board = create_board(10, 10, 5);
    game->board = board;

    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (!game->board->tiles[row][column]->is_mine) {
                open_tile(game, row, column);
            }
        }
    }
    open_all_mines(game->board);
    for (int row = 0; row < game->board->row_count; row++) {
        for (int column = 0; column < game->board->column_count; column++) {
            if (game->board->tiles[row][column]->is_mine) {
                ASSERT_EQ(MARKED, game->board->tiles[row][column]->tile_state);
            }
        }
    }
    destroy_game(game);
    PASS();
}


/* 
    game parameters 
*/
TEST valid_row_count_parameter(){
    Board *board = create_board(9, 9, 9);

    ASSERT_EQ(9, board->row_count);
    PASS();
}

TEST valid_column_count_parameter(){
    Board *board = create_board(10, 10, 10);

    ASSERT_EQ(10, board->column_count);
    PASS();
}

TEST valid_mine_count_parameter(){
    Board *board = create_board(8, 8, 8);

    ASSERT_EQ(8, board->mine_count);
    PASS();
}

TEST boundary_row_count_parameter(){
    Board *board = create_board(30, 30, 30);

    ASSERT_EQ(30, board->row_count);
    PASS();
}

TEST boundary_column_count_parameter(){
    Board *board = create_board(30, 30, 30);

    ASSERT_EQ(30, board->column_count);
    PASS();
}

TEST over_max_row_count(){
    Board *board = create_board(45, 45, 10);

    ASSERT_EQ(30, board->row_count);
    PASS();
}

TEST over_max_column_count(){
    Board *board = create_board(45, 45, 10);

    ASSERT_EQ(30, board->column_count);
    PASS();
}

TEST bigger_mines_count_than_board_size(){
    Board *board = create_board(5, 5, 20);

    ASSERT_EQ(12, board->mine_count);
    PASS();
}

TEST negative_row_count_parameter(){
    Board *board = create_board(-10, 10, 5);

    ASSERT_EQ(1, board->row_count);
    PASS();
}

TEST negative_column_count_parameter(){
    Board *board = create_board(10, -10, 5);

    ASSERT_EQ(1, board->column_count);
    PASS();
}

TEST negative_mines_count_parameter(){
    Board *board = create_board(10, 10, -5);

    ASSERT_EQ(1, board->mine_count);
    PASS();
}


SUITE (test_board) {
    RUN_TEST(loosing_on_first_move);
    RUN_TEST(verify_with_high_coordinates);
    RUN_TEST(verify_with_low_coordinates);
    RUN_TEST(verify_with_correct_coordinates);
    RUN_TEST(is_game_solved_at_the_start);
    RUN_TEST(is_game_solved_if_solved);
    RUN_TEST(open_mines_after_win);
    
    RUN_TEST(valid_row_count_parameter);
    RUN_TEST(valid_column_count_parameter);
    RUN_TEST(valid_mine_count_parameter);
    RUN_TEST(boundary_column_count_parameter);
    RUN_TEST(boundary_row_count_parameter);
    RUN_TEST(over_max_column_count);
    RUN_TEST(over_max_row_count);
    RUN_TEST(bigger_mines_count_than_board_size);
    RUN_TEST(negative_row_count_parameter);
    RUN_TEST(negative_column_count_parameter);
    RUN_TEST(negative_mines_count_parameter);
}