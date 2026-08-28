// cl: /DNDEBUG /MD /EHsc

// DelayedDeathBody's constructor, retail 0x00212810.
//
// The base is RespawnBody, not BodyModule: the call goes to 0x00214650, which
// the ledger already carries under that name. The three module vftable pointers
// still land at +0x00, +0x0C and +0x10, so RespawnBody adds no interface of its
// own - what it adds is state, running to +0xE0 where this class's two flags sit.
//
// Retail sets both flags before the vftable stores. That is scheduling, not
// order of construction: `xor al,al' feeds both byte stores and MSVC hoists it
// above the three independent dword stores.

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

class DelayedDeathBody : public RespawnBody
{
public:
	DelayedDeathBody( Thing *thing, const ModuleData *moduleData );

private:
	bool m_unmodelled_E0;			// +0xE0
	bool m_unmodelled_E1;			// +0xE1
};

DelayedDeathBody::DelayedDeathBody( Thing *thing, const ModuleData *moduleData )
	: RespawnBody( thing, moduleData ), m_unmodelled_E0( false ), m_unmodelled_E1( false )
{
}
