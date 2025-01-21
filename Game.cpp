#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>

// Конструктор
Game::Game(int width, int height) : universe(width, height), currentIteration(0) {}

// Метод запуска игры
void Game::run() {
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);
    }
}

// Метод обработки команд
void Game::processCommand(const std::string &cmd) {
    if (cmd == "exit") {
        std::cout << "Игра закончена." << std::endl;
        exit(0);
    } else if (cmd.find("dump") == 0) {
        std::string filename = cmd.substr(5);
        universe.saveToFile(filename);
        std::cout << "Состояние сохранено в файл " << filename << std::endl;
    } else if (cmd.find("tick") == 0 || cmd.find("t") == 0) {
        int n = 1;
        std::istringstream iss(cmd);
        std::string commandType;
        iss >> commandType; 

        if (iss >> n) {
            for (int i = 0; i < n; ++i) {
                universe.update(); 
                currentIteration++;
            }
        } else {
            universe.update(); 
            currentIteration++;
        }

        universe.display();
    } else if (cmd == "help") {
        std::cout << "Команды:\n"
                  << "  dump <filename> - сохранить состояние в файл\n"

                              << "  tick <n> или t <n> - рассчитать n итераций\n"
                              << "  exit - выход\n"
                              << "  help - справка" << std::endl;
                } else {
                    std::cerr << "Неизвестная команда." << std::endl;
                }
            }

            // Метод загрузки из файла
            void Game::loadFromFile(const std::string &filename) {
                universe.loadFromFile(filename);
            }

            // Метод сохранения в файл
            void Game::saveToFile(const std::string &filename) const {
                universe.saveToFile(filename);
            }

