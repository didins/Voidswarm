#include "message.h"

Message::Message()
{
    type = 0;
}

Message::Message(char s[], int n)
{
    fromCString(s, n);
}

void Message::toCString(char s[], int &n)
{
    s[0] = tick & 0xFF;
    s[1] = (tick >> 8) & 0xFF;
    s[2] = (tick >> 16) & 0xFF;
    s[3] = (tick >> 24) & 0xFF;

    s[4] = type & 0xFF;
    s[5] = (type >> 8) & 0xFF;

    for(int i = 0; i < DATA_LEN; i++)
        s[i + 6] = bin[i];
    n = DATA_LEN + 6;
}

void Message::fromCString(char s[], int n)
{
    tick = (s[3] << 24) | (s[2] << 16) | (s[1] << 8) | s[0];
    type = (s[5] << 8) | s[4];
    for(int i = 0; i < n; i++)
        bin[i] = s[i + 6];
}
