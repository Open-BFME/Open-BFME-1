// cl: /DNDEBUG /MD /EHsc

// ReflectDamage's constructor, retail 0x002167A0.
//
// Two rounds of vftable stores rather than one: the BehaviorModule base
// constructor is out of line and sets +0x00 itself, then DamageModule's own
// constructor is INLINE here and writes the two interface pointers it adds at
// +0x0C and +0x10, and only then does the most derived class overwrite all
// three. That second round is what separates this family from the *Create and
// *SpecialPower constructors, where the middle constructor is out of line and
// only one round appears.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );

	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class InlineDamageModuleInterface
{
public:
	virtual void damageModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModule : public BehaviorModule,
	public InlineDamageModuleInterface,
	public ModuleInterface
{
public:
	DamageModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData )
	{
	}
};

class ReflectDamage : public DamageModule
{
public:
	ReflectDamage( Thing *thing, const ModuleData *moduleData );
};

ReflectDamage::ReflectDamage( Thing *thing, const ModuleData *moduleData )
	: DamageModule( thing, moduleData )
{
}
