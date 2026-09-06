// cl: /O2 /DNDEBUG /MD -Ireference/shims/gamespy
// Retail behavior is nickname sanitization: a leading digit or '-' and every
// character outside the GameSpy VALID_NICK_CHARS set become '_'.  No owning
// SDK symbol survives at this address, so the address-derived name is used.

#include <ctype.h>
#include <string.h>

#define VALID_NICK_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-"

extern "C" void __cdecl Rva00860620(char *translated, const char *nick)
{
    if (isdigit(*nick) || (*nick == '-'))
        *translated++ = '_';

    char *out = translated;
    for (;;)
    {
        int character = *nick;
        if (character == 0)
            break;
        ++nick;
        if (strchr(VALID_NICK_CHARS, character) == NULL)
            character = '_';
        *out++ = (char)character;
    }
    *out = '\0';
}
