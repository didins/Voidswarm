#include "engine.h"

Engine::Engine(int n)
{
    currTick = 0;
    players = n;

    x.resize(n); y.resize(n); r.resize(n);
    t_x.resize(n); t_y.resize(n);

    for(int i = 0; i < n; i++)
    {
        x[i] = y[i] = t_x[i] = t_y[i] = i * 50;
        r[i] = 20;
    }
}

Engine::~Engine()
{
    // nothin' for now
}

void Engine::process(Message m)
{
    if(m.getTick() != currTick)
        printf("[ENGINE] message tick does not match: %i @ %i\n", m.getTick(), currTick);

    switch(m.getType())
    {
    case MSG_SET_TARGET:
        t_x[m.getSender()] = m.getSetTarget().x - r[m.getSender()];
        t_y[m.getSender()] = m.getSetTarget().y - r[m.getSender()];
        break;

    case MSG_RESIZE:
        r[m.getSender()] += m.getResize().delta;
        x[m.getSender()] -= m.getResize().delta;
        t_x[m.getSender()] -= m.getResize().delta;
        y[m.getSender()] -= m.getResize().delta;
        t_y[m.getSender()] -= m.getResize().delta;
        break;

    default:
        printf("[ENGINE] unknown message type: %i\n", m.getType());
    }
}

int abs(int x) { return x < 0 ? -x : x; }
void Engine::tick()
{
    for(int i = 0; i < players; i++)
    {
        x[i] += ((x[i] > t_x[i]) ? -1 : 1) * std::min(5, abs(x[i] - t_x[i]));
        y[i] += ((y[i] > t_y[i]) ? -1 : 1) * std::min(5, abs(y[i] - t_y[i]));
    }

    currTick++;
}

// sdbm
unsigned Engine::hash()
{
    unsigned res = currTick + players;
    for(int i = 0; i < players; i++)
    {
        res = x[i] + (res << 6) + (res << 16) - res;
        res = y[i] + (res << 6) + (res << 16) - res;
        res = r[i] + (res << 6) + (res << 16) - res;
        res = t_x[i] + (res << 6) + (res << 16) - res;
        res = t_y[i] + (res << 6) + (res << 16) - res;
    }
}

void Engine::draw(sf::RenderWindow &w)
{
    w.clear();
    for(int i = 0; i < players; i++)
    {
        sf::CircleShape tmp(r[i]);
        tmp.setPosition(x[i], y[i]);
        tmp.setFillColor(sf::Color(255 * ((i + 1) & 1), 255 * (((i + 1) >> 1) & 1), 255 * (((i + 1) >> 2) & 1)));
        w.draw(tmp);
    }
}
