// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: OathbreakersFadeAwayBehavior module constructor.

class Thing;
class ModuleData;
class Object;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class OathbreakersFadeAwayBehaviorIface1
{
public:
	virtual void slot();
};

class OathbreakersFadeAwayBehaviorIface2
{
public:
	virtual void slot();
};

class UpdateModule : public PB_DeepBase,
	public OathbreakersFadeAwayBehaviorIface1,
	public OathbreakersFadeAwayBehaviorIface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	OathbreakersFadeAwayBehavior(Thing *, const ModuleData *);
	virtual ~OathbreakersFadeAwayBehavior();

private:
	bool m_f20;
	float m_f24;
};

// ??0OathbreakersFadeAwayBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
OathbreakersFadeAwayBehavior::OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_f20(false), m_f24(1.0f)
{
}
