// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug

#include "_pch.h"
#include <string.h>

struct Rva0088A7E0FrameHashEntry
{
    char m_prefix[8];
    unsigned frameType;
    const char *fileOrGroup;
    int line;
    char m_between[4];
    unsigned status;
};

struct Rva0088A7E0PatternListEntry
{
    Rva0088A7E0PatternListEntry *next;
    unsigned frameTypes;
    bool isActive;
    char m_flags[3];
    const char *pattern;
};

class Rva0088A7E0Debug
{
public:
    void UpdateFrameStatus(Rva0088A7E0FrameHashEntry &entry);

private:
    char m_prefix[0x9e00];
    Rva0088A7E0PatternListEntry *firstPatternEntry;
};

// ?UpdateFrameStatus@Rva0088A7E0Debug@@QAEXAAURva0088A7E0FrameHashEntry@@@Z
void Rva0088A7E0Debug::UpdateFrameStatus(
    Rva0088A7E0FrameHashEntry &entry)
{
    char help[512];
    if (entry.frameType == 1 || entry.frameType == 2)
        wsprintf(help, "%s(%i)", entry.fileOrGroup, entry.line);
    else
        strcpy(help, entry.fileOrGroup);

    unsigned frameType = entry.frameType;
    bool active = frameType != 4;
    for (Rva0088A7E0PatternListEntry *cur = firstPatternEntry;
         cur; cur = cur->next)
    {
        if (!(cur->frameTypes & frameType))
            continue;
        if (Debug::SimpleMatch(help, cur->pattern))
            active = cur->isActive;
    }

    if (entry.status)
    {
        if ((entry.status == 1) != active)
            return;
    }
    entry.status = active ? 2 : 1;
}
