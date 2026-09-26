// cl: /DNDEBUG /DWIN32 /MD /EHsc
// The portrait-entry list uses the adjacent Rva000FA610 selector bodies.

typedef int Int;

class Image;
class Player;

class Rva000FA830PortraitEntry
{
public:
    const Image *getPortrait(Player *player);

    char m_prefix[0x30];
    Int m_stamp;
    char m_between[0x08];
    Int m_key;
    char m_suffix[0x20];
};

class Rva000FA830PortraitList
{
public:
    Rva000FA830PortraitEntry *getEntry(Int index);
    bool updateEntry(Int index, Int key, const Image **image);

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

#define TheGameLogicRva000FA830 (*(GameLogicRva000FA830 **)0x012F0898)

#pragma comment(linker, "/alternatename:?getEntry@Rva000FA830PortraitList@@QAEPAVRva000FA830PortraitEntry@@H@Z=?j_000055e7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPortrait@Rva000FA830PortraitEntry@@QAEPBVImage@@PAVPlayer@@@Z=?j_0000d2a6@@YAXXZ")

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

    entry = getEntry(index);
    if (entry == 0 || entry->m_stamp != -1)
        return false;

    entry->m_stamp = TheGameLogicRva000FA830->m_frame;
    entry->m_key = key;
    if (image == 0)
    {
        return true;
    }

    *image = entry->getPortrait(m_player);
    return true;
}
