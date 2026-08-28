// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SpecialDisguiseUpdate module ctor.
//
// Five vtbls at +0/+0xC/+0x10/+0x20/+0xE8. Only the one at +0xE8 is written
// twice, so that interface base alone is non-novtable, and the two members it
// zeroes at +0xEC/+0xF0 land between the two writes -- base-subobject
// initialisers, which is why the derived body is empty.

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

class __declspec(novtable) SpecialDisguiseUpdateIface1
{
public:
	virtual void specialDisguiseIface1Anchor();
};

class __declspec(novtable) SpecialDisguiseUpdateIface2
{
public:
	virtual void specialDisguiseIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) SpecialDisguiseUpdateIface3
{
public:
	virtual void specialDisguiseIface3Anchor();

	unsigned char m_unreconstructed_24[0xC4];	///< retail this+0x24 .. +0xE8
};

class SpecialDisguiseUpdateIface4
{
public:
	SpecialDisguiseUpdateIface4() : m_ec(0), m_f0(false) {}
	virtual void specialDisguiseIface4Anchor();

	unsigned int m_ec;							///< retail this+0xEC
	bool m_f0;									///< retail this+0xF0
};

class SpecialDisguiseUpdateBase : public BehaviorModule
{
public:
	SpecialDisguiseUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class SpecialDisguiseUpdate : public SpecialDisguiseUpdateBase,
	public SpecialDisguiseUpdateIface1,
	public SpecialDisguiseUpdateIface2,
	public SpecialDisguiseUpdateIface3,
	public SpecialDisguiseUpdateIface4
{
public:
	SpecialDisguiseUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0SpecialDisguiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpecialDisguiseUpdate::SpecialDisguiseUpdate(Thing *thing, const ModuleData *moduleData)
	: SpecialDisguiseUpdateBase(thing, moduleData)
{
}
