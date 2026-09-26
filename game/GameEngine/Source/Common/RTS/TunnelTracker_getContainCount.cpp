// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TunnelTracker::getContainCount, retail 0x000F8810, 67 bytes. The
// body carried only a machine byte-dump row; the name comes from the ILT pin
// in targets/game/reverse/symbols.csv.
//
// The mangled name says the argument is an Int, and the ledger's note on that
// pin records why: BFME gives the function an argument the reference build does
// not have, and CaveSystem::canSwitchIndexToIndex passes zero at both of its
// call sites. Zero is the fast path here -- the cached count at +0x10 goes
// straight back. Anything else is a filter, which the body immediately uses as
// a this pointer, so the source has to cast the Int back.
//
// The list of contained objects hangs off the sentinel pointer at +8, the same
// shape the id list at +4 has in onTunnelCreated: twelve-byte nodes with next
// at +0 and the value at +8. end() is re-read from the member on every trip
// because the filter call could have moved it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Object;
class Player;

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);	// retail 0x003A04A0
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;			// +0x00
	BfmeListNodeBase *m_bfmePrev;			// +0x04
};

struct BfmeObjectNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;				// +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	UnsignedInt getContainCount(Int filterArg);
	static void healObject(Object *obj, void *frames);

private:
	unsigned char m_bfmeHead[0x08 - 0x00];
	BfmeListNodeBase *m_bfmeContainList;		// +0x08, the list's sentinel
	unsigned char m_bfmeGap[0x10 - 0x0C];
	UnsignedInt m_bfmeContainCount;			// +0x10
};

// ?getContainCount@TunnelTracker@@QAEIH@Z
UnsignedInt TunnelTracker::getContainCount(Int filterArg)
{
	Rva2225E0Filter *filter = (Rva2225E0Filter *)filterArg;

	if (!filter)
		return m_bfmeContainCount;

	UnsignedInt count = 0;

	for (BfmeListNodeBase *it = m_bfmeContainList->m_bfmeNext;
			it != m_bfmeContainList;
			it = it->m_bfmeNext)
	{
		if (filter->accepts(((BfmeObjectNode *)it)->m_bfmeValue, 0))
			++count;
	}

	return count;
}

enum DamageType { DAMAGE_HEALING = 7 };
enum DeathType { DEATH_NORMAL = 0, DEATH_NONE = 1 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameLogic/Damage.h
struct DamageInfoInput
{
	char m_bfme_head[0x10];
	DamageType m_damageType;
	char m_bfme_pad[0x18 - 0x14];
	DeathType m_deathType;
	Real m_amount;
};

struct DamageInfo
{
	DamageInfo();
	DamageInfoInput in;
	char m_bfme_tail[0x5C - 0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot0() = 0;
	virtual void attemptHealing(DamageInfo *damageInfo) = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual Real getMaxHealth(void) const = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameLogic/Object.h
class Object
{
public:
	BodyModuleInterface *getBodyModule(void) const { return m_body; }
	UnsignedInt getContainedByFrame(void) const { return m_containedByFrame; }

private:
	char m_slice_padA[0x200];
	BodyModuleInterface *m_body;
	char m_slice_padB[0x21C - 0x204];
	UnsignedInt m_containedByFrame;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_slice_pad[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

void TunnelTracker::healObject( Object *obj, void *frames)
{

	//get the number of frames to heal
	Real *framesForFullHeal = (Real *)frames;

	// setup the healing damageInfo structure with all but the amount
	DamageInfo healInfo;
	healInfo.in.m_damageType = DAMAGE_HEALING;
	healInfo.in.m_deathType = DEATH_NONE;

	// get body module of the thing to heal
	BodyModuleInterface *body = obj->getBodyModule();

	// if we've been in here long enough ... set our health to max
	if( TheGameLogic->getFrame() - obj->getContainedByFrame() >= *framesForFullHeal )
	{

		// set the amount to max just to be sure we're at the top
		healInfo.in.m_amount = body->getMaxHealth();

		// set max health
		body->attemptHealing( &healInfo );

	}  // end if
	else
	{
		//
		// given the *whole* time it would take to heal this object, lets pretend that the
		// object is at zero health ... and give it a sliver of health as if it were at 0 health
		// and would be fully healed at 'framesForFullHeal'
		//
		healInfo.in.m_amount = body->getMaxHealth() / *framesForFullHeal;

		// do the healing
		body->attemptHealing( &healInfo );

	}  // end else
}
