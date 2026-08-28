// cl: /DNDEBUG /MD /EHsc

// AODCrushCollide's constructor, retail 0x00215C50. Three levels of inline
// constructor, which is what the three rounds of stores are:
//
//   BehaviorModule's is out of line and sets +0x00.
//   CollideModule's is inline: the two interface pointers at +0x0C and +0x10,
//   then its own three fields at +0x14, +0x18 and +0x1C - the last two -1.
//   CrushCollide's is inline: the interface pointer it adds at +0x20, then its
//   three fields at +0x24, +0x28 and +0x2C.
//   AODCrushCollide itself adds nothing but overwrites all four pointers.
//
// Declaring any of the middle constructors without a body collapses its round
// and loses the fields with it. Two levels is past what MSVC inlines on its own
// - it emits a call to CrushCollide's instead - so both carry __forceinline.

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
	__forceinline CollideModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData ),
		  m_unmodelled_14( 0 ),
		  m_unmodelled_18( -1 ),
		  m_unmodelled_1C( -1 )
	{
	}

private:
	int m_unmodelled_14;					// +0x14
	int m_unmodelled_18;					// +0x18
	int m_unmodelled_1C;					// +0x1C
};

class CrushCollideInterface
{
public:
	virtual void crushCollideInterfaceAnchor();
};

class CrushCollide : public CollideModule, public CrushCollideInterface
{
public:
	__forceinline CrushCollide( Thing *thing, const ModuleData *moduleData )
		: CollideModule( thing, moduleData ),
		  m_unmodelled_24( 0 ),
		  m_unmodelled_28( 0 ),
		  m_unmodelled_2C( false )
	{
	}

private:
	int m_unmodelled_24;					// +0x24
	int m_unmodelled_28;					// +0x28
	bool m_unmodelled_2C;					// +0x2C
};

class AODCrushCollide : public CrushCollide
{
public:
	AODCrushCollide( Thing *thing, const ModuleData *moduleData );
};

AODCrushCollide::AODCrushCollide( Thing *thing, const ModuleData *moduleData )
	: CrushCollide( thing, moduleData )
{
}
