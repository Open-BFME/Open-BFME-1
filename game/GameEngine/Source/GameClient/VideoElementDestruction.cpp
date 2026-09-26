#include "../../Include/GameClient/Video.h"

// All three retail loops use 28-byte stride and ILT 0x167CF  -> Video::~Video.
// Their own semantic identities are not established, so retain the addresses.
void rva0081C9E0DestroyVideoRange(Video *first, Video *last)
{
    for (; first != last; ++first)
        first->~Video();
}

void rva0081CF10DestroyVideoRange(Video *first, Video *last)
{
    for (; first != last; ++first)
        first->~Video();
}

void rva0081D010DestroyVideoRange(Video *first, Video *last)
{
    for (; first != last; ++first)
        first->~Video();
}
