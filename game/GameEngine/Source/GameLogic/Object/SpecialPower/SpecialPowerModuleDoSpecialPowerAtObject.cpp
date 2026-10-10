// cl: /DNDEBUG /MD
//
// SpecialPowerModule::doSpecialPowerAtObject, retail RVA 0x0026A5B0.
//
// This is the SpecialPowerModule base implementation, shared by every concrete
// special power: the same body sits in slot 12 of the
// SpecialPowerModuleInterface vftable of CashHack, Defector, Darkness,
// ElvenWood, Scavenger, Stop and the rest, each stored at object offset +0x10
// by that power's constructor, and in SpecialPowerModule's own table 0x010B7B00
// (registered constructor 0x002693E0). It is SpecialPowerModule's override of
// the interface's slot 12, which Object::doSpecialPowerAtObject (0x001C37F0)
// calls as doSpecialPowerAtObject. `this` is the interface sub-object; -0x10
// reaches the Module base, where +4 is the module data and +8 the object.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
//
// The shape is upstream's SpecialPowerModule::doSpecialPowerAtObject
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// Object/SpecialPower/SpecialPowerModule.cpp:686) instruction for
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
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions) = 0;
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
	virtual void doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions);

private:
	char m_pad14[4];
	Int m_pausedCount;
};

extern "C" void __cdecl __identifier("?j_000361ab@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000251ad@@YAXXZ")();

void SpecialPowerModule::doSpecialPowerAtObject(Object *target, UnsignedInt commandOptions)
{
	union { void (*raw)(); void (SpecialPowerModuleBaseView::*member)(
		const Object *, const Coord3D *, UnsignedInt, UnsignedInt); }
		intent = { __identifier("?j_000361ab@@YAXXZ") };
	union { void (*raw)(); void (SpecialPowerModuleBaseView::*member)(UnsignedInt); }
		finish = { __identifier("?j_000251ad@@YAXXZ") };
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_pausedCount > 0)
			return;
		if (m_object[0x1a4 / 4] != 0)
			return;
	}
	SpecialPowerModuleBaseView *mod = this;
	(mod->*intent.member)(target, 0, commandOptions, 0);
	if (m_moduleData[0xc] == 0)
		(mod->*finish.member)((UnsignedInt)target + 0x38);
}
