// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CaveContain module ctor.
//
// TransportContain's base and layout (ILT 0x00036E49, eleven vtbls with only
// +0xD4 written twice). Three fields sit behind that vtbl: +0xDC and +0xE0 are
// zeroed before the most-derived vtbl group so they are initialisers on the
// field base, while the true at +0xD8 is written after it and is the derived
// body. It stores an immediate, so it stays put.

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

class __declspec(novtable) CaveContainIface1
{
public:
	virtual void caveContainIface1Anchor();
};

class __declspec(novtable) CaveContainIface2
{
public:
	virtual void caveContainIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) CaveContainIface3
{
public:
	virtual void caveContainIface3Anchor();
};

class __declspec(novtable) CaveContainIface4
{
public:
	virtual void caveContainIface4Anchor();
};

class __declspec(novtable) CaveContainIface5
{
public:
	virtual void caveContainIface5Anchor();
};

class __declspec(novtable) CaveContainIface6
{
public:
	virtual void caveContainIface6Anchor();
};

class __declspec(novtable) CaveContainIface7
{
public:
	virtual void caveContainIface7Anchor();
};

class __declspec(novtable) CaveContainIface8
{
public:
	virtual void caveContainIface8Anchor();

	unsigned char m_unreconstructed_38[0x9C];	///< retail this+0x38 .. +0xD4
};

class CaveContainIface9
{
public:
	virtual void caveContainIface9Anchor();
};

// Not polymorphic: keeps the +0xD4 vtbl write ahead of the zero it precedes.
class CaveContainFields
{
public:
	CaveContainFields()
	{
		m_dc = 0;
		m_e0 = 0;
	}

	bool m_d8;									///< retail this+0xD8
	unsigned int m_dc;
	unsigned int m_e0;
};

class CaveContainBase : public BehaviorModule
{
public:
	CaveContainBase(Thing *thing, const ModuleData *moduleData);
};

class CaveContain : public CaveContainBase,
	public CaveContainIface1,
	public CaveContainIface2,
	public CaveContainIface3,
	public CaveContainIface4,
	public CaveContainIface5,
	public CaveContainIface6,
	public CaveContainIface7,
	public CaveContainIface8,
	public CaveContainIface9,
	public CaveContainFields
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);
};

// ??0CaveContain@@QAE@PAVThing@@PBVModuleData@@@Z
CaveContain::CaveContain(Thing *thing, const ModuleData *moduleData)
	: CaveContainBase(thing, moduleData)
{
	m_d8 = true;
}
