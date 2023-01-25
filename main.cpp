#include "src/Controller/Controller.hpp"

int main (int argc, char **argv) {
    int disksAmount = 3;

    if (argc > 1) {
        disksAmount = atoi(argv[1]);
    }

    Controller game(disksAmount);
    game.menu();
}