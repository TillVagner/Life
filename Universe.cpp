#include "Universe.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

Universe::Universe(int width, int height)
    : width(width), height(height), name(""), rule("") {
    grid.resize(height, std::vector<Cell>(width));
}


void Universe::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    if (line.substr(0, 3) != "#N ") {
        std::cerr << "Формат имени вселенной неверен." << std::endl;
        return;
    }
    name = line.substr(3);

    std::getline(file, line);
    if (line.substr(0, 3) != "#R ") {
        std::cerr << "Формат правила неверен." << std::endl;
        return;
    }
    rule = line.substr(3); 

    grid.resize(height, std::vector<Cell>(width));

    std::set<std::pair<int, int>> liveCells; 
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int x, y;
        if (iss >> x >> y) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                liveCells.emplace(y, x); 
            } else {
                std::cerr << "Координаты (" << x << ", " << y << ") выходят за пределы поля." << std::endl;
            }
        }
    }

    for (const auto &[y, x] : liveCells) {
        grid[y][x].alive = true; 
    }
}

// Метод обновления состояния клеток
void Universe::update() {
    std::vector<std::vector<Cell>> newGrid = grid; 

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int aliveNeighbors = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue; 

                    int newY = (y + dy + height) % height;
                    int newX = (x + dx + width) % width;

                    if (grid[newY][newX].alive) {
                        aliveNeighbors++; 
                    }
                }
            }

            // Правила перехода
            if (grid[y][x].alive) { 
                newGrid[y][x].alive = (aliveNeighbors == 2 || aliveNeighbors == 3); 
            } else { 
                newGrid[y][x].alive = (aliveNeighbors == 3); 
            }
        }
    }

    grid = newGrid;
}

// Метод отображения состояния клеток
void Universe::display() const {
    std::cout << "Вселенная: " << name << "\nПравило: " << rule << "\n";
    for (const auto &row : grid) {
        for (const auto &cell : row) {
            std::cout << (cell.alive ? 'O' : '.'); // Живая клетка - O, мертвая - .
        }
        std::cout << std::endl;
    }
}

// Метод сохранения состояния в файл
void Universe::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
                std::cerr << "Не удалось открыть файл для сохранения: " << filename << std::endl;
                return;
            }
            // имя вселенной
            file << "#N " << name << "\n";
            // правило
            file << "#R " << rule << "\n";

            // координаты "живых" клеток
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    if (grid[y][x].alive) {
                        file << x << " " << y << "\n"; //координаты
                    }
                }
            }
        }