// ?update@Rva007E4AD0Vp6Stream@@QAEXXZ [retail body 0x007E4AD0]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva007E3410Target
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void invoke(int first, int second);
};

class Rva007E3410Object
{
public:
    void invokeForMode(void);

private:
    char m_pad0[4];
    Rva007E3410Target *m_target;
    int m_mode;
};

class BfmeDev996
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void bfmeSet996(int value, int enabled);
};

class BfmeB996
{
public:
    char bfmeGo996B(int first, int second, char *stop);
    void bfmeAdvance996(void);

private:
    char m_pad0[4];
    BfmeDev996 *m_dev;
    int m_kind;
};

class Rva007E4AD0Vp6Stream
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void finalize(void);
    void update(void);

private:
    char m_pad0[0x18];
    Rva007E3410Object m_reader;
    char m_pad28[0x20];
    int m_first;
    int m_second;
    unsigned long m_time;
};

void Rva007E4AD0Vp6Stream::update(void)
{
    BfmeB996 *reader = (BfmeB996 *)&m_reader;
    int first;
    int second;
    char stop;

    m_first = -1;
    m_second = -1;
    m_reader.invokeForMode();
    if (reader->bfmeGo996B((int)&first, (int)&second, &stop)) {
        for (;;) {
            if (first == 0x36505641) {
                reader->bfmeAdvance996();
            } else if (first == 0x6468564D) {
                reader->bfmeAdvance996();
                break;
            }
            if (!reader->bfmeGo996B((int)&first, (int)&second, &stop)) {
                break;
            }
        }
    }
    finalize();
    m_time = timeGetTime();
}
