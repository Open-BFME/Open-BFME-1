// Retail RVA 0x00419A10, 747 bytes. The Zero Hour Drawable::~Drawable
// cleanup sequence establishes identity; BFME adds member ownership below.
// The primary base is the existing address-named destructor at 0x001320E0
// (ILT 0x00029596), size 0x60. Snapshot is the secondary base at +0x60.
// Entry vtables: 0x010F1560 and 0x010F154C; Snapshot restores 0x01073744.
// Member destruction order: four Coord3Ds, pointer-sized vector entries,
// two AsciiStrings, reference-counted holder, Snapshot, primary base.
// The event-ID and InterlockedDecrement result locals are significant:
// inlining their expressions into calls/conditions changes MSVC 7.1 bytes.
// cl: /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"
#include "coord3d.h"
#include "snapshot.h"
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *);

class Gen_dtor_00132940
{
  public:
    virtual ~Gen_dtor_00132940();
    char m_04[0x5c];
};

class Owned00419A10
{
  public:
    virtual ~Owned00419A10();
};

class Audio00419A10 : public Owned00419A10
{
  public:
    char m_04[12];
    unsigned m_10;
};

class RefTarget00419A10
{
  public:
    virtual ~RefTarget00419A10();
    long m_04;
    void release()
    {
        long count = InterlockedDecrement(&m_04);
        if (count <= 0)
            delete this;
    }
};

class RefHolder00419A10
{
  public:
    RefTarget00419A10 *p;
    ~RefHolder00419A10()
    {
        if (p)
            p->release();
    }
    void reset()
    {
        if (p)
        {
            p->release();
            p = 0;
        }
    }
};

class DisplayStringManager
{
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void freeDisplayString(void *);
};
extern DisplayStringManager *TheDisplayStringManager;

class AudioManager
{
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void removeAudioEvent(unsigned);
};
extern AudioManager *TheAudio;

class Drawable;

class GameClient
{
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void removeFromRayEffects(Drawable *);
};
extern GameClient *TheGameClient;

class Drawable : public Gen_dtor_00132940, public Snapshot
{
  public:
    virtual ~Drawable();

    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &);

    Owned00419A10 *m_64;
    Owned00419A10 *m_colorTintEnvelope;

    char m_6c[0x8c - 0x6c];
    Owned00419A10 *m_8c;

    char m_90[0xfc - 0x90];
    void *m_object;
    unsigned m_id;
    Drawable *m_nextDrawable;
    Drawable *m_prevDrawable;

    RefHolder00419A10 m_10c;
    unsigned m_status;

    char m_114[0x138 - 0x114];
    Owned00419A10 *m_locoInfo;
    char m_13c[8];

    Audio00419A10 *m_ambientSound;
    Audio00419A10 *m_148;
    Audio00419A10 *m_14c;

    Owned00419A10 **m_modules[3];
    char m_15c[0x2cc - 0x15c];

    void *m_2cc;
    void *m_captionDisplayString;
    AsciiString m_2d4;
    AsciiString m_2d8;
    char m_2dc[4];

    Owned00419A10 *m_2e0;
    char m_2e4[0x2f8 - 0x2e4];
    std::vector<unsigned> m_2f8;

    char m_304[0x37c - 0x304];
    Coord3D m_37c[4];
    char m_3ac[0x10];
    Owned00419A10 *m_3bc;

    void stop()
    {
        if (m_ambientSound)
        {
            unsigned event = m_ambientSound->m_10;
            TheAudio->removeAudioEvent(event);
        }
        if (m_148)
        {
            unsigned event = m_148->m_10;
            TheAudio->removeAudioEvent(event);
        }
    }
};

Drawable::~Drawable()
{
    if (m_2cc)
    {
        TheDisplayStringManager->freeDisplayString(m_2cc);
        m_2cc = 0;
    }
    if (m_captionDisplayString)
    {
        TheDisplayStringManager->freeDisplayString(m_captionDisplayString);
        m_captionDisplayString = 0;
    }
    for (int i = 0; i < 3; ++i)
    {
        for (Owned00419A10 **m = m_modules[i]; m && *m; ++m)
        {
            delete *m;
            *m = 0;
        }
        delete[] m_modules[i];
        m_modules[i] = 0;
    }
    stop();
    delete m_ambientSound;
    m_ambientSound = 0;
    delete m_148;
    m_148 = 0;

    if (m_14c)
    {
        unsigned event = m_14c->m_10;
        TheAudio->removeAudioEvent(event);
    }
    delete m_14c;
    m_14c = 0;

    stop();
    m_10c.reset();
    TheGameClient->removeFromRayEffects(this);
    m_object = 0;

    delete m_2e0;
    m_2e0 = 0;
    delete m_64;
    m_64 = 0;
    delete m_colorTintEnvelope;
    m_colorTintEnvelope = 0;

    delete m_8c;
    m_8c = 0;
    delete m_locoInfo;
    m_locoInfo = 0;
    delete m_3bc;
    m_3bc = 0;
}
