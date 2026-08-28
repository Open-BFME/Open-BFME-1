// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HordeWorkerAIUpdate module ctor. ModuleFactory's create proc
// 0x0011A720 allocates 0x354 and reaches this body.
//
// Same six-vtable layout as HordeAIUpdate but the base ctor is ILT 0x000254A0
// and +0x340 is written once, so the interface base there is novtable and the
// four fields above it belong to the most-derived class.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FIVE = 5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class __declspec(novtable) HWAI_Iface1
{
public:
	virtual void hordeWorkerAIIface1Anchor();
};

class __declspec(novtable) HWAI_Iface2
{
public:
	virtual void hordeWorkerAIIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) HWAI_Iface3
{
public:
	virtual void hordeWorkerAIIface3Anchor();
};

class __declspec(novtable) HWAI_Iface4
{
public:
	virtual void hordeWorkerAIIface4Anchor();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class __declspec(novtable) HWAI_Iface5
{
public:
	virtual void hordeWorkerAIIface5Anchor();
};

class HordeWorkerAIUpdateBase : public BehaviorModule
{
public:
	HordeWorkerAIUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class HordeWorkerAIUpdate : public HordeWorkerAIUpdateBase,
	public HWAI_Iface1,
	public HWAI_Iface2,
	public HWAI_Iface3,
	public HWAI_Iface4,
	public HWAI_Iface5
{
public:
	HordeWorkerAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	Object *getObject(void) const { return m_object; }

private:
	unsigned int m_344;
	unsigned int m_348;
	unsigned int m_34c;
	bool m_350;
};

// ??0HordeWorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HordeWorkerAIUpdate::HordeWorkerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: HordeWorkerAIUpdateBase(thing, moduleData)
{
	m_344 = 0;
	m_348 = 0;
	m_34c = 0;
	m_350 = false;
	setWakeFrame(getObject(), UPDATE_SLEEP_FIVE);
}
