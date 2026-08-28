// cl: /DNDEBUG /MD /EHsc

// DominateEnemySpecialPower's constructor, retail 0x0025ACF0.
//
// Despite the name it does not derive from SpecialPowerModule: the base it
// forwards to is 0x002A6360, which the ledger already carries as
// SpecialAbilityUpdate's constructor. The five *SpecialPower constructors
// landed alongside all reach 0x00011E50 instead.
//
// The store at +0x20 is a MEMBER with a vftable, not a fourth base: retail
// writes it after all three base pointers, which is member-construction order.
// A fourth base is written first and misses by the ordering.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void specialAbilityUpdateInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public BehaviorModule,
	public SpecialAbilityUpdateInterface,
	public ModuleInterface
{
public:
	SpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );

private:
	// Twelve bytes of state that only this derived class pins down: the fourth
	// vftable pointer lands at +0x20, and the three module bases alone reach
	// only +0x14.
	unsigned char m_unmodelled_14[ 0x0C ];
};

// The store at +0x20 is a MEMBER with a vftable, not a fourth base: retail
// writes it after all three base pointers, which is member-construction order.
// A fourth base is written first instead, and misses.
class DominateEnemySpecialPowerHelper
{
public:
	DominateEnemySpecialPowerHelper() {}

	virtual void dominateEnemySpecialPowerHelperAnchor();
};

class DominateEnemySpecialPower : public SpecialAbilityUpdate
{
public:
	DominateEnemySpecialPower( Thing *thing, const ModuleData *moduleData );

private:
	DominateEnemySpecialPowerHelper m_helper;		// +0x20
};

DominateEnemySpecialPower::DominateEnemySpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialAbilityUpdate( thing, moduleData )
{
}
