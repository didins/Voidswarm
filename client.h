#ifndef CLIENT_H
#define CLIENT_H

#include "communicator.h"

namespace Client
{
    int id; // redni broj igraca

    int main()
    {
        printf("Started client.\n");
        printf("Server IP: ");
        char ip[20];
        scanf(" %s", &ip);

        Communicator comm;
        comm.connectTo(ip, 53252);

        printf("Waiting for the game to start . . . ");

        Message start;
        while(start.getType() != MSG_START)
            while(!comm.receive(start)) ;
        id = start.getStart().player_i;

        printf("Started!\n Player ID: %i\n", id);

        while(1)
        {
            Message rec;
            while(comm.receive(rec))
            {
                if(rec.getType() == MSG_CLICK)
                    printf("%i %i\n", rec.getClick().x, rec.getClick().y);
            }
            sf::sleep(sf::milliseconds(20));
            if(rand() % 300 == 0)
            {
                printf(" >\n");
                Message m(MsgClick(id, id), 0);
                comm.send(m);
            }
        }

        return 0;
    }
}

#endif // CLIENT_H
