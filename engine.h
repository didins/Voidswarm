#ifndef ENGINE_H
#define ENGINE_H

#include "message.h"
#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>

class Engine
{
public:
    Engine(int);
    ~Engine();

    int getTick() { return currTick; }
    unsigned hash();

    void process(Message);
    void tick();

    void draw(sf::RenderWindow&);

private:
    int currTick, players;
    std::vector<int> x, y, r;
    std::vector<int> t_x, t_y;
};

#endif // ENGINE_H
