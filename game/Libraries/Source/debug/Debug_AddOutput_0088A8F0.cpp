// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::AddOutput(const char *, unsigned) at 0x0088A8F0 (675 bytes).
// Zero Hour twin: debug_debug.cpp Debug::AddOutput.  Identity: the name came
// with the lift and is corroborated by 15 call sites, four of them matched
// siblings that all declare `void Debug::AddOutput(const char *, unsigned)`.
//
// BFME's Debug is a later revision than the vendored Zero Hour header, so this
// TU carries its own ABI view of the class; the BFME-layout siblings
// Debug_OperatorString_0088C020.cpp and Debug_ExecCommand_0088ABA0.cpp do the
// same.  The retail member accesses witness: seven 16-byte I/O buffer records
// at +0x9C84, curType as the int at +0x9CF4 (Log == 1, MAX == 7; Zero Hour is
// 2/8) and the timestamp flag as the byte at +0x9E6E (Zero Hour +0x9E71).
//
// Relative to the Zero Hour body BFME rewrote the append step: it counts the
// chunk's newlines, grows by (newlines + len + 1024) instead of (len + 1024),
// expands every '\n' into a CR/LF pair and only falls back to memcpy when the
// chunk holds no newline at all.

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

// 0x0088A230, the Debug::FlushOutput(bool) this body reaches through.
struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

// 0x0088EB90, debug_internal.cpp.
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
    IOBuffer ioBuffer[DebugIOInterface::MAX];   // +0x9C84
    DebugIOInterface::StringType curType;       // +0x9CF4
    unsigned char m_beforeTimeStamp[0x176];
    bool timeStamp;                             // +0x9E6E

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

            // scan up to and including the next '\n'
            const char *end=str+remainingLen;
            const char *p=str;
            for (; p!=end; ++p)
                if (*p=='\n')
                {
                    ++p;
                    break;
                }
            len=p-str;
        }
        else
            len=remainingLen;

        // count the newlines in this chunk, each one grows the output by a CR
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
            // expand every '\n' into a CR/LF pair
            const char *src=str;
            char *dest=ioBuffer[curType].buffer+ioBuffer[curType].used;
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
