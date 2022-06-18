#include <iostream>
#include <doctest.h>
#include "flappybird.h"

TEST_CASE("Collision") {
REQUIRE(collision(60, 0, 0) == 0);
REQUIRE(collision(65, 7, 6) == 1);
REQUIRE(collision(65, 3, 11) == 1);
}

TEST_CASE("The bird up") {
REQUIRE(pressSpace(6) == 3);
REQUIRE(pressSpace(2) == 2);
}

TEST_CASE("The bird down") {
REQUIRE(birdDown(6) == 7);
}

// Для проверки всех ошибок
extern "C" const char *__asan_default_options() {
    return "debug=1:detect_invalid_pointer_pairs=2:detect_leak=1:detect_leaks=1:leak_check_at_exit=true:color=always";
}