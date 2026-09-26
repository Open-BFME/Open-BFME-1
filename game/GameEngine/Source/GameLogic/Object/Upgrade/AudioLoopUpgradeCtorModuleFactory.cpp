// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleFactory's create proc 0x0011E0B0 allocates 0x30 and
// reaches this body, which identifies AudioLoopUpgrade.
//
// Four vftable slots: the UpdateModule base is inline (+0x0C/+0x10 and the
// three member inits), the UpgradeMux base at +0x20 is a real call to the
// independently matched constructor ILT 0x0003D24E, and the interface base at
// +0x28 is inline. The most-derived class then overwrites all four.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class ALU_DeepBase
{
public:
	ALU_DeepBase(Thing *, const ModuleData *);
	virtual ~ALU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class ALU_Iface1 { public: virtual void slot(); };
class ALU_Iface2 { public: virtual void slot(); };

class ALU_UpdateModule : public ALU_DeepBase, public ALU_Iface1, public ALU_Iface2
{
public:
	ALU_UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ALU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject(void) const { return m_object; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ALU_UpgradeMux
{
public:
	ALU_UpgradeMux();
	virtual void slot();

private:
	bool m_upgradeExecuted;
};

class ALU_Iface4 { public: virtual void slot(); };

class AudioLoopUpgrade : public ALU_UpdateModule,
	public ALU_UpgradeMux,
	public ALU_Iface4
{
public:
	AudioLoopUpgrade(Thing *, const ModuleData *);

private:
	int m_x2c;
};

// ??0AudioLoopUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
AudioLoopUpgrade::AudioLoopUpgrade(Thing *thing, const ModuleData *moduleData)
	: ALU_UpdateModule(thing, moduleData), ALU_UpgradeMux()
{
	m_x2c = 1;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
