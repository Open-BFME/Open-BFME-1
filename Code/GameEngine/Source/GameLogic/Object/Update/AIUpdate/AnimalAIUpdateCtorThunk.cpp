// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AnimalAIUpdate module ctor.
//
// Six vtbls at +0/+0xC/+0x10/+0x20/+0x24/+0x340. Only +0x340 is written twice,
// so that interface base alone is non-novtable, and the six members it zeroes
// sit between the two writes -- base-subobject initialisers, leaving the derived
// body empty.
//
// Retail zeroes them 0x344, 0x354, 0x350, 0x34C, 0x348, 0x355, which is neither
// declaration nor address order, so they are written as statements in that
// base's constructor body where the order is explicit.

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

class __declspec(novtable) AnimalAIUpdateIface1
{
public:
	virtual void animalAIIface1Anchor();
};

class __declspec(novtable) AnimalAIUpdateIface2
{
public:
	virtual void animalAIIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) AnimalAIUpdateIface3
{
public:
	virtual void animalAIIface3Anchor();
};

class __declspec(novtable) AnimalAIUpdateIface4
{
public:
	virtual void animalAIIface4Anchor();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class AnimalAIUpdateIface5
{
public:
	virtual void animalAIIface5Anchor();
};

// Not polymorphic: retail stores the +0x340 vtbl before materialising the zero,
// so the vtbl write and the member zeroing belong to different subobjects.
class AnimalAIUpdateFields
{
public:
	AnimalAIUpdateFields()
	{
		m_344 = 0;
		m_354 = false;
		m_350 = 0;
		m_34c = 0;
		m_348 = 0;
		m_355 = false;
	}

	unsigned int m_344;							///< retail this+0x344
	unsigned int m_348;
	unsigned int m_34c;
	unsigned int m_350;
	bool m_354;
	bool m_355;
};

class AnimalAIUpdateBase : public BehaviorModule
{
public:
	AnimalAIUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class AnimalAIUpdate : public AnimalAIUpdateBase,
	public AnimalAIUpdateIface1,
	public AnimalAIUpdateIface2,
	public AnimalAIUpdateIface3,
	public AnimalAIUpdateIface4,
	public AnimalAIUpdateIface5,
	public AnimalAIUpdateFields
{
public:
	AnimalAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0AnimalAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AnimalAIUpdate::AnimalAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AnimalAIUpdateBase(thing, moduleData)
{
}
