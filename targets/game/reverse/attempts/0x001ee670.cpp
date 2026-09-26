// ?rva001EE670EligibleForAutoHeal@@YA_NPAVObject@@PBUAutoHealPlayerScanHelper@@@Z
// partial score=0.24 date=2026-09-26
// Retail 0x001EE670, 223 bytes. Private same-TU helper of checkForAutoHeal:
// the callback passes its scan-data pointer in EAX and the candidate Object in
// EBX, without stack arguments. Compile this together with 0x001eed80.cpp;
// that TU includes this file before defining the callback. This is a C++
// candidate, not a byte-match claim.
// Source: GameLogic/Object/Behavior/AutoHealBehavior.cpp, whose vendored
// callback supplies the kind-of, ownership and health checks. The retail
// function has three additional byte flags at helper+0x20..0x22; it does NOT
// test the vendored m_forbiddenKindOf mask.
// Probe through 0x001eed80.cpp: 226/223 bytes, 198 non-relocation byte
// differences, five relocation-layout mismatches. The missing lever is the
// compiler-private EAX/EBX argument convention, not an extra stack parameter.

#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;
class Player;

template <int N>
struct BitFlags
{
	UnsignedInt m_bits[6];
};

class Thing
{
public:
	Bool isAnyKindOf(const BitFlags<69> &mask) const;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

// BFME BodyModuleInterface slots +0x10/+0x18/+0x40, independently witnessed
// by ObjectDamageAndWeapons.cpp and AutoHealBehavior_pulseHealObject.cpp.
class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Bool isEffectivelyDead() const { return (m_status & 1) != 0; }
	Bool isOffMap() const { return (m_status & 8) != 0; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad000[0x200];
	BodyModuleInterface *m_body;             // +0x200
	AIUpdateInterface *m_ai;                 // +0x204
	unsigned char m_pad208[0x344 - 0x208];
	UnsignedInt m_status;                    // +0x344, dead/off-map bits
};

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

typedef _STL::list<Object *> ObjectPointerList;

// The retail caller copies 24 bytes of kind-of mask into +0x00 and places its
// healer, list and three module-data bools at +0x18/+0x1C/+0x20..+0x22.
struct AutoHealPlayerScanHelper
{
	BitFlags<69> m_kindOfToTest;
	Object *m_theHealer;
	ObjectPointerList *m_objectList;
	Bool m_bfmeFlag20; // healer not recently damaged (within five logic frames)
	Bool m_bfmeFlag21; // healer AI must have no current victim
	Bool m_skipSelfForHealing;
};

static Bool rva001EE670EligibleForAutoHeal(
	Object *testObj, const AutoHealPlayerScanHelper *helper)
{
	if (helper->m_skipSelfForHealing && testObj == helper->m_theHealer)
		return false;

	Object *healer = helper->m_theHealer;
	if (healer)
	{
		if (helper->m_bfmeFlag21)
		{
			AIUpdateInterface *ai = healer->getAIUpdateInterface();
			if (ai && ai->getCurrentVictim())
				return false;
		}

		if (helper->m_bfmeFlag20)
		{
			BodyModuleInterface *body = healer->getBodyModule();
			UnsignedInt frame = TheGameLogic->m_frame;
			if (body->getLastDamageTimestamp() < frame &&
				body->getLastDamageTimestamp() + 5 > frame)
				return false;
		}
	}

	if (testObj->isEffectivelyDead())
		return false;

	Player *owner = healer->getControllingPlayer();
	if (testObj->getControllingPlayer() != owner)
		return false;

	if (testObj->isOffMap())
		return false;
	if (!testObj->isAnyKindOf(helper->m_kindOfToTest))
		return false;

	BodyModuleInterface *body = testObj->getBodyModule();
	return body->getHealth() < body->getMaxHealth();
}
