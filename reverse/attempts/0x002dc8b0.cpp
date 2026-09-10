// ?d_002dc8b0@@YAXXZ
// partial score=0.35 date=2026-09-10
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

extern "C" float fabs(float value);
extern "C" float sqrt(float value);
#pragma intrinsic(fabs, sqrt)

struct Coord3D
{
    float x;
    float y;
    float z;
};

struct BFMEDamageInfoInput
{
    unsigned char m_unreconstructed_00[8];
    ObjectID m_sourceID;
    unsigned short m_sourcePlayerMask;
    unsigned char m_unreconstructed_0e[2];
    unsigned short m_damageType;
    unsigned char m_unreconstructed_12[6];
    int m_deathType;
    float m_amount;
    unsigned char m_kill;
};

struct BFMEDamageInfo
{
    BFMEDamageInfo();

    BFMEDamageInfoInput in;
    float m_distance24;
    unsigned char m_unreconstructed_28[4];
    int m_sourceObjectID2c;
    float m_deltaX30;
    float m_deltaY34;
    float m_deltaZ38;
    int m_ownerValue3c;
    int m_ownerValue40;
    int m_ownerValue44;
    int m_ownerValue48;
    unsigned char m_unreconstructed_4c[0x5c - 0x4c];
};

extern const float BfmeZeroRange;
extern const float Rva0109BF40ZeroRange;

class Player
{
public:
    unsigned char m_unreconstructed_00[0x24];
    int m_playerIndex;
};

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
    virtual void rva002DC8B0AttemptDamage(BFMEDamageInfo *damageInfo) = 0;

    bool isKindOf(KindOfType kind) const;

    unsigned char m_gap04[0x38 - 4];
    float m_positionX38;
    float m_positionY3c;
    float m_positionZ40;
    unsigned char m_gap44[0x74 - 0x44];
    ObjectID m_objectID74;
    unsigned char m_gap78[0x98 - 0x78];
    unsigned char m_flags98;
};

class Object
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

    Player *getControllingPlayer() const;

    unsigned char m_gap04[0x38 - 4];
    float m_positionX38;
    float m_positionY3c;
    float m_positionZ40;
    unsigned char m_gap44[0x74 - 0x44];
    ObjectID m_objectID74;
    unsigned char m_gap78[0x1fc - 0x78];
    class Rva002DCAE0Module *m_module;
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

class __declspec(novtable) Rva002DCBA0
{
public:
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

    unsigned char m_gap04[0x54];
    unsigned char m_flag58;
    unsigned char m_flag59;
    int m_value5c;
    int m_value60;
    int m_value64;
    float m_value68;
    int m_value6c;

    void rva002DC8B0Apply(Object *found, Thing *thing);
};

extern void j_000229fd(void);

void Rva002DCBA0::rva002DC8B0Apply(Object *found, Thing *thing)
{
    register Rva002DCBA0 *owner = this;
    register Object *source = found;
    register Thing *victim = thing;
    Coord3D delta;
    BFMEDamageInfo damageInfo;

    delta.x = victim->m_positionX38;
    delta.y = victim->m_positionY3c;
    delta.z = victim->m_positionZ40;
    delta.x -= source->m_positionX38;
    delta.y -= source->m_positionY3c;
    delta.z -= source->m_positionZ40;

    if (fabs(delta.x) < Rva0109BF40ZeroRange &&
        fabs(delta.y) < Rva0109BF40ZeroRange &&
        fabs(delta.z) < Rva0109BF40ZeroRange)
        delta.z = 1.0f;

    damageInfo.m_ownerValue3c = owner->m_value5c;
    damageInfo.m_deltaY34 = delta.y;
    damageInfo.m_ownerValue44 = owner->m_value64;
    damageInfo.m_deltaX30 = delta.x;
    damageInfo.m_ownerValue40 = owner->m_value60;
    damageInfo.m_deltaZ38 = delta.z;
    damageInfo.m_ownerValue48 = owner->m_value6c;
    damageInfo.m_sourceObjectID2c = source->m_objectID74;

    if (owner->m_value68 > BfmeZeroRange)
    {
        damageInfo.m_distance24 =
            sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x) /
            owner->m_value68;
    }

    Player *player = source->getControllingPlayer();
    if (player != 0)
    {
        player = source->getControllingPlayer();
        damageInfo.in.m_sourcePlayerMask =
            (unsigned short)(1 << player->m_playerIndex);
    }

    damageInfo.in.m_sourceID = source->m_objectID74;
    player = source->getControllingPlayer();
    damageInfo.in.m_damageType =
        (unsigned short)(1 << player->m_playerIndex);
    victim->rva002DC8B0AttemptDamage(&damageInfo);
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

    Rva002DCAE0Module *module = found->m_module;
    if (m_flag58 && module != 0 && module->slot33(thingForRecord, 1))
    {
        module->slot34(thingForRecord);
        return;
    }

    if (m_flag59)
    {
        typedef void (Rva002DCBA0::*Function)(Object *, Thing *);
        union
        {
            void (*raw)(void);
            Function member;
        } fn;
        fn.raw = j_000229fd;
        (reinterpret_cast<Rva002DCBA0 *>(this)->*fn.member)(found,
            thingForRecord);
    }
}
