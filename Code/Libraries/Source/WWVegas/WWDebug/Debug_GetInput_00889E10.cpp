// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug input-line helper.  The IO factory list begins at +0x0C.

#include <string.h>

extern void *Rva0088EB90(void *, unsigned);

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    virtual int Read(char *, int)=0;
    virtual bool HasInput(void)=0;
};

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

    unsigned char m_pad[0x0C];
    IOFactoryListEntry *firstIOFactory;

public:
    int GetInput(char *, int, bool *);
};

// ?GetInput@Debug@@QAEHPADHPA_N@Z
int Debug::GetInput(char *buf, int maxchar, bool *hasInput)
{
    for (IOFactoryListEntry *cur=firstIOFactory;cur;cur=cur->next)
    {
        if (!cur->io)
            continue;

        bool gotInput=false;
        if (!cur->io->HasInput())
            continue;

        *hasInput=true;
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
            gotInput=true;
        }

        if (!gotInput)
            continue;

        *hasInput=true;
        char *p=strchr(cur->input,'\n');
        if (!p)
            continue;

        int numChars=p-cur->input;
        if (numChars>maxchar-1)
            numChars=maxchar-1;
        strncpy(buf,cur->input,numChars);
        buf[numChars]=0;
        strcpy(cur->input,p+1);
        cur->inputUsed=strlen(cur->input);
        return numChars;
    }

    return 0;
}
