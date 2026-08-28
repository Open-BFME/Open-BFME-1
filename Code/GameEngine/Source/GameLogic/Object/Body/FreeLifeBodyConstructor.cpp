// cl: /DNDEBUG /MD /EHsc

// FreeLifeBody's constructor, retail 0x00213390.
//
// The base is RespawnBody, not BodyModule: the call goes to 0x00214650, which
// the ledger already carries under that name. The three module vftable pointers
// still land at +0x00, +0x0C and +0x10, so RespawnBody adds no interface of its
// own - what it adds is state, running to +0xE0 where this class's two flags sit.
//
// Three of the five members are copied out of the module data, which the base
// left at this+0x04. Retail loads that pointer before the vftable stores and
// dereferences it after. The store order is what says which members are in the
// member-init list and which are assigned in the body: an init list runs in
// declaration order, so +0xE0 and +0xE4 coming last means they are statements.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;		// +0x04
	unsigned char m_unmodelled_08[4];
};

// Only the three fields this constructor reads.
struct FreeLifeBodyModuleData
{
	unsigned char m_unmodelled_00[0x64];
	int m_unmodelled_64;				// +0x64
	int m_unmodelled_68;				// +0x68
	bool m_unmodelled_6C;				// +0x6C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class RespawnBody : public BehaviorModule,
	public BodyModuleInterface,
	public ModuleInterface
{
public:
	RespawnBody( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_unmodelled_14[ 0xE0 - 0x14 ];
};

class FreeLifeBody : public RespawnBody
{
public:
	FreeLifeBody( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_E0;			// +0xE0
	int m_unmodelled_E4;			// +0xE4
	bool m_unmodelled_E8;			// +0xE8
	int m_unmodelled_EC;			// +0xEC
	int m_unmodelled_F0;			// +0xF0
};

FreeLifeBody::FreeLifeBody( Thing *thing, const ModuleData *moduleData )
	: RespawnBody( thing, moduleData ),
	  m_unmodelled_E8( false ),
	  m_unmodelled_EC( -1 ),
	  m_unmodelled_F0( ((const FreeLifeBodyModuleData *)getModuleData())->m_unmodelled_68 )
{
	// Assigned in the body, not the member-init list. Retail writes these two
	// AFTER the three above, and an init list runs in declaration order - which
	// would put +0xE0 and +0xE4 first, since that is where they sit.
	m_unmodelled_E0 = ((const FreeLifeBodyModuleData *)getModuleData())->m_unmodelled_6C;
	m_unmodelled_E4 = ((const FreeLifeBodyModuleData *)getModuleData())->m_unmodelled_64;
}
