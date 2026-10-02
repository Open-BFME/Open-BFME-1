// cl: /DNDEBUG /MD
//
// SpecialPowerModule::doSpecialPower, retail RVA 0x0026A550.
//
// This is the SpecialPowerModule base implementation, shared by every concrete
// special power: the same body sits in slot 11 of the
// SpecialPowerModuleInterface vftable of CashHack, Defector, Darkness,
// ElvenWood, Scavenger, Stop and the rest, each stored at object offset +0x10
// by that power's constructor.  `this` is therefore the interface sub-object;
// -0x10 reaches the Module base, where +4 is the module data and +8 the object.
//
// The shape is upstream's SpecialPowerModule::doSpecialPower
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// Object/SpecialPower/SpecialPowerModule.cpp:664) instruction for
// instruction: bail while m_pausedCount is positive or the object is disabled,
// tell the update modules the intent, and trigger immediately unless the module
// data says the update module starts the attack.  finishSpecialPower is that
// upstream triggerSpecialPower.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class Object;
class Coord3D;
class Waypoint;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
};

// The Module part ahead of the interface sub-object: vptr, module data at
// +4, Object at +8.
class SpecialPowerModuleBaseView
{
public:
	virtual void baseSlot00();

	unsigned char *m_moduleData;
	void **m_object;
	char m_pad0C[4];
};

class SpecialPowerModule : public SpecialPowerModuleBaseView, public SpecialPowerModuleInterface
{
public:
	Bool initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions);
	void finishSpecialPower(UnsignedInt arg);
	virtual void doSpecialPower(UnsignedInt commandOptions);

private:
	char m_pad14[4];
	Int m_pausedCount;
};

void SpecialPowerModule::doSpecialPower(UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_pausedCount > 0)
			return;
		if (m_object[0x1a4 / 4] != 0)
			return;
	}
	initiateIntentToDoSpecialPower(0, 0, (const Waypoint *)commandOptions, 0);
	if (m_moduleData[0xc] == 0)
		finishSpecialPower(0);
}
