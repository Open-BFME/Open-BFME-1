// ??1Rva007E3C20Vp6Stream@@UAE@XZ
// partial score=0.93 date=2026-09-04
// ??1Rva007E3C20Vp6Stream@@UAE@XZ present-unmatched
// ?d_007e3c20@@YAXXZ
// partial score=0.93 date=2026-09-03
// ??1Rva007E3C20Vp6Stream@@UAE@XZ [retail body 0x007E3C20]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Gen_0081E480
{
public:
    virtual ~Gen_0081E480(void);
    int m_count; int m_first; int m_second; int m_flags;
};

class Rva007E3C20Parser
{
public:
    ~Rva007E3C20Parser(void);

private:
    int m_word0;
    int m_word1;
    int m_word2;
    int m_word3;
};

class Rva007E3C20Owner
{
public:
    virtual void spare(void);
    virtual void release(int value);
};

class Rva007E3C20AudioClient
{
public:
    virtual void spare00(void); virtual void spare01(void);
    virtual void spare02(void); virtual void spare03(void);
    virtual void spare04(void); virtual void spare05(void);
    virtual void spare06(void); virtual void spare07(void);
    virtual void spare08(void); virtual void spare09(void);
    virtual void spare0A(void); virtual void spare0B(void);
    virtual void spare0C(void); virtual void spare0D(void);
    virtual void spare0E(void); virtual void spare0F(void);
    virtual void spare10(void); virtual void spare11(void);
    virtual void spare12(void); virtual void release(int value);
};

extern Rva007E3C20AudioClient *g_rva007E3C20AudioClient;
extern int __cdecl rva007E3C20Release(void **value);
void operator delete[](void *value);

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
    virtual ~Rva007E3C20Vp6Stream(void);

private:
    void *m_at14;
    void *m_at18;
    Rva007E3C20Parser m_parser;
    Rva007E3C20Owner *m_at2c;
    int m_at30;
    int m_at34;
    unsigned char m_at38;
    int m_at3c;
    int m_at40;
    int m_at44;
    int m_at48;
    int m_at4c;
    int m_at50;
    char *m_at54;
    int m_at58;
    int m_at5c;
    int m_at60;
};

Rva007E3C20Vp6Stream::~Rva007E3C20Vp6Stream(void)
{
    if (m_at14 != 0) {
        rva007E3C20Release(&m_at14);
        m_at14 = 0;
    }
    if (m_at18 != 0) {
        rva007E3C20Release(&m_at18);
        m_at18 = 0;
    }
    if (m_at2c != 0) {
        m_at2c->release(1);
        m_at2c = 0;
    }
    char *at54 = m_at54;
    if (at54 != 0) {
        _ReadWriteBarrier();
        if (at54 != 0)
            operator delete[](at54);
        m_at54 = 0;
    }
    m_at54 = 0;
    if (m_at5c != 1)
        g_rva007E3C20AudioClient->release(m_at5c);
    if (m_at60 != 1)
        g_rva007E3C20AudioClient->release(m_at60);
}
