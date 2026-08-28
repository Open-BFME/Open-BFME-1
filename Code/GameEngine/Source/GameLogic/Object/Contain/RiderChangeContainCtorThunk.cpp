// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RiderChangeContain module ctor.
//
// Ten vtbls at +0/+0xC/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xD4, each
// written once, so every interface base is novtable. The four members zeroed at
// +0x100..+0x10C land before the vtbl group, which makes them initialisers on the
// last base rather than body statements, and the derived body is empty.

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

class __declspec(novtable) RiderChangeContainIface1
{
public:
	virtual void riderChangeIface1Anchor();
};

class __declspec(novtable) RiderChangeContainIface2
{
public:
	virtual void riderChangeIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) RiderChangeContainIface3
{
public:
	virtual void riderChangeIface3Anchor();
};

class __declspec(novtable) RiderChangeContainIface4
{
public:
	virtual void riderChangeIface4Anchor();
};

class __declspec(novtable) RiderChangeContainIface5
{
public:
	virtual void riderChangeIface5Anchor();
};

class __declspec(novtable) RiderChangeContainIface6
{
public:
	virtual void riderChangeIface6Anchor();
};

class __declspec(novtable) RiderChangeContainIface7
{
public:
	virtual void riderChangeIface7Anchor();
};

class __declspec(novtable) RiderChangeContainIface8
{
public:
	virtual void riderChangeIface8Anchor();

	unsigned char m_unreconstructed_38[0x9C];	///< retail this+0x38 .. +0xD4
};

class __declspec(novtable) RiderChangeContainIface9
{
public:
	RiderChangeContainIface9() { m_100 = 0; m_104 = 0; m_10c = false; m_108 = 0; }
	virtual void riderChangeIface9Anchor();

	unsigned char m_unreconstructed_d8[0x28];	///< retail this+0xD8 .. +0x100
	unsigned int m_100;							///< retail this+0x100
	unsigned int m_104;
	unsigned int m_108;
	bool m_10c;
};

class RiderChangeContainBase : public BehaviorModule
{
public:
	RiderChangeContainBase(Thing *thing, const ModuleData *moduleData);
};

class RiderChangeContain : public RiderChangeContainBase,
	public RiderChangeContainIface1,
	public RiderChangeContainIface2,
	public RiderChangeContainIface3,
	public RiderChangeContainIface4,
	public RiderChangeContainIface5,
	public RiderChangeContainIface6,
	public RiderChangeContainIface7,
	public RiderChangeContainIface8,
	public RiderChangeContainIface9
{
public:
	RiderChangeContain(Thing *thing, const ModuleData *moduleData);
};

// ??0RiderChangeContain@@QAE@PAVThing@@PBVModuleData@@@Z
RiderChangeContain::RiderChangeContain(Thing *thing, const ModuleData *moduleData)
	: RiderChangeContainBase(thing, moduleData)
{
}
