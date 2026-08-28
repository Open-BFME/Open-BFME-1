// cl: /DNDEBUG /MD /EHsc

// CastleMemberBehavior's two-argument constructor, retail 0x0036CEA0.
//
// The two-round shape of the module constructor family: the BehaviorModule base
// constructor is out of line and writes +0x00, the middle module's constructor
// is inline here and writes the two interface pointers it adds at +0x0C and
// +0x10 followed by its own members, and only then does the leaf overwrite all
// three vftable slots.
//
// The member at +0x20 is the odd one out. It is not in the middle
// constructor's initialiser list - the run of zeroes skips straight from +0x1C
// to +0x24 - and the leaf sets it to one after its vftable stores, so it is
// written in the leaf's body rather than in either initialiser list.
//
// The name was on 0x0036CDD0, which is the no-argument constructor: fifty-eight
// bytes that fill members with 0xFFFFFFFE and never touch a Thing. This body
// takes two arguments and forwards both.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// Known only by shape: it adds the two interface pointers at +0x0C and +0x10 and
// the members from +0x14 to +0x25.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule,
	public UpdateModuleInterface,
	public ModuleInterface
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData ),
			m_14( 0 ),
			m_18( 0 ),
			m_1c( 0 ),
			m_24( false ),
			m_25( false )
	{
	}

protected:
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	bool m_24;
	bool m_25;
};

class CastleMemberBehavior : public UpdateModule
{
public:
	CastleMemberBehavior( Thing *thing, const ModuleData *moduleData );
};

// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
CastleMemberBehavior::CastleMemberBehavior( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_20 = 1;
}
