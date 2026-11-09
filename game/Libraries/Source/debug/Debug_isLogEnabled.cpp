// cl: /DNDEBUG /MD /EHs-c- /Oy-

// Retail's 0x0088A7E0 body is the ledger row ?UpdateFrameStatus@Rva0088A7E0Debug;
// call it through that spelling (same this, same single reference argument).
struct Rva0088A7E0FrameHashEntry;
class Rva0088A7E0Debug
{
public:
    void UpdateFrameStatus(Rva0088A7E0FrameHashEntry &entry);
};

class Debug
{
public:
    struct FrameHashEntry
    {
        FrameHashEntry *next;
        unsigned address;
        unsigned type;
        const char *file;
        int line;
        int hits;
        int status;
    };

    bool isLogEnabled(unsigned address);

private:
    int m_prefix[6];
    FrameHashEntry *m_frameHash[10007];

    FrameHashEntry *AddFrameEntry(unsigned address, unsigned type,
        const char *file, int line);
    void UpdateFrameStatus(FrameHashEntry &entry);

    __forceinline FrameHashEntry *LookupFrame(unsigned address)
    {
        FrameHashEntry *entry = m_frameHash[address % 10007];
        while (entry != 0)
        {
            if (entry->address == address)
                return entry;
            entry = entry->next;
        }
        return 0;
    }
};

bool Debug::isLogEnabled(unsigned address)
{
    FrameHashEntry *entry = LookupFrame(address);
    if (entry == 0)
        entry = AddFrameEntry(address, 4, (const char *)address, 0);
    if (entry->status == 0)
        ((Rva0088A7E0Debug *)this)->UpdateFrameStatus(*(Rva0088A7E0FrameHashEntry *)entry);
    return entry->status == 2 || entry->status == 3;
}
