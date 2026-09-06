// cl: /DNDEBUG /MD
//
// SpecialPowerModuleInterface::doSpecialPower, retail RVA 0x0026A550.
//
// This is the SpecialPowerModule base implementation, shared by every concrete
// special power: the same body sits in slot 11 of the
// SpecialPowerModuleInterface vftable of CashHack, Defector, Darkness,
// ElvenWood, Scavenger, Stop and the rest, each stored at object offset +0x10
// by that power's constructor.  `this` is therefore the interface sub-object;
// -0x10 reaches the Module base, where +4 is the module data and +8 the object.
//
// The shape is upstream's SpecialPowerModule::doSpecialPower
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
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

class SpecialPowerModule
{
public:
	Bool initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions);
	void finishSpecialPower(UnsignedInt arg);
};

class SpecialPowerModuleInterface
{
public:
	void doSpecialPower(UnsignedInt commandOptions);

private:
	char m_pad00[8];
	Int m_pausedCount;
};

struct SpecialPowerModuleBase
{
	char m_pad00[4];
	unsigned char *m_moduleData;
	void **m_object;
	char m_pad0C[4];
	SpecialPowerModuleInterface m_interface;
};

static SpecialPowerModuleBase *specialPowerModuleBase(SpecialPowerModuleInterface *self)
{
	return (SpecialPowerModuleBase *)((char *)self - 0x10);
}

void SpecialPowerModuleInterface::doSpecialPower(UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_pausedCount > 0)
			return;
		if (specialPowerModuleBase(this)->m_object[0x1a4 / 4] != 0)
			return;
	}
	SpecialPowerModule *mod = (SpecialPowerModule *)specialPowerModuleBase(this);
	mod->initiateIntentToDoSpecialPower(0, 0, (const Waypoint *)commandOptions, 0);
	if (specialPowerModuleBase(this)->m_moduleData[0xc] == 0)
		mod->finishSpecialPower(0);
}
