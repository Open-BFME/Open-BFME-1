// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/GameEngine/Source/Common
// Retail 0x00699B40 refreshes output side b of all six channels in each of
// three 0x1C4-byte volume blocks at TheAudioClientUpdate+0xB8. Keeping
// refreshPair's body in this TU lets MSVC keep ECX across the inner loop.
#include "Rva00699180Volume.cpp"

struct Rva00699B40Block
{
    Rva00699180Owner owner;
    char bytes_1B8[0x1C4 - sizeof(Rva00699180Owner)];
};

struct Rva00699B40Client
{
    char bytes_0[0xB8];
    Rva00699B40Block blocks[3];
};

extern void *TheAudioClientUpdate;

void rva00699B40RefreshChannel(int b)
{
    if (TheAudioClientUpdate)
    {
        for (int i = 0; i < 3; ++i)
        {
            Rva00699180Owner &owner = ((Rva00699B40Client *)TheAudioClientUpdate)->blocks[i].owner;
            for (int a = 0; a < 6; ++a)
                owner.refreshPair(a, b);
        }
    }
}
