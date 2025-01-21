#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <string>
#include <set>
#include "Cell.h"

class Universe {
private:
    std::vector<std::vector<Cell>> grid; // Сетка клеток
    int width;  // Ширина
    int height; // Высота
    std::string name; // Имя вселенной
    std::string rule; // Правило перехода

public:
    Universe(int width, int height);
    void loadFromFile(const std::string &filename);
    void update();
    void display() const;
    void saveToFile(const std::string &filename) const;

    std::string getName() const { return name; }
    std::string getRule() const { return rule; }
};

#endif // UNIVERSE_H

