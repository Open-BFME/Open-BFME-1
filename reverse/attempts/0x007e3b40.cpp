// ?d_007e3b40@@YAXXZ
// partial score=0.9 date=2026-09-03
// ??0Rva007E3B40Vp6TailStream@@QAE@HH@Z [retail body 0x007E3B40]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Gen_0081E480
{
public:
    Gen_0081E480(int first, int second);
    ~Gen_0081E480(void);
    int *m_vtable; int m_count; int m_first; int m_second; int m_flags;
};

class Rva007E3430Ops
{
public:
    Rva007E3430Ops *zero(void);
};

class Rva007E3B40Vp6Prefix
{
public:
    Rva007E3B40Vp6Prefix(int first, int second) : m_base(first, second) {}
protected:
    Gen_0081E480 m_base;
    int m_at14;
    int m_at18;
};

class Rva007E3B40Vp6TailStream : public Rva007E3B40Vp6Prefix
{
public:
    Rva007E3B40Vp6TailStream(int first, int second);

private:
    void setTail(void);
    char m_parser[16];
    volatile int m_at2c; volatile int m_at30; volatile int m_at34;
    volatile unsigned char m_at38; volatile int m_at3c; volatile int m_at40;
    volatile int m_at44; volatile int m_at48; volatile int m_at4c;
    volatile int m_at50; volatile int m_at54; volatile int m_at58;
    volatile int m_at5c; volatile int m_at60;
};

void Rva007E3B40Vp6TailStream::setTail(void)
{
    m_at44 = 1;
    m_at5c = 1;
    m_at60 = 1;
    m_at2c = 0;
    m_at30 = 0;
    m_at34 = 0;
    m_at38 = 0;
    m_at3c = 0;
    m_at40 = 0;
    int negative = -1;
    m_at4c = m_at48 = negative;
    m_at50 = 0;
    m_at54 = 0;
    m_at58 = 0;
}

Rva007E3B40Vp6TailStream::Rva007E3B40Vp6TailStream(int first, int second)
    : Rva007E3B40Vp6Prefix(first, second)
{
    m_base.m_vtable = (int *)0x01128DA8;
    m_at14 = 0;
    m_at18 = 0;
    ((Rva007E3430Ops *)m_parser)->zero();
    setTail();
}
