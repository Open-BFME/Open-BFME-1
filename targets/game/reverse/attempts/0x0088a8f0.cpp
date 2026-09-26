// ?AddOutput@Debug@@AAEXPBDI@Z
// partial score=0.64 date=2026-09-15
// cl: /DNDEBUG /MD /Oy- /EHsc
// BFME Debug::AddOutput, reconstructed from the retail body at 0x0088A8F0.
//
// This TU deliberately does not include the canonical Debug header.  The
// matched BFME Debug siblings and the retail member accesses prove a forked
// layout here: ioBuffer starts at +0x9C84 (not ZH +0x9C78), curType is at
// +0x9CF4 (not +0x9CF8), BFME's StringType::Log is 1 and MAX is 7 (ZH is 2/8),
// and timeStamp is at +0x9E6E (not +0x9E71).  The opaque bytes are therefore a
// TU-scoped ABI view, not a redefinition of the canonical class.

#include "windows.h"
#include <string.h>

class DebugIOInterface
{
public:
    enum StringType
    {
        Assert = 0,
        Log = 1,
        Check = 2,
        Crash = 3,
        Exception = 4,
        CmdReply = 5,
        StructuredCmdReply = 6,
        MAX = 7
    };
};

struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

void *DebugReAllocMemory(void *, unsigned);

class Debug
{
    struct IOBuffer
    {
        char *buffer;
        unsigned used;
        unsigned alloc;
        bool lastWasCR;
    };

    unsigned char m_beforeIOBuffer[0x9C84];
    IOBuffer ioBuffer[DebugIOInterface::MAX];
    DebugIOInterface::StringType curType;
    unsigned char m_beforeTimeStamp[0x176];
    bool timeStamp;

    void AddOutput(const char *, unsigned);
};

// ?AddOutput@Debug@@AAEXPBDI@Z
void Debug::AddOutput(const char *str, unsigned remainingLen)
{
    if (curType==DebugIOInterface::MAX)
        return;

    while (remainingLen)
    {
        unsigned len;
        if (timeStamp)
        {
            if (ioBuffer[curType].lastWasCR)
            {
                SYSTEMTIME systime;
                GetLocalTime(&systime);

                char ts[40];
                wsprintf(ts,"[%02i:%02i.%02i.%03i] ",systime.wHour,
                         systime.wMinute,systime.wSecond,
                         systime.wMilliseconds);

                unsigned tsLen=strlen(ts);
                memcpy(ioBuffer[curType].buffer+ioBuffer[curType].used,
                       ts,tsLen+1);
                ioBuffer[curType].used+=tsLen;
            }

            const char *end=str+remainingLen;
            const char *p=str;
            while (p!=end)
            {
                if (*p++=='\n')
                    break;
            }
            len=p-str;
        }
        else
            len=remainingLen;
        unsigned newlines=0;
        for (unsigned k=0;k<len;k++)
            if (str[k]=='\n')
                ++newlines;

        if (ioBuffer[curType].used+len+newlines+64>=ioBuffer[curType].alloc)
        {
            ioBuffer[curType].alloc+=len+newlines+1024;
            ioBuffer[curType].buffer=(char *)DebugReAllocMemory(
                ioBuffer[curType].buffer,ioBuffer[curType].alloc);
        }

        if (newlines)
        {
            char *dest=ioBuffer[curType].buffer+ioBuffer[curType].used;
            const char *src=str;
            for (unsigned count=0;count<len;++count)
            {
                *dest++=*src++;
                if (dest[-1]=='\n')
                {
                    dest[-1]='\r';
                    *dest++='\n';
                }
            }
            *dest=0;
            ioBuffer[curType].used+=len+newlines;
        }
        else
        {
            memcpy(ioBuffer[curType].buffer+ioBuffer[curType].used,
                   str,len+1);
            ioBuffer[curType].used+=len;
        }

        ioBuffer[curType].lastWasCR=str[len-1]=='\n';
        str+=len;
        remainingLen-=len;

        if (curType==DebugIOInterface::Log&&ioBuffer[curType].lastWasCR)
        {
            ((BfmeThingQO *)this)->bfmeFlushQO(1);
            curType=DebugIOInterface::Log;
        }
    }
}
