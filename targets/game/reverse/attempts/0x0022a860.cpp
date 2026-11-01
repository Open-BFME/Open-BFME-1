// ?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z
// partial score=0.5318 date=2026-11-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
// partial: 738/739 B, 344 non-reloc diffs, shape 0.968 (register permutation obj/rider/i); see attempt_support/0022a860-riderchangecontain-oncontaining-20261101.md
// stlport

// Open-BFME: RiderChangeContain::onContaining, retail 0x0022A860 (739 bytes,
// ret 8 at +0x2E0).  Vtable 0x010AC870 slot 17 identifies it (earlier
// verdicts).  The receiver is the contain interface at +0x20, so the owning
// object is this-0x18 and the module data this-0x1C.
//
// Structure follows the Open BFME 2 donor (45afcff3) Code/GameEngine/Source/
// GameLogic/Object/Contain/RiderChangeContainOnContaining.cpp (its retail
// 0x0047E5D4): a non-allied rider goes straight to the base onContaining;
// otherwise mark containing, move a selected rider's selection to the
// container, find the rider among the eight RiderInfo slots (BFME 1: +0x24C,
// 0x18 apart) and apply its model condition, weapon set flag, status,
// command set and locomotor set, give the rider status 39, mark a stealthed
// container as detected, hand the experience over, then chain to the base.
// BFME 1 offsets come from the retail body; callee names are the ledger's.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "Common/AsciiString.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef UnsignedInt ObjectID;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

enum
{
	MAX_RIDERS = 8
};

template <int N> class Rva0022A860Slots : public Rva0022A860Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva0022A860Slots<0>
{
};

template <int NUMBITS> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };

	BitFlags() { }
	BitFlags(BogusInitType, Int bit) { m_bits.set(bit); }
	void set(Int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<86> ObjectStatusMaskType;

class ModelConditionFlags
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}

private:
	UnsignedInt m_words[10];
};

class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;				// +0x04
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *tmplate) const;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
class ThingFactory;
extern ThingFactory *TheThingFactory;

class Drawable
{
public:
	Bool isSelected() const { return m_selected; }

private:
	char m_pad000[0x3ac];
	Bool m_selected;							// +0x3AC
};

class GameMessage
{
public:
	void appendBooleanArgument(Bool arg);
	void appendObjectIDArgument(ObjectID id);
};

class MessageStream : public Rva0022A860Slots<13>
{
public:
	virtual GameMessage *appendMessage(Int type);	// +0x34
};
extern MessageStream *TheMessageStream;

class InGameUI : public Rva0022A860Slots<56>
{
public:
	virtual void selectDrawable(Drawable *draw);	// +0xE0
	virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72();
	virtual void s73(); virtual void s74(); virtual void s75(); virtual void s76();
	virtual void s77(); virtual void s78(); virtual void s79(); virtual void s80();
	virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84();
	virtual void s85(); virtual void s86(); virtual void s87(); virtual void s88();
	virtual void s89(); virtual void s90(); virtual void s91(); virtual void s92();
	virtual void setDisplayedMaxWarning(Bool show);	// +0x174
};
extern InGameUI *TheInGameUI;

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }

private:
	char m_pad00[0x24];
	Bool m_UIDirty;								// +0x24
};
extern ControlBar *TheControlBar;

class AIUpdateInterface : public Rva0022A860Slots<127>
{
public:
	virtual void chooseLocomotorSet(Int set);	// +0x1FC
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

class StealthUpdate
{
public:
	void markAsDetected(UnsignedInt numFrames, Bool forceFriendly);
};

class Rva001B2040
{
public:
	void copyFields(void *from);
};

class ExperienceTracker
{
public:
	void setExperienceAndLevel(Real experience, Bool provideFeedback);
};

class Gen001C9A10
{
public:
	void handle(Int weaponSetFlag);
};

class Object;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

class Object : public Rva0022A860Slots<10>
{
	friend class RiderChangeContain;
public:
	virtual Drawable *getDrawable() const;		// +0x28

	Relationship getRelationship(const Object *that) const;
	void notifyModelConditionChanged();
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);

	const ThingTemplate *getTemplate() const
	{
		const Overridable *t = m_template;
		if (t)
			t = t->getFinalOverride();
		return (const ThingTemplate *)t;
	}
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }

	__forceinline void setModelConditionState(UnsignedInt mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			notifyModelConditionChanged();
		}
	}
	void setWeaponSetFlag(Int wst) { ((Gen001C9A10 *)this)->handle(wst); }
	void setCommandSetStringOverride(AsciiString newCommandSet)
	{
		m_commandSetStringOverride = newCommandSet;
	}

protected:
	Module *findModule(NameKeyType key) const;

private:
	const ThingTemplate *m_template;			// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;								// +0x74
	char m_pad078[0x110 - 0x78];
	ModelConditionFlags m_modelConditionFlags;	// +0x110
	char m_pad138[0x204 - 0x138];
	AIUpdateInterface *m_ai;					// +0x204
	char m_pad208[0x210 - 0x208];
	ExperienceTracker *m_experienceTracker;		// +0x210
	char m_pad214[0x328 - 0x214];
	AsciiString m_commandSetStringOverride;		// +0x328
};

struct RiderInfo
{
	AsciiString m_templateName;					// +0x00
	Int m_weaponSetFlag;						// +0x04
	Int m_modelConditionFlagType;				// +0x08
	Int m_objectStatusType;						// +0x0C
	AsciiString m_commandSet;					// +0x10
	Int m_locomotorSetType;						// +0x14
};

class RiderChangeContainModuleData
{
public:
	char m_pad000[0x24c];
	RiderInfo m_riders[MAX_RIDERS];				// +0x24C
};

class Rva0022A860Module
{
public:
	virtual void s00();

protected:
	const RiderChangeContainModuleData *m_moduleData;	// +0x04
	Object *m_object;							// +0x08
	char m_pad0C[0x20 - 0x0C];
};

// Contain interface entered at +0x20; the base onContaining at 0x0022B3E0
// is rowed under SiegeEngineContain with the same receiver.
class SiegeEngineContain : public Rva0022A860Slots<17>
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected);
};

class RiderChangeContain : public Rva0022A860Module, public SiegeEngineContain
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected);

private:
	Object *getObject() const { return m_object; }
	const RiderChangeContainModuleData *getRiderChangeContainModuleData() const { return m_moduleData; }

	char m_pad24[0x10c - 0x24];
	Bool m_containing;							// +0x10C
};

// ?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z
void RiderChangeContain::onContaining(Object *rider, Bool wasSelected)
{
	Object *obj = getObject();
	if (obj->getRelationship(rider) != ALLIES)
	{
		SiegeEngineContain::onContaining(rider, wasSelected);
		return;
	}

	m_containing = true;

	Drawable *containDraw = getObject()->getDrawable();
	if (containDraw && wasSelected && !containDraw->isSelected())
	{
		GameMessage *teamMsg = TheMessageStream->appendMessage(0x3E9);
		teamMsg->appendBooleanArgument(false);
		teamMsg->appendObjectIDArgument(getObject()->getID());
		TheInGameUI->selectDrawable(containDraw);
		TheInGameUI->setDisplayedMaxWarning(false);
	}

	const RiderChangeContainModuleData *data = getRiderChangeContainModuleData();
	for (Int i = 0; i < MAX_RIDERS; i++)
	{
		const ThingTemplate *thing = ((BfmeThingFactory *)TheThingFactory)->findTemplate(data->m_riders[i].m_templateName);
		if (thing->isEquivalentTo(rider->getTemplate()))
		{
			getObject()->setModelConditionState(data->m_riders[i].m_modelConditionFlagType);
			obj->setWeaponSetFlag(data->m_riders[i].m_weaponSetFlag);
			obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, data->m_riders[i].m_objectStatusType), true);
			rider->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 39), true);
			obj->setCommandSetStringOverride(data->m_riders[i].m_commandSet);
			TheControlBar->markUIDirty();

			AIUpdateInterface *ai = obj->getAI();
			if (ai)
				ai->chooseLocomotorSet(data->m_riders[i].m_locomotorSetType);

			if (((BFMEObjectStealthQuery *)obj)->isStealthedAndUndetected(0))
			{
				static const NameKeyType key = TheNameKeyGenerator->nameToKey("StealthUpdate");
				StealthUpdate *stealth = (StealthUpdate *)obj->findModule(key);
				if (stealth)
					stealth->markAsDetected(0, true);
			}

			ExperienceTracker *bikeTracker = obj->m_experienceTracker;
			ExperienceTracker *riderTracker = rider->m_experienceTracker;
			((Rva001B2040 *)bikeTracker)->copyFields(rider);
			riderTracker->setExperienceAndLevel(0.0f, true);
			break;
		}
	}

	SiegeEngineContain::onContaining(rider, wasSelected);
	m_containing = false;
}
