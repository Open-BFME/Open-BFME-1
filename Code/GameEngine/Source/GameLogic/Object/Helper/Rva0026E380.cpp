// cl: /DNDEBUG /MD
// stlport
// Address-qualified reconstruction of retail body 0x0026E380 (173 bytes).
// Caller evidence identifies no semantic owner class for this body.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
class Weapon;
enum WeaponSlotType;

template <Int NUMBITS>
class Rva0026E380BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }
	void reset(Int bit) { m_bits.reset(bit); }
private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef Rva0026E380BitFlags<320> Rva0026E380ModelConditionFlags;
typedef char Rva0026E380ModelConditionFlagsSize[
	(sizeof(Rva0026E380ModelConditionFlags) == 40) ? 1 : -1];

#define BFME_HAVE_MODELCONDITIONFLAGS
typedef Rva0026E380ModelConditionFlags ModelConditionFlags;
#define OBJECT_TU_MEMBERS \
	void notifyModelConditionChanged(); \
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
#include "../object.h"

class Rva0026E380AI
{
public:
	void *m_opaque;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

// ILT 0x0002EDCF (body 0x001535A0): AI command interface, (Object*, int, int).
enum CommandSourceType;
class AICommandInterface
{
public:
	void aiAttackObject(Object *target, Int arg1, CommandSourceType source);
};
// Existing caller-verified ABI adapter for ILT 0x000122AB.
class Gen001C9AC0
{
public:
	void handle(Int value);
};

class Rva001BEF20FieldAddress
{
public:
	char *get();
};

class Rva0026E380Owner
{
public:
	void rva0026E380OwnerHelper();
	void update();
	UnsignedByte m_pad00[0x8];
	Object *m_owner;				// +0x08
	UnsignedByte m_pad0C[0xAC - 0x0C];
	Int m_targetID;				// +0xAC
	UnsignedByte m_padB0[0xE8 - 0xB0];
	UnsignedByte m_flagE8;
};

void Rva0026E380Owner::update()
{
	m_flagE8 = 1;
	rva0026E380OwnerHelper();
	Object *owner = m_owner;
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	if (target == 0 || (*(UnsignedByte *)((char *)target + 0x344) & 1) != 0)
		return;

	Rva0026E380AI *ai = (Rva0026E380AI *)owner->m_ai;
	if (ai == 0)
		return;

	if (!owner->m_modelConditionFlags.test(196))
	{
		owner->m_modelConditionFlags.set(196);
		owner->notifyModelConditionChanged();
	}
	void *weapon = owner->getCurrentWeapon(0);
	if (weapon != 0)
	{
		const char *weaponFlags = ((Rva001BEF20FieldAddress *)owner)->get();
		if ((*weaponFlags & 0x80) != 0)
		{
			((Gen001C9AC0 *)owner)->handle(7);
			if (owner->m_modelConditionFlags.test(150))
			{
				owner->m_modelConditionFlags.reset(150);
				owner->notifyModelConditionChanged();
			}
		}
	}
	((AICommandInterface *)((char *)ai + 0x20))->aiAttackObject(target, 1, (CommandSourceType)2);
}
