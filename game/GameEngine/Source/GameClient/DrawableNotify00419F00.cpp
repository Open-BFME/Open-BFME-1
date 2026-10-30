// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x00419F00, 647 bytes. Original method identity is unproved.
// Enumerates the matched 0x00419E40 predicate with {Drawable*, message} context,
// schedules EVA/radar events, then handles CastleMemberBehavior/CastleBehavior.
// Both castle sites call the file-static nearest-object query at 0x004182A0
// directly (not through the ILT); it is defined below, beside them.
// The 0x00410C90 callback is a 30-byte cdecl body: test Object, virtual getDrawable,
// OR drawable status with 0x40, return 1; its second callback argument is unused.
// Player::iterateObjects is declared with the void-predicate/int-result ABI
// established by the matched body at 0x000CDCF0 (retail call via ILT 0x0002F1CB);
// the predicate return value is discarded and the int result compared to 1.
// The source-visible message and castle-ID locals preserve retail's evaluation
// order; removing them also causes the compiler to hoist constant 1 into EBX.
// Coord3D retains the struct ABI of the existing Radar/Eva callee contracts;
// the canonical WWMath header instead declares a nontrivial class Coord3D.
class Player;
class Module;
class Drawable;

// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"

enum KindOfType
{
    K7 = 7,
    K47 = 47
};
enum NameKeyType
{
    NK0 = 0
};
enum EvaMessage
{
    EVA8 = 8
};
enum RadarEventType
{
    RADAR10 = 10
};

class Overridable
{
  public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
  public:
    char m_08[0x45c - 8];
    int m_45c;

    bool bfmeTemplatePredicate() const;
    bool isKindOf(KindOfType) const;
};

class Object
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
    virtual Drawable *getDrawable() const;

    char m_04[0x38 - 4];
    Coord3D m_position;
    char m_44[0x344 - 0x44];
    unsigned m_privateStatus;

    bool query(Object *, int);
    Player *getControllingPlayer() const;
    Module *findModule(NameKeyType) const;

    const Coord3D *getPosition() const
    {
        return &m_position;
    }
};

class Player
{
  public:
    int iterateObjects(void (*)(Object *, void *), void *) const;
};

class PlayerList
{
  public:
    char m_00[12];
    Object *m_local;
};
extern PlayerList *ThePlayerList;

class GameLogic
{
  public:
    char m_00[0x3c];
    unsigned m_frame;
    Object *findObjectByID(int);
};
extern GameLogic *TheGameLogic;

class Eva
{
  public:
    bool setShouldPlay(EvaMessage, const Coord3D *);

    char m_unmodelled00[0x60];
    Real m_radius60;            // +0x60, the nearest-object query's radius
};
extern Eva *TheEva;

class Radar
{
  public:
    void createEvent(const Coord3D *, RadarEventType, float);
};
extern Radar *TheRadar;

class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
  public:
    char m_00[0x18];
    int m_18;
};

class Rva0036ff70Module
{
  public:
    int query(int (*)(void *, void *), void *);
};

struct Rva00410C90Provider;

// The callback address passed to query below is rva00410C90SetFlag, the
// matched 30B function at RVA00410C90 (Common/Rva00410C90SetFlag.cpp): it
// reads the first argument as the provider pointer and ignores the second
// callback slot, so the address is cast to query's two-slot function
// pointer. The retired mark00410C90 placeholder spelled
// ?mark00410C90@@YAHPAX0@Z at the same address. Declaring the parameter
// type as struct (not class) keeps the provider TU's exact mangled name.
int rva00410C90SetFlag(Rva00410C90Provider *);

class Drawable
{
  public:
    void *m_00;
    ThingTemplate *m_template;
    char m_08[0xfc - 8];
    Object *m_object;
    char m_100[0x10];
    unsigned m_status;

    void notify00419F00();

    const ThingTemplate *finalTemplate() const
    {
        ThingTemplate *p = m_template;
        if (!p)
            return 0;
        return p->m_nextOverride ? (const ThingTemplate *)p->m_nextOverride->getFinalOverride() : p;
    }
};


typedef BitFlags<192> Rva004182A0KindOfMask;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

// The root table is the already-witnessed native table at 0x01083B80. Its
// two-word base head is the complete stack object used by this body.
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// Retail vtable 0x0109687C is recorded as PartitionFilterOnMap's.
class PartitionFilterOnMap : public PartitionFilter
{
public:
	PartitionFilterOnMap() {}
	virtual ~PartitionFilterOnMap() {}
	virtual Bool allow(Object *);
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}
	virtual ~PartitionFilterPlayer() {}
	virtual Bool allow(Object *);
	const Player *m_player;
	Bool m_match;
};

struct BfmeSrc1196
{
	unsigned char m_pad0[0x38];
	Coord3D m_position;
	unsigned char m_pad1[0x78];
	Real m_range;
};

// The matched constructor writes this exact 28-byte base-plus-payload shape:
// vptr/next, Coord3D, Real, Bool, and three bytes of tail padding.
class BfmeA1196 : public PartitionFilter
{
public:
	BfmeA1196(BfmeSrc1196 *owner, char match);
	virtual ~BfmeA1196() {}
	virtual Bool allow(Object *);
	Coord3D m_position;
	Real m_range;
	Bool m_match;
	unsigned char m_tail[3];
};

// This is the native one-mask 192-bit filter evidenced by vtable
// 0x010F11B4, recorded under the address-derived Rva00410750VptrZeroBlockObject. It is deliberately separate from the sibling two-mask
// accept/reject declarations.
class Rva00410750VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva00410750VptrZeroBlockObject(const Rva004182A0KindOfMask &mask)
		: m_mask(mask) {}
	virtual ~Rva00410750VptrZeroBlockObject() {}
	virtual Bool allow(Object *);
	Rva004182A0KindOfMask m_mask;
};

enum DistanceCalculationType
{
	RVA004182A0_FROM_CENTER_2D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real radius,
		DistanceCalculationType distanceType, PartitionFilter *filters);
};
extern PartitionManager *ThePartitionManager;


// Retail 0x004182A0 (271 bytes): the nearest-object query both castle sites
// below make. Retail calls it directly, not through the ILT, so it is a
// file-static of this TU; as one it compiles to retail's bytes, where the
// former member spelling swapped the receiver's ESI/EDI. The kind-of, on-map,
// player and shroud filters are linked behind the kind-of filter, and that
// head is what the partition manager receives.
static Object *nearest004182A0( BfmeSrc1196 *self )
{
	Rva0025ED50RootFilter rootFilter;
	PartitionFilterOnMap onMapFilter;
	PartitionFilterPlayer playerFilter(
		(const Player *)ThePlayerList->m_local, true);
	Rva00410750VptrZeroBlockObject kindOfFilter(
		Rva004182A0KindOfMask(
			Rva004182A0KindOfMask::kInit, 121, 157));
	BfmeA1196 shroudFilter(self, true);

	kindOfFilter.link(&rootFilter)
		->link(&onMapFilter)
		->link(&playerFilter)
		->link(&shroudFilter);
	return ThePartitionManager->getClosestObject(
		&self->m_position, TheEva->m_radius60,
		RVA004182A0_FROM_CENTER_2D, &kindOfFilter);
}

class Rva00419E40Context
{
  public:
    Drawable *m_drawable;
    unsigned m_field04;
};

int bfmeDrawableFilter00419E40(Object *, Rva00419E40Context *);

void Drawable::notify00419F00()
{
    const ThingTemplate *t = finalTemplate();
    Object *object = m_object;
    Object *local = ThePlayerList ? ThePlayerList->m_local : 0;

    if (t && object && local && TheGameLogic && TheGameLogic->m_frame > 5 &&
        object->query(local, 1))
    {

        if (!(object->m_privateStatus & 1) && t->bfmeTemplatePredicate() && t->m_45c != -1 &&
            !t->isKindOf(K47))
        {
            Player *p = object->getControllingPlayer();
            if (p)
            {
                Rva00419E40Context context;
                unsigned message = t->m_45c;
                context.m_drawable = this;
                context.m_field04 = message;

                if (p->iterateObjects((void (*)(Object *, void *))bfmeDrawableFilter00419E40,
                                      &context) == 1)
                {
                    Object *nearby = nearest004182A0( (BfmeSrc1196 *)object );
                    if (nearby)
                    {
                        EvaMessage message = (EvaMessage)t->m_45c;
                        if (TheEva->setShouldPlay(message, nearby->getPosition()))
                        {
                            TheRadar->createEvent(object->getPosition(), RADAR10, 4.0f);
                        }
                    }
                }
            }
        }
        if (t->isKindOf(K7) && !(m_status & 0x40))
        {
            static NameKeyType memberKey = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");

            Module *member = object->findModule(memberKey);
            if (!member)
                return;

            int castleID = member->m_18;
            Object *castle = TheGameLogic->findObjectByID(castleID);
            if (!castle)
                return;

            Drawable *d = castle->getDrawable();
            if (!d)
                return;

            if (!(d->m_status & 0x40))
            {
                Object *nearby = nearest004182A0( (BfmeSrc1196 *)object );
                if (nearby && TheEva->setShouldPlay(EVA8, nearby->getPosition()))
                {
                    TheRadar->createEvent(object->getPosition(), RADAR10, 4.0f);
                }
            }
            static NameKeyType castleKey = TheNameKeyGenerator->nameToKey("CastleBehavior");

            Module *behavior = castle->findModule(castleKey);
            if (!behavior)
            {
                d->m_status |= 0x40;
                return;
            }
            ((Rva0036ff70Module *)behavior)->query((int (*)(void *, void *))rva00410C90SetFlag, 0);
        }
    }
}
