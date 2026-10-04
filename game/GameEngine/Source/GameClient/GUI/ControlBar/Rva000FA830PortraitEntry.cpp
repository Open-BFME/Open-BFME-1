// cl: /DNDEBUG /DWIN32 /MD /EHsc
// The portrait-entry list uses the adjacent Rva000FA610 selector bodies.
#include "../../../Common/Bfme/BfmeVecVLH.h"

typedef int Int;

class Image;
class Player;

class Rva000FA830PortraitEntry
{
public:
    char m_prefix[0x30];
    Int m_stamp;
    char m_between[0x08];
    Int m_key;
    char m_suffix[0x20];
};

class Rva000FA830PortraitList
{
public:
    bool updateEntry(Int index, Int key, const Image **image);
    const Image *rva000FA800(Int index);

private:
    void *m_vtable;
    Rva000FA830PortraitEntry *m_begin;
    Rva000FA830PortraitEntry *m_end;
    void *m_unused;
    Player *m_player;
};

class GameLogicRva000FA830
{
public:
    char m_prefix[0x3c];
    Int m_frame;
};

class GameLogic;
extern GameLogic *TheGameLogic;
static inline GameLogicRva000FA830 *TheGameLogicRva000FA830View() { return (GameLogicRva000FA830 *)TheGameLogic; }

// Retail calls the entry getter and the portrait getter through ILT thunks.
extern void j_000055e7();
extern void j_0000d2a6();

bool Rva000FA830PortraitList::updateEntry(
    Int index, Int key, const Image **image)
{
    Rva000FA830PortraitEntry *entry = m_begin;
    Rva000FA830PortraitEntry *end = m_end;
    if (entry != end)
    {
        do
        {
            if (entry->m_key == key)
                return false;
            entry = reinterpret_cast<Rva000FA830PortraitEntry *>(
                reinterpret_cast<char *>(entry) + 0x60);
        }
        while (entry != end);
    }

    typedef Rva000FA830PortraitEntry *(Rva000FA830PortraitList::*Fn)(Int);
    union { void (*fn)(); Fn call; } u = { j_000055e7 };
    entry = (this->*u.call)(index);
    if (entry == 0 || entry->m_stamp != -1)
        return false;

    entry->m_stamp = TheGameLogicRva000FA830View()->m_frame;
    entry->m_key = key;
    if (image == 0)
    {
        return true;
    }

    typedef const Image *(Rva000FA830PortraitEntry::*Portrait)(Player *) const;
    union { void (*fn)(); Portrait call; } p = { j_0000d2a6 };
    *image = (entry->*p.call)(m_player);
    return true;
}

// The bounds-checked getter at 0x000F94B0 shares this list's 0x60-byte
// entries. The null path returns an Image pointer, not void.
const Image *Rva000FA830PortraitList::rva000FA800(Int index)
{
    Rva000FA830PortraitEntry *entry =
        reinterpret_cast<Rva000FA830PortraitEntry *>(
            reinterpret_cast<BfmeVecVLH *>(this)->bfmeAtVLH(index));
    if (!entry)
        return 0;
    typedef const Image *(Rva000FA830PortraitEntry::*Portrait)(Player *) const;
    union { void (*fn)(); Portrait call; } p = { j_0000d2a6 };
    return (entry->*p.call)(m_player);
}
