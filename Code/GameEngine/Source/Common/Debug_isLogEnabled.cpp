// cl: /DNDEBUG /MD /EHs-c- /Oy-

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
        UpdateFrameStatus(*entry);
    return entry->status == 2 || entry->status == 3;
}
