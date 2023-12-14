#include "greatest.h"

extern SUITE(test_game);
extern SUITE(test_board);
extern SUITE(test_hall_of_fame);
extern SUITE(test_view);
extern SUITE(test_user_interface);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(test_game);
    RUN_SUITE(test_board);
    RUN_SUITE(test_hall_of_fame);
    RUN_SUITE(test_view);
    RUN_SUITE(test_user_interface);
    GREATEST_MAIN_END();
}
