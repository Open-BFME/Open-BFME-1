// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HordeAIUpdate module ctor.
//
// Same base and layout as AnimalAIUpdate (base ctor ILT 0x000292A3, six vtbls
// with only +0x340 written twice), but this one initialises no members at all:
// the whole body is the wake call, so the interface base at +0x340 needs no
// field split.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
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

class __declspec(novtable) HordeAIUpdateIface1
{
public:
	virtual void hordeAIIface1Anchor();
};

class __declspec(novtable) HordeAIUpdateIface2
{
public:
	virtual void hordeAIIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) HordeAIUpdateIface3
{
public:
	virtual void hordeAIIface3Anchor();
};

class __declspec(novtable) HordeAIUpdateIface4
{
public:
	virtual void hordeAIIface4Anchor();

	unsigned char m_unreconstructed_28[0x318];	///< retail this+0x28 .. +0x340
};

class HordeAIUpdateIface5
{
public:
	virtual void hordeAIIface5Anchor();
};

class HordeAIUpdateBase : public BehaviorModule
{
public:
	HordeAIUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class HordeAIUpdate : public HordeAIUpdateBase,
	public HordeAIUpdateIface1,
	public HordeAIUpdateIface2,
	public HordeAIUpdateIface3,
	public HordeAIUpdateIface4,
	public HordeAIUpdateIface5
{
public:
	HordeAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	Object *getObject(void) const { return m_object; }
};

// ??0HordeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
HordeAIUpdate::HordeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: HordeAIUpdateBase(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
