// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: EntEnragedUpdate constructor with the retail module layout.

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
private:
	unsigned char m_gap00[8];
public:
	unsigned int m_initialValue;
};

extern "C" char EntEnragedInitialValueData;
int __cdecl entEnragedInitialValue(int, unsigned int, const void *, int);

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void slot(); };
class UpdateModuleInterface { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: PB_DeepBase(thing, moduleData), m_field14(0),
		  m_field18(-1), m_field1C(-1) {}

private:
	unsigned int m_field14;
	int m_field18;
	int m_field1C;
};

class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);
	virtual ~EntEnragedUpdate();

private:
	int m_value;
	unsigned int m_sleepTime;
	unsigned int m_field28;
	bool m_field2C;
	bool m_field2D;
	bool m_field2E;
	bool m_field2F;
	bool m_field30;
};

// ??0EntEnragedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
EntEnragedUpdate::EntEnragedUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const ModuleData *data = m_moduleData;
	m_value = 0;
	m_value += entEnragedInitialValue(0, data->m_initialValue,
		&EntEnragedInitialValueData, 0x4c);
	m_field2C = false;
	m_field2E = false;
	m_field2F = false;
	m_field2D = false;
	m_field28 = 0;
	m_field30 = false;
	m_sleepTime = 0x3fffffff;
}
