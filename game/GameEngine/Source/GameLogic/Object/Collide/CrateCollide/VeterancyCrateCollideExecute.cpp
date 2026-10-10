// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/VeterancyCrateCollide.h"
#include "GameClient/GameText.h"
#include <vector>

struct Rva00218EE0Data
{
    unsigned char m_pad00[0x54];
    unsigned int m_rangeOfEffect;
    bool m_addsOwnerVeterancy;
    bool m_isPilot;
};

__forceinline const Rva00218EE0Data *crateData(const VeterancyCrateCollide *module)
{
    return *(const Rva00218EE0Data *const *)((const char *)module + 4);
}
__forceinline Object *crateObject(const VeterancyCrateCollide *module)
{
    return *(Object *const *)((const char *)module + 8);
}
__forceinline int crateLevels(const VeterancyCrateCollide *module)
{
    const Rva00218EE0Data *data = crateData(module);
    if (!data || !data->m_addsOwnerVeterancy)
        return 1;
    return 0;
}

extern void j_00020824();
extern void j_000102d0();
class Rva00218EE0Calls {};
class ExperienceTracker
{
public:
    Bool gainExpForLevel(Int, Bool, Bool);
};
__forceinline Player *player(Object *object)
{
    typedef Player *(Rva00218EE0Calls::*Call)() const;
    union { void (*fn)(); Call call; } u = { j_00020824 };
    return (((const Rva00218EE0Calls *)object)->*u.call)();
}
__forceinline void feedback(VeterancyCrateCollide *module, Object *object, const UnicodeString &text)
{
    typedef void (Rva00218EE0Calls::*Call)(Object *, const UnicodeString &);
    union { void (*fn)(); Call call; } u = { j_000102d0 };
    (((Rva00218EE0Calls *)module)->*u.call)(object, text);
}

class PartitionFilter
{
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool allow(Object *) = 0;
    virtual int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
    Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
    virtual ~Rva0025ED50ObjectFilter() {}
    virtual bool allow(Object *);
    Object *m_object;
};
class PlayerFilter0028AE90 : public PartitionFilter
{
public:
    PlayerFilter0028AE90(Player *player) : m_player(player) {}
    virtual ~PlayerFilter0028AE90() {}
    virtual bool allow(Object *);
    virtual int getPlayerMask();
    Player *m_player;
};
struct Rva00218EE0Item
{
    Object *m_object;
    float m_distance;
};
struct Rva00218EE0Payload
{
    std::vector<Rva00218EE0Item> m_items;
    Rva00218EE0Item *m_cursor;
    int m_refCount;
};
struct BfmeWideResult
{
    Rva00218EE0Payload *m_value;
    ~BfmeWideResult()
    {
        --m_value->m_refCount;
        if (m_value->m_refCount == 0)
            delete m_value;
    }
    Object *next()
    {
        if (m_value->m_cursor == m_value->m_items.end())
            return 0;
        return (m_value->m_cursor++)->m_object;
    }
};
class BfmeWideForwardC
{
public:
    // RVA 0x009F2960 owns the five raw-word call signature.
    BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};
class PartitionManager;
extern PartitionManager *ThePartitionManager;
class InGameUI;
extern InGameUI *TheInGameUI;
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class Rva00218EE0UI
{
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void addFloatingText(const UnicodeString &, const Coord3D *, Color);
};
class Rva00218EE0Script
{
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void transferObjectName(const AsciiString &, Object *);
};

// ?executeCrateBehavior@VeterancyCrateCollide@@MAE_NPAVObject@@@Z
Bool VeterancyCrateCollide::executeCrateBehavior(Object *other)
{
    const Rva00218EE0Data *md = crateData(this);
    float range = md->m_rangeOfEffect;
    if (range == 0)
    {
        if (other)
        {
            ExperienceTracker *tracker = *(ExperienceTracker **)((char *)other + 0x210);
            if (tracker)
            {
                tracker->gainExpForLevel(crateLevels(this), !md->m_isPilot, false);
                UnicodeString text;
                text.format(TheGameText->fetch("GUI:GainRank"), crateLevels(this));
                feedback(this, other, text);
            }
        }
    }
    else
    {
        BfmeWideResult result = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
            (int)((char *)other + 0x38), *reinterpret_cast<const int*>(&range), 0,
            (int)PlayerFilter0028AE90(player(other)).link(&Rva0025ED50ObjectFilter(other)), 0);
        while (Object *potential = result.next())
        {
            ExperienceTracker *tracker = *(ExperienceTracker **)((char *)potential + 0x210);
            if (!tracker)
                continue;
            tracker->gainExpForLevel(crateLevels(this), !md->m_isPilot, false);
            UnicodeString text;
            text.format(TheGameText->fetch("GUI:GainRank"), crateLevels(this));
            Coord3D pos;
            const Coord3D *ownerPos = (const Coord3D *)((char *)crateObject(this) + 0x38);
            pos.x = ownerPos->x;
            pos.y = ownerPos->y;
            pos.z = ownerPos->z + 10.0f;
            unsigned int color = *(unsigned int *)((char *)player(potential) + 0x1c4) | 0xe6000000;
            ((Rva00218EE0UI *)TheInGameUI)->addFloatingText(text, &pos, color);
        }
    }
    if (md->m_isPilot)
        ((Rva00218EE0Script *)TheScriptEngine)->transferObjectName(
            *(const AsciiString *)((char *)crateObject(this) + 0x84), other);
    return true;
}
