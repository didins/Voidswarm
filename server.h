#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include <vector>
#include "communicator.h"

namespace Server
{
    const int MAX_PLAYERS = 10;
    Communicator players[MAX_PLAYERS]; // ovo nije vector zato sto resize() ne saradjuje sa TcpSocket
    int n_players;

    int main()
    {
        printf("Started server.\n");
        printf("Number of players: ");
        scanf("%i", &n_players);

        for(int i = 0; i < n_players; i++)
        {
            printf("Waiting for player %i to connect . . . ", i + 1);
            players[i].waitForConnection(53252);
            printf("Done.\n");
        }

        for(int i = 0; i < n_players; i++)
            players[i].send(Message(MsgStart(i, n_players), 0));

        printf("Started game.\n");

        bool running = true;
        while(running)
        {
            Message m;
            for(int i = 0; i < n_players; i++)
                if(players[i].receive(m))
                {
                    if(m.getType() == MSG_END) running = false;
                    m.setSender(i);
                    for(int j = 0; j < n_players; j++)
                        players[j].send(m);
                }
        }

        printf("Game finished.\n");

        return 0;
    }
}

#endif // SERVER_H
