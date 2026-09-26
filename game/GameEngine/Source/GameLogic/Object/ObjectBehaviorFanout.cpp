// cl: /DNDEBUG /MD /EHsc

// The two Object bodies that fan out over m_behaviors and call the module
// interface DIRECTLY, through its multiple-inheritance base:
//
//   onLevelStart       0x001BF0A0  slot 39, then the drawable's own onLevelStart
//   bfmeWakeAutoPickup 0x001BFEF0  slot 26, then the interface it hands back
//
// Both files described BehaviorModule the same way -- an ObjectModule of a vptr
// and two dwords, then BehaviorModuleInterface, which puts the interface at
// +0x0C -- and both described BehaviorModuleInterface only as deep as the one
// slot they used: 39 slots in one, 26 in the other. One declaration here names
// both, slot 26 getAutoPickUpUpdateInterface and slot 39 onLevelStart.
//
// This is the same interface ObjectSpecialPowers.cpp and ObjectUpgrades.cpp
// reach, and those two get to it by casting a BehaviorModule* forward 0x0C
// rather than by inheritance. The two spellings compile to the same
// displacement; between the four files the interface now has slots 7, 9, 24, 26
// and 39 named, which no one of them could have said.
//
// The Object accounts differed on whether Object has a vtable at all: the
// onLevelStart file gave it eleven slots to reach getDrawable at slot 10, the
// other started its members at offset 0. Both land m_behaviors at +0x1F0, but
// only one of them can be retail's, and it is the one with the vptr -- retail
// dispatches getDrawable through it. Pads here are measured from +0x04.

typedef int Int;

class Dict;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void onLevelStart();
};

// Retail command dispatch index 47 is MSG_WAKE_AUTO_PICKUP. Callers pass button
// numbers 1, 2 or 3, and a module wakes only when its own number agrees.
class AutoPickUpUpdateInterface
{
public:
	virtual Int getRunFromButtonNumber() const = 0;
	virtual void autoPickUpSlot1() = 0;
	virtual void wakeUp() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	// slot 7, +0x1C, is getSpecialPower; see ObjectSpecialPowers.cpp.
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	// slot 9, +0x24, is getUpgrade; see ObjectUpgrades.cpp.
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	// slot 24, +0x60, is getSpecialPowerUpdateInterface; see ObjectSpecialPowers.cpp.
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	// slot 26, +0x68
	virtual AutoPickUpUpdateInterface *getAutoPickUpUpdateInterface() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	// slot 39, +0x9C
	virtual void onLevelStart(Dict *properties) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

private:
	unsigned int m_data[2];
};

// The second base lands at +0x0C, which is the displacement the sibling TUs cast
// to by hand.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void objectSlot00() = 0;
	virtual void objectSlot01() = 0;
	virtual void objectSlot02() = 0;
	virtual void objectSlot03() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot05() = 0;
	virtual void objectSlot06() = 0;
	virtual void objectSlot07() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot09() = 0;
	// slot 10, +0x28
	virtual Drawable *getDrawable() const = 0;

	void onLevelStart(Dict *properties);
	void bfmeWakeAutoPickup(Int runFromButtonNumber);

private:
	unsigned char m_unmodelled_004[0x1f0 - 4];
	BehaviorModule **m_behaviors;			// +0x1F0
};

// ?onLevelStart@Object@@QAEXPAVDict@@@Z
void Object::onLevelStart(Dict *properties)
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
		(*module)->onLevelStart(properties);

	Drawable *drawable = getDrawable();
	if (drawable)
		drawable->onLevelStart();
}

// ?bfmeWakeAutoPickup@Object@@QAEXH@Z
//
// The bfme prefix records that the exact retail spelling of this helper is not
// present in the image.
void Object::bfmeWakeAutoPickup(Int runFromButtonNumber)
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		AutoPickUpUpdateInterface *autoPickUp = (*module)->getAutoPickUpUpdateInterface();
		if (autoPickUp && autoPickUp->getRunFromButtonNumber() == runFromButtonNumber)
			autoPickUp->wakeUp();
	}
}
