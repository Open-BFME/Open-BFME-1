// cl: /DNDEBUG /MD /EHsc

// The three Object bodies that drive special powers and abilities:
//
//   bfmeStartAllSpecialPowerRecharges 0x001BE820  put every power on cooldown
//   bfmeAbortActiveSpecialAbilities   0x001BF7C0  stop every ability in progress
//   bfmeTriggerEatSpecialPower        0x001C49C0  fire SPECIAL_EAT at a target
//
// Two of the three walk m_behaviors at +0x1F0, and one of them did not model it
// as a member at all: it declared a whole second struct, BFMEObjectBehaviorsField,
// with a 0x1F0 pad, and reinterpret_cast `this` to it -- an Object with no fields
// standing beside a shadow Object that had one. There is one Object here and it
// names m_behaviors, m_position at +0x38 and m_disabledMask at +0x1A4, the last
// two from the third body.
//
// The behaviour interface at BehaviorModule+0x0C had two accounts, seven slots
// deep and twenty-five slots deep, because that is as far as each body reached.
// One declaration now names both slots it is known to have: 7 (+0x1C)
// getSpecialPower and 24 (+0x60) getSpecialPowerUpdateInterface. ObjectUpgrades.cpp
// names slot 9 (+0x24) getUpgrade on this same interface.
//
// What slot 7 returns had a third name again, BFMESpecialPowerRechargeShim, with
// one slot at +0x40. It is SpecialPowerModuleInterface -- the interface the eat
// body reaches by name and uses at slots 6 and 13 -- because ZH's
// BehaviorModuleInterface declares getSpecialPower with exactly that return type.
// One declaration, three named slots: 6 getSpecialPowerTemplate, 13
// doSpecialPowerAtLocation, 16 startPowerRecharge.
//
// Slot 24's return type stays separate: it is a different virtual with a
// different return type upstream, and the bytes here never bring the two
// together.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;
class BehaviorModule;
class SpecialPowerTemplate;
class CommandButton;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// The retail SpecialPower name table identifies 0x71 as SPECIAL_EAT.
enum SpecialPowerType
{
	SPECIAL_EAT = 0x71
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore
{
public:
	Bool canUseSpecialPower(Object *object,
		const SpecialPowerTemplate *specialPowerTemplate);
};

extern SpecialPowerStore *TheSpecialPowerStore;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	// slot 6, +0x18
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	// slot 13, +0x34
	virtual void doSpecialPowerAtLocation(const Coord3D *location,
		UnsignedInt commandOptions) = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	// slot 16, +0x40
	virtual void startPowerRecharge() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class BFMESpecialPowerUpdateInterface
{
public:
	virtual void slot00();
	// slot 1, +0x04
	virtual Bool isSpecialAbility() const;
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	// slot 6, +0x18
	virtual Bool isPowerCurrentlyInUse(const CommandButton *command) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	void bfmeAbortAbility();
};

// The interface every BehaviorModule carries at +0x0C, reached by that fixed
// displacement rather than by a cast the compiler knows about.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	// slot 7, +0x1C
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;
	virtual void bfmeSlot08() = 0;
	// slot 9, +0x24, is getUpgrade; see ObjectUpgrades.cpp.
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void bfmeSlot13() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	virtual void bfmeSlot16() = 0;
	virtual void bfmeSlot17() = 0;
	virtual void bfmeSlot18() = 0;
	virtual void bfmeSlot19() = 0;
	virtual void bfmeSlot20() = 0;
	virtual void bfmeSlot21() = 0;
	virtual void bfmeSlot22() = 0;
	virtual void bfmeSlot23() = 0;
	// slot 24, +0x60
	virtual BFMESpecialPowerUpdateInterface *getSpecialPowerUpdateInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeStartAllSpecialPowerRecharges() const;
	void bfmeAbortActiveSpecialAbilities() const;
	void bfmeTriggerEatSpecialPower(const Object *target);

	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate) const;

private:
	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;				// +0x038
	unsigned char m_unmodelled_044[0x1a4 - 0x44];
	UnsignedInt m_disabledMask;			// +0x1A4
	unsigned char m_unmodelled_1a8[0x1f0 - 0x1a8];
	BehaviorModule **m_behaviors;			// +0x1F0
};

// ?bfmeStartAllSpecialPowerRecharges@Object@@QBEXXZ
//
// The original method spelling is unrecovered. RespawnUpdate reaches this fan-out
// through the retail ILT before restoring spellbook powers.
void Object::bfmeStartAllSpecialPowerRecharges() const
{
	for (BehaviorModule *const *module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior =
			reinterpret_cast<BehaviorModuleInterface *>(
				reinterpret_cast<char *>(const_cast<BehaviorModule *>(*module)) + 0x0c);
		SpecialPowerModuleInterface *power = behavior->getSpecialPower();
		if (!power)
			continue;

		power->startPowerRecharge();
	}
}

// ?bfmeAbortActiveSpecialAbilities@Object@@QBEXXZ
//
// The update interface sits 0x20 bytes into its SpecialAbilityUpdate, and retail
// steps back to the owner and forward again rather than keeping both pointers.
void Object::bfmeAbortActiveSpecialAbilities() const
{
	for (BehaviorModule *const *module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior =
			reinterpret_cast<BehaviorModuleInterface *>(
				reinterpret_cast<char *>(const_cast<BehaviorModule *>(*module)) + 0x0c);
		BFMESpecialPowerUpdateInterface *specialPower =
			behavior->getSpecialPowerUpdateInterface();
		if (specialPower && specialPower->isSpecialAbility())
		{
			SpecialAbilityUpdate *update = reinterpret_cast<SpecialAbilityUpdate *>(
				reinterpret_cast<char *>(specialPower) - 0x20);
			specialPower = reinterpret_cast<BFMESpecialPowerUpdateInterface *>(
				reinterpret_cast<char *>(update) + 0x20);
			if (specialPower->isPowerCurrentlyInUse(0))
				update->bfmeAbortAbility();
		}
	}
}

// ?bfmeTriggerEatSpecialPower@Object@@QAEXPBV1@@Z
//
// The sole caller is AIUpdateInterface code and passes the AI's Object as the
// argument, which is why the command source is CMD_FROM_AI.
void Object::bfmeTriggerEatSpecialPower(const Object *target)
{
	SpecialPowerModuleInterface *typeModule =
		findSpecialPowerModuleInterface(SPECIAL_EAT);
	if (typeModule == 0)
		return;

	const SpecialPowerTemplate *specialPowerTemplate =
		typeModule->getSpecialPowerTemplate();
	if (m_disabledMask != 0)
		return;

	if (!TheSpecialPowerStore->canUseSpecialPower(this, specialPowerTemplate))
		return;

	SpecialPowerModuleInterface *module =
		getSpecialPowerModule(specialPowerTemplate);
	if (module != 0)
		module->doSpecialPowerAtLocation(&target->m_position, CMD_FROM_AI);
}
