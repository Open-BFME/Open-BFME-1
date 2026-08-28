// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: PartTheHeavensUpdate constructor.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	Object *m_object;
	const ModuleData *m_moduleData;
};

class PartTheHeavensUpdateIface1
{
public:
	virtual void slot();
};

class PartTheHeavensUpdateIface2
{
public:
	virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase,
	public PartTheHeavensUpdateIface1,
	public PartTheHeavensUpdateIface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
	Object *getObject() const { return m_object; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *, const ModuleData *);
	virtual ~PartTheHeavensUpdate();

private:
	unsigned int m_nextUpdateFrame;
	void *m_pointee;
};

// ??0PartTheHeavensUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
PartTheHeavensUpdate::PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_nextUpdateFrame(0x3fffffff), m_pointee(0)
{
	if (getObject())
		m_nextUpdateFrame = TheGameLogic->m_frame;
}
