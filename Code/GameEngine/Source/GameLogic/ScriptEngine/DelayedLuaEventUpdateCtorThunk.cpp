// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DelayedLuaEventUpdate retail constructor expressed as C++.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_moduleData;
	Object *m_object;
};

class DelayedLuaEventIface1 { public: virtual void slot(); };
class DelayedLuaEventIface2 { public: virtual void slot(); };

class UpdateModule : public PB_DeepBase, public DelayedLuaEventIface1,
	public DelayedLuaEventIface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class Gen_dtor_000edca0
{
public:
	Gen_dtor_000edca0();
	virtual ~Gen_dtor_000edca0();

private:
	unsigned char m_storage[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *, const ModuleData *);

private:
	unsigned int m_f20;
	Gen_dtor_000edca0 m_event;
	unsigned int m_f70;
	bool m_f74;
	bool m_f75;
};

// ??0DelayedLuaEventUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DelayedLuaEventUpdate::DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
	m_f20 = 0;
	m_f70 = 0;
	m_f74 = false;
	m_f75 = false;
}
