// ?onCollide@AODCrushCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z
// partial score=0.9835 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc /Igame/GameEngine/Source /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB
// stlport
// AODCrushCollide collide-interface receiver is complete-object +0x20.

class Player;
enum ObjectID { INVALID_ID = 0 };
enum DamageType { Rva00215E50DamageTypeZero = 0 };
enum DeathType { DEATH_NORMAL = 0 };
#define BFME_HAVE_OBJECTID
enum Relationship { RELATIONSHIP_NEUTRAL, RELATIONSHIP_ENEMIES, RELATIONSHIP_ALLIES };
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; Relationship getRelationship(const Object *) const; void notifyModelConditionChanged();
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const;
#include "GameLogic/Object/object.h"

struct Rva00215E50ConditionFlags
{
    // ?test@Rva00215E50ConditionFlags@@QBEIH@Z absent-from-retail
    unsigned test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
    // ?set@Rva00215E50ConditionFlags@@QAEXH@Z absent-from-retail
    void set(int bit) { m_bits[bit >> 5] |= (1u << (bit & 31)); }
    unsigned m_bits[10];
};
// ?setCondition@@YAXPAVObject@@H@Z absent-from-retail
static __forceinline void setCondition(Object *object, int bit)
{
    Rva00215E50ConditionFlags *flags = (Rva00215E50ConditionFlags *)object->m_modelConditionFlags;
    if (!flags->test(bit))
    {
        flags->set(bit);
        object->notifyModelConditionChanged();
    }
}

struct Rva00215E50DamageInput
{
    void *m_vptr;
    ObjectID m_sourceID;
    unsigned short m_sourcePlayerMask;
    unsigned char m_padding0a[2];
    DamageType m_damageType;
    int m_value10;
    DeathType m_deathType;
    float m_amount;
    bool m_kill;
    bool m_value1d;
    unsigned char m_padding1e[2];
    float m_delay20;
    unsigned char m_unreconstructed24[0x44 - 0x24];
    unsigned m_bits44;
};
struct Rva00215E50DamageOutput
{
    void *m_vptr;
    float m_actualDamageDealt;
    float m_actualDamageClipped;
    bool m_noEffect;
};
struct BFMEDamageInfo
{
    BFMEDamageInfo();
    void *m_vptr;
    Rva00215E50DamageInput in;
    Rva00215E50DamageOutput out;
};
typedef char DamageInfo_size[sizeof(BFMEDamageInfo) == 0x5c ? 1 : -1];
typedef char DamageInput_size[sizeof(Rva00215E50DamageInput) == 0x48 ? 1 : -1];

class Rva2225E0Filter { public: bool accepts(Object *, Player *); int m_index; };
#include "GameClient/FXListRetail.h"
class BfmeSubBPB;
void bfmeGoBPB(BfmeSubBPB *, void *, void *, void *);
class UpdateModule;
class GameLogic
{
public:
    void j_00009944(Object *, UpdateModule *, unsigned);
    unsigned char m_unmodelled00[0x3c];
    unsigned m_frame;
};
extern GameLogic *TheBfmeGameLogic;

struct Rva00215E50Physics
{
    unsigned char m_unmodelled00[0x5c];
    bool m_flag5c;
};
struct Rva00215E50DamageDispatch
{
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void attemptDamage(BFMEDamageInfo *);
};
struct Rva00215E50HordeDispatch
{
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
    virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
    virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
    virtual void slot64(); virtual void slot65(); virtual void slot66();
    virtual void dispatch(Object *, Object *);
};
struct Rva00215E50Contain
{
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual Rva00215E50HordeDispatch *get26();
};
struct Rva00215E50Data
{
    unsigned char m_unmodelled00[8];
    const FXList *m_fx08;
    BfmeSubBPB *m_ocl0c;
    const FXList *m_fx10;
    BfmeSubBPB *m_ocl14;
    const FXList *m_fx18;
    BfmeSubBPB *m_ocl1c;
    DamageType m_type20;
    DeathType m_death24;
    float m_amount28;
    Rva2225E0Filter m_filter2c;
    DamageType m_type30;
    DeathType m_death34;
    float m_amount38;
    DamageType m_type3c;
    DeathType m_death40;
    float m_amount44;
};
struct Rva00215E50State
{
    void *m_vptr;
    unsigned m_expirationFrame;
    int m_lastObjectID;
    bool m_active;
};

class AODCrushCollide
{
public:
    virtual void onCollide(Object *, const Coord3D *, const Coord3D *);
};

// ?onCollide@AODCrushCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z
void AODCrushCollide::onCollide(Object *other, const Coord3D *loc, const Coord3D *normal)
{
    if (!other)
        return;
    Rva00215E50Physics *physics = (Rva00215E50Physics *)other->m_physics;
    Object *object = *(Object **)((char *)this - 0x18);
    if (physics && physics->m_flag5c)
        return;
    if (object->m_privateStatus & 1)
        return;
    if (object->m_modelConditionFlags[6] & 0x1000)
        return;
    physics = (Rva00215E50Physics *)object->m_physics;
    if (physics && physics->m_flag5c)
        return;
    if (other->getRelationship(object) == RELATIONSHIP_ALLIES)
        return;
    Object *container = object->m_containedBy;
    if (container)
    {
        Rva00215E50Contain *contain = (Rva00215E50Contain *)container->m_contain;
        if (contain)
        {
            Rva00215E50HordeDispatch *horde = contain->get26();
            if (horde)
                horde->dispatch(object, other);
        }
    }
    if (other->m_privateStatus & 1)
        return;
    physics = (Rva00215E50Physics *)other->m_physics;
    if (!physics || physics->m_flag5c)
        return;
    Rva00215E50State *state = (Rva00215E50State *)this;
    if (!state->m_active)
    {
        state->m_active = true;
        setCondition(object, 40);
        TheBfmeGameLogic->j_00009944(object, (UpdateModule *)((char *)this - 0x20), TheBfmeGameLogic->m_frame + 10);
        state->m_expirationFrame = TheBfmeGameLogic->m_frame + 10;
    }
    state->m_expirationFrame = TheBfmeGameLogic->m_frame + 10;
    BFMEDamageInfo damage;
    const Rva00215E50Data *data = *(const Rva00215E50Data **)((char *)this - 0x1c);
    bool special = const_cast<Rva2225E0Filter &>(data->m_filter2c).accepts(other, object->getControllingPlayer());
    if (special)
    {
        damage.in.m_damageType = data->m_type30;
        damage.in.m_deathType = data->m_death34;
        damage.in.m_amount = data->m_amount38;
    }
    else
    {
        damage.in.m_damageType = data->m_type20;
        damage.in.m_deathType = data->m_death24;
        damage.in.m_amount = data->m_amount28;
    }
    damage.in.m_sourceID = object->m_id;
    ((Rva00215E50DamageDispatch *)other)->attemptDamage(&damage);
    state->m_lastObjectID = other->m_id;
    if (special)
    {
        BFMEDamageInfo reflected;
        reflected.in.m_damageType = data->m_type3c;
        reflected.in.m_deathType = data->m_death40;
        reflected.in.m_amount = data->m_amount44;
        reflected.in.m_sourceID = other->m_id;
        ((Rva00215E50DamageDispatch *)object)->attemptDamage(&reflected);
    }
    const FXList *fx;
    BfmeSubBPB *ocl;
    switch (*(signed char *)((char *)other->getTemplate() + 0x495))
    {
    case 0: fx = data->m_fx08; ocl = data->m_ocl0c; break;
    case 1: fx = data->m_fx10; ocl = data->m_ocl14; break;
    default: fx = data->m_fx18; ocl = data->m_ocl1c; break;
    }
    if (fx)
        FXList::doFXObj(fx, other, object);
    if (ocl)
        bfmeGoBPB(ocl, other, object, 0);
}
