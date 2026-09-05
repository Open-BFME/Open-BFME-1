// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
class Thing;
class ModuleData;
class Object;

// GateOpenAndCloseBehavior reads the current simulation frame off TheGameLogic;
// only the +0x3c slot (GameLogic::getFrame's m_frame, inlined) is recovered here.
struct GameLogicFrameView
{
	unsigned char m_pad00[0x3c];
	int m_frame;
};
extern GameLogicFrameView *TheGameLogic; // retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual int update() = 0;
	virtual UnsignedInt getDisabledTypesToProcess() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
	}
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1),
		  m_updateState(-1)
	{
	}
	virtual ~UpdateModule() {}
protected:
	UnsignedInt m_nextCallFrameAndPhase;
	int m_indexInLogic;
	UnsignedInt m_updateState;
};

// Address-derived placeholder: a second, otherwise unidentified interface that
// GateOpenAndCloseBehavior implements ahead of UpdateModule (its vtable pointer
// sits at object offset 0, one slot before UpdateModule's own subobject).
class GateOpenAndCloseBehaviorFirstBase
{
public:
	virtual void slot();
};

struct GateOpenAndCloseBehaviorModuleDataView
{
	unsigned char m_pad00[8];
	unsigned char m_startsClosed;
	unsigned char m_pad09[3];
	UnsignedInt m_openCloseFrames;
};

class GateOpenAndCloseBehavior : public GateOpenAndCloseBehaviorFirstBase, public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GateOpenAndCloseBehavior() {}
	virtual void slot();
	virtual void getBehaviorModuleInterface();
	virtual int update();
	virtual UnsignedInt getDisabledTypesToProcess() const;

private:
	int m_field24;
	int m_field28;
	int m_field2c;
	bool m_field30;
	float m_field34;
	float m_field38;
	int m_field3c;
	int m_field40;
	int m_field44;
	unsigned char m_field48;
};

// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
GateOpenAndCloseBehavior::GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const GateOpenAndCloseBehaviorModuleDataView *data =
		reinterpret_cast<const GateOpenAndCloseBehaviorModuleDataView *>(m_moduleData);

	m_indexInLogic = -1;
	m_updateState = -1;
	m_nextCallFrameAndPhase = 0;
	m_field40 = -1;

	m_field28 = (data->m_startsClosed == 0) ? 3 : 1;
	m_field38 = 100.0f / (float)data->m_openCloseFrames;
	m_field34 = 100.0f;
	m_field3c = TheGameLogic->m_frame;
	m_field2c = 0;
	m_field24 = 0;

	m_field44 = 1;
	m_field30 = true;
	m_field48 = 0;
}
