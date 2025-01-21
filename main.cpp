#include "Game.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
    std::string filename;
    int width = 10;
    int height = 10;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--iterations") == 0) {
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {

        } else {
            filename = argv[i]; 
        }
    }

    Game game(width, height); // Создаем игру
    
    if (!filename.empty()) {
        game.loadFromFile(filename); // Загружаем вселенную из файла
    } else {

    }

    game.run();
    return 0;
}
