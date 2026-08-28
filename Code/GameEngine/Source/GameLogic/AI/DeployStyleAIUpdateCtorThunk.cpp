// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DeployStyleAIUpdate module ctor.
//
// AnimalAIUpdate's base (ILT 0x000292A3) and five novtable interface bases. The
// object at +0x340 is a member rather than a base: retail loads its address
// before the vtbl writes but calls its constructor after them, which is where
// member initialisation runs.
//
// The thirteen zero stores that follow are in retail's order, which is neither
// declaration nor address order. They sit behind a call, so they do not float
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

class __declspec(novtable) DeployStyleAIUpdateIface1
{
public:
	virtual void deployStyleIface1Anchor();
};

class __declspec(novtable) DeployStyleAIUpdateIface2
{
public:
	virtual void deployStyleIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) DeployStyleAIUpdateIface3
{
public:
	virtual void deployStyleIface3Anchor();
};

class __declspec(novtable) DeployStyleAIUpdateIface4
{
public:
	virtual void deployStyleIface4Anchor();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class DeployStyleAIUpdateMember
{
public:
	DeployStyleAIUpdateMember();				///< ILT 0x0001A9B0

	unsigned char m_unreconstructed_00[0xA0];	///< retail this+0x340 .. +0x3E0
};

class DeployStyleAIUpdateBase : public BehaviorModule
{
public:
	DeployStyleAIUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class DeployStyleAIUpdate : public DeployStyleAIUpdateBase,
	public DeployStyleAIUpdateIface1,
	public DeployStyleAIUpdateIface2,
	public DeployStyleAIUpdateIface3,
	public DeployStyleAIUpdateIface4
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	DeployStyleAIUpdateMember m_340;			///< retail this+0x340

	bool m_3e0;
	unsigned int m_3e4;
	unsigned int m_3e8;
	unsigned int m_3ec;
	unsigned int m_3f0;
	unsigned int m_3f4;
	unsigned int m_3f8;
	unsigned int m_3fc;
	bool m_400;
	bool m_401;
	bool m_402;
	bool m_403;
	bool m_404;
};

// ??0DeployStyleAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DeployStyleAIUpdate::DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData)
	: DeployStyleAIUpdateBase(thing, moduleData)
{
	m_3e0 = false;
	m_3e4 = 0;
	m_3e8 = 0;
	m_3ec = 0;
	m_400 = false;
	m_404 = false;
	m_403 = false;
	m_401 = false;
	m_3f0 = 0;
	m_402 = false;
	m_3f4 = 0;
	m_3f8 = 0;
	m_3fc = 0;
}
