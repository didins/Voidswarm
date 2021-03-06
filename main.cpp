#include <cstdio>
#include "server.h"
#include "client.h"

using namespace std;

int main()
{
    printf("[C]lient or [s]erver?\n");
    char c;
    do
        scanf(" %c", &c);
    while(c != 'c' && c != 's');

    try
    {
        if(c == 'c') return Client::main();
        else return Server::main();
    }
    catch(const char *err)
    {
        printf("ERROR: %s!\n", err);

        FILE *log = fopen("crash.txt", "w");
        fprintf(log, "Crash reason: \"%s\"", err);
        fclose(log);

        printf(".voidswarm will now exit.\n");
    }

    return 0;
}
