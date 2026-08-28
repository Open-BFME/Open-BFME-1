// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <set>
#include <vector>

class ModuleData;
class Object;
class Emotion;
class EmotionTrackerUpdateEntry;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual Object *asObject();

	unsigned char m_unknown04[0x70];
	unsigned int m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Thing *m_object;
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
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData) {}
	virtual ~BehaviorModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1),
		  m_updateState(-1) {}
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

struct Gen_t_000ef440_k4
{
	int value;
	Gen_t_000ef440_k4();
	Gen_t_000ef440_k4(const Gen_t_000ef440_k4 &other);
	~Gen_t_000ef440_k4();
	Gen_t_000ef440_k4 &operator=(const Gen_t_000ef440_k4 &other);
};

bool operator==(const Gen_t_000ef440_k4 &left, const Gen_t_000ef440_k4 &right);
bool operator<(const Gen_t_000ef440_k4 &left, const Gen_t_000ef440_k4 &right);

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_unknown00[0x0c];
	unsigned int m_distributionCount;
	unsigned char m_unknown10[0x20];
	std::vector<EmotionTrackerUpdateEntry *> m_entries;
};

class EmotionSystem
{
public:
	Emotion *createEmotion(EmotionTrackerUpdateEntry *entry, Object *object);
};

extern EmotionSystem *TheEmotionSystem;

struct EmotionTrackerStateTail
{
	EmotionTrackerStateTail()
		: m_currentEmotion(-1), m_unknownb4(-1) {}

	int m_currentEmotion;
	int m_unknowna4;
	int m_unknowna8;
	int m_unknownac;
	bool m_enabled;
	int m_unknownb4;
};

class EmotionTrackerUpdate
	: public UpdateModule,
	  public EmotionTrackerUpdateSecondaryBase
{
public:
	EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~EmotionTrackerUpdate();

private:
	bool m_active[10];
	unsigned int m_startFrame[10];
	unsigned int m_endFrame[10];
	std::vector<Emotion *> m_emotions;
	int m_unknown8c;
	unsigned int m_distributionIndex;
	std::set<Gen_t_000ef440_k4> m_emotionTypes;
	EmotionTrackerStateTail m_state;
};

EmotionTrackerUpdate::EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	  m_unknown8c(0)
{
	const EmotionTrackerUpdateModuleData *data =
		reinterpret_cast<const EmotionTrackerUpdateModuleData *>(m_moduleData);

	m_state.m_unknowna4 = 0;
	m_state.m_unknowna8 = 0;
	m_state.m_unknownac = 0;
	m_state.m_enabled = true;

	for (int i = 0; i < 10; ++i)
	{
		m_active[i] = false;
		m_startFrame[i] = 0;
		m_endFrame[i] = 0;
	}

	if (data->m_distributionCount > 0)
		m_distributionIndex = m_object->m_id % data->m_distributionCount + 1;
	else
		m_distributionIndex = 1;

	for (unsigned int i = 0; i < data->m_entries.size(); ++i)
	{
		Object *object = thing != 0 ? thing->asObject() : 0;
		Emotion *emotion = TheEmotionSystem->createEmotion(data->m_entries[i], object);
		if (emotion != 0)
			m_emotions.push_back(emotion);
	}
}
