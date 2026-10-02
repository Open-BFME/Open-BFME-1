// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x006176A0 (700 B, ret 0xC). All four matched callers link this body as
// ?registerItem@BfmeSinkAM@@QAEXHPAVGen_003BEA30@@H@Z through ILT 0x0001DF02
// (Gen_003BEBA0Add, Load003C4160, LivingWorldRegionManager_Rva003C9CB0,
// RegionTransfer003C9EF0), so that caller-decided placeholder name is kept.
// `this` is the LivingWorld manager singleton g_bfmeSinkAM (0x012F706C): the
// body calls BfmeLivingWorldManager::rva00616240 on it, and its +0x210 item
// table is the hash_map<int, BfmeItemAM *> the landed bfmeDrop (0x00617A10)
// erases from.
// Behaviour: build "BattleMarker%04d" (rva0060E7F0), skip a handle already in
// the table, else construct the 0xA0-byte marker (ctor 0x0061DA30, AsciiString
// by value), hand it one of two model strings, place its render object at the
// caller's x/y with height from g_bfmeStateDF plus this+0xBC, insert it, report
// it to rva00616240 and play the +0xF4 sound if one is set.
// Shape: single-exit form (an early return adds a name destructor reference and
// rotates the frame); render-object reads through an inline accessor; the
// position argument is the in-place BfmeCoordESM (see bfme_run_esm_00609da0.md).
// Member and slot names are offset/slot names: nothing here is witnessed.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "ascii_string.h"

extern "C" AsciiString rva0060E7F0(int marker);

struct Coord2D { float x; float y; };

class Vector3
{
public:
    Vector3() {}
    Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
    float X, Y, Z;
};

class Matrix3D
{
public:
    explicit Matrix3D(bool init)
    {
        if (init)
        {
            Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
            Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
            Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
        }
    }
    void Set_Translation(const Vector3 &t) { Row[0][3] = t.X; Row[1][3] = t.Y; Row[2][3] = t.Z; }
    float Row[3][4];
};

class RenderObjClass
{
public:
    virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
    virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
    virtual void vslot08(); virtual void vslot09(); virtual void vslot0A(); virtual void vslot0B();
    virtual void vslot0C(); virtual void vslot0D(); virtual void vslot0E(); virtual void vslot0F();
    virtual void vslot10(); virtual void vslot11(); virtual void vslot12(); virtual void vslot13();
    virtual void vslot14();
    virtual void vslot15(const Matrix3D &transform);
};
void Rva00739B30(RenderObjClass *robj, bool flag);

// Retail 0x00609DA0's position parameter (identity_evidence/bfme_run_esm_00609da0.md).
struct BfmeCoordESM
{
    BfmeCoordESM(float x, float y) { m_x = x; m_y = y; }
    BfmeCoordESM(const BfmeCoordESM &other) throw() { m_x = other.m_x; m_y = other.m_y; }
    float m_x;
    float m_y;
};

class BfmeHostESM
{
public:
    virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
    virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
    virtual void vslot08(); virtual void vslot09();
    virtual void vslot0A(RenderObjClass *robj);
    char bfmeRunESM(BfmeCoordESM pos, float *height);
};
// The client LivingWorld singleton cell at VA 0x012F7048, defined once by
// game/GameEngine/Source/GameClient/LivingWorld.cpp.  The local ESM view
// above keeps the witnessed slots; the cast is byte-neutral.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &name, int extra);
    ~AudioEventRTS();
private:
    unsigned char m_body[0x70];
};

class AudioManager
{
public:
    virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
    virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
    virtual void vslot08(); virtual void vslot09(); virtual void vslot0A(); virtual void vslot0B();
    virtual void vslot0C(); virtual void vslot0D(); virtual void vslot0E(); virtual void vslot0F();
    virtual void vslot10();
    virtual int addAudioEvent(const AudioEventRTS *event);
};
extern AudioManager *TheAudio;

class BfmeItemAM;
class Gen_003BEA30;

class BfmeThingDY
{
public:
    void bfmeSetDY(int a, int b);
};

// The 0xA0-byte marker built here; ctor pinned at ILT 0x0001BD5B -> 0x0061DA30.
class Rva0061DA30Base
{
public:
    Rva0061DA30Base(AsciiString name);
    virtual void vslot00(AsciiString value);

    // +0x08 is what Rva00739B30 and the render-object virtual calls receive.
    RenderObjClass *getRenderObject() const { return m_renderObject; }

    char m_pad04[4];
    RenderObjClass *m_renderObject;
    char m_pad0C[0x1C];
    int m_field28;
    char m_pad2C[0x68];
    Vector3 m_field94;
};

typedef _STL::hash_map<int, BfmeItemAM *> BfmeItemMapAM;

class BfmeLivingWorldManager
{
public:
    void rva00616240(BfmeItemAM *item, int which, int second);
};

class BfmeSinkAM
{
public:
    void registerItem(int handle, Gen_003BEA30 *item, int variant);

private:
    char m_pad00[0xA0];
    AsciiString m_fieldA0;
    AsciiString m_fieldA4;
    char m_padA8[0x14];
    float m_fieldBC;
    char m_padC0[0x34];
    AsciiString m_fieldF4;
    char m_padF8[0x118];
    BfmeItemMapAM m_items;
};

void BfmeSinkAM::registerItem(int handle, Gen_003BEA30 *item, int variant)
{
    AsciiString name = rva0060E7F0(handle);
    if (m_items.find(handle) == m_items.end())
    {
        Rva0061DA30Base *marker = new Rva0061DA30Base(name);
        AsciiString model;
        if (variant == 0)
            model = m_fieldA0;
        else
            model = m_fieldA4;
        marker->vslot00(model);
        Rva00739B30(marker->getRenderObject(), false);
        if (marker->getRenderObject() != 0)
        {
            const Coord2D *pos = (const Coord2D *)item;
            float height;
            Matrix3D transform(true);
            ((BfmeHostESM *)g_rva012F7048LivingWorld)->bfmeRunESM(BfmeCoordESM(pos->x, pos->y), &height);
            transform.Set_Translation(Vector3(pos->x, pos->y, height + m_fieldBC));
            marker->getRenderObject()->vslot15(transform);
            ((BfmeHostESM *)g_rva012F7048LivingWorld)->vslot0A(marker->getRenderObject());
            marker->m_field94 = Vector3(1.0f, 1.0f, 1.0f);
            marker->m_field28 = 1;
            ((BfmeThingDY *)marker)->bfmeSetDY(30, 0);
        }
        m_items[handle] = (BfmeItemAM *)marker;
        ((BfmeLivingWorldManager *)this)->rva00616240((BfmeItemAM *)marker, 2, 0);
        // Retail tests only the +0xF4 string's buffer pointer.
        if (*(void *const *)&m_fieldF4 != 0)
        {
            AudioEventRTS sound(m_fieldF4, 1);
            TheAudio->addAudioEvent(&sound);
        }
    }
}
