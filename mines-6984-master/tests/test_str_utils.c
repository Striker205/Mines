#include "greatest.h"
#include "../str_utils.h"

TEST remove_spaces_from_name_without_spaces() {
    char name_to_change[] = "peto";
    str_remove_spaces(name_to_change);
    ASSERT_STR_EQ("peto", name_to_change);
    PASS();
}

TEST remove_spaces_from_name_with_spaces() {
    char name_to_change[] = "peto z \nruzinova\n\n";
    str_remove_spaces(name_to_change);
    ASSERT_STR_EQ("petozruzinova", name_to_change);
    PASS();
}

SUITE (test_user_interface) {
    RUN_TEST(remove_spaces_from_name_without_spaces);
    RUN_TEST(remove_spaces_from_name_with_spaces);
}