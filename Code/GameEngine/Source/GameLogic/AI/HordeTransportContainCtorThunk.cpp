// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HordeTransportContain module ctor.
//
// Ten vtbls at +0/+0xC/+0x10/+0x20..+0x34/+0xD4, each written once, so every
// interface base is novtable. The two stores after the vtbl group are the
// derived body: they use immediates rather than a shared register, so there is
// nothing for MSVC to group them with above the vtbls.

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

class __declspec(novtable) HordeTransportContainIface1
{
public:
	virtual void hordeTransportIface1Anchor();
};

class __declspec(novtable) HordeTransportContainIface2
{
public:
	virtual void hordeTransportIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) HordeTransportContainIface3
{
public:
	virtual void hordeTransportIface3Anchor();
};

class __declspec(novtable) HordeTransportContainIface4
{
public:
	virtual void hordeTransportIface4Anchor();
};

class __declspec(novtable) HordeTransportContainIface5
{
public:
	virtual void hordeTransportIface5Anchor();
};

class __declspec(novtable) HordeTransportContainIface6
{
public:
	virtual void hordeTransportIface6Anchor();
};

class __declspec(novtable) HordeTransportContainIface7
{
public:
	virtual void hordeTransportIface7Anchor();
};

class __declspec(novtable) HordeTransportContainIface8
{
public:
	virtual void hordeTransportIface8Anchor();

	unsigned char m_unreconstructed_38[0x9C];	///< retail this+0x38 .. +0xD4
};

class __declspec(novtable) HordeTransportContainIface9
{
public:
	virtual void hordeTransportIface9Anchor();
};

class HordeTransportContainBase : public BehaviorModule
{
public:
	HordeTransportContainBase(Thing *thing, const ModuleData *moduleData);
};

class HordeTransportContain : public HordeTransportContainBase,
	public HordeTransportContainIface1,
	public HordeTransportContainIface2,
	public HordeTransportContainIface3,
	public HordeTransportContainIface4,
	public HordeTransportContainIface5,
	public HordeTransportContainIface6,
	public HordeTransportContainIface7,
	public HordeTransportContainIface8,
	public HordeTransportContainIface9
{
public:
	HordeTransportContain(Thing *thing, const ModuleData *moduleData);

protected:
	unsigned char m_unreconstructed_d8[0xC];	///< retail this+0xD8 .. +0xE4
	int m_e4;									///< retail this+0xE4
	bool m_e8;									///< retail this+0xE8
};

// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z
HordeTransportContain::HordeTransportContain(Thing *thing, const ModuleData *moduleData)
	: HordeTransportContainBase(thing, moduleData)
{
	m_e8 = false;
	m_e4 = -1000;
}
