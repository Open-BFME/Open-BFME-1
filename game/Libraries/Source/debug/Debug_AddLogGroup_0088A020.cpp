// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::AddLogGroup, with the BFME list head at +0x9C80.

#include <string.h>

extern "C" __declspec(dllimport) char * __cdecl strrchr(const char *, int);
extern "C" __declspec(dllimport) char * __cdecl _strlwr(char *);

extern void *DebugAllocMemory(unsigned);

class Debug
{
    struct KnownLogGroupList
    {
        KnownLogGroupList *next;
        char *nameGroup;
        char *descr;
    };

    unsigned char m_pad[0x9C80];
    KnownLogGroupList *firstLogGroup;

    const char *AddLogGroup(const char *, const char *);
};

// ?AddLogGroup@Debug@@AAEPBDPBD0@Z
const char *Debug::AddLogGroup(const char *fileOrGroup, const char *descr)
{
    char help[200];

    const char *source=fileOrGroup;
    const char *p=strrchr(source,'\\');
    if (!p)
        p=strrchr(source,'/');
    const char *q=strchr(p?p:source,'.');
    if (p||q)
    {
        p=p?p+1:source;
        if (!q)
            q=p+strlen(p);
        if (q-p>=sizeof(help))
            q=p+sizeof(help)-1;
        memcpy(help,p,q-p);
        help[q-p]=0;
    }
    else
        strcpy(help,source);
    _strlwr(help);

    KnownLogGroupList *cur;
    for (cur=firstLogGroup;cur;cur=cur->next)
    {
        if (!strcmp(cur->nameGroup,help))
            return cur->nameGroup;
    }

    cur=(KnownLogGroupList *)DebugAllocMemory(sizeof(KnownLogGroupList));
    cur->next=firstLogGroup;
    cur->nameGroup=(char *)DebugAllocMemory(strlen(help)+1);
    strcpy(cur->nameGroup,help);
    if (descr)
    {
        cur->descr=(char *)DebugAllocMemory(strlen(descr)+1);
        strcpy(cur->descr,descr);
    }
    else
        cur->descr=0;
    firstLogGroup=cur;
    return cur->nameGroup;
}
