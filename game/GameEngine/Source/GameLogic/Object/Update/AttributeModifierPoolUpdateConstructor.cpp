// cl: /DNDEBUG /MD /EHsc

// Retail vtable stores and the module registry identify this body as
// AttributeModifierPoolUpdate, not W3DProjectileStreamDraw.

// stlport
#include <vector>

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class PB_BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class PB_UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class UpdateModule : public PB_DeepBase,
	public PB_BehaviorModuleInterface,
	public PB_UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData),
		  m_f14(0),
		  m_f18(-1),
		  m_f1c(-1)
	{
	}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);

	Object *getObject() const
	{
		return m_object;
	}

	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

struct Gen_t_001d2940_p16cd
{
	int a[4];
	Gen_t_001d2940_p16cd();
	Gen_t_001d2940_p16cd(const Gen_t_001d2940_p16cd &);
	~Gen_t_001d2940_p16cd();
	Gen_t_001d2940_p16cd &operator=(const Gen_t_001d2940_p16cd &);
};

class ZeroArray
{
public:
	void initialize()
	{
		volatile unsigned int *p = m_values;
		*p++ = 0;
		*p++ = 0;
		*p++ = 0;
		*p++ = 0;
		*p++ = 0;
		*p++ = 0;
		*p = 0;
	}

	volatile unsigned int m_values[7];
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	AttributeModifierPoolUpdate(Thing *, const ModuleData *);

private:
	_STL::vector<Gen_t_001d2940_p16cd> m_modifiers;
	volatile unsigned int m_maxFrame;
	ZeroArray m_initial;
	volatile unsigned int m_tail[7];
};

// ??0AttributeModifierPoolUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
AttributeModifierPoolUpdate::AttributeModifierPoolUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_initial.initialize();
	_STL::vector<Gen_t_001d2940_p16cd> *modifiers = &m_modifiers;
	modifiers->erase(modifiers->begin(), modifiers->end());
	m_maxFrame = UPDATE_SLEEP_FOREVER;
	m_initial.m_values[0] = 0;
	m_tail[0] = 0;
	m_initial.m_values[1] = 0;
	m_tail[1] = 0;
	m_initial.m_values[2] = 0;
	m_tail[2] = 0;
	m_initial.m_values[3] = 0;
	m_tail[3] = 0;
	m_initial.m_values[4] = 0;
	m_tail[4] = 0;
	m_initial.m_values[5] = 0;
	m_tail[5] = 0;
	m_initial.m_values[6] = 0;
	m_tail[6] = 0;
	setWakeFrame(*(Object * volatile *)((char *)this + 8),
		UPDATE_SLEEP_FOREVER);
}
