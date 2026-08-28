// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the dynamic-shroud update constructor to clean C++.

class Thing;
class ModuleData;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
	float getShroudClearingRange() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unreconstructed_00[0x3C];
	unsigned int m_frame;
	unsigned int getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}
	virtual ~UpdateModule() {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x08];
	unsigned int m_shrinkDelay;
	unsigned int m_shrinkTime;
	unsigned int m_growDelay;
	unsigned int m_growTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	DynamicShroudClearingRangeUpdate(Thing *, const ModuleData *);
	virtual ~DynamicShroudClearingRangeUpdate();

private:
	int m_state;
	int m_stateCountDown;
	int m_totalFrames;
	unsigned int m_growStartDeadline;
	unsigned int m_sustainDeadline;
	unsigned int m_shrinkStartDeadline;
	unsigned int m_doneForeverFrame;
	unsigned int m_changeIntervalCountdown;
	unsigned char m_decalsCreated;
	unsigned char m_pad_41[3];
	float m_visionChangePerInterval;
	float m_nativeClearingRange;
	float m_currentClearingRange;
	RadiusDecal m_gridDecal[30];
};

template <class T>
static const T &bfmeMax(const T &left, const T &right)
{
	return right < left ? left : right;
}

// ??0DynamicShroudClearingRangeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DynamicShroudClearingRangeUpdate::DynamicShroudClearingRangeUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const DynamicShroudClearingRangeUpdateModuleData *md =
		(const DynamicShroudClearingRangeUpdateModuleData *)moduleData;
	m_changeIntervalCountdown = 0;
	m_visionChangePerInterval = 0.0f;
	m_stateCountDown = md->m_shrinkDelay + md->m_shrinkTime;
	m_totalFrames = bfmeMax(1, m_stateCountDown);
	m_shrinkStartDeadline = m_stateCountDown - md->m_shrinkDelay;
	m_growStartDeadline = m_stateCountDown - md->m_growDelay;
	m_sustainDeadline = m_growStartDeadline - md->m_growTime;
	m_doneForeverFrame = TheGameLogic->getFrame() + m_stateCountDown;
	m_decalsCreated = 0;
	m_nativeClearingRange = 200.0f;
	m_currentClearingRange = 0.0f;
	m_state = 0;

	Object *object = getObject();
	if (!object)
		return;
	Player *controller = object->getControllingPlayer();
	if (!controller)
		return;
	m_nativeClearingRange = object->getShroudClearingRange();

	for (int decal = 0; decal < 30; ++decal)
		m_gridDecal[decal].clear();
}
