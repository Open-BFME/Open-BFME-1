// cl: /O2
// FESL message-codec descriptor lookups at retail 0x007FCF10 (vtable slot
// 0x00D2BFA8) and 0x007FBAB0 (vtable slot 0x00D2BD48). Each codec vtable is
// deleting destructor (Gen007FCF50 / Gen007FBAF0), fetch, this lookup, then
// the per-message encoders. The lookup ignores the codec, reads the message
// id at +0x1c and scans a null-terminated static table of descriptor
// pointers (VA 0x012C3BC8 / 0x012C3B40) for the entry whose +8 id matches.

struct Rva007FCF10Entry
{
    char m_pad00[8];
    int m_id;
};

struct Rva007FCF10Message
{
    char m_pad00[0x1c];
    int m_id;
};

extern Rva007FCF10Entry *g_rva007FCF10Entries[];
extern Rva007FCF10Entry *g_rva007FBAB0Entries[];

class Rva007FCF10Codec
{
public:
    virtual ~Rva007FCF10Codec();
    virtual int fetch();
    virtual Rva007FCF10Entry *findEntry(Rva007FCF10Message *message);
};

class Rva007FBAB0Codec
{
public:
    virtual ~Rva007FBAB0Codec();
    virtual int fetch();
    virtual Rva007FCF10Entry *findEntry(Rva007FCF10Message *message);
};

Rva007FCF10Entry *Rva007FCF10Codec::findEntry(Rva007FCF10Message *message)
{
    int id = message->m_id;
    if (id == -1)
        return 0;
    for (Rva007FCF10Entry **entry = g_rva007FCF10Entries; *entry; ++entry)
        if ((*entry)->m_id == id)
            return *entry;
    return 0;
}

Rva007FCF10Entry *Rva007FBAB0Codec::findEntry(Rva007FCF10Message *message)
{
    int id = message->m_id;
    if (id == -1)
        return 0;
    for (Rva007FCF10Entry **entry = g_rva007FBAB0Entries; *entry; ++entry)
        if ((*entry)->m_id == id)
            return *entry;
    return 0;
}
