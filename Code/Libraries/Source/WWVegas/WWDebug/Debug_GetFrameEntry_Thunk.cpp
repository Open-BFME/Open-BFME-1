// cl: /DNDEBUG /MD /EHsc
// Upstream body and layout:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
private:
    enum FrameStatus
    {
        Unknown,
        Skip,
        NoSkip
    };

    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
    struct FrameHashEntry
    {
        FrameHashEntry *next;
        unsigned int frameAddr;
        unsigned int frameType;
        const char *fileOrGroup;
        int line;
        int hits;
        FrameStatus status;
    };

    enum { FRAME_HASH_SIZE = 10007 };

    char m_prefix[0x18];
    FrameHashEntry *frameHash[FRAME_HASH_SIZE];

    FrameHashEntry *AddFrameEntry(unsigned int addr, unsigned int type,
        const char *fileOrGroup, int line);
    void UpdateFrameStatus(FrameHashEntry &entry);

    __forceinline FrameHashEntry *LookupFrame(unsigned int addr)
    {
        for (FrameHashEntry *entry = frameHash[addr % FRAME_HASH_SIZE]; entry;
             entry = entry->next)
        {
            if (entry->frameAddr == addr)
                return entry;
        }
        return 0;
    }

    FrameHashEntry *GetFrameEntry(unsigned int addr, unsigned int type,
        const char *fileOrGroup, int line);
};

// ?GetFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z
Debug::FrameHashEntry *Debug::GetFrameEntry(unsigned int addr, unsigned int type,
    const char *fileOrGroup, int line)
{
    FrameHashEntry *entry = LookupFrame(addr);
    if (!entry)
        entry = AddFrameEntry(addr, type, fileOrGroup, line);
    if (entry->status == Unknown)
        UpdateFrameStatus(*entry);
    return entry;
}
