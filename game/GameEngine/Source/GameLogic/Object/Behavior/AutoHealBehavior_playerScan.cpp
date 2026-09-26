// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME's player-wide auto-heal scan uses a 24-byte kind-of mask and three
// policy bytes at scan-data offsets 0x20..0x22, unlike the Zero Hour callback.
// Keep the predicate in this translation unit: VC7.1 passes its scan data in
// EAX and candidate in EBX instead of using a public calling convention.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;
class Player;

template <int N>
class BitFlags
{
public:
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
	Bool isOffMap() const { return (reinterpret_cast<const unsigned char *>(&m_status)[0] & 8) != 0; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad000[0x200];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x344 - 0x208];
	UnsignedInt m_status;
};

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

typedef _STL::list<Object *> ObjectPointerList;

struct AutoHealPlayerScanHelper
{
	BitFlags<69> m_kindOfToTest;
	Object *m_theHealer;
	ObjectPointerList *m_objectList;
	Bool m_bfmeFlag20;
	Bool m_bfmeFlag21;
	Bool m_skipSelfForHealing;
};

// ?rva001EE670EligibleForAutoHeal@@YA_NPBUAutoHealPlayerScanHelper@@PAVObject@@@Z
static Bool rva001EE670EligibleForAutoHeal(
	const AutoHealPlayerScanHelper *helper, Object *testObj)
{
	if (helper->m_skipSelfForHealing && testObj == helper->m_theHealer)
		return false;

	if (helper->m_theHealer)
	{
		if (helper->m_bfmeFlag21)
		{
			AIUpdateInterface *ai = helper->m_theHealer->getAIUpdateInterface();
			if (ai && ai->getCurrentVictim())
				return false;
		}

		if (helper->m_bfmeFlag20)
		{
			Object *healer = helper->m_theHealer;
			BodyModuleInterface *body = healer->getBodyModule();
			UnsignedInt frame = TheGameLogic->m_frame;
			if (body->getLastDamageTimestamp() < frame)
			{
				Object *laterHealer = helper->m_theHealer;
				BodyModuleInterface *laterBody = laterHealer->getBodyModule();
				UnsignedInt laterFrame = TheGameLogic->m_frame;
				if (laterBody->getLastDamageTimestamp() + 5 > laterFrame)
					return false;
			}
		}
	}

	if (testObj->isEffectivelyDead())
		return false;

	Player *owner = helper->m_theHealer->getControllingPlayer();
	if (testObj->getControllingPlayer() != owner)
		return false;

	if (testObj->isOffMap())
		return false;
	if (!testObj->isAnyKindOf(helper->m_kindOfToTest))
		return false;

	BodyModuleInterface *body = testObj->getBodyModule();
	Real health = body->getHealth();
	if (body->getMaxHealth() <= health)
		return false;
	return true;
}

// ?checkForAutoHeal@@YAHPAVObject@@PAX@Z present-unmatched
int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (rva001EE670EligibleForAutoHeal(helper, testObj))
		helper->m_objectList->push_back(testObj);
	return 1;
}
