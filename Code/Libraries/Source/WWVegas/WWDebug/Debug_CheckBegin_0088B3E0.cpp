// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::CheckBegin.  The slot uses the BFME member ABI, but its report
// stream is the shared Debug object at 0x01336E5C.

extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeFormatA(
    unsigned long, unsigned long, const void *, const char *, char *, int);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *, const char *);

struct BfmeThingQO
{
    void bfmeFlushQO(int);
};

void bfmeLogQO(BfmeThingQO *, int, const char *, ...);

class Debug
{
public:
    class RepeatChar
    {
        char m_char;
        int m_count;

    public:
        RepeatChar(char ch, int count): m_char(ch), m_count(count) {}
    };

    virtual ~Debug(void);
    virtual void pad01(void);
    virtual void pad02(void);
    virtual void pad03(void);
    virtual void pad04(void);
    virtual void pad05(void);
    virtual void pad06(void);
    virtual void pad07(void);
    virtual void pad08(void);
    virtual void pad09(void);
    virtual void pad10(void);
    virtual void pad11(void);
    virtual void pad12(void);
    virtual Debug &operator<<(const RepeatChar &);
    virtual Debug &operator<<(const char *);
    virtual Debug &operator<<(int);
    virtual void pad16(void);
    virtual void pad17(void);
    virtual void pad18(void);
    virtual void pad19(void);
    virtual void StartOutput(const char *, unsigned);

    struct FrameHashEntry
    {
        FrameHashEntry *next;
        unsigned frameAddr;
        unsigned frameType;
        const char *fileOrGroup;
        int line;
        int hits;
        int status;
    };

private:
    unsigned char m_pad04[8];
    void *firstIOFactory;
    unsigned char m_pad10[4];
    unsigned curStackFrame;
    unsigned char m_pad18[0x9CDC];
    int curType;
    char curSource[256];
    int disableAssertsEtc;
    FrameHashEntry *curFrameEntry;

    FrameHashEntry *GetFrameEntry(unsigned, unsigned, const char *, int);

public:
    Debug &CheckBegin(const char *, int, const char *);
};

#define TheDebug (*(Debug **)0x01336E5C)

// ?CheckBegin@Debug@@QAEAAV1@PBDH0@Z
Debug &Debug::CheckBegin(const char *file, int line, const char *expr)
{
    char help[132];

    if (curType!=7)
        ((BfmeThingQO *)this)->bfmeFlushQO(1);

    curFrameEntry=GetFrameEntry(curStackFrame,1,file,line);
    if (curFrameEntry->status==2 || curFrameEntry->status==3 ||
        curFrameEntry->status==0)
    {
        StartOutput((const char *)0x0107301C,10);
        bfmeLogQO((BfmeThingQO *)this,0,(const char *)0x01133164,
                  curFrameEntry->fileOrGroup,curFrameEntry->line);
        ++curFrameEntry->hits;

        const char *p=strstr(file,(const char *)0x0113338C);
        if (p)
            p+=6;
        else
            p=file;

        GetTimeFormatA(0x400,0,0,0,help,0x80);
        Debug *debug=TheDebug;
        help[128]=0;
        (*debug) << (const char *)0x01080294
                 << RepeatChar('=',80)
                 << (const char *)0x01133374
                 << p
                 << (const char *)0x0113336C
                 << line
                 << (const char *)0x01096AB4
                 << help
                 << (const char *)0x0113335C
                 << expr;
    }

    return *TheDebug;
}
