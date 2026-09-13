// cl: /DNDEBUG /MD /EHsc
// readable body of ??0AssaultTransportAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp

// Open-BFME5: AssaultTransportAIUpdate module ctor.
//
// AnimalAIUpdate's base and layout (ILT 0x000292A3, six vtbls with only +0x340
// written twice). The body sets +0x398 to ten and then makes one no-argument
// thiscall on this.
//
// That callee is unnamed in both ledgers -- ILT 0x0002105D onto the body at
// 0x002B4320 -- so it is declared here under an address-derived shim name rather
// than a guessed one. The +0x398 store is an immediate, so it does not float
// above the vtbl group.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class __declspec(novtable) AssaultTransportAIUpdateIface1
{
public:
	virtual void assaultTransportIface1Anchor();
};

class __declspec(novtable) AssaultTransportAIUpdateIface2
{
public:
	virtual void assaultTransportIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) AssaultTransportAIUpdateIface3
{
public:
	virtual void assaultTransportIface3Anchor();
};

class __declspec(novtable) AssaultTransportAIUpdateIface4
{
public:
	virtual void assaultTransportIface4Anchor();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class AssaultTransportAIUpdateIface5
{
public:
	virtual void assaultTransportIface5Anchor();

	unsigned char m_unreconstructed_344[0x54];	///< retail this+0x344 .. +0x398
};

class AssaultTransportAIUpdateBase : public BehaviorModule
{
public:
	AssaultTransportAIUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	void call_0002105d(void);					///< unnamed body at 0x002B4320
};

class AssaultTransportAIUpdate : public AssaultTransportAIUpdateBase,
	public AssaultTransportAIUpdateIface1,
	public AssaultTransportAIUpdateIface2,
	public AssaultTransportAIUpdateIface3,
	public AssaultTransportAIUpdateIface4,
	public AssaultTransportAIUpdateIface5
{
public:
	AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	unsigned int m_398;							///< retail this+0x398
};

// ??0AssaultTransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AssaultTransportAIUpdate::AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AssaultTransportAIUpdateBase(thing, moduleData)
{
	m_398 = 10;

	call_0002105d();
}
