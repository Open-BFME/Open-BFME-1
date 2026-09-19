// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::Update: the polymorphic Debug instance is passed in ECX and
// keeps its I/O factory head at +0x0C.

#include <string.h>

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    virtual int Read(char *, int)=0;
};

extern void *Rva0088EB90(void *, unsigned);

class Debug
{
    struct IOFactoryListEntry
    {
        IOFactoryListEntry *next;
        const char *ioID;
        const char *descr;
        DebugIOInterface *(*factory)(void);
        DebugIOInterface *io;
        char *input;
        unsigned inputUsed;
        unsigned inputAlloc;
    };

    char m_prefix[0x0C];
    IOFactoryListEntry *firstIOFactory;

    void ExecCommand(const char *, const char *);

public:
    void Update(void);
};

// ?Update@Debug@@QAEXXZ
void Debug::Update(void)
{
    for (IOFactoryListEntry *cur=firstIOFactory;cur;cur=cur->next)
    {
        if (!cur->io)
            continue;

        bool hadInput=false;
        for (;;)
        {
            if (cur->inputAlloc-cur->inputUsed<64)
                cur->input=(char *)Rva0088EB90(
                    cur->input,(cur->inputAlloc+=64)+1);
            int numChars=cur->io->Read(cur->input+cur->inputUsed,
                                       cur->inputAlloc-cur->inputUsed);
            if (!numChars)
                break;

            cur->inputUsed+=numChars;
            cur->input[cur->inputUsed]=0;
            hadInput=true;
        }

        if (!hadInput)
            continue;

        for (;;)
        {
            char *p=strchr(cur->input,'\n');
            if (!p)
                break;

            ExecCommand(cur->input,p);
            strcpy(cur->input,p+1);
            cur->inputUsed=strlen(cur->input);
        }
    }
}
