// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleFactory's create proc 0x001142A0 allocates 0x3C and
// reaches this body through ILT 0x00003B5C, which identifies
// GettingBuiltBehavior.
//
// Two rounds of vftable stores: the UpdateModule base is inline, so its own
// +0x0C/+0x10 stores and its three member inits come first, then the fourth
// interface base stores +0x20, then the most-derived class overwrites all
// four slots.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class GBB_DeepBase
{
public:
	GBB_DeepBase(Thing *, const ModuleData *);
	virtual ~GBB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GBB_Iface1 { public: virtual void slot(); };
class GBB_Iface2 { public: virtual void slot(); };

class GBB_UpdateModule : public GBB_DeepBase, public GBB_Iface1, public GBB_Iface2
{
public:
	GBB_UpdateModule(Thing *thing, const ModuleData *moduleData)
		: GBB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject(void) const { return m_object; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class GBB_Iface3 { public: virtual void slot(); };

class GettingBuiltBehavior : public GBB_UpdateModule, public GBB_Iface3
{
public:
	GettingBuiltBehavior(Thing *, const ModuleData *);

private:
	int m_x24;
	unsigned int m_x28;
	unsigned int m_x2c;
	bool m_x30;
	bool m_x31;
	bool m_x32;
	bool m_x33;
	bool m_x34;
	bool m_x35;
	bool m_x36;
	unsigned int m_x38;
};

// ??0GettingBuiltBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
GettingBuiltBehavior::GettingBuiltBehavior(
	Thing *thing, const ModuleData *moduleData)
	: GBB_UpdateModule(thing, moduleData)
{
	m_x24 = 1;
	m_x2c = 0;
	m_x34 = false;
	m_x35 = false;
	m_x36 = false;
	m_x38 = 0;
	m_x30 = false;
	m_x28 = 0;
	m_x31 = false;
	m_x32 = false;
	m_x33 = false;
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
