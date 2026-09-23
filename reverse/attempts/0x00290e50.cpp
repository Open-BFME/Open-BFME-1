// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.7558479532163742 date=2026-09-23
// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Rebuilt from the banked body; measured probe evidence is in astra_R/PROGRESS.md.
// cl: /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Source/WWVegas/WWLib
//
// EmotionTrackerUpdate::update, retail RVA 0x00290E50, 2052 bytes.
//
// The identity is anchored by the slot-zero entry in the secondary
// UpdateModuleInterface vtable 0x010BE1D8 installed by the matched constructor
// at 0x00290740.  The entry is the ILT at 0x0002B71A.  This method therefore
// receives the interface subobject: the owning Object and ModuleData are at
// this-0x08 and this-0x0c, while the recovered tracker state starts at
// this+0x14.  The BFME emotion-selection code has no Zero Hour twin; the
// address-derived helper views below describe only the witnessed call ABIs and
// stack layouts.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0,
	RELATIONSHIP_NEUTRAL = 1,
	RELATIONSHIP_ALLIES = 2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Emotion;
class PartitionFilter;
enum DistanceCalculationType { Rva00290E50Distance0=0 };
class PartitionManager { public: Object *getClosestObject(const Coord3D*,float,DistanceCalculationType,PartitionFilter*); };


// The named direct callees are existing ledger identities.  The other calls
// remain on their retail ILT spellings, as reported by tools/callees.py.
class Object
{
public:
	float getShroudClearingRange(void) const;
	Relationship getRelationship(const Object *other) const;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class BfmeC1050
{
public:
	void bfmeGo1050D(int a, int b, int c, int d);
};

class Player
{
};

class PlayerList
{
};

class Gen_008f7470
{
public:
	void m(void);
};

class Registry
{
};

class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual float slot18(float x, float y, int normal) = 0;
};

class TacticalView
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(Coord3D *position, float radius,
		UnsignedInt color, int flags) = 0;
};

// These are the retail absolute globals annotated by the disassembler.  The
// address forms keep this TU independent of unrelated BFME class-name shims.
extern unsigned char *Rva012ED5C8;
#define TheWritableGlobalData Rva012ED5C8
extern TerrainLogic *Rva012EF4CC;
#define TheTerrainLogic Rva012EF4CC
extern TacticalView *Rva012F1600;
#define TheTacticalView Rva012F1600
extern BfmeC1050 *Rva012ED5B8;
#define ThePartitionManager Rva012ED5B8
extern PlayerList *Rva012ED748;
#define ThePlayers Rva012ED748
extern Gen_008f7470 *Rva012ED5BC;
#define TheShroudManager Rva012ED5BC
extern Registry *Rva012EF1D8;
#define TheRegistry Rva012EF1D8
extern GameLogic *Rva012F0898;
#define TheBfmeGameLogic Rva012F0898
extern unsigned char *Rva012F0878;
#define TheEmotionSystem Rva012F0878
#define BfmeZeroRange (*(const float *)0x01075350)

extern void j_000016a4(void);
extern void j_000084b8(void);
extern void j_0000c69e(void);
extern void j_00015e2e(void);
extern void j_00019056(void);
extern void j_0001da34(void);
extern void j_0001f253(void);
extern void j_00020824(void);
extern void j_000283d0(void);
extern void j_00028560(void);
extern void j_000326cd(void);
extern void j_0003251f(void);
extern void j_0003a391(void);
extern void j_0003e80b(void);
extern void j_00043ced(void);
extern void j_00044c60(void);
extern void j_000466b4(void);
extern void j_00049f0d(void);
extern void j_000326cd(void);

extern float GetGameLogicRandomValueReal(float low, float high,
	char *file, int line);

// The two direct bodies below are declared with their callee names.  Their
// retail declarations return through EAX even though the old ILT spelling is
// a QAEX void symbol; typed member-pointer views make the ABI explicit without adding a
// new pin or a semantic name.
struct Rva00290E50VoidCall
{
	typedef void (Rva00290E50VoidCall::*Function)(void);
};

static __forceinline void rva00290e50VoidCall(void *object, void (*raw)(void))
{
	union { void (*raw)(void); Rva00290E50VoidCall::Function member; } route;
	route.raw = raw;
	(reinterpret_cast<Rva00290E50VoidCall *>(object)->*route.member)();
}

static __forceinline void rva00290e50StopEmotion(Emotion *emotion)
{
	rva00290e50VoidCall((void *)emotion, j_00015e2e);
}

struct Rva00290E50BoolNoArgsCall
{
	typedef Bool (Rva00290E50BoolNoArgsCall::*Function)(void);
};

static __forceinline Bool rva00290e50BoolNoArgs(void *object, void (*raw)(void))
{
	union { void (*raw)(void); Rva00290E50BoolNoArgsCall::Function member; } route;
	route.raw = raw;
	return (reinterpret_cast<Rva00290E50BoolNoArgsCall *>(object)->*route.member)();
}

static __forceinline Bool rva00290e50EmotionStillActive(Emotion *emotion)
{
	return rva00290e50BoolNoArgs((void *)emotion, j_0000c69e);
}

struct Rva00290E50TestStatusCall
{
	typedef Bool (Rva00290E50TestStatusCall::*Function)(int);
};

static __forceinline Bool rva00290e50TestStatus(Object *object, int status)
{
	union { void (*raw)(void); Rva00290E50TestStatusCall::Function member; } route;
	route.raw = j_000016a4;
	return (reinterpret_cast<Rva00290E50TestStatusCall *>(object)->*route.member)(status);
}

struct Rva00290E50AcceptCall
{
	typedef Bool (Rva00290E50AcceptCall::*Function)(Object *, int);
};

static __forceinline Bool rva00290e50Accept(const void *filter, Object *object)
{
	union { void (*raw)(void); Rva00290E50AcceptCall::Function member; } route;
	route.raw = j_0001da34;
	return (reinterpret_cast<Rva00290E50AcceptCall *>(const_cast<void *>(filter))->*route.member)(object, 0);
}

struct Rva00290E50DistanceCall
{
	typedef float (Rva00290E50DistanceCall::*Function)(const Object *);
};

static __forceinline float rva00290e50Distance(Object *object, Object *other)
{
	union { void (*raw)(void); Rva00290E50DistanceCall::Function member; } route;
	route.raw = j_00043ced;
	return (reinterpret_cast<Rva00290E50DistanceCall *>(object)->*route.member)(other);
}

struct Rva00290E50ShroudRangeCall
{
	typedef float (Rva00290E50ShroudRangeCall::*Function)(void);
};

static __forceinline float rva00290e50ShroudRange(Object *object)
{
	union { void (*raw)(void); Rva00290E50ShroudRangeCall::Function member; } route;
	route.raw = j_000326cd;
	return (reinterpret_cast<Rva00290E50ShroudRangeCall *>(object)->*route.member)();
}

struct Rva00290E50PlayerCall
{
	typedef Player *(Rva00290E50PlayerCall::*Function)(void);
};

static __forceinline Player *rva00290e50ControllingPlayer(Object *object)
{
	union { void (*raw)(void); Rva00290E50PlayerCall::Function member; } route;
	route.raw = j_00020824;
	return (reinterpret_cast<Rva00290E50PlayerCall *>(object)->*route.member)();
}

struct Rva00290E50MaskCall
{
	typedef UnsignedShort (Rva00290E50MaskCall::*Function)(int, int, int);
};

static __forceinline UnsignedShort rva00290e50Mask(PlayerList *players,
	int player, int relationship)
{
	union { void (*raw)(void); Rva00290E50MaskCall::Function member; } route;
	route.raw = j_00044c60;
	return (reinterpret_cast<Rva00290E50MaskCall *>(players)->*route.member)(
		player, relationship, 0);
}

struct Rva00290E50FindObjectCall
{
	typedef Object *(Rva00290E50FindObjectCall::*Function)(int);
};

static __forceinline Object *rva00290e50FindObject(GameLogic *logic, int id)
{
	union { void (*raw)(void); Rva00290E50FindObjectCall::Function member; } route;
	route.raw = j_0001f253;
	return (reinterpret_cast<Rva00290E50FindObjectCall *>(logic)->*route.member)(id);
}

struct Rva00290E50ShroudCall
{
	typedef UnsignedInt (Rva00290E50ShroudCall::*Function)(void *, int, UnsignedInt);
};

static __forceinline UnsignedInt rva00290e50Shroud(Gen_008f7470 *shroud,
	void *position, UnsignedInt playerMask)
{
	union { void (Gen_008f7470::*raw)(); Rva00290E50ShroudCall::Function member; } route;
    route.raw=&Gen_008f7470::m;
    return (reinterpret_cast<Rva00290E50ShroudCall*>(shroud)->*route.member)(position,1,playerMask);
}

struct Rva00290E50KindCall
{
	typedef Bool (Rva00290E50KindCall::*Function)(int);
};

static __forceinline Bool rva00290e50Kind(Object *object, int kind)
{
	union { void (*raw)(void); Rva00290E50KindCall::Function member; } route;
	route.raw = j_0003251f;
	return (reinterpret_cast<Rva00290E50KindCall *>(object)->*route.member)(kind);
}

struct Rva00290E50LayerCall
{
	typedef int (Rva00290E50LayerCall::*Function)(void);
};

static __forceinline int rva00290e50Layer(Object *object)
{
	union { void (*raw)(void); Rva00290E50LayerCall::Function member; } route;
	route.raw = j_0003a391;
	return (reinterpret_cast<Rva00290E50LayerCall *>(object)->*route.member)();
}

static __forceinline Bool rva00290e50SameLayer(Object *first, Object *second) {
    int layer=rva00290e50Layer(first);
    return layer==rva00290e50Layer(second);
}

struct Rva00290E50EmotionTestCall
{
	typedef Bool (Rva00290E50EmotionTestCall::*Function)(int, int, Object *);
};

static __forceinline Bool rva00290e50EmotionTest(Emotion *emotion,
	int firstMask, int secondMask, Object *object)
{
	union { void (*raw)(void); Rva00290E50EmotionTestCall::Function member; } route;
	route.raw = j_000466b4;
	return (reinterpret_cast<Rva00290E50EmotionTestCall *>(emotion)->*route.member)(
		firstMask, secondMask, object);
}

struct Rva00290E50TemplateCall
{
	typedef void *(Rva00290E50TemplateCall::*Function)(void);
};

static __forceinline void *rva00290e50Template(Object *object)
{
	union { void (*raw)(void); Rva00290E50TemplateCall::Function member; } route;
	route.raw = j_000084b8;
	return (reinterpret_cast<Rva00290E50TemplateCall *>(object)->*route.member)();
}

struct Rva00290E50EquivalentCall
{
	typedef Bool (Rva00290E50EquivalentCall::*Function)(void *);
};

static __forceinline Bool rva00290e50Equivalent(void *thing, void *candidate)
{
	union { void (*raw)(void); Rva00290E50EquivalentCall::Function member; } route;
	route.raw = j_0003e80b;
	return (reinterpret_cast<Rva00290E50EquivalentCall *>(thing)->*route.member)(candidate);
}

struct Rva00290E50RegistryCall
{
	typedef void *(Rva00290E50RegistryCall::*Function)(void *);
};

static __forceinline void *rva00290e50RegistryLookup(Registry *registry,
	void *name)
{
	union { void (*raw)(void); Rva00290E50RegistryCall::Function member; } route;
	route.raw = j_00028560;
	return (reinterpret_cast<Rva00290E50RegistryCall *>(registry)->*route.member)(name);
}

struct Rva00290E50SelectCall
{
	typedef Emotion *(Rva00290E50SelectCall::*Function)(void);
};

static __forceinline Emotion *rva00290e50Select(void *primary)
{
	union { void (*raw)(void); Rva00290E50SelectCall::Function member; } route;
	route.raw = j_000283d0;
	return (reinterpret_cast<Rva00290E50SelectCall *>(primary)->*route.member)();
}

struct Rva00290E50SetObjectCall
{
	typedef void (Rva00290E50SetObjectCall::*Function)(Object *);
};

static __forceinline void rva00290e50SetObject(Emotion *emotion,
	Object *object)
{
	union { void (*raw)(void); Rva00290E50SetObjectCall::Function member; } route;
	route.raw = j_00019056;
	(reinterpret_cast<Rva00290E50SetObjectCall *>(emotion)->*route.member)(object);
}

struct BfmeC1050Result
{
	typedef Object *(BfmeC1050Result::*Function)(const Coord3D *, float, int, void *);
};

static __forceinline Object *rva00290e50FindAround(BfmeC1050 *manager,
	const Coord3D *position, float range, int zero, void *filter)
{
	union { void (BfmeC1050::*raw)(int,int,int,int); BfmeC1050Result::Function member; } route;
    route.raw=&BfmeC1050::bfmeGo1050D;
    return (reinterpret_cast<BfmeC1050Result*>(manager)->*route.member)(position,range,zero,filter);
}

// The stack filter constructor is the body at 0x0028F2A0, reached through
// the exact ILT name printed by callees.py.  Its retail object is 0x24 bytes;
// the inline destructor is the vptr reset visible at update+0x024a.
class Rva0028F2A0Filter
{
public:
	Rva0028F2A0Filter(void *owner) {
        union { void (*raw)(void); Function member; } route;
        route.raw = j_00049f0d;
        (reinterpret_cast<Call*>(this)->*route.member)(owner);
    }
	~Rva0028F2A0Filter(void) { m_vptr = 0x01083b5c; }

	unsigned int m_vptr;
	unsigned char m_storage[0x20];

private:
	struct Call
	{
		typedef void (Call::*Function)(void *);
	};
	typedef Call::Function Function;
};


#include "Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
class ThingTemplate;
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString&); };

struct Rva00290E50ModuleData {
    unsigned char pad00[8]; float field08; int field0c; unsigned field10;
    unsigned field14,field18,field1c; float field20,field24,field28;
};
class EmotionTrackerUpdate
{
public:
	virtual UpdateSleepTime update(void);

	// The method is entered with the secondary interface pointer.  These
	// members describe the already-witnessed tracker tail at that pointer;
	// keeping the fields in the class gives VC7.1 the same long-lived `this`
	// value as the retail body instead of forcing every access through a
	// promoted byte pointer.
	unsigned char m_pad04[0x10];
	unsigned char m_active[10];
	unsigned char m_pad1e[2];
	UnsignedInt m_startFrame[10];
	UnsignedInt m_endFrame[10];
	Emotion **m_emotionsBegin;
	Emotion **m_emotionsEnd;
	unsigned char m_pad78[4];
	Emotion *current;
	int m_distributionIndex;
	unsigned char m_pad84[0x10];
	int m_forcedRetry;
	int m_objectID;
	UnsignedInt m_deadline;
	unsigned char m_enabled;
};

static __forceinline UnsignedInt rva00290e50EmotionType(const Emotion *emotion)
{
	const unsigned char *raw = reinterpret_cast<const unsigned char *>(emotion);
	const unsigned char *entry = *reinterpret_cast<const unsigned char * const *>(raw + 4);
	return *reinterpret_cast<const UnsignedInt *>(entry + 4);
}

static __forceinline Object *rva00290e50FindByID(int id)
{
	return rva00290e50FindObject(TheBfmeGameLogic, id);
}

// ?update@EmotionTrackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime EmotionTrackerUpdate::update(void)
{
    const Rva00290E50ModuleData *moduleData = *(const Rva00290E50ModuleData **)((unsigned char*)this-0x0c);
    if (!moduleData) return UPDATE_SLEEP_FOREVER;
    Object *object = *(Object**)((unsigned char*)this-8);
    if (!object) return UPDATE_SLEEP_FOREVER;
    if (*(Object**)((unsigned char*)object+0x214)) {
        if (current) { rva00290e50StopEmotion(current); current=0; }
        return UPDATE_SLEEP_NONE;
    } else {
        if (m_forcedRetry>0) --m_forcedRetry;
        if (*(TheWritableGlobalData+0xec8)) {
            Coord3D position; position.x=*(float*)((unsigned char*)object+0x38); position.y=*(float*)((unsigned char*)object+0x3c); position.z=*(float*)((unsigned char*)object+0x40);
            position.z=TheTerrainLogic->slot18(position.x,position.y,0);
            if (moduleData->field0c)
                TheTacticalView->slot30(&position,moduleData->field08,0xff0000ff,0);
            if (moduleData->field20!=BfmeZeroRange)
                TheTacticalView->slot30(&position,moduleData->field20,0xff00ffff,0);
            if (moduleData->field24!=BfmeZeroRange)
                TheTacticalView->slot30(&position,moduleData->field24,0xffff0000,0);
        }
        Object *type3Object=0;
        float bestDistance=3.402823466e+38F;
        if (--m_distributionIndex<=0 && moduleData->field0c && m_forcedRetry<=0) {
            m_distributionIndex=moduleData->field0c;
            Rva0028F2A0Filter filter((unsigned char*)this-0x10);
            if (!rva00290e50TestStatus(object,0x43))
                type3Object=((PartitionManager*)ThePartitionManager)->getClosestObject((const Coord3D*)((unsigned char*)object+0x38),moduleData->field08,Rva00290E50Distance0,(PartitionFilter*)&filter);
            if (!type3Object) {
                m_active[0]=0; m_active[3]=0;
                if (filter.m_storage[0x1c]) m_active[9]=1; else m_active[9]=0;
            } else {
                if (!rva00290e50Accept(&moduleData->field1c,type3Object) &&
                    !rva00290e50Accept(&moduleData->field14,type3Object) &&
                    !rva00290e50Accept(&moduleData->field18,type3Object)) {
                    m_active[9]=0; m_active[0]=1; m_active[3]=0;
                } else {
                    m_active[9]=0; m_active[0]=0; m_active[3]=1;
                    bestDistance=rva00290e50Distance(object,type3Object);
                }
            }
        }
        Object *type59Object=0;
        Object *type4Object=0;
        if ((moduleData->field20>BfmeZeroRange || moduleData->field24>BfmeZeroRange) && m_forcedRetry<=0) {
            Bool found59=false;
            UnsignedInt objectMask=0,otherObjectMask=0;
            Player *player=rva00290e50ControllingPlayer(object);
            if (player) {
                UnsignedShort enemyMask=rva00290e50Mask(ThePlayers,*(int*)((unsigned char*)player+0x24),3);
                UnsignedShort otherMask=rva00290e50Mask(ThePlayers,*(int*)((unsigned char*)player+0x24),4);
                objectMask=rva00290e50Shroud(TheShroudManager,(unsigned char*)*(Object**)((unsigned char*)this-8)+0x38,otherMask);
                otherObjectMask=rva00290e50Shroud(TheShroudManager,(unsigned char*)*(Object**)((unsigned char*)this-8)+0x38,enemyMask);
            }
            float shroudRange=object->getShroudClearingRange();
            float shroudSquared=shroudRange*shroudRange;
            if (bestDistance>shroudSquared) bestDistance=shroudSquared;
            float range20=moduleData->field20* moduleData->field20;
            float range24=moduleData->field24* moduleData->field24;
            int *id=*(int**)(TheEmotionSystem+0x14);
            int **end=(int**)(TheEmotionSystem+0x18);
            for (;id!=*end;++id) {
                Object *candidate=rva00290e50FindByID(*id);
                if (!candidate || !*((unsigned char*)candidate+0x368)) continue;
                Relationship relationship=object->getRelationship(candidate);
                if (rva00290e50Kind(candidate,0x8f) && (relationship!=RELATIONSHIP_ALLIES || rva00290e50Accept(&moduleData->field18,candidate))) {
                    float distance=rva00290e50Distance(object,candidate);
                    if (distance<range24 && (rva00290e50Accept(&moduleData->field14,candidate) || rva00290e50Accept(&moduleData->field18,candidate)) &&
                        ((*((unsigned char*)candidate+0x90)&0x40) || rva00290e50SameLayer(*(Object**)((unsigned char*)this-8),candidate))) {
                        Emotion **emotion=m_emotionsBegin;
                        for (;emotion!=m_emotionsEnd;++emotion)
                            if (rva00290e50EmotionType(*emotion)==4 && rva00290e50EmotionTest(*emotion,objectMask,otherObjectMask,candidate)) break;
                        if (emotion!=m_emotionsEnd) { type4Object=candidate; range24=distance; continue; }
                    }
                    if (distance<bestDistance && (rva00290e50Accept(&moduleData->field14,candidate) || rva00290e50Accept(&moduleData->field18,candidate) || rva00290e50Accept(&moduleData->field1c,candidate))) {
                        Emotion **emotion=m_emotionsBegin;
                        for (;emotion!=m_emotionsEnd;++emotion)
                            if (rva00290e50EmotionType(*emotion)==3 && rva00290e50EmotionTest(*emotion,objectMask,otherObjectMask,candidate)) break;
                        if (emotion!=m_emotionsEnd) {
                            bestDistance=distance; type3Object=candidate;
                            if (!(*((unsigned char*)candidate+0x90)&0x40) && !rva00290e50SameLayer(*(Object**)((unsigned char*)this-8),candidate)) {
                                m_active[0]=1; m_active[3]=0;
                            } else { m_active[0]=0; m_active[3]=1; }
                        }
                    }
                }
                if (rva00290e50Kind(candidate,0x59)) {
                    void *nameObject;
                    { AsciiString name((const char*)0x010be578); nameObject=(void*)((BfmeThingFactory*)TheRegistry)->findTemplate(name); }
                    if (nameObject && rva00290e50Equivalent(nameObject,rva00290e50Template(candidate))) continue;
                    if (relationship==RELATIONSHIP_ALLIES) {
                        float distance=rva00290e50Distance(object,candidate);
                        if (distance<range20) { range20=distance; type59Object=candidate; found59=true; }
                    }
                }
            }
            if (!m_enabled && !found59) m_enabled=1;
            GameLogic *logic=TheBfmeGameLogic;
            if (logic->m_frame>m_deadline && type59Object && m_enabled) {
                m_deadline=logic->m_frame+300; m_active[2]=1; m_enabled=0;
            } else m_active[2]=0;
            m_active[4]=type4Object!=0;
        }
        if (GetGameLogicRandomValueReal(0.0f,1.0f,(char*)0x010be518,0x226)<moduleData->field28 && rva00290e50Layer(object)==1) {
            GameLogic *frameSource=TheBfmeGameLogic;
            m_active[8]=1; m_startFrame[8]=frameSource->m_frame+1; m_endFrame[8]=0;
        }
        Emotion *selected=rva00290e50Select((unsigned char*)this-0x10);
        Bool changedContainment=false;
        if (selected && type3Object) {
            UnsignedInt type=rva00290e50EmotionType(selected);
            if (type==0 || type==3) {
                UnsignedInt selectedID=m_endFrame[type];
                UnsignedInt candidateID=*(UnsignedInt*)((unsigned char*)type3Object+0x74);
                if (candidateID!=selectedID) {
                    Object *a=rva00290e50FindByID(selectedID), *b=rva00290e50FindByID(candidateID);
                    if (a && *(Object**)((unsigned char*)a+0x214)) a=*(Object**)((unsigned char*)a+0x214);
                    if (b && *(Object**)((unsigned char*)b+0x214)) b=*(Object**)((unsigned char*)b+0x214);
                    if (a!=b) changedContainment=true;
                }
            }
        }
        if (selected==current && !changedContainment) {
            if (current && !rva00290e50EmotionStillActive(current)) {
                rva00290e50StopEmotion(current); current=0;
            }
        } else {
            if (current) rva00290e50StopEmotion(current);
            current=selected;
            if (selected) {
                UnsignedInt type=rva00290e50EmotionType(selected);
                if (type==0 || type==3) { if(type3Object) m_endFrame[type]=*(UnsignedInt*)((unsigned char*)type3Object+0x74); }
                else if (type==2) { if(type59Object) m_endFrame[2]=*(UnsignedInt*)((unsigned char*)type59Object+0x74); }
                else if (type==4) { if(type4Object) m_endFrame[4]=*(UnsignedInt*)((unsigned char*)type4Object+0x74); }
                int objectID;
                if (m_forcedRetry>0) objectID=m_objectID;
                else objectID=m_endFrame[rva00290e50EmotionType(current)];
                rva00290e50SetObject(current,rva00290e50FindByID(objectID));
            }
        }
        for (int i=0;i<10;++i) if (m_startFrame[i] && TheBfmeGameLogic->m_frame>=m_startFrame[i]) {
            m_active[i]=0; m_startFrame[i]=0;
        }
    }
    return UPDATE_SLEEP_NONE;
}

#undef BfmeZeroRange
#undef TheEmotionSystem
#undef TheBfmeGameLogic
#undef TheRegistry
#undef TheShroudManager
#undef ThePlayers
#undef ThePartitionManager
#undef TheTacticalView
#undef TheTerrainLogic
#undef TheWritableGlobalData
