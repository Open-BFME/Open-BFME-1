// cl: /DNDEBUG /MD
// Retail 0x001E6930 / 597 bytes. Weapon::isGoalPosWithinAttackRange is
// identified by the matched isWithinAttackRange wrappers at 001E88F0/001E8930
// and the Pathfinder callers. See docs/analysis/0x003e8e10.md, section 1c.
// Five stack arguments and ret 0x14; slot five is squared with FLD/FMUL at
// +1E5/+1E9, so the actual parameter is float despite the old Int alias pin.
// Weapon+04 agrees with Weapon_getAttackRangeHeightAdjusted.cpp. Template+18
// is m_minimumAttackRange in name_oracle; +4ED remains address-derived.
// Object flags +94/+98, geometry +AC and AI +204/+1CC are witnessed here.
// Unknown fields and callable views retain this body's address token.
//
// Callee contracts, in first-occurrence retail order (all thiscall except
// 001F8AB0): 000A2CF0 takes one kind index, AL; 000ED3B0 one Object, ST0;
// 003EA570 takes source/goal/target, AL; 001BEC20 no args, EAX;
// 001F8AB0 cdecl target Object, pointer EAX and caller add esp,4;
// 0087E8D0 no args, AL and geometry receiver; 001C2070 and 000ED340 take
// position/Object/position, ST0; 001E2A70 takes source/height, ST0;
// 0015BDF0 takes two positions, ST0. The analyst pack independently proves
// the obstacle and module contracts. The gap helpers and range overload
// have matched C++ implementations. Address-claimed thunks avoid guessed
// semantic callee names; the sole direct predicate import is explained below.
struct Coord3D { float x, y, z; };
class Object;

// These declarations import existing address-claimed ILT symbols only.
extern void j_0003251f();
extern void j_00043ced();
extern void j_000441c0();
extern void j_0003a391();
extern void j_0002fc7a();
extern void j_0003bc28();
extern void j_00046bf0();
extern void j_0000aea7();

class Rva001E6930Calls {};
template<class F> static __forceinline F call001E6930(void (*raw)())
{
    union { void (*raw)(); F typed; } call;
    call.raw=raw;
    return call.typed;
}

static __forceinline bool kind001E6930(const Object *self,int kind)
{
    typedef bool (Rva001E6930Calls::*Call)(int) const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_0003251f))(kind);
}
static __forceinline float gap001E6930(const Object *self,const Object *other)
{
    typedef float (Rva001E6930Calls::*Call)(const Object*) const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_00043ced))(other);
}
static __forceinline int layer001E6930(const Object *self)
{
    typedef int (Rva001E6930Calls::*Call)() const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_0003a391))();
}
static __forceinline bool obstacle001E6930(void *self,const Object *source,const Coord3D *goal,const Object *target)
{
    typedef bool (Rva001E6930Calls::*Call)(const Object*,const Coord3D*,const Object*);
    return (((Rva001E6930Calls*)self)->*call001E6930<Call>(j_000441c0))(source,goal,target);
}
static __forceinline float boxGap001E6930(const Object *self,const Coord3D *goal,const Object *target,const Coord3D *targetPos)
{
    typedef float (Rva001E6930Calls::*Call)(const Coord3D*,const Object*,const Coord3D*) const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_0003bc28))(goal,target,targetPos);
}
static __forceinline float pairGap001E6930(const Object *self,const Coord3D *goal,const Object *target,const Coord3D *targetPos)
{
    typedef float (Rva001E6930Calls::*Call)(const Coord3D*,const Object*,const Coord3D*) const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_00046bf0))(goal,target,targetPos);
}
static __forceinline float pointGap001E6930(const Object *self,const Coord3D *goal,const Coord3D *targetPos)
{
    typedef float (Rva001E6930Calls::*Call)(const Coord3D*,const Coord3D*) const;
    return (((const Rva001E6930Calls*)self)->*call001E6930<Call>(j_0000aea7))(goal,targetPos);
}

// Existing emitter symbol at 0087E8D0 is used solely as a callable address.
// Its body actually tests a +2C/+30 vector of 36-byte records: one record
// and first dword 2. This caller passes Object+AC, not ThingTemplate+60.
class BfmeThingTemplateShadowSelector { public: bool usePluralShadowName() const; };
class Rva0087E8D0Geometry
{
public:
    __forceinline bool singleBox001E6930() const
    {
        union {
            bool (BfmeThingTemplateShadowSelector::*emitter)() const;
            bool (Rva0087E8D0Geometry::*predicate)() const;
        } call;
        call.emitter=&BfmeThingTemplateShadowSelector::usePluralShadowName;
        return (this->*call.predicate)();
    }
};
struct Rva001E6930AIUpdate { char m_00[0x1cc]; void *m_1cc; };
struct Rva001E6930ObjectFields
{
    char m_00[0x94];
    unsigned int m_94;
    unsigned int m_98;
    char m_9c[0xac-0x9c];
    Rva0087E8D0Geometry m_ac;
    char m_ad[0x204-0xac-sizeof(Rva0087E8D0Geometry)];
    Rva001E6930AIUpdate *m_204;
};
struct Rva001E6930Module { char m_00[0x3c]; bool m_3c; };
struct Rva001E6930AIData { char m_00[0xcc]; float m_cc; };
struct Rva001E6930AI { char m_00[0xc]; void *m_0c; char m_10[4]; Rva001E6930AIData *m_14; };
#define ai001E6930 (*(Rva001E6930AI**)0x012ef214)
extern float g_bfmeOffsetDF;
extern const float BfmeZeroRange;
struct Rva001E6930WeaponTemplate
{
    char m_00[0x18];
    float m_minimumAttackRange;
    char m_1c[0x4ed-0x1c];
    bool m_4ed;
};

class Weapon
{
public:
    bool isGoalPosWithinAttackRange(const Object *source,const Coord3D *goalPos,
        const Object *target,const Coord3D *targetPos,float extra) const;
    float getAttackRange(const Object *source,float height) const;
private:
    char m_00[4];
    Rva001E6930WeaponTemplate *m_template;
};

bool Weapon::isGoalPosWithinAttackRange(const Object *source,const Coord3D *goalPos,
    const Object *target,const Coord3D *targetPos,float extra) const
{
    const Rva001E6930ObjectFields *s=(const Rva001E6930ObjectFields*)source;
    const Rva001E6930ObjectFields *t=(const Rva001E6930ObjectFields*)target;
    if (m_template->m_4ed)
    {
        if (!target) return false;
        if ((s->m_94&0x10) && (t->m_94&0x10)) return true;
        if (kind001E6930(target,7) || (t->m_204 && t->m_204->m_1cc))
        {
            Rva001E6930AI *ai=ai001E6930;
            if (s->m_98&0x400)
            {
                float radius=ai->m_14->m_cc;
                if (gap001E6930(source,target)<radius*radius) return true;
            }
            bool result=obstacle001E6930(ai->m_0c,source,goalPos,target);
            if (result && !kind001E6930(target,0x95))
            {
                int sourceLayer=layer001E6930(source);
                int targetLayer=layer001E6930(target);
                if (sourceLayer==1 && targetLayer>=17) return false;
                if (targetLayer==1 && sourceLayer>=17)
                {
                    typedef Rva001E6930Module *(__cdecl *Call)(const Object*);
                    Rva001E6930Module *module=call001E6930<Call>(j_0002fc7a)(target);
                    if (!module || !module->m_3c) return false;
                }
            }
            return result;
        }
    }
    float distSqr;
    float attackRange;
    if (target)
    {
        const Rva0087E8D0Geometry *sourceGeometry=&s->m_ac;
        const Rva0087E8D0Geometry *targetGeometry=&t->m_ac;
        if (sourceGeometry->singleBox001E6930() && !targetGeometry->singleBox001E6930())
            distSqr=boxGap001E6930(source,goalPos,target,targetPos);
        else if (!sourceGeometry->singleBox001E6930() && targetGeometry->singleBox001E6930())
            distSqr=boxGap001E6930(target,targetPos,source,goalPos);
        else
            distSqr=pairGap001E6930(source,goalPos,target,targetPos);
        attackRange=getAttackRange(source,targetPos->z-goalPos->z);
    }
    else
    {
        distSqr=pointGap001E6930(source,goalPos,targetPos);
        attackRange=getAttackRange(source,targetPos->z-goalPos->z)-g_bfmeOffsetDF;
    }
    float attackRangeSqr=attackRange*attackRange;
    distSqr += extra*extra;
    float minAttackRange=m_template->m_minimumAttackRange-g_bfmeOffsetDF;
    if (minAttackRange<BfmeZeroRange) minAttackRange=BfmeZeroRange;
    float minAttackRangeSqr=minAttackRange*minAttackRange;
    if (s->m_94&0x10) minAttackRangeSqr=BfmeZeroRange;
    if (distSqr<minAttackRangeSqr) return false;
    if (distSqr<=attackRangeSqr) return true;
    return false;
}
