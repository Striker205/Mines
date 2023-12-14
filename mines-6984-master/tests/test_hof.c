#include "greatest.h"
#include "../hof.h"

TEST isol() {
    Player list_of_players[PLAYERS_LIMIT] = {
        {"misko", 43},
        {"robko", 99},
        {"dusko",  55},
    };

    int size_of_list = 99;
    sort_list(list_of_players, size_of_list);
    ASSERT_EQ(43, list_of_players[0].score);
    PASS();
}

TEST load_file_number_of_players() {
    char hof_file[] = "tests/score/optimal_size";
    Player list_of_players[PLAYERS_LIMIT];

    ASSERT_EQ(5, read_scores(hof_file, list_of_players));
    PASS();
}

TEST load_file_over_limit() {
    char hof_file[] = "tests/score/over_size";
    int high_size_of_list = PLAYERS_LIMIT + 5;
    Player list_of_players[high_size_of_list];

    ASSERT_EQ(PLAYERS_LIMIT, read_scores(hof_file, list_of_players));
    PASS();
}

TEST load_nonexistent_file() {
    char hof_file[] = "tests/score/nonexistent";
    Player list_of_players[PLAYERS_LIMIT];
    ASSERT_EQ(0, read_scores(hof_file, list_of_players));
    PASS();
}

TEST compare_loaded_and_saved_players() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
    };
    int size_of_input_list = 3;
    char hof_file[] = "tests/score/for_saving";

    save_scores(hof_file, list_of_players, size_of_input_list);
    Player test_list_of_players[size_of_input_list];
    int size_of_test_list =
            read_scores(hof_file, test_list_of_players);

            ASSERT_EQ(size_of_input_list, size_of_test_list);
    for (int i = 0; i < size_of_test_list; i++) {
        ASSERT_EQ(list_of_players[i].score, test_list_of_players[i].score);
        ASSERT_STR_EQ(list_of_players[i].name, test_list_of_players[i].name);
    }
    remove(hof_file);
    PASS();
}

TEST save_player_over_limit() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    int size = 10;
    char hof_file[] = "tests/score/for_saving";
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 1;

    ASSERT_FALSE(add_player_to_list(list_of_players, &size, *player));
    free(player);
    remove(hof_file);
    PASS();
}

TEST add_player_to_optimal_list() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"alex",  18},
            {"lubo",  2}
    };
    int size = 3;
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    int size_before_adding = size;
    add_player_to_list(list_of_players, &size, *player);
    ASSERT_EQ(size_before_adding + 1, size);
    free(player);
    PASS();
}

TEST ipol() {
    Player list_of_players[PLAYERS_LIMIT] = {
        {"dusko", 43},
        {"misko", 99},
        {"vladko",  55},
    };
    int size_of_list = 5;
    sort_list(NULL, size_of_list);
    ASSERT_EQ(43, list_of_players[0].score);
    PASS();
}


SUITE (test_hall_of_fame) {
    RUN_TEST(load_file_number_of_players);
    RUN_TEST(load_file_over_limit);
    RUN_TEST(load_nonexistent_file);
    RUN_TEST(compare_loaded_and_saved_players);
    RUN_TEST(save_player_over_limit);
    RUN_TEST(add_player_to_optimal_list); 
    RUN_TEST(ipol);
    RUN_TEST(isol);
}

