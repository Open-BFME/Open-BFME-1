// ?onRemoving@GarrisonContain@@UAEXPAVObject@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// BFME retail ?onRemoving@GarrisonContain@@UAEXPAVObject@@@Z at RVA
// 0x0021F0A0, 383 bytes.
//
// Identity is established independently of the generated placeholder: the
// secondary GarrisonContain vtable at 0x010AB598 has slot +0x48 pointing at
// j_00005c22, whose body is the 0x0021F0A0 range.  Compiling the vendored ZH
// GarrisonContain translation unit independently names this corresponding
// vtable slot onRemoving.  The incoming ECX is the secondary interface; the
// BFME primary module is ECX-0x20.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
typedef bool Bool;
typedef float Real;

class Object;
class Team;

template<int NUMBITS>
class BitFlags
{
public:
	 enum _dummy_kInit { kInit };

	 BitFlags(_dummy_kInit, Int index)
	 {
		 m_bits.set(index);
	 }

private:
	 _STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum DisabledType
{
	DISABLED_HELD = 3
};

struct BfmeObjectIDView
{
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;
};

struct BfmeObjectFlagsView
{
	unsigned char m_unmodelled_000[0x2a0];
	UnsignedInt m_flags;
};

struct BfmeObjectTeamView
{
	unsigned char m_unmodelled_000[0x23c];
	Team *m_team;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void setTeam(Team *) = 0;

	ObjectID getID() const
	{
		return reinterpret_cast<const BfmeObjectIDView *>(this)->m_id;
	}

	Bool clearDisabled(DisabledType type);
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
};

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;
};

// Object+4 is the BFME ThingTemplate link.  The resolved override carries
// the occlusion delay at +0x424 in this executable's layout.
struct BfmeThingTemplateView
{
	unsigned char m_unmodelled_000[4];
	BfmeOverridable *m_override;
};

struct BfmeObjectTemplateLink
{
	void *m_vtable;
	BfmeThingTemplateView *m_template;
};

struct BfmeObjectOverrideLayout
{
	unsigned char m_unmodelled_000[0x424];
	UnsignedInt m_occlusionDelay;
};

struct BfmeObjectFrameView
{
	unsigned char m_unmodelled_000[0x330];
	UnsignedInt m_safeOcclusionFrame;
};

struct BfmeObjectBodyLink
{
	unsigned char m_unmodelled_000[0x200];
	class BfmeBodyModule *m_body;
};

class BfmeBodyModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual float getHealth() const = 0;
};

// The model-condition word is at Object+0x110.  The notification route is
// the already identified BFME ILT used by the containing hook.
class BfmeObjectModelCondition
{
public:
	unsigned char m_unmodelled_000[0x110];
	UnsignedInt m_conditionFlags;

	void notifyModelConditionChanged();
};

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@BfmeObjectModelCondition@@QAEXXZ=?j_0002191d@@YAXXZ")

struct Rva00367E30Logic
{
	unsigned char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class GameLogic
{
public:
	void destroyObject(Object *object);
};

class OpenContain
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void onContaining(Object *, Bool);
	virtual void onRemoving(Object *);
};

struct BfmeGarrisonPointData
{
	ObjectID m_object;
	ObjectID m_targetID;
	UnsignedInt m_placeFrame;
	unsigned char m_unmodelled_00c[8];
};

struct BfmeGarrisonPointView
{
	unsigned char m_unmodelled_000[0xb8];
	BfmeGarrisonPointData m_points[40];
};

struct BfmeGarrisonOwnerLink
{
	Object *m_object;
};

struct BfmeGarrisonOriginalTeamView
{
	unsigned char m_unmodelled_000[0xb4];
	Team *m_originalTeam;
};

class BfmeObjectVTable
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0c() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1c() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0; virtual void slot30() = 0;
	virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3c() = 0; virtual void slot40() = 0;
	virtual void slot44() = 0; virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void setTeam(Team *) = 0;
};

class GarrisonContain : public OpenContain
{
protected:
	void removeObjectFromGarrisonPoint(Object *, Int);

public:
	virtual void recalcApparentControllingPlayer();
	virtual void onContaining(Object *, Bool);
	virtual void onRemoving(Object *);

	virtual void slot4c() = 0; virtual void slot50() = 0;
	virtual void slot54() = 0; virtual void slot58() = 0;
	virtual void slot5c() = 0; virtual void slot60() = 0;
	virtual void slot64() = 0; virtual void slot68() = 0;
	virtual void slot6c() = 0; virtual void slot70() = 0;
	virtual void slot74() = 0; virtual void slot78() = 0;
	virtual void slot7c() = 0; virtual void slot80() = 0;
	virtual void slot84() = 0; virtual void slot88() = 0;
	virtual void slot8c() = 0; virtual void slot90() = 0;
	virtual void slot94() = 0; virtual void slot98() = 0;
	virtual void slot9c() = 0; virtual void slota0() = 0;
	virtual void slota4() = 0; virtual void slota8() = 0;
	virtual void slotac() = 0; virtual void slotb0() = 0;
	virtual void slotb4() = 0; virtual void slotb8() = 0;
	virtual void slotbc() = 0; virtual void slotc0() = 0;
	virtual void slotc4() = 0; virtual void slotc8() = 0;
	virtual void slotcc() = 0; virtual void slotd0() = 0;
	virtual void slotd4() = 0; virtual void slotd8() = 0;
	virtual void slotdc() = 0; virtual void slote0() = 0;
	virtual void slote4() = 0; virtual void slote8() = 0;
	virtual void slotec() = 0; virtual void slotf0() = 0;
	virtual void slotf4() = 0; virtual void slotf8() = 0;
	virtual void slotfc() = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
	virtual void slot104() = 0; virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual UnsignedInt getStealthUnitsContained() const = 0;
};

class Rva00221540
{
public:
	Int isReady();
};

extern const Real BfmeZeroRange;

// ?onRemoving@GarrisonContain@@UAEXPAVObject@@@Z
void GarrisonContain::onRemoving(Object *object)
{
	OpenContain::onRemoving(object);

	if (object != 0)
	{
		Int index = 0;
		BfmeGarrisonPointData *point =
			 reinterpret_cast<BfmeGarrisonPointView *>(this)->m_points;
		for (; index < 40; ++index, ++point)
		{
			if (point->m_object == object->getID())
			{
				reinterpret_cast<GarrisonContain *>(
					reinterpret_cast<unsigned char *>(this) - 0x20)
					->removeObjectFromGarrisonPoint(object, index);
			}
		}
	}

	BfmeObjectFlagsView *objectFlags =
		reinterpret_cast<BfmeObjectFlagsView *>(object);
	const UnsignedInt flags = objectFlags->m_flags & ~1U;
	objectFlags->m_flags = flags;
	object->clearDisabled(DISABLED_HELD);

	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 57), false);

	if (getContainCount(false) == 0)
	{
		if (reinterpret_cast<BfmeObjectTeamView *>(
			reinterpret_cast<BfmeGarrisonOwnerLink *>(
				reinterpret_cast<unsigned char *>(this) - 0x18)->m_object)->m_team != 0)
		{
			Team *originalTeam = reinterpret_cast<BfmeGarrisonOriginalTeamView *>(this)->m_originalTeam;
			reinterpret_cast<BfmeObjectVTable *>(
				reinterpret_cast<BfmeGarrisonOwnerLink *>(
					reinterpret_cast<unsigned char *>(this) - 0x18)->m_object)->setTeam(originalTeam);
			reinterpret_cast<BfmeGarrisonOriginalTeamView *>(this)->m_originalTeam = 0;
		}

		reinterpret_cast<Object *>(reinterpret_cast<BfmeGarrisonOwnerLink *>(
			reinterpret_cast<unsigned char *>(this) - 0x18)->m_object)->setStatus(
			ObjectStatusMaskType(ObjectStatusMaskType::kInit, 1), false);
		*reinterpret_cast<Bool *>(reinterpret_cast<unsigned char *>(this) + 0x995) = false;

		BfmeObjectModelCondition *model =
			reinterpret_cast<BfmeObjectModelCondition *>(
				reinterpret_cast<BfmeGarrisonOwnerLink *>(
					reinterpret_cast<unsigned char *>(this) - 0x18)->m_object);
		if ((model->m_conditionFlags & 0x400) != 0)
		{
			model->m_conditionFlags &= ~0x400U;
			model->notifyModelConditionChanged();
		}
	}
	else
	{
		const UnsignedInt count = getContainCount(false);
		if (getStealthUnitsContained() != count)
			*reinterpret_cast<Bool *>(reinterpret_cast<unsigned char *>(this) + 0x995) = false;
	}

	const UnsignedInt frame = TheBfmeGameLogic->m_frame;
	const BfmeThingTemplateView *thingTemplate =
		reinterpret_cast<BfmeObjectTemplateLink *>(object)->m_template;
	if (thingTemplate != 0 && thingTemplate->m_override != 0)
		thingTemplate = reinterpret_cast<const BfmeThingTemplateView *>(
			thingTemplate->m_override->getFinalOverride());
	const UnsignedInt delay = reinterpret_cast<const BfmeObjectOverrideLayout *>(
		thingTemplate)->m_occlusionDelay;
	reinterpret_cast<BfmeObjectFrameView *>(object)->m_safeOcclusionFrame = frame + delay;

	recalcApparentControllingPlayer();

	if ((reinterpret_cast<Rva00221540 *>(
		reinterpret_cast<unsigned char *>(this) - 0x20)->isReady() & 0xff) != 0)
	{
		BfmeBodyModule *body = reinterpret_cast<BfmeObjectBodyLink *>(
			reinterpret_cast<unsigned char *>(reinterpret_cast<BfmeGarrisonOwnerLink *>(
			reinterpret_cast<unsigned char *>(this) - 0x18)->m_object))->m_body;
		if (body->getHealth() <= BfmeZeroRange)
			reinterpret_cast<GameLogic *>(TheBfmeGameLogic)->destroyObject(object);
	}
}
