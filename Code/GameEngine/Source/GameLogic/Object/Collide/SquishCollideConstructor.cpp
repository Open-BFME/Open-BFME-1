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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData );

	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModule : public BehaviorModule,
	public CollideModuleInterface,
	public ModuleInterface
{
public:
	CollideModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData )
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h
class SquishCollide : public CollideModule
{
public:
	SquishCollide( Thing *thing, const ModuleData *moduleData );
};

SquishCollide::SquishCollide( Thing *thing, const ModuleData *moduleData )
	: CollideModule( thing, moduleData )
{
}
