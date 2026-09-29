// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);

struct BfmeCsDWA;
extern BfmeCsDWA g_bfmeCsDWC;

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

    bool frameStatus(unsigned address, bool reset);

private:
    int m_prefix[6];
    FrameHashEntry *m_frameHash[10007];
    char m_tail[0x184];
    int m_fastPath;

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

bool Debug::frameStatus(unsigned address, bool reset)
{
    if (m_fastPath != 0)
        return true;

    EnterCriticalSection(&g_bfmeCsDWC);
    m_prefix[5] = address;
    FrameHashEntry *entry = LookupFrame(address);
    if (reset)
    {
        if (entry != 0)
            entry->status = 0;
        LeaveCriticalSection(&g_bfmeCsDWC);
        return false;
    }
    if (entry == 0)
    {
        LeaveCriticalSection(&g_bfmeCsDWC);
        return false;
    }
    if (entry->status == 2 || entry->status == 3)
    {
        LeaveCriticalSection(&g_bfmeCsDWC);
        return false;
    }
    if (entry->status == 0)
        UpdateFrameStatus(*entry);
    LeaveCriticalSection(&g_bfmeCsDWC);
    return entry->status == 1;
}
