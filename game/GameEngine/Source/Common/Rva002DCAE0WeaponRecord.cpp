// cl: /O2 /Ob0

// Slot 5 of the 12-entry weapon-record vtable installed by
// Rva002DCBA0's matched constructor.  The retail code accepts an
// address-like record and a Thing, looks up the record's object id, and
// lets the resolved module handle the Thing when the record flags allow it.
// The address-derived names below intentionally avoid claiming a stronger
// semantic identity than the vtable and call evidence establish.

enum KindOfType
{
    // Retail pushes 0x8d; the compact BFME KindOf shim has no recovered
    // semantic name for this value, so keep the exact value explicit.
    RvaKindOfTypeRetail8D = 0x8d
};

typedef unsigned int ObjectID;

struct Coord3D
{
    float x;
    float y;
    float z;
};

struct BFMEDamageInfoInput
{
    unsigned char m_unreconstructed00[8];
    ObjectID m_sourceID;
    unsigned short m_sourcePlayerMask;
    unsigned char m_unreconstructed0e[0x24 - 0x0e];
};

struct BFMEDamageInfo
{
    BFMEDamageInfo();

    BFMEDamageInfoInput in;
    float m_distance24;
    unsigned char m_unreconstructed28[4];
    ObjectID m_sourceObjectID2c;
    Coord3D m_delta30;
    int m_unreconstructed3c;
    int m_unreconstructed40;
    int m_unreconstructed44;
    int m_unreconstructed48;
    unsigned char m_unreconstructed4c[0x5c - 0x4c];
};

class Player
{
public:
    unsigned char m_unreconstructed00[0x24];
    int m_playerIndex;
};

extern "C" float fabs(float value);
extern "C" float sqrt(float value);
#pragma intrinsic(fabs, sqrt)

extern const float BfmeZeroRange;
extern const float Rva0109BF40ZeroRange;

class Thing
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void attemptDamage(BFMEDamageInfo *damageInfo) = 0;

    bool isKindOf(KindOfType kind) const;

    unsigned char m_gap04[0x38 - 4];
    Coord3D m_cachedPos;
    unsigned char m_gap44[0x98 - 0x44];
    unsigned char m_flags98;
};

class Rva002DCAE0Module;

class Object
{
public:
    virtual void slot00() = 0;
    Player *getControllingPlayer() const;

    unsigned char m_gap04[0x38 - 4];
    float m_unreconstructed38;
    float m_unreconstructed3c;
    float m_unreconstructed40;
    unsigned char m_gap44[0x74 - 0x44];
    ObjectID m_id;
    unsigned char m_gap78[0x1fc - 0x78];
    class Rva002DCAE0Module *m_contain;
};

class Rva002DCAE0Module
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual bool slot33(Thing *thing, int mode) = 0;
    virtual void slot34(Thing *thing) = 0;
};

class GameLogic
{
public:
    Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;

// Constructor 0x002DF2B0 builds the 0x58-byte base at offset zero. The
// Rva002DCBA0 constructor then installs retail's 12-slot table at 0x010CECA4;
// that table routes slot 5 through ILT 0x000031E3 to this TU's 0x002DCAE0
// body. The address-derived declarations preserve that witnessed layout
// without assigning a semantic class identity.
class Made002DF2B0
{
public:
    Made002DF2B0();
    virtual void slot00() = 0;

private:
    unsigned char m_gap04[0x54];
};

class Rva002DCBA0 : public Made002DF2B0
{
public:
    Rva002DCBA0();

    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void rva002DCAE0Slot5(void *record, Thing *thing);
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;

    unsigned char m_flag58;
    unsigned char m_flag59;
    int m_value5C;
    int m_value60;
    int m_value64;
    union
    {
        int m_value68Bits;
        float m_value68;
    };
    union
    {
        float m_value6C;
        int m_value6CBits;
    };

    void rva002DC8B0Apply(Object *found, Thing *thing);
};

extern void j_000229fd(void);

class Rva002DC8B0Call
{
public:
    void apply(Object *found, Thing *thing);
};

Rva002DCBA0::Rva002DCBA0()
{
    m_flag59 = 0;
    m_value5C = 0;
    m_value60 = 0;
    m_value64 = 0;
    m_value68 = 0;
    m_flag58 = 1;
    m_value6C = 1.0f;
}

void Rva002DCBA0::rva002DC8B0Apply(Object *found, Thing *thing)
{
    register Rva002DCBA0 *owner = this;
    register Object *source = found;
    register Thing *victim = thing;
    Coord3D delta;
    BFMEDamageInfo damageInfo;

    delta.x = victim->m_cachedPos.x;
    delta.y = victim->m_cachedPos.y;
    damageInfo.m_unreconstructed3c = owner->m_value5C;
    delta.z = victim->m_cachedPos.z;
    delta.x -= source->m_unreconstructed38;
    delta.y -= source->m_unreconstructed3c;
    delta.z -= source->m_unreconstructed40;

    if (fabs(delta.x) < Rva0109BF40ZeroRange &&
        fabs(delta.y) < Rva0109BF40ZeroRange &&
        fabs(delta.z) < Rva0109BF40ZeroRange)
        delta.z = 1.0f;

    damageInfo.m_delta30 = delta;
    damageInfo.m_unreconstructed40 = owner->m_value60;
    damageInfo.m_unreconstructed44 = owner->m_value64;
    damageInfo.m_unreconstructed48 = owner->m_value6CBits;

    if (owner->m_value68 > BfmeZeroRange)
    {
        damageInfo.m_distance24 =
            sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x) /
            owner->m_value68;
    }

    damageInfo.m_sourceObjectID2c = source->m_id;
    Player *player = source->getControllingPlayer();
    if (player != 0)
    {
        player = source->getControllingPlayer();
        damageInfo.in.m_sourcePlayerMask =
            (unsigned short)(1 << player->m_playerIndex);
    }

    damageInfo.in.m_sourceID = source->m_id;
    player = source->getControllingPlayer();
    damageInfo.in.m_sourcePlayerMask =
        (unsigned short)(1 << player->m_playerIndex);
    victim->attemptDamage(&damageInfo);
}

void Rva002DCBA0::rva002DCAE0Slot5(void *record, Thing *thing)
{
    if (record == 0)
        return;

    Thing *thingForRecord;
    Object *found;

    found = TheBfmeGameLogic->findObjectByID(
        *(int *)((unsigned char *)record + 8));

    if (found == 0)
        return;

    thingForRecord = thing;
    if (thingForRecord == 0)
        return;

    if (!thingForRecord->isKindOf(RvaKindOfTypeRetail8D) &&
        (thingForRecord->m_flags98 & 4) == 0)
        return;

    Rva002DCAE0Module *module = found->m_contain;
    if (m_flag58 && module != 0 && module->slot33(thingForRecord, 1))
    {
        module->slot34(thingForRecord);
        return;
    }

    if (m_flag59)
    {
        typedef void (Rva002DC8B0Call::*Function)(Object *, Thing *);
        union
        {
            void (*raw)(void);
            Function member;
        } fn;
        fn.raw = j_000229fd;
        (reinterpret_cast<Rva002DC8B0Call *>(this)->*fn.member)(found,
            thingForRecord);
    }
}
