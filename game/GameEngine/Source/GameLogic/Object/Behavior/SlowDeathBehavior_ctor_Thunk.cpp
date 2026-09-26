// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SlowDeathBehavior constructor.  The module factory and original
// source establish the class identity; the module-data vectors explain BFME's
// derived has-effect flag.

class Thing;
class ModuleData;
class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data)
		: ObjectModule(thing, data), m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1), m_updateState(-1) {}
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *, unsigned int);
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class SlowDeathBehaviorInterface { public: virtual void slowDeathSlot(); };
class DieModuleInterface { public: virtual void dieSlot(); };

class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);
private:
	int m_code;
	int m_line;
};

extern const char Rva010A65BCProbabilityError[];

struct SlowDeathBehaviorModuleDataFacade
{
	unsigned char m_pad00[0x38];
	int m_probabilityModifier;
	unsigned char m_pad3c[0x40];
	void *m_fxBegin;
	void *m_fxEnd;
	unsigned char m_pad84[0x28];
	void *m_oclBegin;
	void *m_oclEnd;
	unsigned char m_padb4[0x28];
	void *m_weaponBegin;
	void *m_weaponEnd;
	unsigned char m_pade4[0x28];
	void *m_lastBegin;
	void *m_lastEnd;
};

class SlowDeathBehavior : public UpdateModule,
	public SlowDeathBehaviorInterface, public DieModuleInterface
{
public:
	SlowDeathBehavior(Thing *, const ModuleData *);
	virtual ~SlowDeathBehavior();
	virtual void slowDeathSlot();
	virtual void dieSlot();
private:
	unsigned int m_flags;
	unsigned int m_sinkFrame;
	unsigned int m_midpointFrame;
	unsigned int m_destructionFrame;
	float m_acceleratedTimeScale;
	unsigned int m_value3c;
	bool m_hasLoadedEffect;
	unsigned char m_pad41[3];
	unsigned int m_value44;
	bool m_value48;
	unsigned char m_pad49[3];
	int m_value4c;
};

// ??0SlowDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
SlowDeathBehavior::SlowDeathBehavior(Thing *thing, const ModuleData *data)
	: UpdateModule(thing, data)
{
	m_value3c = 0;
	m_flags = 0;
	m_sinkFrame = 0;
	m_midpointFrame = 0;
	m_destructionFrame = 0;
	m_hasLoadedEffect = false;
	m_value48 = false;
	m_value4c = -1;
	m_acceleratedTimeScale = 1.0f;
	m_value44 = 99999;

	const SlowDeathBehaviorModuleDataFacade *moduleData =
		(const SlowDeathBehaviorModuleDataFacade *)m_moduleData;
	if (moduleData->m_probabilityModifier < 1)
		throw INIException(3, Rva010A65BCProbabilityError);

	if (moduleData->m_fxBegin != moduleData->m_fxEnd)
		m_hasLoadedEffect = true;
	if (moduleData->m_oclBegin != moduleData->m_oclEnd)
		m_hasLoadedEffect = true;
	if (moduleData->m_weaponBegin != moduleData->m_weaponEnd)
		m_hasLoadedEffect = true;
	if (moduleData->m_lastBegin != moduleData->m_lastEnd)
		m_hasLoadedEffect = true;

	setWakeFrame(m_object, 0x3fffffff);
}
