// cl: /DNDEBUG /MD /EHsc

// SquishCollide's constructor, retail 0x00216BA0.
//
// Two rounds of vftable stores rather than one: the BehaviorModule base
// constructor is out of line and sets +0x00 itself, then CollideModule's own
// constructor is INLINE here and writes the two interface pointers it adds at
// +0x0C and +0x10, and only then does the most derived class overwrite all
// three. That second round is what separates this family from the *Create and
// *SpecialPower constructors, where the middle constructor is out of line and
// only one round appears.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );

	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// +0x0C holds BehaviorModuleInterface's own 41-slot table (0x0109C9D0) and
// +0x10 CollideModuleInterface's own six-slot one (0x010A1DE4).
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public CollideModuleInterface
{
public:
	CollideModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData )
	{
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h
class SquishCollide : public CollideModule
{
public:
	SquishCollide( Thing *thing, const ModuleData *moduleData );
};

SquishCollide::SquishCollide( Thing *thing, const ModuleData *moduleData )
	: CollideModule( thing, moduleData )
{
}
