// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TransportContain module ctor.
//
// Eleven vtbls; only +0xD4 is written twice, so that interface base alone is
// non-novtable. Retail stores that vtbl before materialising the zero used for
// the three members behind it, so the vtbl and the fields are split across two
// subobjects -- a four-byte polymorphic base then a plain field base.

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

class __declspec(novtable) TransportContainIface1
{
public:
	virtual void transportContainIface1Anchor();
};

class __declspec(novtable) TransportContainIface2
{
public:
	virtual void transportContainIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) TransportContainIface3
{
public:
	virtual void transportContainIface3Anchor();
};

class __declspec(novtable) TransportContainIface4
{
public:
	virtual void transportContainIface4Anchor();
};

class __declspec(novtable) TransportContainIface5
{
public:
	virtual void transportContainIface5Anchor();
};

class __declspec(novtable) TransportContainIface6
{
public:
	virtual void transportContainIface6Anchor();
};

class __declspec(novtable) TransportContainIface7
{
public:
	virtual void transportContainIface7Anchor();
};

class __declspec(novtable) TransportContainIface8
{
public:
	virtual void transportContainIface8Anchor();

	unsigned char m_unreconstructed_38[0x9C];	///< retail this+0x38 .. +0xD4
};

class TransportContainIface9
{
public:
	virtual void transportContainIface9Anchor();
};

// Not polymorphic: keeps the +0xD4 vtbl write ahead of the zero it precedes.
class TransportContainFields
{
public:
	TransportContainFields()
	{
		m_d8 = 0;
		m_dc = 0;
		m_e0 = false;
	}

	unsigned int m_d8;							///< retail this+0xD8
	unsigned int m_dc;
	bool m_e0;
};

class TransportContainBase : public BehaviorModule
{
public:
	TransportContainBase(Thing *thing, const ModuleData *moduleData);
};

class TransportContain : public TransportContainBase,
	public TransportContainIface1,
	public TransportContainIface2,
	public TransportContainIface3,
	public TransportContainIface4,
	public TransportContainIface5,
	public TransportContainIface6,
	public TransportContainIface7,
	public TransportContainIface8,
	public TransportContainIface9,
	public TransportContainFields
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
};

// ??0TransportContain@@QAE@PAVThing@@PBVModuleData@@@Z
TransportContain::TransportContain(Thing *thing, const ModuleData *moduleData)
	: TransportContainBase(thing, moduleData)
{
}
