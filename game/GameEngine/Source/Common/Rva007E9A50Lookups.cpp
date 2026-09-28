// cl: /GS
// Retail lookup bodies: independent starts after int3, each 179 bytes through
// RET 4, followed by int3 padding. Each dispatch table address is witnessed
// by the two absolute operands in that body's retail instructions.
#include <string.h>
#pragma intrinsic(strcmp)
class Rva007E8810Message {
public:
    bool getString(const char *, char *, int);
};
struct Rva007E9A50Entry {
    void *field00;
    const char *field04;
};

extern Rva007E9A50Entry *g_Rva012C37F8[];
class Rva007E9A50 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007E9A50::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C37F8; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C3958[];
class Rva007F1160 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F1160::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3958; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C3988[];
class Rva007F1EA0 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F1EA0::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3988; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C3998[];
class Rva007F2D70 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F2D70::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3998; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C39CC[];
class Rva007F3320 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F3320::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C39CC; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C39E4[];
class Rva007F4000 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F4000::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C39E4; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}

extern Rva007E9A50Entry *g_Rva012C3A1C[];
class Rva007F4380 {
public:
    Rva007E9A50Entry *lookup(Rva007E8810Message *message);
};
Rva007E9A50Entry *Rva007F4380::lookup(Rva007E8810Message *message)
{
    char text[32];
    if (!message->getString("TXN", text, 32))
        return 0;
    for (Rva007E9A50Entry **entry = g_Rva012C3A1C; *entry; ++entry) {
        if (strcmp((*entry)->field04, text) == 0)
            return *entry;
    }
    return 0;
}
