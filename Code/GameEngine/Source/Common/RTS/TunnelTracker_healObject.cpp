// cl: /DNDEBUG /MD /EHsc
// readable body of ?healObject@TunnelTracker@@: Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp
// Open-BFME: TunnelTracker::healObject, retail 0x000F8640, 144 bytes.
//
// The reference's body unchanged: fill in a healing DamageInfo, then either
// top the object up outright once it has been inside long enough, or give it
// the sliver of health that a full heal spread over framesForFullHeal comes
// to.
//
// Two BFME numbers show. DAMAGE_HEALING is 7 rather than the reference's 10,
// so the damage-type list lost three entries ahead of it; DEATH_NONE is still
// 1. And the frame difference is unsigned -- the `fild` carries the 2^32 fixup
// for a negative dword -- so both frame accessors return UnsignedInt.
//
// The rest is offsets. The DamageInfo is the frame's whole 0x5C-byte local
// block, with the damage type at +0x10, the death type at +0x18 and the amount
// at +0x1C; the object's body module is at +0x200 and the frame it was
// contained on at +0x21C; and the body module's attemptHealing and
// getMaxHealth are vtable+0x04 and +0x18.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum DamageType { DAMAGE_HEALING = 7 };			// BFME's numbering, not the reference's 10
enum DeathType { DEATH_NORMAL = 0, DEATH_NONE = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfoInput
{
	char m_bfme_head[0x10];				// in+0x00 .. +0x0F, untouched
	DamageType m_damageType;			// in+0x10
	char m_bfme_pad[0x18 - 0x14];			// in+0x14, untouched
	DeathType m_deathType;				// in+0x18
	Real m_amount;					// in+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	DamageInfo();					// ILT 0x0002C9D5

	DamageInfoInput in;
	char m_bfme_tail[0x5C - 0x20];			// sizeof(DamageInfo) is the whole frame
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot0() = 0;
	virtual void attemptHealing(DamageInfo *damageInfo) = 0;	// slot 1, vtable+0x04
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual Real getMaxHealth(void) const = 0;			// slot 6, vtable+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BodyModuleInterface *getBodyModule(void) const { return m_body; }
	UnsignedInt getContainedByFrame(void) const { return m_containedByFrame; }

private:
	char m_slice_padA[0x200];			// retail this+0x00 .. +0x1FF, untouched
	BodyModuleInterface *m_body;			// this+0x200
	char m_slice_padB[0x21C - 0x204];		// this+0x204 .. +0x21B, untouched
	UnsignedInt m_containedByFrame;			// this+0x21C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_slice_pad[0x3C];				// retail this+0x00 .. +0x3B, untouched
	UnsignedInt m_frame;				// this+0x3C
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	static void healObject(Object *obj, void *frames);
};

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
