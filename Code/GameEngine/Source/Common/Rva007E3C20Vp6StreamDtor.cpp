// ??1Rva007E3C20Vp6Stream@@UAE@XZ
// Open-BFME5: derived stream destructor, retail 0x007E3C20, 217 bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Base is the Gen_0081E480 class (ctor 0x0081E480); its destructor body at
// 0x0081E4B0 stores the same vtable 0x0112D210 and runs last here at EH state
// -1, which is why it is spelled as the base destructor and not as a tail call.
// Callees: bfmeFreeCodecJW on +0x14/+0x18, the +0x2C owner's vslot 1 release,
// operator delete[] on +0x54, TheAudio vslot 0x4C release on +0x5C/+0x60, and
// the Rva007E3450 member destructor on +0x1C.
//
// Shape lever: retail tests +0x54 twice (outer je skips both zero stores,
// inner je skips only the delete[] and the first store). A by-reference
// __forceinline SAFE_DELETE_ARRAY helper inside an outer `if` reproduces it;
// a raw nested if, a local copy, or a barrier all fold the inner test.

class Gen_0081E480
{
public:
    virtual ~Gen_0081E480(void);
    int m_count; int m_first; int m_second; int m_flags;
};

// real, already-matched member dtor for the parser-shaped slot (Rva007E3450Destructor.cpp)
class Rva007E3450
{
public:
    ~Rva007E3450(void);

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

// TheAudio -- real pinned global "?TheAudio@@3PAVAudioManager@@A" at 0x012ED668.
// Only the slot we call (vslot 0x4c) needs a real signature; earlier slots are spares.
class AudioManager
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

extern AudioManager *TheAudio;

// real, already-matched codec-state release (BfmeConv2080.cpp)
struct CodecState;
int bfmeFreeCodecJW(CodecState **p);

void operator delete[](void *value);

static __forceinline void rva007E3C20SafeDeleteArray(char *&p)
{
    if (p != 0) {
        delete[] p;
        p = 0;
    }
}

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
    virtual ~Rva007E3C20Vp6Stream(void);

private:
    void *m_at14;
    void *m_at18;
    Rva007E3450 m_parser;
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
        bfmeFreeCodecJW((CodecState **)&m_at14);
        m_at14 = 0;
    }
    if (m_at18 != 0) {
        bfmeFreeCodecJW((CodecState **)&m_at18);
        m_at18 = 0;
    }
    if (m_at2c != 0) {
        m_at2c->release(1);
        m_at2c = 0;
    }
    if (m_at54 != 0) {
        rva007E3C20SafeDeleteArray(m_at54);
        m_at54 = 0;
    }
    if (m_at5c != 1)
        TheAudio->release(m_at5c);
    if (m_at60 != 1)
        TheAudio->release(m_at60);
}
