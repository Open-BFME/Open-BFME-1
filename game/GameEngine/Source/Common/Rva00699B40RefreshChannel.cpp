// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/GameEngine/Source/Common
// Retail 0x00699B40 refreshes output side b of all six channels in each of
// three 0x1C4-byte volume blocks at TheAudio+0xB8. Keeping
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

// The retail global at 0x012ED668 is EA's AudioManager *TheAudio, defined once
// in game/GameEngine/Source/Common/Audio/GameAudio.cpp.  This TU keeps its own
// address-derived view of that object and casts at the use, so the reference
// names the one linked global.
class AudioManager;
extern AudioManager *TheAudio;
static inline Rva00699B40Client *localAudio() { return (Rva00699B40Client *)TheAudio; }

void rva00699B40RefreshChannel(int b)
{
    if (localAudio())
    {
        for (int i = 0; i < 3; ++i)
        {
            Rva00699180Owner &owner = localAudio()->blocks[i].owner;
            for (int a = 0; a < 6; ++a)
                owner.refreshPair(a, b);
        }
    }
}

void Rva00699B90()
{
    if (localAudio())
    {
        for (int i = 0; i < 3; ++i)
        {
            Rva00699180Owner &owner = localAudio()->blocks[i].owner;
            for (int a = 0; a < 6; ++a)
            {
                for (int b = 0; b < 2; ++b)
                    owner.refreshPair(a, b);
            }
        }
    }
}

void rva00699AF0(int a)
{
    if (localAudio())
    {
        for (int i = 0; i < 3; ++i)
        {
            Rva00699180Owner &owner = localAudio()->blocks[i].owner;
            for (int b = 0; b < 2; ++b)
                owner.refreshPair(a, b);
        }
    }
}
