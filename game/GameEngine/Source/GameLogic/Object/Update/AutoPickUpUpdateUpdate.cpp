// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include <vector>

// RVA 00281F40, 1498 bytes. Constructor 00281AB0 installs update-interface
// table 010BB484 at +10; slot zero routes through 00047591 to this body.
// The incoming receiver is that secondary interface (object/data at -8/-C).
// ZH UpdateModuleInterface slot zero and return values 1/3fffffff prove update.
// The old destructor lift mislabeled this update body; the real complete
// destructor is 002818B0 and the deleting destructor is 00281C50.
// See targets/game/reverse/identity_evidence/00281f40-autopickup-update.md.
//
// Native filter lifetimes produce unwind states 0..9 and a 0x80-byte frame.
// The visible noinline mask constructors independently match 000C4B00 (57B)
// and 00251980 (61B). Their non-retaining copies allow temporary slot reuse.
// The indexed health loop retains a byte cursor so its begin pointer is
// reloaded after calls. Initialize that cursor only after the empty check;
// increment the logical index before the byte cursor at the loop tail.

class Object;
class Player;
class SpecialPowerTemplate;
enum SpecialPowerType { PickupPower00281F40 = 0x27, OtherPower00281F40 = 0x41 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };

template<> __declspec(noinline)
BitFlags<192>::BitFlags(BogusInitType, Int idx)
{
    m_bits._Unchecked_set(idx);
}

class PartitionFilter {
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *) = 0;
    virtual Int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};
class Rva001DCBB0Filter : public PartitionFilter {
public:
    Rva001DCBB0Filter(Player *p, Bool match) : m_player(p), m_match(match) {}
    virtual ~Rva001DCBB0Filter() {}
    virtual Bool allow(Object *);
    Player *m_player;
    Bool m_match;
};
class Rva0025ED50RootFilter : public PartitionFilter {
public:
    Rva0025ED50RootFilter() {}
    virtual ~Rva0025ED50RootFilter() {}
    virtual Bool allow(Object *);
};
class PartitionFilterPlayerAffiliation : public PartitionFilter {
public:
    PartitionFilterPlayerAffiliation(Player *p, Int flags, Bool match)
        : m_player(p), m_match(match), m_affiliation(flags) {}
    virtual ~PartitionFilterPlayerAffiliation() {}
    virtual Bool allow(Object *);
    virtual Int getPlayerMask();
    Player *m_player;
    Bool m_match;
    Int m_affiliation;
};
class Rva002DC6D0Filter;
class Rva00265150RJFilter : public PartitionFilter {
public:
    __forceinline Rva00265150RJFilter(const Rva002DC6D0Filter &filter, Player *p, Bool match)
        : m_subobject(&filter), m_player(p), m_match(match) {}
    virtual ~Rva00265150RJFilter() {}
    virtual Bool allow(Object *);
    const Rva002DC6D0Filter *m_subobject;
    Player *m_player;
    Bool m_match;
};
class Rva00260180SelfFilter : public PartitionFilter {
public:
    Rva00260180SelfFilter(Object *p) : m_object(p) {}
    virtual ~Rva00260180SelfFilter() {}
    virtual Bool allow(Object *);
    Object *m_object;
};
class PartitionFilterRelationship : public PartitionFilter {
public:
    PartitionFilterRelationship(Object *p, Int flags, Bool match)
        : m_object(p), m_flags(flags), m_match(match) {}
    virtual ~PartitionFilterRelationship() {}
    virtual Bool allow(Object *);
    virtual Int getPlayerMask();
    Object *m_object;
    Int m_flags;
    Bool m_match;
};
struct VptrZeroBlock24 {
    unsigned int m_dword_00, m_dword_04, m_dword_08;
    unsigned int m_dword_0C, m_dword_10, m_dword_14;
};
class Rva00251980VptrZeroBlockObject : public PartitionFilter {
public:
    __declspec(noinline) Rva00251980VptrZeroBlockObject(const VptrZeroBlock24 &mask)
        : m_block(mask) {}
    virtual ~Rva00251980VptrZeroBlockObject() {}
    virtual Bool allow(Object *);
    VptrZeroBlock24 m_block;
};

class PartitionManager {
public:
    Object *getClosestObject(const Coord3D *, Real, Int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
class TerrainLogic {
public:
    Coord3D *queryPointAt001A62D0(const Coord3D *, Real, Bool, Bool);
};
extern TerrainLogic *TheTerrainLogic;

// Slot-only interfaces retain address labels until their method identity is proven.
class Slot100Receiver00281F40 {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b();
    virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b();
    virtual void s2c(); virtual void s2d(); virtual void s2e(); virtual void s2f();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s3a(); virtual void s3b();
    virtual void s3c(); virtual void s3d(); virtual void s3e(); virtual void s3f();
    virtual Int slot100(Int);
};
class Slot14Receiver00281F40 {
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04();
    virtual Real slot14();
};
class SpecialPowerModuleInterface {
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
    virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s0a(); virtual void s0b();
    virtual void slot30(Object *, UnsignedInt);
    virtual void slot34(const Coord3D *, UnsignedInt);
};
class Object {
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s0a();
    virtual void slot2c(Object *, UnsignedInt);
    Player *getControllingPlayer() const;
    Real getVisionRange() const;
    SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType) const;
    void doSpecialPowerAtObject(const SpecialPowerTemplate *, Object *, UnsignedInt, Bool);
    const Coord3D *position00281F40() const { return (const Coord3D *)((const char *)this+0x38); }
    Object *at214() const { return *(Object **)((char *)this+0x214); }
    Slot100Receiver00281F40 *at1fc() const { return *(Slot100Receiver00281F40 **)((char *)this+0x1fc); }
    Slot14Receiver00281F40 *at200() const { return *(Slot14Receiver00281F40 **)((char *)this+0x200); }
};
class Rva002DC6D0Filter {
public:
    Rva002DC6D0Filter();
    ~Rva002DC6D0Filter();
private:
    unsigned int m_handle;
};
// The existing AutoPickUpUpdate.cpp INI parser proves the handle/percent pair.
struct EatEntry00281F40 {
    Rva002DC6D0Filter filter;
    Real myHealth, targetHealth;
};
typedef char EatEntrySize00281F40[(sizeof(EatEntry00281F40) == 12) ? 1 : -1];
typedef char KindMaskSize00281F40[(sizeof(BitFlags<192>) == 24) ? 1 : -1];
struct AutoPickUpData00281F40 {
    char m_00[8];
    unsigned int m_scanDelay08;
    BitFlags<192> m_mask0c;
    Real m_range24;
    Bool m_flag28;
    char m_29[3];
    Rva002DC6D0Filter m_filter2c;
    std::vector<EatEntry00281F40> m_entries30;
    Bool m_flag3c;
    Bool m_flag3d;
    char m_3e[6];
    Bool m_flag44;
};
class ModuleData;
class PB_DeepBase {
public:
    virtual ~PB_DeepBase();
    const ModuleData *m_moduleData;
    Object *m_object;
};
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public PB_DeepBase, public BehaviorModuleInterface {};
class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; virtual void disabled(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface {
    unsigned int m_storage[3];
};
class AutoPickUpUpdateInterface { public: virtual void anchor(); };
class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface {
public:
    virtual UpdateSleepTime update();
    Bool scanReady00281F40()
    {
        if (getData()->m_flag3d)
            return m_flag28;
        if (m_delay24 == 0) {
            m_delay24 = getData()->m_scanDelay08;
            return true;
        }
        --m_delay24;
        return false;
    }
    const AutoPickUpData00281F40 *getData() const { return (const AutoPickUpData00281F40 *)m_moduleData; }
    unsigned int m_delay24;
    Bool m_flag28;
    Bool m_flag29;
};

UpdateSleepTime AutoPickUpUpdate::update()
{
    Object *object = m_object;
    const AutoPickUpData00281F40 *data = getData();
    if (*(unsigned char *)((char *)object+0x344) & 1)
        return UPDATE_SLEEP_NONE;
    Bool allowed;
    if (!data->m_flag44 && ((*(unsigned int *)((char *)object+0x114) & 0x20)
                    || (*(unsigned int *)((char *)object+0x114) & 0x10000000)))
        allowed = false;
    else
        allowed = true;
    if (!scanReady00281F40()) return UPDATE_SLEEP_NONE;
    if (!allowed) return UPDATE_SLEEP_NONE;
    m_flag28 = false;
    if (data->m_flag3c && object->at214()
        && object->at1fc()->slot100(0) == 1) {
        Coord3D position = *object->position00281F40();
        Object *found = ThePartitionManager->getClosestObject(&position,
            object->getVisionRange(), 0,
            PartitionFilterPlayerAffiliation(object->getControllingPlayer(),4,true).link(
                Rva0025ED50RootFilter().link(&Rva001DCBB0Filter(object->getControllingPlayer(),false))));
        if (found) {
            object->slot2c(found, *(UnsignedInt *)((char *)found+0x74));
            return UPDATE_SLEEP_NONE;
        }
    }
    if (object->at214() && object->at1fc()->slot100(0) == 0) {
        Coord3D position = *object->position00281F40();
        Object *found = ThePartitionManager->getClosestObject(&position,
            getData()->m_range24, 0,
            Rva00251980VptrZeroBlockObject(*(const VptrZeroBlock24 *)&data->m_mask0c).link(
                &Rva00251980VptrZeroBlockObject(*(const VptrZeroBlock24 *)&BitFlags<192>(BitFlags<192>::kInit,0x6b))));
        if (found) {
            SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(PickupPower00281F40);
            if (power) { power->slot30(found,0x2000); return UPDATE_SLEEP_NONE; }
        }
    }
    if (!object->at1fc()) return UPDATE_SLEEP_FOREVER;
    if (object->at1fc()->slot100(0) == 0) {
        UnsignedInt i = 0;
        if (i < data->m_entries30.size()) {
            UnsignedInt entryOffset = 0;
            do {
                const EatEntry00281F40 *entry = (const EatEntry00281F40 *)((const char *)&data->m_entries30[0]+entryOffset);
                if (object->at200()->slot14() <= entry->myHealth) {
                    Object *found = ThePartitionManager->getClosestObject(object->position00281F40(),
                        data->m_range24,0,&Rva00265150RJFilter(entry->filter,object->getControllingPlayer(),true));
                    if (found && found->at200()->slot14() <= entry->targetHealth) {
                        SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(PickupPower00281F40);
                        power->slot30(found,0x4000);
                        return UPDATE_SLEEP_NONE;
                    }
                }
                ++i;
                entryOffset += sizeof(EatEntry00281F40);
            } while (i < data->m_entries30.size());
        }
    }
    if (getData()->m_flag28 && (!object->at1fc() || object->at1fc()->slot100(0) == 0)) {
        Object *found = ThePartitionManager->getClosestObject(object->position00281F40(),
            data->m_range24,0,
            Rva00265150RJFilter(data->m_filter2c,object->getControllingPlayer(),true)
                .link(&PartitionFilterRelationship(object,4,false))->link(&Rva00260180SelfFilter(object)));
        if (found) {
            SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(OtherPower00281F40);
            if (power) object->doSpecialPowerAtObject(power->getSpecialPowerTemplate(),found,2,false);
            return UPDATE_SLEEP_NONE;
        }
    }
    if (object->at1fc()->slot100(0) != 0) return UPDATE_SLEEP_NONE;
    {
        Coord3D position; position = *object->position00281F40();
        if (data->m_mask0c.test(93)) {
            Coord3D *point = TheTerrainLogic->queryPointAt001A62D0(&position,getData()->m_range24,true,true);
            SpecialPowerModuleInterface *power = m_object->findSpecialPowerModuleInterface(PickupPower00281F40);
            if (power && point) {
                Coord3D target = *point;
                power->slot34(&target,0x2000);
                return UPDATE_SLEEP_NONE;
            }
        }
        Object *found = ThePartitionManager->getClosestObject(&position,
            getData()->m_range24,0,&Rva00251980VptrZeroBlockObject(*(const VptrZeroBlock24 *)&data->m_mask0c));
        if (found) {
            SpecialPowerModuleInterface *power = object->findSpecialPowerModuleInterface(PickupPower00281F40);
            if (power) power->slot30(found,0x2000);
        }
    }
    return UPDATE_SLEEP_NONE;
}

