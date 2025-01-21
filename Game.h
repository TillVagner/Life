#ifndef GAME_H
#define GAME_H

#include "Universe.h"

class Game {
private:
    Universe universe; 
    int currentIteration;

public:
    Game(int width, int height);
    void run();
    void processCommand(const std::string &cmd);
    void loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename) const;

};

#endif 

